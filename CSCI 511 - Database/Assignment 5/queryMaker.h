/************************************************************************************
 * header file for the loader utility
 *
 * This file contains all libraries used for the database query utility, and the
 * header declaration of the functions
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 12/02/2018
 ***********************************************************************************/

#include <iostream>
using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::left;
using std::showpos;

#include <string>
using std::string;
using std::stoi;
using std::to_string;

#include <cstring>
using std::strlen;

#include <postgresql/libpq-fe.h>

#include <iomanip>
using std::setw;
using std::setprecision;
using std::fixed;
using std::setfill;

#include <sstream>
using std::stringstream;

#include <cmath>
using std::abs;

void printResult(PGresult*);
string intToDegree(const string& ,const string&);
