#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Vehicle
{
protected:
    std::vector<std::string> parts;
public:
    virtual void add_part(const std::string part_name) = 0;
    virtual void move() = 0;
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
        for (auto part: vehicle.parts)
        {
            os << part << "/n";
        }
        return os;
    }

};

class Car: public Vehicle
{
public:

    void add_part(const std::string part_name) override
    {
        parts.push_back(part_name);
    }

    void move() override
    {
        std::cout << "Moving the car" << std::endl;
    }
};

class Motorcycle: public Vehicle
{
public:

    void add_part(const std::string part_name) override
    {
        parts.push_back(part_name);
    }

    void move() override
    {
        std::cout << "Moving the motorcycle" << std::endl;
    }
};


class VehicleBuilder
{
public:
    virtual void build_body() = 0;
    virtual void insert_wheels() = 0;
    virtual void add_headlights() = 0;
    virtual Vehicle* get_vehicle() = 0;
};

class CarBuilder: public VehicleBuilder
{
    Car car;
public:
    void build_body() override
    {
        car.add_part("This is the body of the car");
    }

    void insert_wheels() override
    {
        car.add_part("Four wheels were added");
    }

    void add_headlights() override
    {
        car.add_part("Car headlights were added");
    }

    Vehicle* get_vehicle() override
    {
        return &car;
    }
};

class MotorcycleBuilder: public VehicleBuilder
{
    Motorcycle motorcycle;
public:
    void build_body() override
    {
        motorcycle.add_part("This is the body of the motorcycle");
    }

    void insert_wheels() override
    {
        motorcycle.add_part("Two wheels were added");
    }

    void add_headlights() override
    {
        motorcycle.add_part("Motorcycle headlights were added");
    }

    Vehicle* get_vehicle() override
    {
        return &motorcycle;
    }
};

class BuildDirector
{
    static Vehicle* build(VehicleBuilder& builder)
    {
        builder.build_body();
        builder.insert_wheels();
        builder.add_headlights();
        return builder.get_vehicle();
    }
};