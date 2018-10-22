#ifndef SYMBOLICSQUAREMATRIX_H_INCLUDED
#define SYMBOLICSQUAREMATRIX_H_INCLUDED

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

///Luokka SymbolicSquareMatrix, voidaan luoda matriiseja jotka sisältävät sekä kokonaislukuja että muuttujia.
class SymbolicSquareMatrix : public SquareMatrix{


private:
    ///Jäsenmuuttujat
    unsigned int n;
    std::vector<std::vector<std::shared_ptr<Element>>> elements;

public:
    ///Tyhjä constructor.
    SymbolicSquareMatrix();
    ///\param std::string& str_m
    ///Varsinainen constructor, luo matriisin stringistä
    SymbolicSquareMatrix(const std::string& str_m);
    ///\param ConcreteSquareMatrix& m
    ///Copy constructor.
    SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
    ///\param ConcreteSquareMatrix&& m
    ///Move constructor.
    SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
    ///Virtuaalinen destructor.
    virtual ~SymbolicSquareMatrix() =default;

    ///\param const SymbolicSquareMatrix& m
    ///Sijoitusoperaattori.
    SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
    ///\param SymbolicSquareMatrix&& m
    ///Move operaattori.
    SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);
    ///\return SymbolicSquareMatrix
    ///Matriisin transpoosi.
    SymbolicSquareMatrix transpose() const;
    ///\param const SymbolicSquareMatrix& m
    ///\return bool
    ///Vertailuoperaattori.
    bool operator==(const SymbolicSquareMatrix& m) const;

    ///Tulostusoperaattorit
    void print(std::ostream& o) const;
    std::string toString() const;

    ///\param const Valuation& val
    ///\return ConcreteSquareMatrix
    ///Evaluate.
    ConcreteSquareMatrix evaluate(const Valuation& val) const;

    SquareMatrix* clone() const;

};

#endif // SYMBOLICSQUAREMATRIX_H_INCLUDED
