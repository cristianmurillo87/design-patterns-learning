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