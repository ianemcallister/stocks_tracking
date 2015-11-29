// This program tracks stocks in a portfolio and utilizes hash tables to generate an array of linked chains
// Written by: Ian McAllister
// Date: 8/02/15
// Source: Class videos, C++ programming by D.S. Malik, discussion boards, stackoverflow
// Notes: Error check not incorporated.

#include "security.h"

//constructors
security::security() :symbol(NULL), name(NULL), netValue(0.0), date(NULL), yearReturn(0.0)
{
}

security::security(const security& aSecurity) :symbol(NULL), name(NULL), netValue(0.0), date(NULL), yearReturn(0.0)
{
    setSymbol(aSecurity.symbol);
    setName(aSecurity.name);
    setNetValue(aSecurity.netValue);
    setDate(aSecurity.date);
    setYearReturn(aSecurity.yearReturn);
}

const security& security::operator= (const security& aSecurity)
{
    //if it is a self copy don't do anything
    if(this == &aSecurity)
        return *this;
    //make current object *this a copy of the passed in winery
    else
    {
        setSymbol(aSecurity.symbol);
        setName(aSecurity.name);
        setNetValue(aSecurity.netValue);
        setDate(aSecurity.date);
        setYearReturn(aSecurity.yearReturn);
        return *this;
    }
}

//destructors
security::~security()
{
    if(symbol)
    {
        delete [] symbol;
        symbol = NULL;
    }
    if(name)
    {
        delete name;
        name = NULL;
    }
    if(date)
    {
        delete date;
        date = NULL;
    }
}

//accessors
void security::getSymbol(char * symbol) const
{
    strcpy(symbol, this -> symbol);
}

void security::getName(char * name) const
{
    strcpy(name, this -> name);
}

float security::getNetValue()
{
    return netValue;
}

void security::getDate(char * date) const
{
    strcpy(date, this -> date);
}

float security::getYearReturn()
{
    return yearReturn;
}

//mutators
void security::setSymbol(const char * symbol)
{
    //release the existing memory if there is any
    if(this -> symbol)
    {
        delete [] this -> symbol;
        this -> symbol = NULL;
    }
    
    
    //set new symbol
    this -> symbol = new char[strlen(symbol + 1)];
    strcpy(this -> symbol, symbol);
}

void security::setName(const char * name)
{
    //release the existing memory if there is any
    if(this -> name)
    {
        delete [] this -> name;
        this -> name = NULL;
    }
    
    
    //set new name
    this -> name = new char[strlen(name + 1)];
    strcpy(this -> name, name);
}

void security::setNetValue(const float netValue)
{
    this -> netValue = netValue;
}

void security::setDate(const char * date)
{
    //release the existing memory if there is any
    if(this -> date)
    {
        delete [] this -> date;
        this -> date = NULL;
    }
    
    
    //set new date
    this -> date = new char[strlen(date + 1)];
    strcpy(this -> date, date);
}

void security::setYearReturn(const float yearReturn)
{
    this -> yearReturn = yearReturn;
}

//overloading
ostream& operator<< (ostream& out, const security& aSecurity)
{
    out << aSecurity.symbol << ";"<< aSecurity.name << ";$"<< aSecurity.netValue << ";"<< aSecurity.date;
    out << ";"<< aSecurity.yearReturn << "%" << endl;
    return out;
}


