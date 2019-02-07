/************************************************************************************
 * Header file for the Sport class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#ifndef SPORT_H
#define SPORT_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;


class Sport{
    static const int S_NAME_SIZE = 60;  //dimension of the sport name
    char name[S_NAME_SIZE];
    int index;
public:
    const char* get_name() const;
    int get_index() const;
    void print() const;
    void read(ifstream &);
};

/************************************************************************************
 * This function takes as input a vector or sports, and prints out a list of all
 * the sports loaded from the file
 ***********************************************************************************/
void sport_list(const vector<Sport> &);

/************************************************************************************
 * This function takes as input a vector or sports, and prints out a list of all
 * the sports loaded from the file. The purpose of this function is to show to the
 * user all the possible sports, and let him make a choice about which sport he wants
 * to select. The function handle the possible cases where the user might insert a
 * wrong value.
 *
 * The function returns the index of the selected sport
 ***********************************************************************************/
int select_sport(const vector<Sport> &);

#endif /* SPORT_H */
