/************************************************************************************
 * Header file for the AmenityFunctor class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 ***********************************************************************************/

#ifndef AMENITYFUNCTOR_H
#define AMENITYFUNCTOR_H


#include "Amenity.h"

#include <iomanip>
using std::setw;        //Used to properly format the output

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::for_each;    //used to go though the vector
using std::sort;        //used to sort the vector


class AmenityFunctor{
    int data;       //field containing the kind of operation to perform on the data
public:
    //Used enum as recommended by Dr. Duffin
    //This enumerator will allow us to select the proper operation that the function object will do
    enum {_JAN_MEAN=0, _SUN_MEAN, _JUL_MEAN, _HUMIDITY, _LAND_FORM, _WATER_AREA, _COMP_AMENITY};

    //Constructor
    AmenityFunctor(int x=0){ data = x; };

    //Update function, used to update the kind of operation that the function object will perform
    void update(int x){ data = x;}

    //overloading the () operator, this will print out one formatted line of the data
    void operator () (const Amenity&) const ;

    //overloading the () operator, this will compare the two amenity, and return true if the
    //first is bigger than the second, false otherwise
    bool operator()(const Amenity &first,const Amenity & second) const;

    //getter for the data field
    int getData() const{ return data;};
};

//Function in charge of looping over the vector, and executing the AmenityFunctor for the first and the
//last n entries of the vector, where n is the second argument of the function.
void print_top_bottom_n(vector<Amenity>,int,AmenityFunctor &);

#endif //AMENITYFUNCTOR_H
