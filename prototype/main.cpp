/**
 * Prototype design pattern
 * The prototype pattern is a creational design pattern that allows cloning objects, 
 * even complex ones, without coupling to their specific classes.
 * To implement the prototype pattern, you need to create a copy of an existing object
 * and then customize it as needed.
 * It is also important to define a common interface for all objects that can be cloned
 * and to implement a cloning method in each concrete class.
 */

#include <string>
#include <iostream>
#include <sstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct Address
{
    std::string street;
    std::string city;
    int suite;

    Address() {}

    Address(std::string street, std::string city, int suite): 
    street(street), city(city), suite(suite) {}

    Address(const Address& other): street(other.street), city(other.city), suite(other.suite) {}

    friend std::ostream &operator<<(std::ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};


struct Contact 
{
    std::string name;
    Address* address;

    Contact() {}

    Contact(const std::string &name, Address *address): name(name), address(address) {}

    Contact(const Contact& other): name(other.name), address(new Address{*other.address}) {}

    ~Contact() {
        delete address;
    }


    friend std::ostream &operator<<(std::ostream &os, const Contact &contact)
    {
        os << "name: " << contact.name << " address: " << *contact.address;
        return os;
    }

    private:
        friend class boost::serialization::access;

        template<class archive>
        void serialize(archive &ar, const unsigned int version) 
        {
            ar & name;
            ar & address;
        }
};

struct EmployeeFactory
{
    static std::unique_ptr<Contact> new_main_office_employee(const std::string &name, const int suite) {
        static Contact p{"", new Address{"123 East Dr", "London", 0}};
        return new_employee(name, suite, p);
    }

private:
    static std::unique_ptr<Contact> new_employee(const std::string &name, const int suite, const Contact&  prototype) {
        auto result = std::make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main() {
    /*Contact john{"John Doe", new Address{"123 East Dr", "London", 123}};
    Contact jane = john;
    jane.name = "Jane Smith";
    jane.address->suite = 103;
    std::cout << john << std::endl << jane << std::endl;*/
    auto clone = [](const Contact& c) {
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        std::string s = oss.str();
        std::cout << s << std::endl;
        std::istringstream iss(s);
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    auto john = EmployeeFactory::new_main_office_employee("John Doe", 123);
    auto jane = clone(*john);
    jane.name = "Jane Smith";
    std::cout << *john << std::endl << jane << std::endl;
    return 0;
}