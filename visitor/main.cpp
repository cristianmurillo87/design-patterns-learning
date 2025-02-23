#include <iostream>
#include "intrusive-visitor.hpp"

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << std::endl;

    delete e;
    return 0;
}