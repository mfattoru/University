/************************************************************************************
 * Source code for the Country class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#include "Country.h"

const char* Country::get_country_code() const{
    return country_code;
}
const char* Country::get_fullname() const{
    return fullname;
}
void Country::print() const{
    cout << country_code << " " << fullname;
}

void Country::read(ifstream &file){
    file.read(country_code,sizeof(country_code));
    file.read(fullname,sizeof(fullname));
}

/************************************************************************************
 * This function takes as input a vector or countryes, and prints out a list of all
 the countries loaded from the file
 ***********************************************************************************/
void country_list(const vector<Country> &C){
    int size=C.size();
    for(int x=0;x<size;x++){
        C[x].print();
        cout << endl;
    }
}
