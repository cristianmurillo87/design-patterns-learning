/*
 * Multimethod Visitor Design Pattern
 *
 * The Multimethod Visitor pattern allows you to define multiple dispatch operations on objects
 * without modifying their classes.
 * It uses a map to store the relationships between different types and the corresponding operations.
 * This approach allows you to add new operations without modifying the existing classes or visitors.
 * In this example, the GameObject hierarchy (Planet, Asteroid, Spaceship) implements the collide method,
 * and the collide function uses a map to determine the appropriate operation based on the types of the objects.
 */

#include <typeindex>
#include <iostream>
#include <map>
#include <memory>

struct GameObject;

void collide(GameObject& first, GameObject& second);

struct GameObject
{
    virtual std::type_index type() const = 0;
    virtual void collide(GameObject& other)
    {
        ::collide(*this, other);
    }
};

template<typename T>
struct GameObjectImpl: GameObject
{
    std::type_index type() const override
    {
        return typeid(T);
    }
};

struct Planet: GameObjectImpl<Planet>
{};

struct Asteroid: GameObjectImpl<Asteroid>
{};

struct Spaceship: GameObjectImpl<Spaceship>
{};

void spaceship_planet(Spaceship& spaceship, Planet& planet)
{
    std::cout << "Spaceship lands on a planet\n";
}

void asteroid_planet(Asteroid& asteroid, Planet& planet)
{
    std::cout << "Asteroid burns up in the planet's atmospthere\n";
}

void asteroid_spaceship(Spaceship& spaceship, Asteroid& asteroid)
{
    std::cout << "Asteroid hits and destroys the spaceship\n";
}

std::map<std::pair<std::type_index, std::type_index>, void(*)(GameObject&, GameObject&)> outcomes {
    {{typeid(Spaceship), typeid(Planet)}, [](GameObject& a, GameObject& b) { spaceship_planet(static_cast<Spaceship&>(a), static_cast<Planet&>(b)); }},
    {{typeid(Asteroid), typeid(Planet)}, [](GameObject& a, GameObject& b) { asteroid_planet(static_cast<Asteroid&>(a), static_cast<Planet&>(b)); }},
    {{typeid(Asteroid), typeid(Spaceship)}, [](GameObject& a, GameObject& b) { asteroid_spaceship(static_cast<Spaceship&>(b), static_cast<Asteroid&>(a)); }}
};

void collide(GameObject& first, GameObject& second)
{
    auto it = outcomes.find({first.type(), second.type()});
    if (it == outcomes.end())
    {
        it = outcomes.find({second.type(), first.type()});
        if (it == outcomes.end())
        {
            std::cout << "objects pass each other harmlessly\n";
            return;
        }
    }
    it->second(first, second);
}
