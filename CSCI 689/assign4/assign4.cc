/*******************************************************************************
 * Read the content of a text file containing data in a the following format:
 *     <int> <string>
 * and saves all the informaation in a set.
 *
 * The program receives in input from the user the name of the file containing
 * the information and it will parse and load it in a set.
 * the set is then printed to standard output.
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/24/2018
 * @return 0 if the program is Successful.
 *         1 Wrong usage
 *         2 for errors in reading the file
 ******************************************************************************/

#include "assign4.h"
#include "DataBlock.h"

int main(int argc, char *argv[]){
    ifstream file;
    int temp_id;        //temporary hold the the id read from the file
    string temp_data;   //temporary hold the data read from the file
    //DataBlock x;
    set <DataBlock> s;
    //Check if the program received the correct number of arguments
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << "<Filename>" << endl;
        exit(1);
    }
    //open the file, and check that it's been opened correctly
    file.open(argv[1]);
    if( !file ){
        cerr << "Unable to open the file " << argv[1] << endl;
        exit(2);
    }

    //loop and half to read the data from the file, and save it in a set
    file >> temp_id >> temp_data;
    while (!file.eof()){
        DataBlock x(temp_id,temp_data);
        s.insert(x);
        file >> temp_id >> temp_data;
    }
    //close the file
    file.close();

    //loop over the set to print all the values stored
    for (auto p=s.begin(); p!=s.end(); ++p){
        cout << *p;
    }

    return 0;
}
