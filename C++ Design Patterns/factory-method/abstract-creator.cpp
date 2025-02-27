#include <iostream>

class Shape
{
public:
    virtual void draw() = 0;
};

class Rectangle: public Shape
{
public:
    Rectangle()
    {}

    void draw() override
    {
        std::cout << "Called Rectangle::draw() method" << std::endl;
    }
};

class Square: public Shape
{
public:
    Square()
    {}

    void draw() override
    {
        std::cout << "Called Square::draw() method" << std::endl;
    }
};

class Circle: public Shape
{
public:
    Circle()
    {}

    void draw() override
    {
        std::cout << "Called Circle::draw() method" << std::endl;
    }
};

// Abstract factory class
class AbstractShapeFactory
{
protected:
    virtual Shape create() = 0;

public:
    Shape instance()
    {
        return create();
    }

};

// Concrete factory classes
// The method that actually creates the objects is 
// only accessible within the class
class RectangleFactory: public AbstractShapeFactory
{
private:
    Shape create() override
    {
        return Rectangle();
    }
};

class SquareFactory: public AbstractShapeFactory
{
private:
    Shape create() override
    {
        return Square();
    }
};

class CircleFactory: public AbstractShapeFactory
{
private:
    Shape create() override
    {
        return Circle();
    }
};


int main()
{
    auto shape_1 = CircleFactory().instance();
    shape_1.draw();

    return 0;
}