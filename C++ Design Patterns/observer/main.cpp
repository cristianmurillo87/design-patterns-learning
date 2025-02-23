/*
 * Observer Design Pattern
 *
 * The Observer pattern defines a one-to-many dependency between objects so that when one object changes state,
 * all its dependents are notified and updated automatically.
 * It is useful for implementing distributed event-handling systems.
 * In this example, the Person class is the subject that notifies its observers (ConsolePersonObserver)
 * whenever its state changes.
 */

#include <string>
#include <iostream>

#include "observer.hpp"
#include "observable.hpp"
#include "safer-observable.hpp"

class Person: public SaferObservable<Person>
{
    int age;
public:
    Person(int age): age(age) {}

    int get_age() const{
        return age;
    }

    void set_age(int age)
    {
        if (this->age == age) return;
        this->age = age;
        this->notify(*this, "age");
    }
};


// observer and observable

struct ConsolePersonObserver: Observer<Person>
{
    void field_changed(Person& source, const std::string& field_name) override
    {
        std::cout << "Person's " << field_name << " has changed to " << source.get_age() << std::endl;
    }
};

int main()
{
    Person person{10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);
    person.set_age(13);
    
    return 0;
}