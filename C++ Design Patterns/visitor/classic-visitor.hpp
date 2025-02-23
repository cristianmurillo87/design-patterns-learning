/*
 * Classic (Double Dispatch) Visitor Design Pattern
 *
 * The Classic Visitor pattern, also known as Double Dispatch, allows you to add further operations to objects without having to modify them.
 * It involves creating a visitor interface with visit methods for each type of element and implementing these methods in concrete visitor classes.
 * Each element class implements an accept method that takes a visitor and calls the appropriate visit method on it.
 * In this example, the Expression hierarchy (DoubleExpression, AdditionExpression, SubtractionExpression) implements the accept method,
 * and the ExpressionVisitor interface defines visit methods for each type of expression.
 * The ExpressionPrinter and ExpressionEvaluator classes implement the ExpressionVisitor interface to provide specific operations.
 */

#pragma once

#include <sstream>
#include <iostream>

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
    virtual void visit(SubtractionExpression* se) = 0;
};

// Following the single responsabilitz principle
// ExpressionPrinter only takes care of printing the expression
// whereas ExpressionEvaluator takes care of evaluating the expression
struct ExpressionPrinter: ExpressionVisitor
{
    std::ostringstream oss;
    std::string str() const { return oss.str(); }
    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubtractionExpression* se) override;
};

struct ExpressionEvaluator: ExpressionVisitor
{
    double result;
    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubtractionExpression* se) override;
};


struct Expression
{
    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : Expression
{
    DoubleExpression(double value) : value(value) {}

    double value;

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};

struct AdditionExpression : Expression
{
    Expression* left;
    Expression* right;

    AdditionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};

struct SubtractionExpression: Expression
{
    Expression* left;
    Expression* right;

    SubtractionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    ~SubtractionExpression()
    {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};