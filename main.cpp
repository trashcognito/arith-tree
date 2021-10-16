#include <iostream>
#include "arith.hpp"
int main(int argc, char *kwargs[]) {
    auto x = new Variable("x");
    auto f = *(*(*x + new Constant(1.0)) * (*x + new Constant(1.0))) / (*(*x + new Constant(2.0)) * (*x + new Constant(3.0)));

    std::cout << "Function: ";
    f->display(std::cout);
    auto df = f->derivative("x");
    std::cout << "\nDerivative: ";
    df->display(std::cout);
    std::cout << "\nOptimized: ";
    auto odf = df->optimize();
    odf->display(std::cout);
    std::cout << "\n";
    return 0;
}
