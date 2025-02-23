/*
 * Acyclic Visitor Design Pattern
 *
 * The Acyclic Visitor pattern is a variation of the Visitor pattern that allows adding new visitable classes without modifying the existing visitor interface.
 * It achieves this by using multiple inheritance and dynamic_cast to determine the type of the visitable object at runtime.
 * This approach avoids the cyclic dependency between the visitor and visitable classes.
 * In this example, the Expression hierarchy (DoubleExpression, AdditionExpression) implements the accept method,
 * and the Visitor template class defines visit methods for each type of expression.
 * The ExpressionPrinter class implements the Visitor interface to provide specific operations.
 */

#include <sstream>

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase
{
    virtual ~VisitorBase() =default;
};

struct Expression
{
    virtual ~Expression() = default;
    virtual void accept(VisitorBase& visitor)
    {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&visitor))
            ev->visit(*this);
    };
};


struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double value) : value(value) {}

    void accept(VisitorBase& visitor) override
    {
        using EV = Visitor<DoubleExpression>;
        if (auto ev = dynamic_cast<EV*>(&visitor))
            ev->visit(*this);
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

    void accept(VisitorBase& visitor) override
    {
        using EV = Visitor<AdditionExpression>;
        if (auto ev = dynamic_cast<EV*>(&visitor))
            ev->visit(*this);
    }
};

struct ExpressionPrinter : VisitorBase, Visitor<DoubleExpression>, Visitor<AdditionExpression>
{
    void visit(DoubleExpression& obj) override
    {
        oss << obj.value;
    }

    void visit(AdditionExpression& obj) override
    {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }
private:
    std::ostringstream oss;
};