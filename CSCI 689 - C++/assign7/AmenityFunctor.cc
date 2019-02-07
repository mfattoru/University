/************************************************************************************
 * Source code file for the AmenityFunctor class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 ***********************************************************************************/

#include "AmenityFunctor.h"

/************************************************************************************
 * overloading the () operator, this will print out one formatted line of the data
 * based on the different value of the data field.
 *
 * The function will print the city and the state, then it will print a third field,
 * based on the data attribute. each field is formatted in a 15 characters padding.
 * @param x - The kind of additional data field that you desire to print
 ***********************************************************************************/
void AmenityFunctor::operator () (const Amenity &x) const {
    //set the field separator to 15
    int fieldWidth=15;
    //print out the city and the state in a 15 character field, then set the character field
    //for the next print
    cout << setw(fieldWidth) << x.getCity()
         << setw(fieldWidth) << x.getState()
         << setw(fieldWidth);
    //switch over the possible values of data
    switch(data){
        //if data is equal to _JAN_MEAN
        case AmenityFunctor::_JAN_MEAN:
            //print out the January mean temperature
            cout << x.getJanMean();
            break;
        //if data is equal to _SUN_MEAN
        case AmenityFunctor::_SUN_MEAN:
            //print out the mean Shushine
            cout << x.getSunMean();
            break;
        //if data is equal to _JUL_MEAN
        case AmenityFunctor::_JUL_MEAN:
            //print out the July mean temperature
            cout << x.getJulMean();
            break;
        //if data is equal to _HUMIDITY
        case AmenityFunctor::_HUMIDITY:
            //print out the Humidity
            cout << x.getHumidity();
            break;
        //if data is equal to _LAND_FORM
        case AmenityFunctor::_LAND_FORM:
            //print out the landform
            cout << x.getLandForm();
            break;
        //if data is equal to _WATER_AREA
        case AmenityFunctor::_WATER_AREA:
            //print out the water area
            cout << x.getWaterArea();
            break;
        //if area is qeual to _COMP_AMENITY
        case AmenityFunctor::_COMP_AMENITY:
            //print out the comp amenity
            cout << x.getAmenityValue();
            break;
        //if it's not equal to any of the allowed values
        default:  //in case the user mistakenly uses the operator
            //print Not a Number
            cout << "NaN";
    }
    //return a newline
    cout << endl;
}

/************************************************************************************
 * overloading the () operator, this will return true if the amenity value of the
 * first operand is bigger than the amenity value of the second operand
 ***********************************************************************************/
bool AmenityFunctor::operator()(const Amenity &first,const Amenity & second) const{
    //return true if the composite amenity value of the first argument is
    // greater than the composite amenity value of the second argument.
    return first.getAmenityValue() > second.getAmenityValue();
}

/************************************************************************************
 * Function in charge of looping over the vector, and executing the AmenityFunctor for
 * the first and the last n entries of the vector.
 *
 * @param vec - vector of values to print
 * @param n - number of lines to print
 * @param fun - reference to a function object
 ***********************************************************************************/
void print_top_bottom_n(vector<Amenity> vec,int n,AmenityFunctor &fun){
    //declare a function pointer
    bool (* cmpFunc)(const Amenity&,const Amenity&)=nullptr;

    //Switch case to understand what value the function object is assigned to
    //print now. This will take care of checking the data value, and then assigning
    // the proper comparison function to the function pointer, to allow to properly
    //sort the vector
    switch (fun.getData()){
        //if data is equal to _JAN_MEAN
        case AmenityFunctor::_JAN_MEAN:
            //assign the compare january temperature function to the function pointer
            cmpFunc=cmpJanMean;
            cout << "Ranking by January Temperature" <<endl;
            break;
        //if data is equal to _SUN_MEAN
        case AmenityFunctor::_SUN_MEAN:
            //assign the compare sunshine temperature function to the function pointer
            cmpFunc=cmpSunMean;
            cout << "Ranking by January Sunshine" <<endl;
            break;
        //if data is equal to _JUL_MEAN
        case AmenityFunctor::_JUL_MEAN:
            //assign the compare July temperature function to the function pointer
            cmpFunc=cmpJulMean;
            cout << "Ranking by July Temperature" <<endl;
            break;
        //if data is equal to _HUMIDITY
        case AmenityFunctor::_HUMIDITY:
            //assign the compare humidity function to the function pointer
            cmpFunc=cmpHumidity;
            cout << "Ranking by July Humidity" <<endl;
            break;
        //if data is equal to _LAND_FORM
        case AmenityFunctor::_LAND_FORM:
            //assign the compare landform function to the function pointer
            cmpFunc=cmpLandForm;
            cout << "Ranking by Landform Type" <<endl;
            break;
        //if data is equal to _WATER_AREA
        case AmenityFunctor::_WATER_AREA:
            //assign the compare water area function to the function pointer
            cmpFunc=cmpWaterArea;
            cout << "Ranking by Water Area" <<endl;
            break;
        //if area is qeual to _COMP_AMENITY
        case AmenityFunctor::_COMP_AMENITY:
            //assign e nullpointer to the function pointer, as we will need a different
            //function to execute this comparison
            cmpFunc= nullptr;
            cout << "Composite Ranking" <<endl;
            break;
    }

    //open the table
    cout << "==============================================="<<endl;

    //if we need to use the function pointer
    if(cmpFunc!= nullptr){
        //sort the vector based on the function pointed  by the function pointer
        sort(vec.begin(),vec.end(),cmpFunc);
    }//or we need to use the object function, as we are comparing composite amenity
    else{
        //sort the vector using the () operator of the functor
        sort(vec.begin(),vec.end(),fun);
    }

    //assign the vector size to a variable, to avoid the call to the function at each iteration
    //of the loop.
    int vec_size=vec.size();

    //if we have more values than 2*n, then we need to print n values from the beginning,
    // and value before the end
    if(vec_size > 2*n) {
        //execute the function object for the first n elements
        for_each(vec.begin(),vec.begin()+n,fun);
        //print three dots to mark that we have more values between the two
        cout << "..." << endl;
        //execute the function object for the last n elements
        for_each(vec.end()-n,vec.end(),fun);
    }
    //the number of values is less or equal than 2*n, this means that we can print all the values, without
    //printing the "..." .Also this will remove the errors of printing duplicate values, or going
    //out of bound of the array, if the array is smaller than n.
    else{
        //execute the function object for all the elements
        for_each(vec.begin(),vec.end(),fun);
    }

    //close tha table
    cout << "==============================================="<<endl<<endl;


}
