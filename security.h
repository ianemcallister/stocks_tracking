// This program tracks stocks in a portfolio and utilizes hash tables to generate an array of linked chains
// Written by: Ian McAllister
// Date: 8/02/15
// Source: Class videos, C++ programming by D.S. Malik, discussion boards, stackoverflow
// Notes: Error check not incorporated.

#ifndef __a03__security__
#define __a03__security__

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class security
{
public:
    //constructors
    security();
    security(const security& aSecurity);        //copy constructor
    //destructors
    ~security();
    //accessors
    void getSymbol(char * symbol) const;
    void getName(char * name) const;
    float getNetValue();
    void getDate(char * date) const;
    float getYearReturn();
    //mutators
    void setSymbol(const char * symbol);
    void setName(const char * name);
    void setNetValue(const float netValue);
    void setDate(const char * date);
    void setYearReturn(const float yearReturn);
    
    //overloading
    friend ostream& operator<< (ostream& out, const security& aSecurity);
    const security& operator= (const security& aSecurity);
    
private:
    char * symbol;
    char * name;
    float netValue;
    char * date;
    float yearReturn;
};

#endif /* defined(__a03__security__) */
