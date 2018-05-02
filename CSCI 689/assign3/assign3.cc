/*******************************************************************************
 * Read the content of a binary file containing info about the olympics, and
 * display information on the screen through a choices menu.
 *
 * The program receives in input from the user the name of the file containing
 * the information about the olympics, The program will parse and load to memory
 * all the information, and will allow the user to perform different queries on
 * the data collected. The queries will be displayed on the screen through a
 * menu. To close the program the user should execute the shourcut to terminate
 * the program, CTRL + C
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/24/2018
 * @return 0 if the program is Successful, 1 for errors in reading the file
 ******************************************************************************/

#include "assign3.h"

int main(){
    char filename[MAX_FILENAME];
    int element_count=0;
    vector<Country> CountryS;
    vector<Sport> SportS;
    vector<Athlete> AthleteS;
    vector<Event> EventS;
    ifstream file;

    while(true){
        cout << "Insert the name of the file: ";
        cin >> filename;
        file.open(filename,ios::binary);

        if( !file ){
            cerr << "couldn't open the file,Try again!" << endl;
        }
        else break;
    }

    //reading from file the number of countries entries in the file
    file.read((char*)&element_count,sizeof(element_count));
    check_stream(file);

    //resizing the Country vector to allocate enough memory for all the elements
    CountryS.resize(element_count);

    //Reading from file all the country information
    for(int x=0;x<element_count;x++){
        //file.read((char*)&CountryS[x],sizeof(CountryS[x]));
        CountryS[x].read(file);
        check_stream(file);
    }

    //reading the information about the number of sports entries in the file
    file.read((char*)&element_count,sizeof(element_count));
    check_stream(file);
    //resizing the sports vector to allocate enough memory for all the elements
    SportS.resize(element_count);

    //reading from file the information about the sports
    for(int x=0;x<element_count;x++){
        SportS[x].read(file);
        check_stream(file);
        //file.read((char*)&SportS[x],sizeof(SportS[x]));
    }

    //reading the information about the number of athletes entries in the file
    file.read((char*)&element_count,sizeof(element_count));
    check_stream(file);

    //resizing the Athlete vector to allocate enough memory for all the elements
    AthleteS.resize(element_count);
    //reading from file the information about the athletes
    for(int x=0;x<element_count;x++){
        AthleteS[x].read(file);
        //file.read((char*)&AthleteS[x],sizeof(AthleteS[x]));
        check_stream(file);
    }

    //reading the information about the number of Events entries in the file
    file.read((char*)&element_count,sizeof(element_count));
    check_stream(file);

    //resizing the EventS vector to allocate enough memory for all the elements
    EventS.resize(element_count);

    //reading from file the information about the events
    for(int x=0;x<element_count;x++){
        file.read((char*)&EventS[x],sizeof(EventS[x]));
        //EventS[x].read(file);
        check_stream(file);
    }

    //close the file stream
    file.close();

    //display the menu
    menu(AthleteS,CountryS,EventS,SportS);
    return 0;
}

/*******************************************************************************
 * This function is used to verify if the file stream is in error. This will
 * happen if when reading from the stream an error occurs, and the function
 * stops
 *
 * The function doesn't have a return value, because we consider impossible to
 * resume the program after an error during the read of the data.
 * Instead the finction exit with an exit code 1, that will cause the program to
 * terminate with an error.
 ******************************************************************************/
void check_stream(ifstream &file){
    if (!file){
        cout << "ERROR: read only " << file.gcount() << " bytes" << endl;
        file.close();
        exit(1);
    }
}

/*******************************************************************************
 * This function is used to display the choice menu to the user. The user will
 * have different operation from which choose, and will be able to terminate the
 * program by executing the CTRL + C shortcut on the keyboard.
 * The function checks for non legit values, and loop over the menu in case of
 * non legit options
 ******************************************************************************/
void menu(const vector<Athlete> &A,  //vector of athletes
          const vector<Country> &C,  //vector of country
          const vector<Event> &E,    //vector of events
          const vector<Sport> &S){   //vector of sports
    char choice=' ';

    while(true){
        cout << endl << "1) Print countries" << endl;
        cout << "2) Print sports" << endl;
        cout << "3) Print athletes by name" << endl;
        cout << "4) Print athletes by country" << endl;
        cout << "5) Print ranking by sport" << endl;
        cout << "Q)uit"<<endl;
        cout << "Choice? ";
        cin >> choice;
        cout << endl;

        switch(choice){
            case '1':
                //print all the countries with 3 letter code and fullname
                country_list(C);
                break;
            case '2':
                //print an ordered list of sports
                sport_list(S);
                break;
            case '3':
                //prints a list of athletes ordered by name
                print_athletes_by_name(A, C);
                break;
            case '4':
                //prints list of athletes ordered by country
                print_athletes_by_country(A, C);
                break;
            case '5':
                //print a list of ranking grouped by sports
                print_ranking_by_sport( select_sport(S) , A, C, E, S);
                break;
            case 'Q':
            case 'q':
                cout << "Bye!" << endl;
                exit(0);
            default:
                cout << "Option not valid!! Try again "<<endl;
                //reset the cin fail state in case the input is not an integer
                cin.clear();
                cin.ignore();
                break;
        }
    }
}

/*******************************************************************************
 * This function is used to display The ranking of all the teams, grouped by
 * sport. The finction takes as input vectors of athletes countries, events and
 * sports, and also an integer representing the index of the sport in the sport
 * vector
 ******************************************************************************/
void print_ranking_by_sport(int pos,
                            const vector<Athlete> &A,
                            const vector<Country> &C,
                            const vector<Event> &E,
                            const vector<Sport> &S){
    //print the selected sport name
    S[pos].print();
    cout << endl;

    //get the index of the first athlete in the ranking
    int event_index = S[pos].get_index();

    //the function continues until it finds a negative index
    while(event_index>=0){
        //prints the country,ranking, and fullname of the athlete in the event
        E[event_index].print(A, C);
        //get the index of the next element to be printed
        event_index=E[event_index].get_next_event();
    }

}
