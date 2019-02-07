#include "utils.h"

/*****************************************************************************************
 * Calculate the average of a vector of floats
 *
 * @param vec -  vector of floats
 * @return average
 ****************************************************************************************/
float average(const vector<float> &vec){
    //variable to hold the sum of all the values
    float elementSum=0.0;

    //loop over all the element of the vector, and for each of then, execute tha lambda function.
    //the lambda function will take as input a float, and have access to the reference of the
    //variable elementSum.
    for_each(vec.begin(),vec.end(),[&elementSum](float a){
        elementSum+=a;
    });

    //return the value of the sum of elements, devided by the number of elements in the vector
    return elementSum/vec.size();
}


/*****************************************************************************************
 * Calculate the standard deviation of a vector of floats
 * @param vec - vector of floats
 * @param avg - average of the vector of floats
 * @return
 *****************************************************************************************/
float std_deviation(const vector<float> &vec, const float avg){
    //variable to hold the value of the standard deviation
    float std_dev=0.0;

    //loop over all the element of the vector, and for each of then, execute tha lambda function
    //the lambda function takes as input a float, and have access to a reference of the variable
    //std_dev, and a copy of the avg value.
    for_each(vec.begin(),vec.end(),[&std_dev,avg](float x){
        std_dev+=pow(x-avg,2);
    });

    //formula to calculate the standard deviation
    std_dev=sqrt( std_dev/(vec.size()-1) );
    //return the standard deviation
    return std_dev;
}
