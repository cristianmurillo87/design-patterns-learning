#include <string>
#include <sstream>
#include <iostream>

class InvalidPointTypeException: std::exception
{
public:
    InvalidPointTypeException() noexcept = default;
    ~InvalidPointTypeException() = default;
    virtual const char* what() noexcept
    {
        return "Invalid point type. Only types POLAR and CARTESIAN are accepted.";
    }
};

enum PointType
{
    POLAR,
    CARTESIAN
};

class BasePoint
{
public:
    virtual std::string coordinates() = 0;
};

class CartesianPoint: public BasePoint
{
private:
    float x, y;
public:
    CartesianPoint(float x, float y): x{x}, y{y}  {}
    CartesianPoint(): x{0.0}, y{0.0} {}

    std::string coordinates() {
        std::ostringstream oss;
        oss << "X: " << x << ", Y: " << y;
        return oss.str();
    }
};


class PolarPoint: public BasePoint
{
private:
    float rho, phi;

public:
    PolarPoint(float rho, float phi): rho{rho}, phi{phi}  {}
    PolarPoint(): rho{0.0}, phi{0.0} {}

    std::string coordinates() {
        std::ostringstream oss;
        oss << "Rho: " << rho << ", Phi: " << phi;
        return oss.str();
    }
};

// No abstract factory
// in this case only a concrete factory is created
class PointFactory
{
public:
    PointFactory() {}

    BasePoint create_point(PointType type)
    {
        switch (type)
        {
        case PointType::POLAR:
            return PolarPoint();
        case PointType::CARTESIAN:
            return CartesianPoint();
        default:
            throw InvalidPointTypeException();
        }
    }
};

int main()
{
    PointFactory factory;
    auto cartesian = factory.create_point(PointType::CARTESIAN);
    auto polar = factory.create_point(PointType::POLAR);

    std::cout << cartesian.coordinates() << std::endl;
    std::cout << polar.coordinates() << std::endl;

    return 0;
}