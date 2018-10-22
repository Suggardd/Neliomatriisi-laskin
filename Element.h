#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>


using Valuation = std::map<char,int>;

///Abstrakti luokka element.
class Element{
    ///Virtuaaliset public funktiot.
    public:
        virtual ~Element()=default;
        virtual Element* clone() const =0;
        virtual std::string toString() const =0;
        virtual int evaluate(const Valuation& val) const =0;

};

class VariableElement : public Element{

private:
    char var;

public:
    ///Tyhjä constructor, varsinainen constructor ja destructor.
    VariableElement();
    VariableElement(char v);
    virtual ~VariableElement() =default;

    ///Luokan metodit
    char getVal();
    void setVal(char v);
    Element* clone() const;
    std::string toString() const;
    int evaluate(const Valuation& v) const;
    ///Vertailuoperaattori
    bool operator==(const VariableElement& i) const;
};

class IntElement : public Element {

private:
    int val;

public:
    ///Tyhjä constructor, varsinainen constructor ja destructor.
    IntElement();
    IntElement(int v);
    virtual ~IntElement() = default;

    ///Luokan metodit
    int getVal() const;
    void setVal(int v);
    IntElement* clone() const override;
    std::string toString() const override;

    ///Laskentaoperaattorit.
    IntElement& operator+=(const IntElement& i);
    IntElement& operator-=(const IntElement& i);
    IntElement& operator*=(const IntElement& i);
    bool operator==(const IntElement& i) const;
    int evaluate(const Valuation& v) const;
};


///Yhteiset operaattorit.
IntElement operator+(const IntElement& i, const IntElement& j);
IntElement operator-(const IntElement& i, const IntElement& j);
IntElement operator*(const IntElement& i, const IntElement& j);
std::ostream& operator<<(std::ostream& o, const Element& i);



#endif // ELEMENT_H_INCLUDED
