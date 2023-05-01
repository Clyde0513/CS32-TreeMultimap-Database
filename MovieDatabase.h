#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"



class Movie;

class MovieDatabase
{
public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

private:
    /*4 maps for each 
    --> ID
    --> Director
    --> Actor
    --> Genre
    
    And a vector of movie pointers*/
    TreeMultimap<std::string, Movie*> m_movieById;
    TreeMultimap<std::string, std::vector<Movie*>> m_movieByDirector;
    TreeMultimap<std::string, std::vector<Movie*>> m_movieByActor;
    TreeMultimap<std::string, std::vector<Movie*>> m_movieByGenre;
    std::vector<Movie*> m_movie;

    /*pretty straight forward based on the function name :D*/
    std::string toLower(const std::string& line) { //ACtOR
        /*size_t i = 0; char c;*/
        std::string newLine = line;
        int i = 0;
        while (i < newLine.size()) {
            if (isdigit(newLine[i])) {

            }
            else {
                newLine[i] = tolower(newLine[i]);
            }
            i++;
        }
        return newLine;
    } //actor
    /* the only difference between this function is the const. The const part is where I use it in the getters when
    getting the ids actors, etc. and the non const function is to use on the load function*/
    std::string toLower_2(const std::string line) const {
        std::string newLine = line;
        int i = 0;
        while( i < newLine.size()) {
            if (isdigit(newLine[i])) {

            }
            else {
                newLine[i] = tolower(newLine[i]);
            }
            i++;
        }
        return newLine;
    }
    //23 lines of code
   
  


};

#endif // MOVIEDATABASE_INCLUDED
