// This program tracks stocks in a portfolio and utilizes hash tables to generate an array of linked chains
// Written by: Ian McAllister
// Date: 8/02/15
// Source: Class videos, C++ programming by D.S. Malik, discussion boards, stackoverflow
// Notes: Error check not incorporated.

#include <stdlib.h>
#include <iostream>
#include "hashTable.h"

using namespace std;

void displayMenu();
char getCommand();
void executeCmd(char command, hashTable& aHashTable);

void getSecurity(security& aSecurity);
void getString(char * prompt, char * input);


int main()
{
    
    //declare and initialize local variables
    char command = 'a';
    char fileName[] = "data.dat";
    hashTable portfolio(fileName);
    
    displayMenu();
    command = getCommand();
    
    while(command != 'q')
    {
        executeCmd(command, portfolio);
        displayMenu();
        command = getCommand();
    }
    
    portfolio.writeOut(fileName);
    cout << "\nThank you for using CSPM!" << endl << endl;
    return 0;
}

void displayMenu()
{
    cout << "\nImplemented by: Ian McAllister" << endl;
    cout << "\nWelcome to CS Portfolio Management System! "<< endl;
    cout << "\ta> add a security" << endl
    << "\tr> remove a security" << endl
    << "\tl> alter a security" << endl
    << "\ts> search for a security" << endl
    << "\td> display all the security" << endl
    << "\tq> quit the application" << endl << endl;
}

char getCommand()
{
    char cmd;
    cout << "Please enter your choice (a, r, l, s, d or q):";
    cin.clear();
    cin >> cmd;
    cin.ignore(100, '\n');
    return tolower(cmd);
}

void executeCmd(char command, hashTable& aHashTable)
{
    security aSecurity;
    char removalPrompt[65] = "\nPlease enter the symbol of the security you want to remove: ";
    char searchPrompt[65] = "\nPlease enter the symbol of the security you want to search: ";
    char tempSymbol[MAX_LEN];
    char tempName[MAX_LEN];
    char tempDate[MAX_LEN];
    char key[MAX_LEN];
    
    switch(command)
    {
        case 'a': getSecurity(aSecurity);
            aHashTable.add(aSecurity);
            cout << endl << "the security has been saved in the database. " << endl;
            break;
        case 'r': getString(removalPrompt, key);
            aHashTable.remove(key);
            cout << endl << key << " has been removed from the database. " << endl;
            break;
        case 'l': getSecurity(aSecurity);
            aSecurity.getSymbol(tempSymbol);
            aSecurity.getName(tempName);
            aSecurity.getDate(tempDate);
            if(aHashTable.modify(tempSymbol, aSecurity.getNetValue(), tempDate, aSecurity.getYearReturn()))
                cout << "Record sucessfully updated" << endl;
            else
                cout << "No record found by that symbol" << endl;
            break;
        case 's': getString(searchPrompt, key);
            if(aHashTable.retrieve (key, aSecurity))
            {
             cout << endl << "Information about " << key << ": " << endl << '\t' << aSecurity << endl;
            }
            else
            {
                cout << "No record found" << endl;
            }
            break;
        case 'd': aHashTable.display();
            break;
        default: cout << "illegal command!" << endl;
            break;
    }
}

void getSecurity(security& aSecurity)
{
    //declare and initialize local variables
    char tempChar[MAX_LEN];
    char blank[MAX_LEN] = { '\0' };
    char * symbol = NULL;
    char * name = NULL;
    float netValue;
    char * date = NULL;
    float yearReturn;
    
    cout << "\nPlease enter information about the security: " << endl;
    cout << "\tsymbol: ";
    cin.get(tempChar, 100, '\n');
    symbol = new char[strlen(tempChar + 1)];
    strcpy(symbol, tempChar);
    strcpy(tempChar, blank);
    cin.ignore(100, '\n');
    
    cout << "\tname: ";
    cin.get(tempChar, 100, '\n');
    name = new char[strlen(tempChar + 1)];
    strcpy(name, tempChar);
    strcpy(tempChar, blank);
    cin.ignore(100, '\n');
    
    cout << "\tnet value (usd): $";
    cin >> netValue;
    cin.ignore(100, '\n');
    
    cout << "\tdate (Mon, dd yyyy): ";
    cin.get(tempChar, 100, '\n');
    date = new char[strlen(tempChar + 1)];
    strcpy(date, tempChar);
    strcpy(tempChar, blank);
    cin.ignore(100, '\n');
    
    cout << "\tyear to date return (%): ";
    cin >> yearReturn;
    cin.ignore(100, '\n');
    
    aSecurity.setSymbol(symbol);
    aSecurity.setName(name);
    aSecurity.setNetValue(netValue);
    aSecurity.setDate(date);
    aSecurity.setYearReturn(yearReturn);
}

void getString(char * prompt, char * input)
{
    cout << prompt;
    cin.get(input, MAX_LEN, '\n');
    cin.ignore(100, '\n');
}


