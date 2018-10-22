#include "Element.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>


int val;

///Tyhjä constructor
IntElement::IntElement(): val(0){

}

///\param kokonaisluku v
///luokan constructor
IntElement::IntElement(int v) :val(v){

}

///\return kokonaisluku
///Luokan get-funktio, palauttaa kokonaisluvun
int IntElement::getVal() const{
    return val;
}

///\param kokonaisluku
///Luokan set-funktio, asettaa kokonaisluvun v muuttujalle val
void IntElement::setVal(int v){
    val = v;
}

///\return std::string
///Palauttaa IntElementin stringinä
std::string IntElement::toString() const{
    return std::to_string(val);
}

///\return IntElement
///Luo kopion IntElementistä
IntElement* IntElement::clone() const{
    return new IntElement(val);
}

int IntElement::evaluate(const Valuation& v) const{
    return val;
}

///\param IntElement i
///\return Yhteenlaskettu IntElement
///Yhteenlasku operaattori
IntElement& IntElement::operator+=(const IntElement& i){
    val = val + i.val;
    return *this;
}
///\param IntElement i
///return vähennyslaskettu IntElement
///Vähennyslasku operaattori
IntElement& IntElement::operator-=(const IntElement& i){
    val = val - i.val;
    return *this;
}
///\param IntElement i
///\return Kertolaskettu IntElement
///Kertolasku operaattori
IntElement& IntElement::operator*=(const IntElement& i){
    val = val * i.val;
    return *this;
}

bool IntElement::operator==(const IntElement& i) const{
    if(val == i.val) return true;
    return false;
}

char var;

///Tyhjä constructor
VariableElement::VariableElement(): var('x'){

}

///VariableElement-luokan constructor
VariableElement::VariableElement(char v) :var(v){

}


///\return char
///Palauttaa char v
char VariableElement::getVal(){
    return var;
}

///\param char v
///Asettaa char v arvon
void VariableElement::setVal(char v){
    var = v;
}

///\return
///
Element* VariableElement::clone() const{
    return new VariableElement(var);
}

///\return String
///Muuttaa stringiksi ja palauttaa
std::string VariableElement::toString() const{
    return std::string(1, var);
}

///\param muuttuja valuation V
///\return int
///
int VariableElement::evaluate(const Valuation& v) const{

    auto num = v.find(var);
    if(num == v.end()){
        throw "Virhe!";
    }
    return num->second;
}

///\param VariableElement i
///\return bool
///Vertailuoperaattori
bool VariableElement::operator==(const VariableElement& i) const{
    if(var == i.var) return true;
    return false; 
}
                        ////////////////////////////////////////////////
                        ////////////Yhteiset operaattorit///////////////
                        ////////////////////////////////////////////////
///\param IntElement i, IntElement j
///\return IntElement
///Kahden IntElementin summa
IntElement operator+(const IntElement& i, const IntElement& j){
    IntElement el1(i.getVal());
    el1+=j;
    return el1;
}

///\param IntElement i, IntElement j
///\return IntElement
///Kahden IntElementin erotus
IntElement operator-(const IntElement& i, const IntElement& j){
    IntElement el1(i.getVal());
    el1-=j;
    return el1;
}
///\param IntElement i, IntElement j
///\return IntElement
///Kahden IntElementin tulo
IntElement operator*(const IntElement& i, const IntElement& j){
    IntElement el1(i.getVal());
    el1*=j;
    return el1;
}

///\param ostream o, IntElement i
///\return ostream
///Tulostus operaatori matriisin tulostusta varten.
std::ostream& operator<<(std::ostream& o, const Element& i){

    o << i.toString();
    return o;

}
