#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "symbolicmatrix.h"
#include "concretematrix.h"
#include "compositematrix.h"
#include "squarematrix.h"
#include "Element.h"
#include <iostream>
#include <map>

TEST_CASE("matrix_tests", "[]"){

    SymbolicSquareMatrix olio1("[[1,x][4,y]]");
    ConcreteSquareMatrix olio3("[[1,2][3,4]]");
    ConcreteSquareMatrix olio4("[[2,3][4,5]]");
    CompositeSquareMatrix olio5(olio3, olio4, kertolasku, '*');

    std::map<char,int> kartta;
    kartta['x'] = 1;
    kartta['y'] = 2;

    ConcreteSquareMatrix olio2(olio1.evaluate(kartta));
    CHECK(olio2.toString() == "[[1,1][4,2]]" );
    olio2 *= olio3;
    CHECK(olio2.toString() == "[[4,6][10,16]]");

    CHECK(olio3.toString() == "[[1,2][3,4]]");
    olio3 *= olio4;
    CHECK(olio3.toString() == "[[10,13][22,29]]");

    ConcreteSquareMatrix com(olio5.evaluate(kartta));
    CHECK(com.toString() == "[[10,13][22,29]]");
    }
