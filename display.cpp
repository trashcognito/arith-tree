#include "arith.hpp"

void Addition::display(std::ostream &output) const {
    output << "(";
    this->lhs->display(output);
    output << " + ";
    this->rhs->display(output);
    output << ")";
}
void Multiplication::display(std::ostream &output) const {
    output << "(";
    this->lhs->display(output);
    output << " * ";
    this->rhs->display(output);
    output << ")";
}
void Division::display(std::ostream &output) const {
    output << "(";
    this->lhs->display(output);
    output << " / ";
    this->rhs->display(output);
    output << ")";
}
void Subtraction::display(std::ostream &output) const {
    output << "(";
    this->lhs->display(output);
    output << " - ";
    this->rhs->display(output);
    output << ")";
}
void Constant::display(std::ostream &output) const {
    output << this->c;
}
void ConstExponentiation::display(std::ostream &output) const {
    output << "(";
    this->lhs->display(output);
    output << " ^ ";
    output << this->e << ")";
}
void Variable::display(std::ostream &output) const {
    output << this->name;
}

std::ostream & operator << (std::ostream &out, const Arithmetic &c)
{
    c.display(out);
}