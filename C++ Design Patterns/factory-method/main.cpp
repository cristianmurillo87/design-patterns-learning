#include <cmath>
#include <iostream>

/**
 * Factory method is a static method of a class that returns an object of that class type.
 * It is used to create objects without specifying the exact class of object that will be created.
 * A factory can be external or it can be a member of the class it creates.
 */

class Point {
    Point(float x, float y) : x(x), y(y) {}
public:
    float x, y;

    static Point new_cartesian(float x, float y) {
        return {x, y};
    }

    static Point new_polar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        return os << "x: " << point.x << " y: " << point.y;
    }
};

int main() {
    auto p = Point::new_cartesian(5, M_PI_4);
    std::cout << p << p.y << std::endl;
    return 0;
}