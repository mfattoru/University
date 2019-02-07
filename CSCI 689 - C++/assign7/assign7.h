/************************************************************************************
 * Header file for the assign7.cc file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 ***********************************************************************************/

#ifndef ASSIGN7_H
#define ASSIGN7_H

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
using std::getline;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;
using std::stoi;    //convert string to integer
using std::stof;    //convert string to float

#include <vector>
using std::vector;

#include "Amenity.h"  //to include the Amenity class

#include "utils.h"    //to include the utility functions

#include <math.h>
using std::log;      //used to convert the water area percent to normal value

#include "AmenityFunctor.h"     //used to unclude the helper class

//Function to parse the read string, and generate an Amenity
Amenity *amenityParser(string s);
//Function to calculate the composite amenity of all the created objects
void compositeAmenity(vector<Amenity> & vec);

#endif /* ASSIGN7_h */
