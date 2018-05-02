/************************************************************************************
 * Source code for the Sport class
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 ***********************************************************************************/

#include "Sport.h"

const char* Sport::get_name() const{
    return name;
}

int Sport::get_index() const{
    return index;
}

void Sport::print() const{
    cout << name;
}

void Sport::read(ifstream &file){
    file.read(name,sizeof(name));
    file.read((char*)&index,sizeof(index));
}

/************************************************************************************
 * This function takes as input a vector or sports, and prints out a list of all
 * the sports loaded from the file
 ***********************************************************************************/
void sport_list(const vector<Sport> &S){
    int size=S.size();
    for(int x=0;x<size;x++){
        S[x].print();
        cout << endl;
    }
}

/************************************************************************************
 * This function takes as input a vector or sports, and prints out a list of all
 * the sports loaded from the file. The purpose of this function is to show to the
 * user all the possible sports, and let him make a choice about which sport he wants
 * to select. The function handle the possible cases where the user might insert a
 * wrong value.
 *
 * The function returns the index of the selected sport
 ***********************************************************************************/
int select_sport(const vector<Sport> &S){
    int n_elem=S.size();
    int choice=0;
    //printing the information about sports
    for(int x=0;x<n_elem;x++){
        cout << x << ") ";
        S[x].print();
        cout << endl;
    }
    while(true){
        cout << "Sport to view? ";
        cin >> choice;
        cout << endl;
        if(choice<0 || choice >= n_elem){
            cout << "Not a valid choice!! Try again" << endl;
            //reset the cin fail state in case the input is not an integer
            cin.clear();
            cin.ignore();
        }
        else break;
    }
    return choice;
}
