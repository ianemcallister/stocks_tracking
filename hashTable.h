// This program tracks stocks in a portfolio and utilizes hash tables to generate an array of linked chains
// Written by: Ian McAllister
// Date: 8/02/15
// Source: Class videos, C++ programming by D.S. Malik, discussion boards, stackoverflow
// Notes: Error check not incorporated.

#ifndef __a03__hashTable__
#define __a03__hashTable__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "security.h"

using namespace std;

const int MAX_LEN = 101;

class hashTable
{
public:
    //constructors
    hashTable();
    hashTable(char * fileName);
    hashTable(const hashTable& aTable);
    //destructors
    ~hashTable();
    //accessors
    void display(void) const;
    void monitor(int index);
    void writeOut(char * fileName);
    //mutators
    void add(const security& aSecurity);
    bool remove(char * symbol);
    bool modify(char * symbol, float newNetValue, char * newDate, float newYearReturn);
    bool retrieve(char * symbol, security& aSecurity);
    
    //opperator overload
    const hashTable& operator= (const hashTable& aTable);
    
private:
    struct node
    {
        security item;
        node * next;
        
        node(const security& aSecurity)
        {
            item = aSecurity;
            next = NULL;
        }
        
    };
    
    node ** table;
    int capacity;
    int size;
    
    const static int DEFAULT_CAPACITY = 11;
    
    int collisions[DEFAULT_CAPACITY];
    
    void destroyTable();
    void initializeTable();
    int calculateIndex(char * key)const;
};

#endif /* defined(__a03__hashTable__) */
