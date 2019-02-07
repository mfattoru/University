/************************************************************************************
 * Header file for the Event class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <cstring>
using std::memcpy;

#include <vector>
using std::vector;

#include <iomanip>
using std::setw;

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>

#include "Country.h"
#include "Athlete.h"

class Event{
    static const int SCORES_SIZE = 25;
    static const int ATHLETES_SIZE = 4;
    static const int COMPILER_PADDING = 3;

    int sport;
    int country;
    char scores[SCORES_SIZE];
    int athletes[ATHLETES_SIZE];
    int ranking;
    int next_event;
public:
    int get_next_event() const;
    void print(const vector<Athlete> &, const vector<Country> &) const;
    void read(ifstream &);
};

#endif /* EVENT_H */
