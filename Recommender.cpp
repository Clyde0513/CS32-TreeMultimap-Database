#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database) : ub(user_database), md(movie_database) {}


vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    unordered_map<string, M_A_R_2> map_compatible;
    vector<MovieAndRank> recommend_movies;
    vector<M_A_R_2> sort_movies;
    unordered_set<string> vector_already;
    User* email = ub.get_user_from_email(user_email);

    if (email != nullptr) {
        /*if email nullptr, returns an empty vector of struct MovieAndRank*/
        unordered_set<string> watchHistory;
        /*iterates through all of the get watch history of the user.*/
        for (const auto& movie_id : email->get_watch_history()) {
            //then insert all of the get watch history's user into the unordered set watchHistory.
            watchHistory.insert(toLower(movie_id));
 
        }
        for (const auto& movie_watched_history : email->get_watch_history()) {
            /*then iterates through the user's watch history and stores it into a movie pointer object
            if it cannot find it, return nullptr. else...
            
            */
            Movie* movie = md.get_movie_from_id(movie_watched_history);
            if (movie == nullptr) { }
            else {
                /*I'm also going to say how the directors work because it's the same logic as for the rest of them*/
                for (const auto& director : movie->get_directors()) {
                    /*loops through the directors*/
                        for (const auto& directors_in_movie : md.get_movies_with_director(director)) {
                            /*loops through the movies with directors */
                        if (watchHistory.count(directors_in_movie->get_id()) == 0) {
                            /*if the count of the unordered set of the watchHistory is 0
                            then, check if the unordered set of string called vector_already is 1
                            if it is, then add the compatibility score by 20 because that director has already been seen
  
                            then make the first bool to false because we don't want to double the results when the 
                            director has only seen once.
                            
                            then if first and second are true, then that means the director is getting seen'ed first time
                            so update the compatibility score to 20, id to the id of the director's movie, to the rating
                            of the director's movie, and to the movie_title of the director's title they are in.
                            and set second bool to false. 
                            */
                            bool first = true; bool second = true;
  
                            if (vector_already.count(directors_in_movie->get_id()) == 1) {
                                map_compatible[directors_in_movie->get_id()].compatibility_score += 20;

                                first = false;
                            }
                            if (first && second) {
                                map_compatible[directors_in_movie->get_id()].compatibility_score = 20;
                                map_compatible[directors_in_movie->get_id()].movie_id = directors_in_movie->get_id();
                                map_compatible[directors_in_movie->get_id()].rating = directors_in_movie->get_rating();
                                map_compatible[directors_in_movie->get_id()].movie_title = directors_in_movie->get_title();
                                vector_already.insert(directors_in_movie->get_id());
                                second = false;
                            }
                        }
                    }
                }
                /*same logic as for the diretors*/
                for (const auto& actor : movie->get_actors()) {
                    for (const auto& actors_in_movie : md.get_movies_with_actor(actor)) {
                      
                        if (watchHistory.count(actors_in_movie->get_id()) == 0) {
                            bool first = true; bool second = true;
                         
                            if (vector_already.count(actors_in_movie->get_id()) == 1) {
                                map_compatible[actors_in_movie->get_id()].compatibility_score += 30;
                                first = false;
                            }
                            if (first && second) {
                                map_compatible[actors_in_movie->get_id()].compatibility_score = 30;
                                map_compatible[actors_in_movie->get_id()].movie_id = actors_in_movie->get_id();
                                map_compatible[actors_in_movie->get_id()].rating = actors_in_movie->get_rating();
                                map_compatible[actors_in_movie->get_id()].movie_title = actors_in_movie->get_title();
                                vector_already.insert(actors_in_movie->get_id());
                                second = false;
                            }
                        }
                    }
                }
                /*same logic as for the directors*/
                for (const auto& genre : movie->get_genres()) {
                   
                    for (const auto& genre_in_movie : md.get_movies_with_genre(genre)) {
                        if (watchHistory.count(genre_in_movie->get_id()) == 0) {
                            bool first = true; bool second = true;
                            if (vector_already.count(genre_in_movie->get_id()) == 1) {
                                map_compatible[genre_in_movie->get_id()].compatibility_score += 1;
                                first = false;
                            }
                            if (first && second) {
                                map_compatible[genre_in_movie->get_id()].compatibility_score = 1;
                                map_compatible[genre_in_movie->get_id()].movie_id = genre_in_movie->get_id();
                                map_compatible[genre_in_movie->get_id()].rating = genre_in_movie->get_rating();
                                map_compatible[genre_in_movie->get_id()].movie_title = genre_in_movie->get_title();
                                vector_already.insert(genre_in_movie->get_id());
                                second = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else {
    return vector<MovieAndRank>(); 
    }
  
    for (auto itr = vector_already.begin(); itr != vector_already.end(); itr++) {
    
        sort_movies.emplace_back(M_A_R_2(map_compatible[*itr].movie_id, map_compatible[*itr].compatibility_score , map_compatible[*itr].rating , map_compatible[*itr].movie_title));

    }
   
    sort(sort_movies.begin(), sort_movies.end(), compare);

    for (auto it = sort_movies.begin(); it != sort_movies.end(); it++) {
        recommend_movies.emplace_back(MovieAndRank(it->movie_id, it->compatibility_score));
    }
  
    if (recommend_movies.size() > movie_count)
    {
        recommend_movies.resize(movie_count);
    }
  
    return recommend_movies;

    }