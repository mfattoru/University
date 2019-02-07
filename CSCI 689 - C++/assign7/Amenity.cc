/************************************************************************************
 * Source file for the Amenity class
 *
 * This class will be used to contain all the information read from the file.
 * All the data will be properly separated in fields, plus it will have an additional
 * value, called amenityValue, that will be calculated at runtime, that will consist
 * of the combined amenity of all the values read from the file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 ***********************************************************************************/

#include "Amenity.h"

/***************************************************************************************
 * Constructor for the amenity class
 *
 * @param id        ID of the amenity
 * @param state     String containing the state of the aenity
 * @param city      String containing the city name
 * @param jan       float containing the mean january temperature
 * @param sun       float containing the mean sunshine
 * @param jul       float containing the mean july temperature
 * @param humidity  float containing the mean july temperature
 * @param land      int representing the landform
 * @param water     float wepresenting the percent of water area
 **************************************************************************************/
Amenity::Amenity(int id=0, string state="", string city="", float jan=0.0, float sun=0.0,
                 float jul=0.0, float humidity=0.0, int land=0, float water=0.0) {
    this->id=id;
    this->state=state;
    this->city=city;
    this->janMean=jan;
    this->sunMean=sun;
    this->julMean=jul;
    this->humidity=humidity;
    this->landForm=land;
    this->waterArea=water;
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their january mean temperature
 *                              (Higher is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpJanMean(const Amenity& left,const Amenity& right){
    return left.getJanMean() > right.getJanMean();
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their mean sunshine
 *                               (Higher is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpSunMean(const Amenity& left,const Amenity& right){
    return left.getSunMean() > right.getSunMean();
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their July mean temperature
 *                               (Lower is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpJulMean(const Amenity& left,const Amenity& right){
    return left.getJulMean() < right.getJulMean();
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their July mean humidity
 *                               (Lower is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpHumidity(const Amenity& left,const Amenity& right){
    return left.getHumidity() < right.getHumidity();
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their landform value
 *                               (Higher is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpLandForm(const Amenity& left,const Amenity& right){
    return left.getLandForm() > right.getLandForm();
}

/**************************************************************************************
 * Function used to compare two Amenity class, based on their water area percentage
 *                               (Higher is better)
 * @return true if the first one is better than the second, false otherwise
 **************************************************************************************/
bool cmpWaterArea(const Amenity& left,const Amenity& right){
    return left.getWaterArea() > right.getWaterArea();
}