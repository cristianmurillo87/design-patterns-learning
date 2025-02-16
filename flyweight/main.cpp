/*
 * Flyweight Design Pattern
 *
 * The Flyweight pattern is used to minimize memory usage or computational expenses
 * by sharing as much as possible with similar objects.
 * It is particularly useful when dealing with a large number of objects that
 * have some shared state among them.
 * In this example, the User class uses the Flyweight pattern to share
 * common first and last names among multiple User instances.
 */

#include <cstdint>
#include <map>
#include <iostream>
#include <sstream>

typedef uint32_t key;

struct User
{
    User(const std::string& first_name, const std::string& last_name)
        : first_name{add(first_name)}, last_name{add(last_name)} {}

    const std::string& get_first_name() const
    {
        return names.find(first_name)->second;
    }

    const std::string& get_last_name() const
    {
        return names.find(last_name)->second;
    }

protected:
    key first_name, last_name;
    static std::map<key, std::string> names;
    static key seed;

    static key add(const std::string& s)
    {
        auto it = std::find_if(names.begin(), names.end(), [&s](const auto& pair) { return pair.second == s; });
        if (it == names.end())
        {
            key id = ++seed;
            names.insert({id, s});
            return id;
        }
        return it->first;
    }
};

key User::seed = 0;
std::map<key, std::string> User::names{};

std::ostream& operator<<(std::ostream& os, const User& obj)
{
    return os << "first_name: " << obj.get_first_name() << " last_name: " << obj.get_last_name();
}

int main()
{
    User user_1{"John", "Smith"};
    User user_2{"Jane", "Smith"};

    std::cout << user_1 << std::endl;
    std::cout << user_2 << std::endl;
    
    return 0;
}