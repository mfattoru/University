//
// Created by mfattoru on 4/30/18.
//

#ifndef UTILS_H
#define UTILS_H

#include <vector>
using std::vector;

#include <algorithm>
using std::for_each;

#include <math.h>
using std::pow;

#include <iostream>

//Calculate the average value of a vector of floats
float average(const vector<float> &vec);

//calculate the standara deviation of a vector of floats
float std_deviation(const vector<float> &vec,const float avg);

#endif //UTILS_H
