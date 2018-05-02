/************************************************************************************
 * Source code for the Athlete class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#include "Athlete.h"

void Athlete::print() const{
    cout << lastname << ", " << name;
}

const char* Athlete::get_name() const{
    return name;
}

const char* Athlete::get_lastname() const{
    return lastname;
}

int Athlete::get_country() const{
    return country;
}

int Athlete::get_next_by_name() const{
    return next_by_name;
}
int Athlete::get_next_by_country() const{
    return next_by_country;
}

/*******************************************************************************
 * This function takes as input a file stream, read data from a file and load it
 * in the instance of the class
 ******************************************************************************/
void Athlete::read(ifstream& file){
    file.read(lastname,sizeof(lastname));
    file.read(name,sizeof(name));
    file.read((char*)&country,sizeof(country));
    file.read((char*)&next_by_name,sizeof(next_by_name));
    file.read((char*)&next_by_country,sizeof(next_by_country));
}

/*******************************************************************************
 * This function is used to display a list of all the athletes ordered by
 * country. It takes in input a vector of athleted and a vector of countries.
 ******************************************************************************/
void print_athletes_by_name( const vector<Athlete> &athletes,
                             const vector<Country> &countries){

    //Initialize the index to the value of the next athlete to be showed
    int index=athletes[0].get_next_by_name();
    int country_index=0;
    //the function continues until it finds a negative index
    while(index>=0){
        //get the index of the country vector to display the correct country code
        country_index=athletes[index].get_country();
        //print the country code and the full name of the athlete
        athletes[index].print();

        //check to see if the index of the country code is inside the bounrs of the
        //vector, if yes, print the country code, If not print XXX to mark the
        //country as not defined
        if (country_index >= 0 && country_index < (int) countries.size()){
            cout << " " << countries[country_index].get_country_code();
        }
        else{
            cout << " XXX ";
        }
        //get the index of the next athlete
        index=athletes[index].get_next_by_name();
        cout << endl;
    }
}


/*******************************************************************************
 * This function is used to display a list of all the athletes ordered by
 * country. It takes in input a vector of athleted and a vector of countries.
 ******************************************************************************/
void print_athletes_by_country( const vector<Athlete> &athletes  ,
                                const vector<Country> &countries){
    //Initialize the index to the value of the next athlete to be showed
    int index=athletes[0].get_next_by_country();
    int country_index=0;
    while(index>=0){
        //get the index of the country vector to display the correct country code
        country_index=athletes[index].get_country();

        //check to see if the index of the country code is inside the bounrs of the
        //vector, if yes, print the country code, If not print XXX to mark the
        //country as not defined
        if (country_index >= 0 && country_index < (int) countries.size()){
            cout << countries[country_index].get_country_code() << " ";
        }
        else{
            cout << "XXX ";
        }
        athletes[index].print();
        //get the index of the next athlete
        index=athletes[index].get_next_by_country();
        cout << endl;
    }
}
