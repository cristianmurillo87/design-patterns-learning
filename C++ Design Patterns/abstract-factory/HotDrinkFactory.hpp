#pragma once
#include "HotDrink.hpp"

// abstract factory
struct HotDrinkFactory
{
    // method that creates the product
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

// concrete factories, one for each product
struct TeaFactory: HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory: HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};