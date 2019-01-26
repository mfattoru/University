/************************************************************************************
 * Source code for the loader utility
 *
 * This file contains all the source code necessary to load boundary files and RTC
 * files to the database defined in the main progrsm
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 12/02/2018
 ***********************************************************************************/

#include "databaseLoader.h"

int main(){
    string filename;

    //Try to connect to the database
    PGconn * db = PQconnectdb("host=babbage.cs.niu.edu user=z1840898 password=1990Dec30");

    //and check if the connection was successful
    if(!(PQstatus(db)) == CONNECTION_OK){
        cerr << "Can't connect to database: "<< PQerrorMessage(db)<<endl;
        return -1;
    }

    //ask the user to load the files he wants
    cout << "########### Load your files to the database ###########" << endl;
    cout << "Please insert the name of the file you want to load in the database( CTRL+D to exit ): ";

    while(cin >> filename ){
        //extract the file extension fron the filename
        if(filename.find_last_of(".") == string::npos){
            //if the file doesn't have extension, we can't determine the category
            cerr << "filename withouth extension, unable to recognize the input file" << endl;
        }else{
            //extract the extension of the file
            string extension = filename.substr(filename.find_last_of(".") + 1);
            //convert the extension to lowercase, so we support even extension with lower or capital letters
            transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            //we open the file
            ifstream fd(filename.c_str());
            if (fd){
                //and call the right function based on the type
                if(extension == "bnd"){ //if the file is a boundary file
                    parseBoundFile(db,fd);
                }else if(extension == "rtc"){//if the file is a name file
                    parseNameFile(db,fd);
                }else{ //if the file is neither, then the file is not supported
                    cerr << "file extension ." <<extension<<" is not supported" << endl;
                }

            }else{
                cerr << "Unable to open the file "<<filename << endl;
            }
            fd.close();
        }
        cout << "Please insert a new file to load ( CTRL+D to exit): ";
    }
    //we close the connection to the database
    PQfinish(db);
    return 0;
}


/*
 * Function used to parse the content of bound files and perform the appropriate
 * query based on the content read
 */
void parseBoundFile(PGconn * db,ifstream& fd){
    int digitInId;
    string  line,
            id,
            minLong,
            minLat,
            maxLong,
            maxLat;
    //vactor containing a list of tables where we need to push the values
    vector<string> tables;

    if(fd){
        //read the file line by line
        while( getline(fd,line) ){
            //reading the id, and the boundaries values
            id = line.substr(0,7);
            minLong = line.substr(7,10);
            minLat = line.substr(17,9);
            maxLong = line.substr(26,10);
            maxLat = line.substr(36,9);

            //which table should i insert the values is based on the id size
            digitInId = digitsInNumber(stoi(id));

            if(digitInId<=2){  //id with two digits is a state
                tables.push_back("State");
            }else if(digitInId<=5){  //Id with 5 digits is a county
                tables.push_back("County");
            }else if(digitInId<=7){ //id with 7 digits is subcountry or place
                tables.push_back("Subcounty");
                tables.push_back("Place");
            }

            //loop over the list of tables, and push the values there
            while(!tables.empty()){
                //extract the table name
                string table = tables.back();
                //compose the query
                string query =  "UPDATE Z1840898."+table+
                                " SET minLong="+minLong+",minLat="+minLat+
                                " , maxLong="+maxLong+", maxLat="+maxLat+
                                " WHERE id="+id+" AND minLong IS NULL AND minLat IS NULL"+
                                " AND maxLong IS NULL AND maxLat IS NULL;";

                //execute the query
                PGresult * res = PQexec(db,query.c_str());
                //display a loading bar while running the query
                loadProgress();
                //if the query is not successful, print an error message
                if(PGRES_COMMAND_OK != PQresultStatus(res)){
                    cerr << "Can't execute query: "<<PQerrorMessage(db)<<endl;
                }
                //removed the processed table from the lsit
                tables.pop_back();
            }
        }
    }
    //remove the left character from the loading bar
    cout << "\b";
}

/*
 * Function used to parse the content of RTM files and perform the appropriate
 * query based on the content read
 */
void parseNameFile(PGconn* db,ifstream& fd){
    string  line,
            stateCode,
            type,
            countyCode,
            year,
            placeCode,
            name,
            table,
            id,
            key;
    //map used to save the read data and filter old records
    map<string,Place*> parsedData;

    if(fd){
        //read the file line by line
        while( getline(fd,line) ){
            //save the values in a map, by id, and then replace the map element for id if
            //the year if the one saved is smaller than the new one read.

            type = line.substr(24,1);
            stateCode = line.substr(5,2);

            if(stateCode == ""){
                continue;
            }

            countyCode = line.substr(7,3);
            year = line.substr(10,4);
            placeCode = line.substr(14,5);
            name = line.substr(52,60);

            //generating the record Id
            if(type == "P"){ //it's a place
                id = stateCode + placeCode;
            }else if(type == "S"){ //it's a state
                id = stateCode;
            }else if(type == "C" || type == "M"){  //It's a county
                id = stateCode + countyCode;
            }else{
                //the value read is malformed or not supported
                continue;
            }

            //generating an unique key for the map
            key=type+id;
            //find the key is already there, if so we need to compare the years
            map<string,Place*>::iterator it = parsedData.find(key);
            if(it != parsedData.end()) {
                // compare the years
                if(it->second->getYear() < year){  //if the saved is older than the one now
                    Place* p = new Place(id,year,type,name);
                    //we replace it
                    parsedData[key]=p;
                }
            }else{
                //if it's not already there, we just add it
                Place* p = new Place(id,year,type,name);
                parsedData[key]=p;
            }
            //update the progress bar loading
            loadProgress();
        }
    }
    //now we need to insert all the data in the map to the database
    for(auto const& place : parsedData){
        //we choose the table where we will intert the value based on the type
        type = place.second->getType();
        if(type == "P"){ //it's a place
            table = "Place";
        }else if(type == "S"){ //it's a state
            table = "State";
        }else if(type == "C"){  //It's a county
            table = "County";
        }else if(type == "M"){
            table = "Subcounty";
        }

        //build the query
        string query =  "INSERT INTO Z1840898."+table+"(Id,Name)"+
                        " VALUES("+place.second->getId()+",'"+place.second->getName()+"')"+
                        " ON CONFLICT DO NOTHING;";
        //execute the query
        PGresult * res = PQexec(db,query.c_str());
        //advance progress bar
        loadProgress();
        //if the query fail, we print an error pessage
        if(PGRES_COMMAND_OK != PQresultStatus(res)){
            cerr << "Can't execute query: "<<PQerrorMessage(db)<<endl;
            // return 1;
        }
    }
    //we remove all the values from the map
    parsedData.clear();
    //and remove leftover atrifacts from the progress bar
    cout << "\b";
}

/*
 * Function used to calculate the number of digits in a number
 */

int digitsInNumber(int num){
    int digits = 1;

    while((num/10)!=0){
        num /=10;
        digits++;
    }
    return digits;
}

/*
 * Function used to display a rotating progress bar in the termina, used to
 * display to the user that the parsing and insertion of data in the database
 * is in progress, and the program is not stuck
 */
void loadProgress(){
    static int val=0;
    switch(val){
        case 0:
            cout << "\b\\" << std::flush;
            break;
        case 1:
            cout << "\b|" << std::flush;
            break;
        case 2:
            cout << "\b/" << std::flush;
            break;
        case 3:
            cout << "\b-" << std::flush;
            break;
    }
    val=(val+1)%4;
}
