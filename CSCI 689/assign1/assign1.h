#include <iostream>
#include <cmath>
#include <iomanip>

//CELL_WIDTH represents the number of blocks used by each cell in the table
#ifndef CELL_WIDTH
#define CELL_WIDTH 8
#endif

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
//pow( base, index ) returns base^index
using std::pow;
using std::setw;
using std::setfill;
using std::setprecision;
using std::fixed;

float heatIndexValue(float airTemperature, float humidity);

void printTable(float minT,
                float maxT,
                float deltaT,
                float minH,
                float maxH,
                float deltaH);
