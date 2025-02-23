/*
 * Intrusive Visitor Design Pattern
 *
 * The Intrusive Visitor pattern is a way to add new operations to existing object structures without modifying the structures.
 * It involves adding a method to each class in the hierarchy that accepts a visitor object.
 * This approach can be intrusive because it requires modifying the existing classes.
 * In this example, the Expression hierarchy (DoubleExpression, AdditionExpression) implements the print method
 * to allow a visitor to print the expression.
 */

#pragma once
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;
    virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression: Expression
{
    double value;

    explicit DoubleExpression(const double value): value(value)
    {}

    void print(std::ostringstream& oss) override
    {
        oss << value;
    }
};

struct AdditionExpression: Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right): left(left), right(right)
    {}

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void print(std::ostringstream& oss) override
    {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};