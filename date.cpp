//
//  date.cpp
//  a03
//
//  Created by Ian McAllister on 7/23/15.
//  Copyright (c) 2015 com.IMEnt. All rights reserved.
//

#include "date.h"

//constructors
date::date() :day(0), month(0), year(0)
{
}

date::date(const int day, const int month, const int year) :day(0), month(0), year(0)
{
    setDay(day);
    setMonth(month);
    setYear(year);
}

//destructors
date::~date()
{
}

//accessors
int date::getDay()
{
    return day;
}

int date::getMonth()
{
    return month;
}

int date::getYear()
{
    return year;
}

//mutators
void date::setDay(const int day)
{
    this -> day = day;
}

void date::setMonth(const int month)
{
    this -> month = month;
}

void date::setYear(const int year)
{
    this -> year = year;
}

//operator overloading
ostream& operator<< (ostream& out, const date& aDate)
{
    switch (aDate.month) {
        case 1:
            out << "Jan";
            break;
        case 2:
            out << "Feb";
            break;
        case 3:
            out << "Mar";
            break;
        case 4:
            out << "Apr";
            break;
        case 5:
            out << "May";
            break;
        case 6:
            out << "Jun";
            break;
        case 7:
            out << "Jul";
            break;
        case 8:
            out << "Aug";
            break;
        case 9:
            out << "Sep";
            break;
        case 10:
            out << "Oct";
            break;
        case 11:
            out << "Nov";
            break;
        case 12:
            out << "Dec";
            break;
            
        default:
            break;
    }
    
    out << ", " << aDate.day << " " << aDate.year << endl;
    
    return out;
}

const date& date::operator=(const date& aDate)
{
    //if it is a self copy don't do anything
    if(this == &aDate)
        return *this;
    //make current object *this a copy of the passed in winery
    else
    {
        setDay(aDate.day);
        setMonth(aDate.month);
        setYear(aDate.year);
        return *this;
    }
}