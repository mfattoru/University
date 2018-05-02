#ifndef ASSIGN2_H
#define ASSIGN2_H

#define CELL_WIDTH 2
#define N_MONTHS 12
#define WEEKDAYS 7

#include <iostream>
#include <iomanip>
#include <cstring>


using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::setw;
using std::strlen;

bool leap_year( int );
void calendar_header( int , int );
int days_in_month( int , int );
int starting_day( int , int );
int num_of_digits( int );
void calendar_body( int , int );

#endif /* ASSIGN2_H */
