#pragma once
#include <iostream>
#include <memory>

// abstract product
struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

// concrete products, each product is a class
struct Tea: HotDrink 
{
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << std::endl;
    }
};

struct Coffee: HotDrink
{
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << std::endl;
    }
};