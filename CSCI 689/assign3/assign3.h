/************************************************************************************
 * Header file for the assign3.cc file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#ifndef ASSIGN3_H
#define ASSIGN3_H

#define MAX_FILENAME 40 //maximum length of the name of the input file

#include "Athlete.h"
#include "Country.h"
#include "Sport.h"
#include "Event.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include <fstream>
using std::istream;
using std::ios;

#include <cstring>
using std::strncpy;

#include <vector>
using std::vector;

/*******************************************************************************
 * This function is used to verify if the file stream is in error. This will
 * happen if when reading from the stream an error occurs, and the function
 * stops
 *
 * The function doesn't have a return value, because we consider impossible to
 * resume the program after an error during the read of the data.
 * Instead the finction exit with an exit code 1, that will cause the program to
 * terminate with an error.
 ******************************************************************************/
void check_stream(ifstream &);

/*******************************************************************************
 * This function is used to display the choice menu to the user. The user will
 * have different operation from which choose, and will be able to terminate the
 * program by executing the CTRL + C shortcut on the keyboard.
 * The function checks for non legit values, and loop over the menu in case of
 * non legit options
 ******************************************************************************/
void menu(const vector<Athlete> &,
          const vector<Country> &,
          const vector<Event> &,
          const vector<Sport> &);

/*******************************************************************************
* This function is used to display The ranking of all the teams, grouped by
* sport. The finction takes as input vectors of athletes countries, events and
* sports, and also an integer representing the index of the sport in the sport
* vector
******************************************************************************/
void print_ranking_by_sport(int,
                            const vector<Athlete> &,
                            const vector<Country> &,
                            const vector<Event> &,
                            const vector<Sport> &);

#endif /* ASSIGN3_H*/
