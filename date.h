//
//  date.h
//  a03
//
//  Created by Ian McAllister on 7/23/15.
//  Copyright (c) 2015 com.IMEnt. All rights reserved.
//

#ifndef __a03__date__
#define __a03__date__

#include <stdio.h>
#include <fstream>

using namespace std;

class date
{
public:
    //constructors
    date();
    date(const int day, const int month, const int year);
    //destructors
    ~date();
    //accessors
    int getDay();
    int getMonth();
    int getYear();
    //mutators
    void setDay(const int day);
    void setMonth(const int month);
    void setYear(const int year);
    
    //operator overloading
    friend ostream& operator<< (ostream& out, const date& aDate);
    const date& operator=(const date& aDate);      //overloard assignment opperator
    
private:
    int day;
    int month;
    int year;
};

#endif /* defined(__a03__date__) */
