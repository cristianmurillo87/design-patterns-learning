/*
 * Chain of Responsibility Design Pattern
 *
 * The Chain of Responsibility pattern allows an object to send a command without knowing which object will handle it.
 * The request is passed along a chain of potential handlers until one of them handles the request.
 * This pattern is useful for decoupling the sender and receiver of a request.
 * In this example, the Game class forms the chain, and different modifiers (DoubleAttackModifier)
 * handle the request to modify the creature's attributes.
 */

#include <iostream>
#include "boost/signals2.hpp"

struct Query
{
    std::string creature_name;
    enum Argmunent {attack, defense} argument;
    int result;

    Query(const std::string &name, Argmunent argument, int result)
        : creature_name(name), argument(argument), result(result) {}
};

struct Game
{
    boost::signals2::signal<void(Query&)> queries;
};

struct Creature
{
    Game& game;
    int attack, defense;
    std::string name;
public:
    Creature(Game &gsme, int attack, int defense, const std::string& name)
        : game(game), attack(attack), defense(defense), name(name) {}

    int get_attack() const
    {
        Query query{name, Query::Argmunent::attack, attack};
        game.queries(query);
        return query.result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Creature &creature)
    {
     
        os << "name: " << creature.name << " attack: " << creature.get_attack();
        return os;
    }
};

class CreatureModifier
{
    Game &game;
    Creature &creature;
public:
    CreatureModifier(Game &game, Creature &creature) : game(game), creature(creature) {}

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier: public CreatureModifier
{
    boost::signals2::connection conn;
public:
    DoubleAttackModifier(Game &game, Creature &creature) : CreatureModifier(game, creature) 
    {
        conn = game.queries.connect([&](Query& q)
        {
            if (q.creature_name == creature.name && q.argument == Query::Argmunent::attack)
                q.result *= 2;
        });
    }

    ~DoubleAttackModifier()
    {
        conn.disconnect();
    }
};

int main()
{
    Game game;
    Creature goblin{game, 2, 2, "Strong Goblin"};

    std::cout << goblin << std::endl;

    {
        DoubleAttackModifier dam{game, goblin};
        std::cout << goblin << std::endl;
    }

    std::cout << goblin << std::endl;
    
    return 0;
}