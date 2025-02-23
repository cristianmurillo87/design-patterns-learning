/*
 * This example demonstrates the Decorator design pattern using a dynamic approach.
 * 
 * The Decorator pattern allows behavior to be added to individual objects, 
 * either statically or dynamically, without affecting the behavior of other 
 * objects from the same class.
 * 
 * In this example, we have:
 * - Shape: an abstract base class with a virtual str() method.
 * - Circle and Square: concrete classes that implement the str() method.
 * - ColoredShape and TransparentShape: decorator classes that add color and 
 *   transparency properties to shapes, respectively.
 * 
 * The dynamic approach uses composition to apply decorators at runtime, 
 * allowing for more flexible and dynamic behavior changes.
 */

#include <iostream>
#include <sstream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle: Shape
{
    float radius;

    Circle() {}

    Circle(float radius): radius(radius) {}

    void resize(float factor)
    {
        radius *= factor;
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square: Shape
{
    float side;

    Square() {}

    Square(float side): side(side) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};


struct ColoredShape: Shape
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, const std::string &color): shape(shape), color(color) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape: Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t transparency): shape(shape), transparency(transparency) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};

int main()
{
    Square square{5};
    ColoredShape red_square{square, "red"};
    std::cout << square.str() << red_square.str() << std::endl;

    TransparentShape transparent_red_square{red_square, 51};
    std::cout << transparent_red_square.str() << std::endl;
    return 0;
}