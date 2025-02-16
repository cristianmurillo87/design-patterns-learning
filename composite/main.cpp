/*
 * This example demonstrates the Composite design pattern.
 * 
 * The Composite pattern allows to compose objects into tree structures 
 * to represent part-whole hierarchies. It lets clients treat individual objects 
 * and compositions of objects uniformly.
 * 
 * In this example, we have:
 * - GraphicObject: an abstract base class with a virtual draw() method.
 * - Circle: a concrete class that implements the draw() method.
 * - Group: a composite class that can contain multiple GraphicObject instances 
 *   (including other Group instances) and implements the draw() method to draw 
 *   all its children.
 * 
 * Additionally, we have a neural network example using the Composite pattern:
 * - Neuron: represents a single neuron.
 * - NeuronLayer: represents a layer of neurons and can connect to other neurons 
 *   or layers.
 */

#include <iostream>
#include <vector>

template<typename Self>
struct SomeNeurons
{
    template<typename T> void connect_to(T &other)
    {
        for(Neuron &from: *static_cast<Self *>(this))
        {
            for(Neuron &to: other)
            {
                from.connect_to(to);
            }
        }
    }
};

struct Neuron: SomeNeurons<Neuron>
{
    std::vector<Neuron *> in, out;
    unsigned int id;

    Neuron()
    {
        static int id = 1;
        this->id = id++;
    }



    // begin and end are used to make Neuron a range
   Neuron* begin() { return this; }
    // No end since this is a single object
   Neuron* end() { return this + 1; }

    friend std::ostream &operator<<(std::ostream &os, const Neuron &obj)
    {
        for(auto&& n: obj.in)
        {
            os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;
        }

        for(auto&& n: obj.out)
        {
            os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
        }

        return os;
    }
};


struct NeuronLayer: std::vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while(count-- > 0)
        {
            emplace_back(Neuron{});
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &obj)
    {
        for(auto&& n: obj)
        {
            os << n;
        }

        return os;
    }
};



struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle: GraphicObject
{
    void draw() override {
        std::cout << "Circle" << std::endl;
    }
};

struct Group: GraphicObject
{
    std::string name;
    std::vector<GraphicObject *> objects;

    Group(const std::string &name): name(name) {}

    void draw() override
    {
        std::cout << "Group " << name.c_str() << " contains:" << std::endl;
        for(auto&& object: objects)
        {
            object->draw();
        }
    }

};

int main()
{
    /*Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);
    root.draw();*/
    Neuron n1, n2;
    n1.connect_to(n2);

    std::cout << n1 << n2 << std::endl;

    NeuronLayer layer1{2}, layer2{3};
    n1.connect_to(layer1);
    layer1.connect_to(layer2);

    std::cout << "Layer 1" << std::endl << layer1;

    return 0;
}