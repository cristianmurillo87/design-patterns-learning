/*
 * Chain of Responsibility Design Pattern
 *
 * The Chain of Responsibility pattern allows an object to send a command without knowing which object will handle it.
 * The request is passed along a chain of potential handlers until one of them handles the request.
 * This pattern is useful for decoupling the sender and receiver of a request.
 * In this example, the CreatureModifier class forms the chain, and different modifiers (DoubleAttackModifier, IncreaseDefenseModifier, NoBonusesModifier)
 * handle the request to modify the creature's attributes.
 */

#include <iostream>

struct Creature
{
    std::string name;
    int attack, defense;

    Creature(const std::string &name, int attack, int defense) 
        : name(name), attack(attack), defense(defense) {}

    friend std::ostream &operator<<(std::ostream &os, const Creature &creature)
    {
        os << "name: " << creature.name << " attack: " << creature.attack << " defense: " << creature.defense;
        return os;
    }
};

class CreatureModifier
{
    CreatureModifier *next{nullptr};
protected:
    Creature &creature;
public:
    CreatureModifier(Creature &creature) : creature(creature) {}

    void add(CreatureModifier *cm)
    {
        if (next) next->add(cm);
        else next = cm;
    }

    virtual void handle()
    {
        if (next) next->handle();
    }
};

class DoubleAttackModifier: public CreatureModifier
{
public:
    DoubleAttackModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier: public CreatureModifier
{
public:
    IncreaseDefenseModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override
    {
        if (creature.attack <= 2)
            creature.defense++;
        CreatureModifier::handle();
    }
};

class NoBonusesModifier: public CreatureModifier
{
public:
    NoBonusesModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override
    {
        // Do nothing: prevent execution of handle() for the next modifiers
    }
};

int main()
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};
    IncreaseDefenseModifier r2{goblin};

    NoBonusesModifier curse{goblin};

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);
    root.add(&curse);

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}