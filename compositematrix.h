#ifndef COMPOSITEMATRIX_H_INCLUDED
#define COMPOSITEMATRIX_H_INCLUDED

#include "squarematrix.h"
#include "Element.h"
#include "concretematrix.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>


class CompositeSquareMatrix : public SquareMatrix {

private:
    ///Jäsenmuuttujat
    std::shared_ptr<SquareMatrix> oprnd1;
    std::shared_ptr<SquareMatrix> oprnd2;
    std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> oprtor;
    char op_sym;

public:
    ///Constructori
    CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2,
                          const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)>& opr, char ops);
    ///Move constructor
    CompositeSquareMatrix(const CompositeSquareMatrix& m);
    ///Copy constructor
    CompositeSquareMatrix(CompositeSquareMatrix&& m);
    ///Destructor
    virtual ~CompositeSquareMatrix() =default;

    ///Sijoitus- ja siirto-operaattorit
    CompositeSquareMatrix& operator=(const CompositeSquareMatrix&);
    CompositeSquareMatrix& operator=(CompositeSquareMatrix&&);

    SquareMatrix* clone() const;

    void print(std::ostream& os) const;

    std::string toString() const;

    ConcreteSquareMatrix evaluate(const Valuation& v) const;
};

ConcreteSquareMatrix kertolasku(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);


#endif // COMPOSITEMATRIX_H_INCLUDED
