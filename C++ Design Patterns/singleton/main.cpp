/**
 * Singleton pattern
 * 
 * The Singleton pattern ensures that a class has only one instance and 
 * provides a global point of access to it. This is useful when exactly one 
 * object is needed to coordinate actions across the system.
 * 
 * In this example, `SingletonDatabase` is a singleton class that provides 
 * access to a database of city populations. The constructor is private, 
 * and the class provides a static method `get()` to access the single instance.
 * The copy constructor and assignment operator are deleted to prevent creating
 * additional instances.
 */

#include <map>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

class Database {
public:
    virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase: public Database
{
    SingletonDatabase()
    {
        std::cout << "Initializing database\n" << std::endl;
        std::ifstream ifs("capitals.txt");

        std::string s, s2;
        while (std::getline(ifs, s))
        {
            std::getline(ifs, s2);
            int population = boost::lexical_cast<int>(s2);
            capitals[s] = population;
        }
    }
    std::map<std::string, int> capitals;

public:
    // ensuring that is not possible to create a new instance of SingletonDatabase
    // by deleting the copy constructor and the assignment operator
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name)
    {
        return capitals[name];
    }
};

class DummyDatabase: public Database
{
    std::map<std::string, int> capitals;
public:
    DummyDatabase()
    {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(const std::string& name) override
    {
        return capitals[name];
    }
};

struct SingletonRecordFinder
{
    int total_population(std::vector<std::string> names)
    {
        int result = 0;
        for (auto& name: names)
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};

struct ConfigurableRecordFinder
{
    Database& db;

    ConfigurableRecordFinder(Database& db): db(db) {}

    int total_population(std::vector<std::string> names)
    {
        int result = 0;
        for (auto& name: names)
            result += db.get_population(name);
        return result;
    }
};

/**
 * Example of the Bill Pugh singleton implementation
 * Here, an inner class is used to create the singleton instance using a static method
 * and is one of the most widely used variants for implementing the singleton pattern
 */
struct BillPughSingleton
{
    static BillPughSingleton instance()
    {
        return InnerBillPughSingleton::unique_instance;
    }

    std::string get_value(std::string key)
    {
        return database[key];
    }

private:

    std::map<std::string, std::string> database;

    BillPughSingleton() {}

    struct InnerBillPughSingleton
    {
        static BillPughSingleton unique_instance; 
    };
};

int main()
{
    std::string city = "Tokyo";
    std::cout << city << " has population " <<
    SingletonDatabase::get().get_population(city) << std::endl;

    BillPughSingleton instance = BillPughSingleton::instance();
    std::cout << "Value: " << instance.get_value("some_key") << std::endl;

    return 0;
}