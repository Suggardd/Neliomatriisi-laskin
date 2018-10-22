#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

#include "concretematrix.h"
#include "Element.h"


ConcreteSquareMatrix::ConcreteSquareMatrix(){
   n = 0;
}

///
///\param string
///Constructori joka luo olion stringist‰, tallettaa vektoriin smart pointtereita
///
ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& str){

    std::string alkio;
    std::string rivi;
    std::istringstream iss(str);
    std::vector<std::shared_ptr<IntElement>> vektori;
    std::string apustaja;

    unsigned int i = 0;
    unsigned int j = 0;
    char c;
    n = 0;
    int num;

    iss >> c;
    if(c != '[') throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
    iss >> c;
    if(c != '[') throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");

    while(!iss.eof()){
        elements.push_back(vektori);
        j = 0;
        getline(iss, rivi, ']');
        std::istringstream temp(rivi);

        while(!temp.eof()){
           getline(temp, alkio, ',');
           try{
               num = std::stoi(alkio);
               std::shared_ptr<IntElement> ie_ptr(new IntElement(num));
               elements[i].push_back(ie_ptr);
               }
               catch(const std::invalid_argument& ia){
                   throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
                   }
                   j++;
            }
        if (n == 0){
            n = j;
            iss >> c;
            i++;
        }
        else if (n != j){
            throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
        }
        else{
            iss >> c;
            i++;
            apustaja = iss.str();
            std::cout << apustaja << std::endl;
            if(apustaja.back() == ']'){
                    apustaja.pop_back();
                    if(apustaja.back() != ']'){
                        throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
                    }
                if(i == n){
                    iss >> c;
                    if(iss.eof()){
                        break;
                    }
                }
              }
            }
        }
        if(!iss.eof()){
            throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
        }
}
///
///\param ConcreteSquareMatrix m
///Copy constructor
///
ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m){
    std::vector<std::shared_ptr<IntElement>> rivi;
    n = m.n;
    for(unsigned int i = 0; i < n; i++){
        elements.push_back(rivi);
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter){
           elements[i].push_back(std::shared_ptr<IntElement>((*(*iter)).clone()));
        }
    }
}
///
///\param ConcreteSquareMatrix m
///Move constructor.
///
ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m){
    elements = std::move(m.elements);
    n = m.n;
}


///\param ConcreteSquareMatrix matriisi m
///\return ConcreteSquareMatrix matriisi m
///+= operaattori. Suorittaa + laskun matriiseille
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m){
    if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}

    int j;

    for(unsigned int i = 0; i < n; i++){
        j=0;
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter, j++){
            *elements[i][j] += *(*iter);
        }

    }
    return *this;
}
///\param ConcreteSquareMatrix matriisi m
///\return ConcreteSquareMatrix matriisi m
///-= operaattori. Suorittaa - laskun matriiseille
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m){
    if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}

    int j;

    for(unsigned int i = 0; i < n; i++){
        j=0;
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter, j++){
            *elements[i][j] -= *(*iter);
        }

    }
    return *this;
}
///\param ConcreteSquareMatrix matriisi m
///\return ConcreteSquareMatrix matriisi m
///*= operaattori. Suorittaa * laskun matriiseille. K‰ytt‰‰ matriisin transpoosia.
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m){
    if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}
    ConcreteSquareMatrix apu;
    ConcreteSquareMatrix transp(m.transpose());
    IntElement elem(0);

    std::vector<std::shared_ptr<IntElement>> rivi;

    unsigned int i = 0;
    unsigned int j = 0;

    while(i < n){
        apu.elements.push_back(rivi);
        i++;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){

            auto iter1 = elements[i].begin();
            auto iter2 = transp.elements[j].begin();

            for( ; iter1 != elements[i].end(); ++iter1, ++iter2){
                elem += (*(*iter1) * *(*iter2));
                }
                apu.elements[i].push_back(std::shared_ptr<IntElement>(elem.clone()));
                elem.setVal(0);
        }
    }
    elements = apu.elements;

    return *this;
}
///\param ConcreteSquareMatrix matriisi m
///\return ConcreteSquareMatrix matriisi m
///= operaattori.
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& m){
if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}

    unsigned int j;

    for(unsigned int i = 0; i < n; i++){
        j=0;
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter, j++){
            elements[i][j] = *iter;
        }

    }
    return *this;
}

///\param C.SquareMatrix m
///\return ConcreteSquareMatrix
///Move operaattori
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& m){
    n = m.n;
    elements = std::move(m.elements);
    return *this;
}
///
///\param ConcreteSquareMatrix matriisi m
///\return boolean
///Vertailu ==(ISIS) operaattori.
///
bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const{

    if(m.toString() == toString()){
        return true;
    }
return false;

}


///\param ostream o
///Tulostaa matriisin.
void ConcreteSquareMatrix::print(std::ostream& o) const{

    o << toString();

}
///\return string
///Muuntaa matriisin string muotoon.
std::string ConcreteSquareMatrix::toString() const{

    std::stringstream ss;
    int i;

    ss << "[[";
    for(i=0; i<n; i++){
        for(auto iter = elements[i].begin(); iter != elements[i].end(); ++iter){
            ss << ((*(*iter)).toString());
            if(iter+1 != elements[i].end()){
                ss << ',';
            }
        }
    if(i+1 != n){
        ss << "][";
    }
}
ss << "]]";
return ss.str();
}
///\return ConcreteSquareMatrix
///Matriisin transpoosi. K‰ytet‰‰n kertolaskussa.
ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const{

    ConcreteSquareMatrix matr;
    unsigned int i = 0;
    std::vector<std::shared_ptr<IntElement>> rivi;

    while(i < n){
        matr.elements.push_back(rivi);
        i++;
    }

    for(auto iter1: this->elements){
        i=0;
        for(auto iter2: iter1){
            matr.elements[i].push_back(iter2);
            i++;
            }
    }

    return matr;
}

///\param vektori v
///Asettaa elements = v
void ConcreteSquareMatrix::setVector(std::vector<std::vector<std::shared_ptr<IntElement>>> v){
    elements = v;
}

///\param int num
///Asettaa int n = num
void ConcreteSquareMatrix::setN(unsigned int num){
    n = num;
}

SquareMatrix* ConcreteSquareMatrix::clone() const{
    return new ConcreteSquareMatrix(*this);
}

ConcreteSquareMatrix ConcreteSquareMatrix::evaluate(const Valuation& v) const{
    return *this;
}




