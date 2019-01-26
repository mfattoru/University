#include "assign1.h"

/**
 * Sort a dinamically allocated array
 *
 * The program takes as input three iptions, one required and two optional
 *      -G      Define the algorithm to be used (Required):
 *                  I       Insertion Sort
 *                  S       Selection Sort
 *      -N      Define the size of the array to be defined.
 *                  Default size is 1000
 *      -S      Define the way the dinamically generated array is ordered at start:
 *                  R       Array populated with randomly generated order
 *                  A       Array populated with ascending ordered elements
 *                  D       Array populated with descending ordered elements
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 08/31/2018
 * @return 0 if the programi is Successful, for illegal imputs:
 *           1: Wrong command line options
 *.
 */

int main(int argc, char * const argv[]){

    int option,  //command line option parsed
        arraySize = 1000;  //default array size, in case the user doesn't insert one
    char arrayOrder = 'R',  //default start array order, Random
         sortAlgorithm = ' '; /*initialize the sorting algorithm to be used as an
                                empty spaced. Used later to check that the value
                                was inserted by the user as command option*/
    int* array = NULL;          //pointer to an int, used to point to the head of
                                //the array

    //Loop to parse the command line options
    while( ( option = getopt(argc, argv, "N:S:G:") ) != -1){
        //Do a different operation based on the option received
        switch( option ){
            case 'N':  //Set the dimension of the array
                //if the argument of the option exists, then convert it to int
                // and assign the value to the arraySize variable
                if( optarg ) arraySize = atoi( optarg );
                break;
            case 'S': //Start order of the array elements
                //if the argument of the option exists and if the argument is a
                //single character, as those are the allowed values
                if( optarg && strlen(optarg) == 1){
                    //get the single character, and check if it's one of the supported
                    switch(optarg[0]){
                        case 'R':
                        case 'A':
                        case 'D':
                            //set the ordering to be used to generate the array
                            arrayOrder = optarg[0];
                            break;
                        default:
                            //if it's not a supported argument, then print an
                            //error and exit the program
                            cerr << "The allowed values for S are R,A or D";
                            exit(1);
                        }
                }else{
                    //if the user inserted more than a single character, then
                    //print the usage of the program
                    usage(argv[0]);
                }
                break;
            case 'G': // Set the algorithm to be used
                //if the argument of the option exists and if the argument is a
                //single character, as those are the allowed values
                if( optarg && strlen( optarg ) == 1){
                    //get the single character, and check if it's one of the supported
                    switch(optarg[0]){
                        case 'I':
                        case 'S':
                            // Set the sorting algorithm to be used
                            sortAlgorithm = optarg[0];
                            break;
                        default:
                            //if it's not a supported argument, then print an
                            //error and exit the program
                            cerr << "The allowed values for G are I or S";
                            exit(1);
                    }
                }else{
                    //if the user inserted more than a single character, then
                    //print the usage of the program
                    usage( argv[0] );
                }
                break;
        }
    }

    //If the user doesn't insert a value for the required option to define the
    //sorting algorithm, then call the usage and abort the program
    if( sortAlgorithm == ' ' ){
        usage(argv[0]);
    }

    //Generate the array
    array = generateArray(arraySize, arrayOrder );

    //Execute the defined algorighm
    if( sortAlgorithm == 'I' ){
        insertion_sort( array, arraySize );
    }else if( sortAlgorithm == 'S' ){
        selection_sort(array, arraySize );
    }

    //free the memory occupied pointed by array
    delete [] array;
    //remove the reference to the memory location, to prevent invalid memory reference
    array = NULL;
    //return
    return 0;
}

/*
 *
 * Display the correct usage of the program, and exit
 *
 */
void usage( char * const progName ){
    cout << "usage: " << progName << " [-N n] [-S R/A/D] -G I/S" << endl;
    exit(1);
}

/*
 * Generate a dinamycally allocated array of integers, and returns a pointer to
 * the array.
 *
 * This functions takes as input the size of the array to be generated, and the
 * type, which is used to define the ordering of the generated array.
 *
 *          R       Array populated with randomly generated order
 *          A       Array populated with ascending ordered elements
 *          D       Array populated with descending ordered elements
 *
 *
 *
 */
int* generateArray(int size, char type){
    //allocate the memory for the defined size
    int* array = new int[size];
    //initialize random seed:
    srand( time(NULL) );

    if( type == 'R' ){ //Random order
        for( int i = 0; i < size ; i++ ){
            array[i] = rand() % size;
        }
    }else if( type == 'A' ){ //Ascending order
        for( int i = 0; i < size ; i++ ){
            array[i] = i;
        }

    }else if( type == 'D' ){ //Descending Order
        for( int i = 0; i < size ; i++ ){
            array[i] = size -i -1;
        }
    }
    //return the pointer to the array
    return array;
}

/*
 * Insertion sort algorithm
 *
 * This algorithm receives in input a pointer to the array, and the size of the
 * array, and order all the elements in the ascending order
 *
 */
void insertion_sort( int* array, int size ){
    //variables used to store the index used to go through the array, and the
    //value of the current element, that gets stored to don't lose it during the
    //process
    int value,
        index;

    //Loop over the array from the first+1 position to the last-1 position
    //As we compare the current with the previous, we need to start from the
    //second position, also we and at the last-1 position as the last
    //element in the array will be already in order
    for( int i = 1; i < size -1; i++ ){
        //we store the value of the current position
        value = array[i];
        //and we get the index of the previous element
        index = i -1;
        //we check all the previous elements, until we find the element that
        //is smaller than the current
        while( index >= 0 && array[index] > value){
            //we move one position forward the element analyzed, as it's bigger
            //than the one we are trying to insert
            array[ index +1 ] = array[index];
            //we then update the index, to check the element on the left
            index = index -1;
        }
        //Once we've found an element that is smaller than the current, or if we reached
        //the end of the array, we then insert the current element in the position
        //following the that one
        array[ index +1 ] = value;
    }
}

/*
 * Selection sort algorithm
 *
 * This algorithm receives in input a pointer to the array, and the size of the
 * array, and order all the elements in the ascending order
 *
 */
void selection_sort( int* array, int size ){
    int min,  //variable used to store the minimin value found
        minIndex,  //variable used to store the index position of the min value
        temp;   //temporary variable used to perform a swap of two elements

    //we loop over the array, until to the position last-1, which will be already
    //ordered once all the previous elements are ordered
    for( int i = 0; i < size -1; i++ ){
        //we save as minimum value the current element
        min = array[i];
        //and as minimum index the current index
        minIndex = i;
        //we then loop over the array, starting from the element after the current
        //up to the end of the array,
        for(int j = i +1 ; j < size ; j++ ){
            //and we compare the analyzed element with the current minimum value.
            //if the analyzed element is smaller than the minimum
            if( array[j] < min ){
                //then we save the analyzed element as new minimun, and we
                //update the index of the minimum element
                minIndex = j;
                min = array[j];
            }
        }
        //once we finished to check all the element after the current, we swap
        //the current, with the minumum
        temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}
