/*
 * This example demonstrates the Decorator design pattern using a static approach.
 * 
 * The Decorator pattern allows behavior to be added to individual objects, 
 * either statically or dynamically, without affecting the behavior of other 
 * objects from the same class.
 * 
 * In this example, we have:
 * - Shape: an abstract base class with a virtual str() method.
 * - Circle and Square: concrete classes that implement the str() method.
 * - ColoredShape and TransparentShape: template decorators that add color and 
 *   transparency properties to shapes, respectively.
 * 
 * The static approach uses templates to apply decorators at compile time, 
 * ensuring type safety and avoiding the overhead of dynamic polymorphism.
 */

#include <iostream>
#include <sstream>
#include <concepts>

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

template<typename T>
concept IsShape = std::is_base_of<Shape, T>::value;

template<IsShape T>
struct ColoredShape: T
{
    std::string color;

    ColoredShape() {}

    template<typename...Args>
    ColoredShape(const std::string &color, Args...args)
    : T(std::forward<Args>(args)...), color(color) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template<IsShape T>
struct TransparentShape: T
{
    uint8_t transparency;

    template<typename...Args>
    TransparentShape(const uint8_t transparency, Args...args)
        : T(std::forward<Args>(args)...), transparency(transparency) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has " << static_cast<float>(transparency) / 255.0f * 100.0f << "% transparency";
        return oss.str();
    }
};


int main()
{
    ColoredShape<Circle> green_circle("green", 5);
    std::cout << green_circle.str() << std::endl;

    TransparentShape<ColoredShape<Square>> blue_invisible_square(0, "blue", 10);
    blue_invisible_square.color = "light blue";
    blue_invisible_square.side = 21;
    std::cout << blue_invisible_square.str() << std::endl;

    return 0;
}