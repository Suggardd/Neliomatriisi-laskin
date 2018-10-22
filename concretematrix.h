#ifndef CONCRETESQUAREMATRIX_H_INCLUDED
#define CONCRETESQUAREMATRIX_H_INCLUDED

#include "Element.h"
#include "squarematrix.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

///Luokka ConcreteSquareMatrix, voidaan luoda matriiseja jotka käyttävät kokonaislukuja.
class ConcreteSquareMatrix : public SquareMatrix{

private:
    ///Jäsenmuuttujat
    unsigned int n;
    std::vector<std::vector<std::shared_ptr<IntElement>>> elements;

public:
    ///Tyhjä constructor.
    ConcreteSquareMatrix();
    ///\param std::string& str
    ///Varsinainen constructor, luo matriisin stringistä
    ConcreteSquareMatrix(const std::string& str);
    ///\param ConcreteSquareMatrix& m
    ///Copy constructor.
    ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
    ///\param ConcreteSquareMatrix&& m
    ///Move constructor.
    ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
    ///Virtuaalinen destructor.
    virtual ~ConcreteSquareMatrix() =default;

    ///\param std::vector<std::vector<std::shared_ptr<IntElement>>> v
    ///Asetetaan vektoriin arvo.
    void setVector(std::vector<std::vector<std::shared_ptr<IntElement>>> v);
    ///\param unsigned int num
    ///Asetetaan N.
    void setN(unsigned int num);

    ///Luokan operaattorit.
    ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
    bool operator==(const ConcreteSquareMatrix& m) const;

    ///\brief Tulostusoperaatiot.
    void print(std::ostream& o) const;
    std::string toString() const;

    SquareMatrix* clone() const;
    ConcreteSquareMatrix evaluate(const Valuation& v) const;


    ///\return ConcreteSquareMatrix
    ///Matriisin transpoosi.
    ConcreteSquareMatrix transpose() const;
};

#endif // CONCRETESQUAREMATRIX_H_INCLUDED
