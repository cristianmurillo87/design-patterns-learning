/*
 * Proxy Design Pattern
 *
 * The Proxy pattern provides a surrogate or placeholder for another object to control access to it.
 * It is useful when you want to add a layer of control over the object, such as lazy initialization,
 * access control, logging, or caching.
 * In this example, the Property template class acts as a proxy for primitive types, allowing additional behavior
 * to be added when accessing or modifying the values, such as validation or logging.
 */

template<typename T> struct Property
{
    T value;

    Property(T value) { *this = value; }

    T operator=(T new_value)
    {
        return value = new_value;
    }

    operator T()
    {
        return value;
    }

};

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{5};
};

int main()
{
    Creature creature;
    creature.strength = 11;
    int x = creature.agility;
    return 0;
}