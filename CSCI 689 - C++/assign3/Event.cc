/************************************************************************************
 * Source code file for the Eent class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#include "Event.h"

int Event::get_next_event() const{
    return next_event;
}
/*******************************************************************************
 * take a vector of Athletes and a vector of Countrys as arguments. The function
 * prints out the country code of the event after looking up the alphabetic
 * version of the code in the country vector and then some space. The ranking
 * is then printed in a field of 3 characters, followed by the event score.
 *
 * The event athletes are then printed. The integer values in the vector of
 * athletes in the event are used to select specific athletes out of the vector
 *  of Athletes. If any of the integer values is negative, then nothing is
 * printed for that particular athlete.
 ******************************************************************************/

void Event::print(const vector<Athlete> &ath,const vector<Country> &cnt) const{
    //check to see if the index of the country code is inside the bounrs of the
    //vector, if yes, print the country code, If not print XXX to mark the
    //country as not defined
    if (country >= 0 && country < (int) cnt.size()){
        cout << cnt[country].get_country_code() << " ";
    }
    else{
        cout << "XXX ";
    }
    //cout << cnt[country].get_country_code() << " "
    cout << setw(3) << ranking << " "<<scores << " ";

    for(int x=0;x<ATHLETES_SIZE;x++){
        if(athletes[x]>=0){
            if(x>0) cout << ";";

            ath[ athletes[x] ].print();
        }

    }
    cout << endl;
}

/*******************************************************************************
 * This function is used to load sequentially all the data from the stream file
 * taken as input.
 *
 * I'm not going to use this function for this specific assignent as the binary
 * file hasn't been written in a sequential way. I will use a function to read
 * the whole structure at once.
 * I will keep the function as it could result useful in case we want to change
 * the way the structure get saved on the binary file.
 ******************************************************************************/

void Event::read(ifstream &file){
    file.read((char*)&sport, sizeof(sport));
    file.read((char*)&country, sizeof(country));
    file.read(scores,sizeof(scores));
    //The compiler in our case created a padding when reading the whole structure
    //to the binary file. Expecially the compiler created a on a 4 bit cells.
    //The array of athleted in our case is 25 bites, but the compiler saves the
    //whole structure as 28 bit, so with 3 bit of padding.
    file.ignore(COMPILER_PADDING);
    file.read((char*)athletes,sizeof(athletes));
    file.read((char*)&ranking, sizeof(ranking));
    file.read((char*)&next_event, sizeof(next_event));
}
