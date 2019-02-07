/************************************************************************************
 * Header file for the Athlete class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/
#ifndef ATHLETE_H
#define ATHLETE_H

#include "Country.h"

#include <iostream>
using std::cout;

#include <fstream>
using std::ifstream;

class Athlete {
    //defined the array size of the name and lastname
    static const int NAME_SIZE = 30;
    char lastname[NAME_SIZE];
    char name[NAME_SIZE];
    int country; //index used to identify the country code in the country vector
    int next_by_name; //next athlete ordered by name
    int next_by_country;  //next athlete ordered by country
public:
    const char* get_name() const;   //returns the name of the athlete
    const char* get_lastname() const;  //returns the lastname of the athlete
    int get_country() const;     //returns the country index in the country vector
    int get_next_by_name() const;   //get next athlete in the order by name
    int get_next_by_country() const;   //get next athlete in the order by country
    void print() const; //print name and lastname separated by a comma
    void read(ifstream& file);//read data from a file and load it in the instance
};

/*******************************************************************************
 * This function is used to display a list of all the athletes ordered by
 * country. It takes in input a vector of athleted and a vector of countries.
 ******************************************************************************/
void print_athletes_by_country( const vector<Athlete> &,
                                const vector<Country> &);

/*******************************************************************************
 * This function is used to display a list of all the athletes ordered by
 * country. It takes in input a vector of athleted and a vector of countries.
 ******************************************************************************/
void print_athletes_by_name( const vector<Athlete> &,
                             const vector<Country> &);

#endif /*  ATHLETE_H */
