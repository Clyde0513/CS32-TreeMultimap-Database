#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

MovieDatabase::MovieDatabase() : m_movieByDirector(), m_movieByActor(), m_movie(), m_movieByGenre(), m_movieById(){}

MovieDatabase::~MovieDatabase() {
    for (auto movie : m_movie) {
        delete movie;
    }
}

bool MovieDatabase::load(const string& filename) {

    string line;
    string movie_id = ""; string movie_name = ""; string release_year = "";
    vector<string> directors, actors, genres;
    float rating = 0; int count = 0; 
    
    
    ifstream load_file(filename);
    if (!load_file) {
        cerr << "Error" << endl;
        return false;
    }

    while (getline(load_file, line)) {

        if (line == "") {
             continue;
        }
        if (count == 0) {
            movie_id = toLower(line); count++;

        }
        else if (count == 1) {
            movie_name = line; count++;
        }
        else if (count == 2) {
            release_year = line; count++;
        }
        else if (count == 3) {
            /*parse through the commas of the directors*/
            std::stringstream ss(line);
            std::string name_of_directors;
            while (std::getline(ss, name_of_directors, ',')) {
                directors.emplace_back(toLower(name_of_directors));
            }
            count++;
        }

        /*parse through the commas of the actors*/
        else if (count == 4) {
            std::stringstream ss(line);
            std::string name_of_actor;
            while (std::getline(ss, name_of_actor, ',')) {
                 actors.emplace_back(toLower(name_of_actor));
            }
            count++;
         
        }

        else if (count == 5) {
            /*parse through the commas of the genres*/
            std::stringstream ss(line);
            std::string name_of_genre;
            while (std::getline(ss, name_of_genre, ',')) {
                genres.emplace_back(toLower(name_of_genre));
            }
            count++;
          
        }

        else if (count == 6) {
        
            rating = stof(line); count++;

        }

        if (count == 7) {
            Movie* movie_pointer = new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating);
            /*allocate a new Movie based on the 7 things in the parameter*/
            m_movie.emplace_back(movie_pointer); m_movieById.insert(movie_id, movie_pointer);
            /*emplace/push back the newly allocated movie object into the vectors of movies.
            then using the tree multimap for the IDs, insert the vector of movies and newly allocated
            object into it.*/



            /*I'll only explain how the directors work here since everything else is essentially very similar:
            you loop through all directors, if it can find it, get its value, then push back the newly allocated object into 
            the tree map of the directors. This idea is the same for the rest*/
            for (const auto& director : directors) { // O(Log(D) + Md)
                if (m_movieByDirector.find(director).is_valid()) { // O(LOG(D)
                    m_movieByDirector.find(director).get_value().emplace_back(movie_pointer); // O(LOG(D)
                }
                else {
                    std::vector<Movie*> temp;
                    temp.emplace_back(movie_pointer);
                    m_movieByDirector.insert(director, temp); // O(LOG(D)
                }
            }
            for (const auto& actor : actors) { // O(Log(A) + Ma)
                if (m_movieByActor.find(actor).is_valid()) { // O(LOG(A)
                    m_movieByActor.find(actor).get_value().emplace_back(movie_pointer); // O(LOG(A)
                }
                else {
                    std::vector<Movie*> temp;
                    temp.emplace_back(movie_pointer);
                    m_movieByActor.insert(actor, temp); // O(LOG(A)
                }

            }
            for (const auto& genre : genres) { // O(Log(G) + Mg)
                if (m_movieByGenre.find(genre).is_valid()) { // O(LOG(G)
                    m_movieByGenre.find(genre).get_value().emplace_back(movie_pointer); // O(LOG(G)
                }
                else {
                    std::vector<Movie*> temp;
                    temp.emplace_back(movie_pointer);
                    m_movieByGenre.insert(genre, temp); //O(LOG(G)
                }
            }
            
            movie_id.clear(); movie_name.clear(); release_year.clear();
            rating = 0; count = 0;
            directors.clear(); actors.clear(); genres.clear();
           // delete movie_pointer;
        }
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = m_movieById.find(toLower_2(id)); // O (LOG M)

    if (it.is_valid()) {
        return it.get_value();
    }
    
    return nullptr;  
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    
    TreeMultimap<std::string, std::vector<Movie*>>::Iterator it = m_movieByDirector.find(toLower_2(director)); // O (LOG D)

    if (it.is_valid()) {
        return it.get_value();
    }
    return vector<Movie*>();
   
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
  
    TreeMultimap<std::string, std::vector<Movie*>>::Iterator it = m_movieByActor.find(toLower_2(actor)); // O (LOG A)
 
        if (it.is_valid()) {
            return it.get_value();
        }
    
   
    return vector<Movie*>();  
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<std::string, std::vector<Movie*>>::Iterator it = m_movieByGenre.find(toLower_2(genre)); // O (LOG G)

    if (it.is_valid()) {
        return it.get_value();
    }
    return vector<Movie*>(); 
}

//78 lines of codes approximate