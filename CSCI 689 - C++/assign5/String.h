//
// Created by mfattoru on 4/13/18.
//

#ifndef STRING_H
#define STRING_H

#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

#include <stdlib.h>

using std::malloc;

#include <fstream>
using std::ostream;

class String{
private:
    int len;
    char* data;
    int difference(const String &first,const String &second) const;
public:
    //Constructors and destructors
    String();
    String(const char*);
    ~String();
    String(const String &);        //copy constructor
    String(String &&);
    //utility functions
    int size() const;
    int length() const;
    bool empty() const;
    //output operator
    friend ostream & operator << (ostream &ostr,const String s);
    //Comparison Operators
    bool operator == (const String &) const;
    bool operator != (const String &) const;
    bool operator < (const String &) const;
    bool operator <= (const String &) const;
    bool operator > (const String &) const;
    bool operator >= (const String &) const;
    //indexing operators
    char operator  [] (int index) const;
    char & operator [] (int index) ;
    //Assignment operators
    String & operator = (const String & other); //copy assignment
    String & operator = (String && other);
    //Concatenation operators
    String operator + (const char) const;
    String operator + (const String &) const;

};

#endif // STRING_H
