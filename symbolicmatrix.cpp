#include "symbolicmatrix.h"
#include "Element.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <locale>


SymbolicSquareMatrix::SymbolicSquareMatrix(){
    n = 0;
}
///\param std::string str_m
///\return SymbolicSquareMatrix
///Luokan constructori, rakentaa matriisin stringist‰
SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& str_m){
    std::string alkio;
    std::string rivi;
    std::istringstream iss(str_m);
    std::vector<std::shared_ptr<Element>> vektori;
    std::string apustaja;
    std::locale loc;

    unsigned int i = 0;
    unsigned int j = 0;
    char c;
    n = 0;
    int num;
    char kir;

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
                   try{
                        kir = alkio[0];
                        if(std::isalpha(kir, loc) == false) throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");
                        std::shared_ptr<VariableElement> ie_ptr(new VariableElement(kir));
                        elements[i].push_back(ie_ptr);
                   }
                   catch(std::invalid_argument ia){
                   throw std::invalid_argument("Virheellinen syote! Tarkista syotetun matriisin oikeellisuus");}
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
///\param SymbolicSquareMatrix m
///Copy constructor
///
SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m){

    std::vector<std::shared_ptr<Element>> rivi;
    n = m.n;
    for(unsigned int i = 0; i < n; i++){
        elements.push_back(rivi);
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter){
            elements[i].push_back(std::shared_ptr<Element>((*(*iter)).clone()));
        }
    }
}


///
///\param SymbolicSquareMatrix m
///Move constructor.
///
SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m){
    elements = std::move(m.elements);
    n = m.n;
}

///
///\param SymbolicSquareMatrix matriisi m
///\return SymbolicSquareMatrix matriisi m
///= operaattori
///
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m){

if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}

    int j;

    for(unsigned int i = 0; i < n; i++){
        j=0;
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter, j++){
            elements[i][j] = *iter;
        }

    }
    return *this;
}

///\param SymbolicSquareMatrix m
///\return SymbolixSquareMatrix
///Move-operaattori
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m){
    n = m.n;
    elements = std::move(m.elements);
    return *this;
}

///\return SymbolicSquareMatrix
///Matriisin transpoosi, k‰ytet‰‰n kertolaskussa
SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const{

    SymbolicSquareMatrix matr;
    unsigned int i = 0;
    std::vector<std::shared_ptr<Element>> rivi;

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
    matr.n = n;
    return matr;
}

///\param SymbolicSquareMatrix m
///\return bool
///Vertailuoperaattori ==
bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const{

    if (n != m.n){
        throw(std::out_of_range("Dimensiot eiv‰t t‰sm‰‰"));}

    int j;

    for(unsigned int i = 0; i < n; i++){
        j=0;
        for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); ++iter, j++){
            if(elements[i][j] == *iter) continue;
            throw("Virhe!");
            return false;
        }

    }
    return true;
}
///\param ostream o
///Tulostaa matriisin, k‰ytt‰‰ toString-metodia
void SymbolicSquareMatrix::print(std::ostream& o) const{

    o << toString();

}

///\return std::string
///Muuttaa matriisin stringiksi jotta se voidaan tulostaa
std::string SymbolicSquareMatrix::toString() const{

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
///\param Valuation val
///\return ConcreteSquareMatrix matr
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& val) const{

    ConcreteSquareMatrix matr;
    unsigned int i = 0;
    int k = 0;
    std::vector<std::shared_ptr<IntElement>> rivi;
    std::vector<std::vector<std::shared_ptr<IntElement>>> elem;

    while(i < n){
        elem.push_back(rivi);
        i++;
    }

    i=0;
    for(auto iter1: this->elements){
        for(auto iter2: iter1){
            k = iter2->evaluate(val);
            std::shared_ptr<IntElement> p (new IntElement(k));
            elem[i].push_back(p);
            }
        i++;
    }
matr.setVector(elem);
matr.setN(n);
return matr;

}

SquareMatrix* SymbolicSquareMatrix::clone() const{
    return new SymbolicSquareMatrix(*this);
}

