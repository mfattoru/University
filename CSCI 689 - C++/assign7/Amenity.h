/************************************************************************************
 * Header file for the Amenity.cc file
 *
 * This class will be used to contain all the information read from the file.
 * All the data will be properly separated in fields, plus it will have an additional
 * value, called amenityValue, that will be calculated at runtime, that will consist
 * of the combined amenity of all the values read from the file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 ***********************************************************************************/

#ifndef AMENITY_H
#define AMENITY_H

#include <string>
using std::string;
using std::stoi;
using std::stof;


class Amenity{
    //Amenity ID
    int id;
    //Amenity state
    string state;
    //Amenity city
    string city;
    //January mean temperature
    float janMean;
    //January mean sunshine
    float sunMean;
    //July mean temperature
    float julMean;
    //July mean humidity
    float humidity;
    //Landform
    int landForm;
    //percent of water area
    float waterArea;
    //value, representing how good is this amenity. will be calculated at runtime
    float amenityValue;
public:
    //constructor
    Amenity(int , string , string , float , float , float , float , int , float );

    //getter and setter methods
    string getCity() const { return city; }
    string getState() const { return state; }
    float getJanMean() const { return janMean; }
    float getSunMean() const { return sunMean; }
    float getJulMean() const { return julMean; }
    float getHumidity() const { return humidity; }
    float getLandForm() const { return landForm; }
    float getWaterArea() const { return waterArea; }
    void setAmenityValue(float x){ amenityValue=x; }
    float getAmenityValue() const { return amenityValue; }
};

//Comparison function for each category of data
bool cmpJanMean(const Amenity&,const Amenity&);
bool cmpSunMean(const Amenity&,const Amenity&);
bool cmpJulMean(const Amenity&,const Amenity&);
bool cmpHumidity(const Amenity&,const Amenity&);
bool cmpLandForm(const Amenity&,const Amenity&);
bool cmpWaterArea(const Amenity&,const Amenity&);


#endif /* AMENITY_H */