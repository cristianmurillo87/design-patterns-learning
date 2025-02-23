#include "classic-visitor.hpp"

void ExpressionPrinter::visit(DoubleExpression* de)
{
    oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression* ae)
{
    bool need_braces = dynamic_cast<SubtractionExpression*>(ae->right);
   if (need_braces)
    oss << "(";
    
   ae->left->accept(this);
   oss << "+";
   ae->right->accept(this);
   if (need_braces)
    oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression* se)
{
   bool need_braces = dynamic_cast<SubtractionExpression*>(se->right);
   if (need_braces)
    oss << "(";
    
   se->left->accept(this);
   oss << "-";
   se->right->accept(this);
   if (need_braces)
    oss << ")";

}


void ExpressionEvaluator::visit(DoubleExpression* de)
{
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression* ae)
{
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;
}

void ExpressionEvaluator::visit(SubtractionExpression* se)
{
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result = temp - result;
}