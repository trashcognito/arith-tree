#include "arith.hpp"
#include <cmath>

Arithmetic *Addition::optimize() const {
    auto lhs = this->lhs->optimize();
    auto rhs = this->rhs->optimize();

    auto lconst = dynamic_cast<Constant *>(lhs);
    auto rconst = dynamic_cast<Constant *>(rhs);

    if (lconst) {
        if (rconst) {
            //both constant, simply compute value
            return new Constant(lconst->c + rconst->c);
        } else {
            //left side constant, right side not constant
            if (lconst->c == 0.0) {
                return rhs;
            }
            return new Addition(lhs, rhs);
        }
    } else if (rconst) {
        //right side constant, left side not constant
        if (rconst->c == 0.0) {
            return lhs;
        }
        return new Addition(lhs, rhs);
    }
    //no constants anywhere, no further optimizations can be done
    return new Addition(lhs, rhs);
}
Arithmetic *Multiplication::optimize() const {
    auto lhs = this->lhs->optimize();
    auto rhs = this->rhs->optimize();

    auto lconst = dynamic_cast<Constant *>(lhs);
    auto rconst = dynamic_cast<Constant *>(rhs);

    if (lconst) {
        if (rconst) {
            //both constant, simply compute value
            return new Constant(lconst->c * rconst->c);
        } else {
            //left side constant, right side not constant
            if (lconst->c == 0.0) {
                return new Constant(0.0);
            } else if (lconst->c == 1.0) {
                return rhs;
            }
            return new Multiplication(lhs, rhs);
        }
    } else if (rconst) {
        //right side constant, left side not constant
        if (rconst->c == 0.0) {
            return new Constant(0.0);
        } else if (rconst->c == 1.0) {
            return lhs;
        }
        return new Multiplication(lhs, rhs);
    }
    //no constants anywhere, no further optimizations can be done
    return new Multiplication(lhs, rhs);
}
Arithmetic *Subtraction::optimize() const {
    auto lhs = this->lhs->optimize();
    auto rhs = this->rhs->optimize();

    auto lconst = dynamic_cast<Constant *>(lhs);
    auto rconst = dynamic_cast<Constant *>(rhs);

    if (lconst) {
        if (rconst) {
            //both constant, simply compute value
            return new Constant(lconst->c - rconst->c);
        }
    } else if (rconst) {
        //right side constant, left side not constant
        if (rconst->c == 0.0) {
            return lhs;
        }
        return new Subtraction(lhs, rhs);
    }
    //no constants anywhere, no further optimizations can be done
    return new Subtraction(lhs, rhs);
}
Arithmetic *Division::optimize() const {
    auto lhs = this->lhs->optimize();
    auto rhs = this->rhs->optimize();

    auto lconst = dynamic_cast<Constant *>(lhs);
    auto rconst = dynamic_cast<Constant *>(rhs);

    if (lconst) {
        if (rconst) {
            //both constant, simply compute value
            return new Constant(lconst->c / rconst->c);
        } else {
            //left side constant, right side not constant
            if (lconst->c == 0.0) {
                return new Constant(0.0);
            }
            return new Division(lhs, rhs);
        }
    } else if (rconst) {
        //right side constant, left side not constant
        if (rconst->c == 1.0) {
            return lhs;
        }
        return new Addition(lhs, rhs);
    }
    //no constants anywhere, no further optimizations can be done
    return new Division(lhs, rhs);
}
Arithmetic *Constant::optimize() const {
    return new Constant(this->c);
}
Arithmetic *ConstExponentiation::optimize() const {
    auto lhs = this->lhs->optimize();
    auto lconst = dynamic_cast<Constant *>(lhs);
    if (lconst) {
        return new Constant(std::pow(lconst->c, this->e));
    }
    return new ConstExponentiation(lhs, this->e);
}
Arithmetic *Variable::optimize() const {
    return new Variable(this->name);
}