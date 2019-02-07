/************************************************************************************
 * Header file for the Country class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

class Country{
    //defined the array size of the name and lastname
    static const int C_CODE_SIZE = 4;       //dimension of the country code
    static const int C_FULLNAME = 34;       //dimension of the country fullname
    char country_code[C_CODE_SIZE];
    char fullname[C_FULLNAME];
public:
    const char* get_country_code() const;
    const char* get_fullname() const;
    void print() const;  //prints country_code and fullmane separated by a space
    void read(ifstream &);  //read data from a file and load it in the instance
};

/************************************************************************************
 * This function takes as input a vector or countryes, and prints out a list of all
 the countries loaded from the file
 ***********************************************************************************/
 void country_list(const vector<Country> &);

#endif /* COUNTRY_H */
