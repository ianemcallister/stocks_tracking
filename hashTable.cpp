// This program tracks stocks in a portfolio and utilizes hash tables to generate an array of linked chains
// Written by: Ian McAllister
// Date: 8/02/15
// Source: Class videos, C++ programming by D.S. Malik, discussion boards, stackoverflow
// Notes: Error check not incorporated.

#include "hashTable.h"

//initialize
void hashTable::initializeTable()
{
    table = new node*[DEFAULT_CAPACITY];
    
    //initialize each head of the individual linked list
    for(int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        table[i] = NULL;
    }
}

//constructors
hashTable::hashTable() :table(NULL), capacity(DEFAULT_CAPACITY), size(0)
{
    initializeTable();
    
    //collision monitoring
    for(int i = 0; i < DEFAULT_CAPACITY; i++)
        collisions[i] = 0;
}

hashTable::hashTable(char * fileName) :table(NULL), capacity(DEFAULT_CAPACITY), size(0)
{
    //declare and initialize local variables
    ifstream inFile;
    security aSecurity;
    char tempSymbol[MAX_LEN];
    char tempName[MAX_LEN];
    float tempNetValue;
    char tempDate[MAX_LEN];
    float tempYearReturn;

    //collision monitoring
    for(int i = 0; i < DEFAULT_CAPACITY; i++)
        collisions[i] = 0;
    
    initializeTable();
    
    //initialize the table with the records in the file
    inFile.open(fileName);
    if(!inFile)
    {
        inFile.clear();
        cout << endl << "Failed to open " << fileName << " for input!" << endl << endl;
        exit(1);
    }
    
    //load file data into member variables, name first
    inFile.get(tempSymbol, MAX_LEN, ';');
    
    //loop through file until all data is read
    while (!inFile.eof())
    {
        //clear buffer
        inFile.ignore(MAX_LEN, ';');
        //then location
        inFile.get(tempName, MAX_LEN, ';');
        //clear buffer
        inFile.ignore(MAX_LEN, ';');
        //then year
        inFile>>tempNetValue;
        //clear buffer
        inFile.ignore(MAX_LEN, ';');
        //then acres
        inFile.get(tempDate, MAX_LEN, ';');
        //clear buffer
        inFile.ignore(MAX_LEN, ';');
        //then rating
        inFile>>tempYearReturn;
        //clear buffer
        inFile.ignore(MAX_LEN, '\n');
        
        //load all temp values in to place holder object
        aSecurity.setSymbol(tempSymbol);
        aSecurity.setName(tempName);
        aSecurity.setNetValue(tempNetValue);
        aSecurity.setDate(tempDate);
        aSecurity.setYearReturn(tempYearReturn);
        
        //add task to list
        add(aSecurity);
        
        //start next record
        inFile.get(tempSymbol, MAX_LEN, ';');
    } //out of loop
    
    //close the resource file
    inFile.close();

}

hashTable::hashTable(const hashTable& aTable) :table(NULL), capacity(DEFAULT_CAPACITY), size(0)
{
    table = new node*[DEFAULT_CAPACITY];
    
    //copy the array of the linked list
    for(int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        //copy each linked list in the array
        if (aTable.table[i] == NULL)
            table[i] = NULL;
        else
        {
            //copy the first node in current chain
            table[i] = new node(aTable.table[i]->item);
            
            //copy the rest of the chain
            node * srcNode = aTable.table[i]->next;
            node * destNode = table[i];
            while(srcNode)
            {
                destNode->next = new node(srcNode->item);
                destNode = destNode->next;
                srcNode = srcNode->next;
            }
            destNode->next = NULL;
        }
        
    }
    
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
    if(this == &aTable)
        return *this;
    else
    {
        //release dynamically allocated memory held by current object
        destroyTable();
        
        //make *this a deep copy of "aTable"
        table = new node*[capacity];
        capacity = aTable.capacity;
        size = aTable.size;
        
        //copy the array of linked list
        int i;
        for(i=0; i<capacity; i++)
        {
            //copy each linked list in the array
            if (aTable.table[i] == NULL)
                table[i] = NULL;
            else
            {
                //copy the first node in current chain
                table[i] = new node(aTable.table[i]->item);
                
                //copy the rest of the chain
                node * srcNode = aTable.table[i]->next;
                node * destNode = table[i];
                while(srcNode)
                {
                    destNode->next = new node(srcNode->item);
                    destNode = destNode->next;
                    srcNode = srcNode->next;
                }
                destNode->next = NULL;
            }
        }		
        return *this;
    }
}

