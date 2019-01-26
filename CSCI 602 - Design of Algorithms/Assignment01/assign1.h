/*
 * Header file for the assign1.cc source code
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 08/31/2018
 */

#include <iostream>
#include <unistd.h>
#include <string.h>     // strlen
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

using std::cout;
using std::endl;
using std::cerr;

//Usage function
void usage(char * const argv);
//Insertion sort function
void insertion_sort(int* array,int size);
//Selection sort function
void selection_sort(int* array,int size);
//Function used to generate and return a dynamically allocated array of int
int* generateArray(int size, char type);
