/*
 * Mediator Design Pattern
 *
 * The Mediator pattern defines an object that encapsulates how a set of objects interact.
 * It promotes loose coupling by keeping objects from referring to each other explicitly,
 * and it lets you vary their interaction independently.
 * In this example, the ChatRoom class acts as a mediator for the Person class,
 * facilitating communication between different Person instances.
 */

#include "ChatRoom.hpp"
#include "Person.hpp"

int main()
{
    ChatRoom room;
    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon{"Simon"};
    
    room.join(&simon);
    simon.say("hi everyone!");
    jane.pm("Simon", "glad you could join us, Simon");

    return 0;
}