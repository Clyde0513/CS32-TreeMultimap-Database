#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
class UserDatabase;
class MovieDatabase;
     
struct M_A_R_2 {
    /*I created a new struct with the difference of rating and movie title so that I can compare them. This struct will be used
    in the recommender.cpp and convert it to the original struct so that I can recommend new movies.*/
    M_A_R_2() : movie_id(""), compatibility_score(0) , rating(0), movie_title("") {}
    M_A_R_2(const std::string& id, int score, float rate, std::string title)
        : movie_id(id), compatibility_score(score), rating(rate) , movie_title(title) {}

    std::string movie_id;
    std::string movie_title;
    int compatibility_score;
    float rating;

};

struct MovieAndRank
{
    MovieAndRank() : movie_id(""), compatibility_score(0) {}
    MovieAndRank(const std::string& id, int score)
        : movie_id(id), compatibility_score(score) {}

    std::string movie_id;
    int compatibility_score;

};

class Recommender
{
public:
    Recommender(const UserDatabase& user_database,
        const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email, int movie_count) const;
    
private:
   const UserDatabase& ub;
   const MovieDatabase& md;
   // std::vector<MovieAndRank>* sort_movies;
   
   /*as the name suggests, I am comparing compartibility scores, ratings, and the movie titles.*/
    static bool compare(const M_A_R_2& a, const M_A_R_2& b) {
       
        if (a.compatibility_score != b.compatibility_score) {
            return a.compatibility_score > b.compatibility_score;
        }

        if (a.compatibility_score == b.compatibility_score) {
            if (a.rating == b.rating) {
                return a.movie_title < b.movie_title;
            }
            else {
                return a.rating > b.rating;
            }
        }
        return false;

   }
    /*I also need this to make sure the IDs are turned into lower case.*/
    std::string toLower(const std::string& line) const { //ACtOR
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


};


#endif // RECOMMENDER_INCLUDED
