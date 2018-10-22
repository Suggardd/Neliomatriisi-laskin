#include "compositematrix.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>

///\param monta luokkaa
///Luokan constructor.
CompositeSquareMatrix::CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2,
                          const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&,
                                                                   const ConcreteSquareMatrix&)>& opr, char ops)
{
oprnd1 = std::shared_ptr<SquareMatrix>(op1.clone());
oprnd2 = std::shared_ptr<SquareMatrix>(op2.clone());
oprtor = opr;
op_sym = ops;
}

///\param CompositeSquareMatrix m
///Copy constructor.
CompositeSquareMatrix::CompositeSquareMatrix(const CompositeSquareMatrix& m){
oprnd1 = m.oprnd1;
oprnd2 = m.oprnd2;
oprtor = m.oprtor;
op_sym = m.op_sym;
}
///\param CompositeSquareMatrix m
///Move constructor.
CompositeSquareMatrix::CompositeSquareMatrix(CompositeSquareMatrix&& m){
oprnd1 = std::move(m.oprnd1);
oprnd2 = std::move(m.oprnd2);
oprtor = std::move(m.oprtor);
op_sym = std::move(m.op_sym);

}

///\param CompositeSquareMatrix& csm
///\return Composite SquareMatrix
///\brief move operator.
CompositeSquareMatrix& CompositeSquareMatrix::operator=(const CompositeSquareMatrix& csm){
oprnd1 = csm.oprnd1;
oprnd2 = csm.oprnd2;
oprtor = csm.oprtor;
op_sym = csm.op_sym;
return *this;
}
///\param CompositeSquareMatrix& csm
///\return Composite SquareMatrix
///\brief copy operator.
CompositeSquareMatrix& CompositeSquareMatrix::operator=(CompositeSquareMatrix&& csm){
oprnd1 = std::move(csm.oprnd1);
oprnd2 = std::move(csm.oprnd2);
oprtor = std::move(csm.oprtor);
op_sym = std::move(csm.op_sym);
return *this;
}
///\return SquareMatrix* pointteri
///\brief palauttaa pointterin CSM-olioon.
SquareMatrix* CompositeSquareMatrix::clone() const{
    return new CompositeSquareMatrix(*this);
}
///\param std::ostream& os
///\brief Tulostaa matriisin.
void CompositeSquareMatrix::print(std::ostream& os) const{
    os << '(' << *oprnd1 << op_sym << *oprnd2 << ')';
}
///\return std::string
///\brief palauttaa matriisin stringinä.
std::string CompositeSquareMatrix::toString() const{
    std::stringstream ss;
    ss << '(' << *oprnd1 << op_sym << *oprnd2 << ')';
    return ss.str();
}
///\param const Valuation& v
///\return ConcreteSquareMatrix
///\brief Palauttaa kahden matriisin lasketun tuloksen.
ConcreteSquareMatrix CompositeSquareMatrix::evaluate(const Valuation& v) const{
    return oprtor(oprnd1->evaluate(v), oprnd2->evaluate(v));
}
///\param std::ostream& o, const SquareMatrix& sm
///\return std::ostream&
///\brief tulostusoperaattori.
std::ostream& operator<<(std::ostream& o, const SquareMatrix& sm){
    return o << sm.toString();
}

///\brief apufunktio testejä varten.
ConcreteSquareMatrix kertolasku(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
    ConcreteSquareMatrix c(m1);
    c*=m2;
    return c;
}