void hashTable::destroyTable()
{
    //delete each chain
    int i;
    for(i=0; i<capacity; i++)
    {
        node * head = table[i];
        node * curr;
        while(head)
        {
            curr = head->next;
            head->next = NULL;
            delete head;
            head = curr;
        }
    }
    
    //delete the array
    delete [] table;
}

//destructors
hashTable::~hashTable()
{
    destroyTable();
}

//mutators
void hashTable::add(const security& aSecurity)
{
    //declare and initialize local variables
    char symbol[100];
    aSecurity.getSymbol(symbol);
    int index = calculateIndex(symbol);
    
    //create a new node to hold data
    node * newNode = new node(aSecurity);
    
    //check for colissions
    if(table[index] != NULL)
        monitor(index);
        
    //insert the new node at the beginning of the linkedlist
    newNode -> next = table[index];
    table[index] = newNode;
    size++;
}

bool hashTable::remove(char * symbol)
{
    //calculate the retrieval location
    int index = calculateIndex(symbol);
    
    //search for the data to be retrieved in the chain
    node * curr = table[index];
    node * prev = NULL;
    char tempSymbol[100];
    
    while(curr)
    {
        curr -> item.getSymbol(tempSymbol);
        if(strcmp(symbol, tempSymbol) == 0)
        {
            //find match and remove node
            if(!prev)
                table[index] = curr -> next;
            else
                prev -> next = curr -> next;
            
            curr -> next = NULL;
            delete curr;
            size--;
            return true;
        }
        else
        {
            //if not, advance the pointers
            prev = curr;
            curr = curr -> next;
        }
        
    }
    return true;
}

bool hashTable::modify(char * symbol, float newNetValue, char * newDate, float newYearReturn)
{
    //declare and initialize local variables
    int index = calculateIndex(symbol);
    
    //search for the data to be updated
    node * curr = table[index];
    node * prev = NULL;
    char reference[100];
    while(curr)
    {
        curr -> item.getSymbol(reference);
        if(strcmp(symbol, reference) == 0)
        {
            //find match, update the values
            curr ->item.setNetValue(newNetValue);
            curr ->item.setDate(newDate);
            curr ->item.setYearReturn(newYearReturn);
            return true;
        }
        else
        {
            prev = curr;
            curr = curr -> next;
        }
        
    }
    
    return false;
}

//accessors
bool hashTable::retrieve(char * symbol, security& aSecurity)
{
    //calculate the retrieval location
    int index = calculateIndex(symbol);
    
    //search for the data to be retrieved in the chain
    node * curr = table[index];
    char tempSymbol[100];
    
    while(curr)
    {
        curr -> item.getSymbol(tempSymbol);
        
        if(strcmp(symbol, tempSymbol) == 0)
        {
            //if a match is found copy the security and return true
            aSecurity = curr -> item;
            return true;
        }
        else
            curr = curr->next;
    }
    
    //it will never get here
    return false;
}

void hashTable::display(void) const
{
    //declare and initialize local variables
    node * curr;
    
    cout << "Data in the table: " << endl << endl;
    //run through each table row
    for(int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        for(curr = table[i]; curr; curr = curr->next)
            //we can use << on data object because we overload << in the data class
            cout << '\t' << curr->item << endl;
    }
    
}

void hashTable::monitor(int index)
{
    collisions[index]++;
    
    cout << "There is a collsion at index " << index + 1 << ": " << collisions[index] + 1 << " records" << endl;
}

void hashTable::writeOut(char * fileName)
{
    ofstream out;
    
    out.open(fileName);
    if(!out)
    {
        cerr << "fail to open " << fileName << " for output!" << endl;
        exit(1);
    }
    
    //security aSecurity;
    char tempSymbol[MAX_LEN];
    char tempName[MAX_LEN];
    char tempDate[MAX_LEN];
    node * curr;
    for(int i=0; i<capacity; i++)
    {
        for(curr = table[i]; curr; curr = curr->next)
        {
            curr -> item.getSymbol(tempSymbol);
            curr -> item.getName(tempName);
            curr -> item.getDate(tempDate);
            
            out << tempSymbol << ';' << tempName << ';' << curr -> item.getNetValue() << ';';
            out << tempDate << ';' << curr -> item.getYearReturn() << '\n';
        }
    }
    out.close ();
}

int hashTable::calculateIndex(char * key)const
{
    //declare and initialize local variables
    char * c = key;
    int total = 0;
    while(*c)
    {
        total += *c;
        c++;
    }
    
    return total%capacity;
}



