#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <string>
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"
#include <chrono>
#include <list>
#include <vector>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


void findMatches(const Recommender& r,
    const MovieDatabase& md,
    const string& user_email,
    int num_recommendations) {
    auto start = chrono::steady_clock::now();
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
    auto stop = chrono::steady_clock::now();
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
    if (recommendations.empty()) {
        cout << "No recommendations found" << endl;
    }
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            Movie* m = md.get_movie_from_id(recommendations.at(i).movie_id);
            cout << i << ". " << m->get_title() << " ("
                << m->get_release_year() << ")\n Rating: "
                << m->get_rating() << "\n Compatibility Score: " << recommendations.at(i).compatibility_score << "\n";
        }
    }

}

// If your program is having trouble finding these files. replace the
// string literals with full path names to the files.  Also, for test
// purposes, you may want to create some small, simple user and movie
// data files to make debugging easier, so you can replace the string
// literals with the names of those smaller files.

const string USER_DATAFILE = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
    cout << "Loading student database..." << endl;
    auto startUser = chrono::steady_clock::now();
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    auto stopUser = chrono::steady_clock::now();
    cout << "User database loaded" << endl;
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stopUser - startUser).count()) << "ms" << endl;
    cout << "Loading movie database..." << endl;
    auto startMovie = chrono::steady_clock::now();
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    auto stopMovie = chrono::steady_clock::now();

    cout << "Movie database loaded" << endl;
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stopMovie - startMovie).count()) << "ms" << endl;


    while (true) {
        cout << "1. User lookup\n2. Movie lookup\n3. Recommendation generator\n9. Exit" << endl;
        cout << "Enter in a number: ";
        string choice;
        getline(cin, choice);
        if (choice == "1") {
            for (;;)
            {
                cout << "Enter user email address (or quit): ";
                string email;
                getline(cin, email);    
                if (email == "quit")
                    break;
                auto start = chrono::steady_clock::now();
                User* u = udb.get_user_from_email(email);
                auto stop = chrono::steady_clock::now();
                if (u == nullptr)
                    cout << "No user in the database has that email address." << endl;
                else
                    cout << "Found " << u->get_full_name() << endl;
                cout << "Took (*very* roughly) " << (chrono::duration_cast<chrono::microseconds>(stop - start).count()) << "ms" << endl;
            }
        }
        else if (choice == "2") {
            for (;;) {
                list<string> outputBuf;
                cout << "Enter movie attribute (or quit): ";
                string attr;
                getline(cin, attr);
                if (attr == "quit")
                    break;
                auto start = chrono::steady_clock::now();
                Movie* m1 = mdb.get_movie_from_id(attr);
                if (m1 != nullptr) {
                    outputBuf.push_back("ID: Found " + m1->get_title());
                }
                vector<Movie*> m2 = mdb.get_movies_with_actor(attr);
                for (auto movie : m2) {
                    outputBuf.push_back("Actor: Found " + movie->get_title());
                }
                vector<Movie*> m3 = mdb.get_movies_with_director(attr);
                for (auto movie : m3) {
                    outputBuf.push_back("Director: Found " + movie->get_title());
                }
                vector<Movie*> m4 = mdb.get_movies_with_genre(attr);
                for (auto movie : m4) {
                    outputBuf.push_back("Genre: Found " + movie->get_title());
                }
                auto stop = chrono::steady_clock::now();
                for (auto s : outputBuf) {
                    cout << s << endl;
                }
                cout << "Found a total of " << outputBuf.size() << " matches." << endl;
                cout << "Took (*very* roughly) " << (chrono::duration_cast<chrono::microseconds>(stop - start).count()) << "μs" << endl;
                outputBuf.clear();
            }
        }
        else if (choice == "3") {
            {
                cout << "Enter in an email: ";
                string user_email;
                getline(cin, user_email);
                cout << "Number of recommendations? ";
                int recs;
                cin >> recs;
                cin.ignore(10000, '\n');

                Recommender r(udb, mdb);
                findMatches(r, mdb, user_email, recs);
            }

        }
        else if (choice == "9") {
            return 0;
        }
        else {
            cout << "Unknown choice" << endl;
        }

    }
}

