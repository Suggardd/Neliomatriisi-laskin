#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED
#include "Element.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

class ConcreteSquareMatrix;

///Abstrakti luokka SquareMatrix.
class SquareMatrix {

public:
    ///Luokan virtuaaliset funktiot.
    virtual ~SquareMatrix() =default;
    virtual SquareMatrix* clone() const =0;
    virtual std::string toString() const =0;
    virtual ConcreteSquareMatrix evaluate(const Valuation& v) const =0;
    virtual void print(std::ostream& o) const =0;
};

std::ostream& operator<<(std::ostream& o, const SquareMatrix& sm);






#endif // SQUAREMATRIX_H_INCLUDED
