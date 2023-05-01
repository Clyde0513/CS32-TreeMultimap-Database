#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
    const vector<string>& directors, const vector<string>& actors,
    const vector<string>& genres, float rating) : m_id(id) , m_title(title) , m_releaseYear(release_year) ,
    m_directors(directors) , m_actors(actors) , m_genres(genres) , m_rating(rating)
{
    
}

Movie::~Movie() {
    m_directors.clear(); m_genres.clear(); m_actors.clear();
}

string Movie::get_id() const
{
    return m_id;  // Replace this line with correct code.
}

string Movie::get_title() const
{
    return m_title;  // Replace this line with correct code.
}

string Movie::get_release_year() const
{
    return m_releaseYear;  // Replace this line with correct code.
}

float Movie::get_rating() const
{
    return m_rating;  // Replace this line with correct code.
}

vector<string> Movie::get_directors() const
{
    return m_directors;  // Replace this line with correct code.
}

vector<string> Movie::get_actors() const
{
    return m_actors;  // Replace this line with correct code.
}

vector<string> Movie::get_genres() const
{
    return m_genres;  // Replace this line with correct code.
}

//8 lines of code
