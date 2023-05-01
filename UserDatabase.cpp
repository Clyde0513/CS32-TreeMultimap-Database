#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase() : user_tree() {}

UserDatabase::~UserDatabase() {
  
    for (auto user : m_user) {
        delete user;
    }
    
}

bool UserDatabase::load(const string& filename)
{   

    string line;
    string userName = "";
    string userEmail = "";
    int count = 0;
    int size = 0;
    vector<string> id_list;


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
                userName = line; count++;
            }
            else if (count == 1) {
                userEmail = line; count++;

            }
            else if (count == 2) {
                size = std::stoi(line); id_list.reserve(size); count++;
            }
            else if (line != "") {
                id_list.emplace_back(line); count++;
            }
            if (size + 3 == count) {
                /*creates the user Object based on username email and the watch history of Ids
                then you insert the object into the tree multimap
                then push/emplace back that newly allocated user object into private vector of user object.
                reset everything.*/
               User* m_users = new User(userName, userEmail, id_list);
                user_tree.insert(userEmail, m_users);
                m_user.emplace_back(m_users);

                userName.clear(); userEmail.clear();
                count = 0; size = 0;  id_list.clear();
                
                
                
            }
            

            /* string name = line;
             getline(load_file , line);
             std::cout << name << std::endl;

             string email = line;
             getline(load_file, line);
             cout << email << std::endl;

             int count_movies = std::stoi(line);
             std::cout << count_movies << std::endl;
             vector<string> id_list;


             while (count_movies > 0) {
                 std::getline(load_file, line);
                 count_movies--;
                 string id = line;
                 std::cout << id << std::endl;
                 id_list.push_back(id);
             }


             if (std::getline(load_file, line)) {}

             User* user_pointer = new User(name, email, id_list);
             user_tree.insert(email, user_pointer);


         }
         return true;*/
        }
       
        return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{

    TreeMultimap<std::string, User*>::Iterator it = user_tree.find(email);

    if (it.is_valid()) {
        return it.get_value();
    }
    return nullptr;


}
//32 lines of codes 
