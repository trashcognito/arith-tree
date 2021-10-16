#include <sstream>
#include <string>
#include <map>

class Addition;
class Multiplication;
class Subtraction;
class Division;

class Arithmetic {
    public:
    virtual Arithmetic *derivative(std::string varname) = 0;
    virtual double compute(std::map<std::string, double> &values) = 0;    
    virtual void display(std::ostream &output) const = 0;

    Addition *operator+(Arithmetic *other);
    Multiplication *operator*(Arithmetic *other);
    Subtraction *operator-(Arithmetic *other);
    Division *operator/(Arithmetic *other);

    friend std::ostream & operator << (std::ostream &out, const Arithmetic &c);
};

class Addition : public Arithmetic {
    private:
    Arithmetic *lhs;
    Arithmetic *rhs;
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Addition(Arithmetic *lhs, Arithmetic *rhs);
};

class Multiplication : public Arithmetic {
    private:
    Arithmetic *lhs;
    Arithmetic *rhs;
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Multiplication(Arithmetic *lhs, Arithmetic *rhs);
};

class Division : public Arithmetic {
    private:
    Arithmetic *lhs;
    Arithmetic *rhs;
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Division(Arithmetic *lhs, Arithmetic *rhs);
};

class Subtraction : public Arithmetic {
    private:
    Arithmetic *lhs;
    Arithmetic *rhs;
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Subtraction(Arithmetic *lhs, Arithmetic *rhs);
};

class Constant : public Arithmetic {
    private:
    double c;
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Constant(double c);
};

class ConstExponentiation : public Arithmetic {
    private:
    Arithmetic *lhs;
    double e;
    
    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    ConstExponentiation(Arithmetic *lhs, double rhs);
};

class Variable : public Arithmetic {
    private:
    std::string name;

    public:
    virtual Arithmetic *derivative(std::string varname);
    virtual double compute(std::map<std::string, double> &values);
    virtual void display(std::ostream &output) const;
    Variable(std::string name);
};