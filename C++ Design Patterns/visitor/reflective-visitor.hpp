/*
 * Reflective Visitor Design Pattern
 *
 * The Reflective Visitor pattern is a way to add new operations to existing object structures without modifying the structures.
 * It uses runtime type information (RTTI) to determine the type of the object and perform the appropriate operation.
 * This approach can be less efficient than the traditional Visitor pattern because it relies on dynamic_cast.
 * In this example, the ExpressionPrinter class uses dynamic_cast to determine the type of the Expression
 * and print it accordingly.
 */

#pragma once
#include "intrusive-visitor.hpp"

struct ExpressionPrinter
{
    std::string str() const
    {
        return oss.str();
    }

    void print(Expression* e)
    {
        if (auto de = dynamic_cast<DoubleExpression*>(e))
        {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression*>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }
    
private:
    std::ostringstream oss;
};