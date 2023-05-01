#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>


class User
{
public:
    User(const std::string& full_name, const std::string& email,
        const std::vector<std::string>& watch_history);
    ~User();
    std::string get_full_name() const;
    std::string get_email() const;
    std::vector<std::string> get_watch_history() const;

private:
    std::vector<std::string> m_watchHistory;
    std::string m_fullName;
    std::string m_email;
};
//3 lines of code
#endif // USER_INCLUDED
