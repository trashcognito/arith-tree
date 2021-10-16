#include "arith.hpp"
#include <cmath>
Addition *Arithmetic::operator+(Arithmetic *other) {
    return new Addition(this, other);
}
Subtraction *Arithmetic::operator-(Arithmetic *other) {
    return new Subtraction(this, other);
}
Multiplication *Arithmetic::operator*(Arithmetic *other) {
    return new Multiplication(this, other);
}
Division *Arithmetic::operator/(Arithmetic *other) {
    return new Division(this, other);
}
Variable::Variable(std::string name) : name(name) {

}
Arithmetic *Variable::derivative(std::string varname) {
    if (this->name == varname) {
        return new Constant(1.0);
    } else {
        return new Constant(0.0);
    }
}
double Variable::compute(std::map<std::string, double> &values) {
    return values[this->name];
}
ConstExponentiation::ConstExponentiation(Arithmetic *lhs, double rhs) : lhs(lhs), e(rhs) {

}
Arithmetic *ConstExponentiation::derivative(std::string varname) {
    return new Multiplication(
        new Constant(this->e),
        new ConstExponentiation(
            this->lhs,
            this->e - 1.0
        )
    );
}
double ConstExponentiation::compute(std::map<std::string, double> &values) {
    return pow(this->lhs->compute(values), this->e);
}
Constant::Constant(double c) : c(c) {

}
Arithmetic *Constant::derivative(std::string varname) {
    return new Constant(0.0);
}
double Constant::compute(std::map<std::string, double> &values) {
    return this->c;
}
Subtraction::Subtraction(Arithmetic *lhs, Arithmetic *rhs) : lhs(lhs), rhs(rhs) {

}
Arithmetic *Subtraction::derivative(std::string varname) {
    return (*this->lhs->derivative(varname) - this->rhs->derivative(varname));
}
double Subtraction::compute(std::map<std::string, double> &values) {
    return this->lhs->compute(values) - this->rhs->compute(values);
}
Division::Division(Arithmetic *lhs, Arithmetic *rhs) : lhs(lhs), rhs(rhs) {

}
Arithmetic *Division::derivative(std::string varname) {
    Arithmetic *upper_derivative = this->lhs->derivative(varname);
    Arithmetic *lower_derivative = this->rhs->derivative(varname);
    return new Division(
        new Subtraction(
            new Multiplication(upper_derivative, this->rhs),
            new Multiplication(lower_derivative, this->lhs)
        ),
        new Multiplication(
            this->rhs,
            this->rhs
        )
    );
}
double Division::compute(std::map<std::string, double> &values) {
    return this->lhs->compute(values) / this->rhs->compute(values);
}
Multiplication::Multiplication(Arithmetic *lhs, Arithmetic *rhs) : lhs(lhs), rhs(rhs) {

}
Arithmetic *Multiplication::derivative(std::string varname) {
    return new Addition(
        new Multiplication(
            this->lhs->derivative(varname),
            this->rhs
        ),
        new Multiplication(
            this->lhs,
            this->rhs->derivative(varname)
        )
    );
}
double Multiplication::compute(std::map<std::string, double> &values) {
    return this->lhs->compute(values) * this->rhs->compute(values);
}
Addition::Addition(Arithmetic *lhs, Arithmetic *rhs) : lhs(lhs), rhs(rhs) {
    
}
Arithmetic *Addition::derivative(std::string varname) {
    return new Addition(
        this->lhs->derivative(varname),
        this->rhs->derivative(varname)
    );
}

double Addition::compute(std::map<std::string, double> &values) {
    return this->lhs->compute(values) + this->rhs->compute(values);
}

