/************************************************************************************
 * Source code for the query maker utility
 *
 * This file contains all the source code necessary to qyery the database, receiving
 * as input the name of the region to load information
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 12/02/2018
 ***********************************************************************************/

#include "queryMaker.h"

int main(){
    string name;

    //Connect to the database
    PGconn * db = PQconnectdb("host=babbage.cs.niu.edu user=z1840898 password=1990Dec30");

    //if the connection is not successful, then we return with an error
    if(!(PQstatus(db)) == CONNECTION_OK){
        cerr << "Unable to connect to the database: "<< PQerrorMessage(db)<<endl;
        return -1;
    }

    cout << "########### Load your files to the database ###########" << endl;
    cout << "Please insert the name of the region you want to load information( CTRL+D to exit ): ";

    while(cin >> name ){
        //we build a query for the region, searching in all the tables for any region which
        //contains the input string as substring. the search is case insensitive
        string query =  "SELECT * FROM Z1840898.County WHERE Name ILIKE '%"+name+"%' UNION "+
                        "SELECT * FROM Z1840898.Place WHERE Name ILIKE '%"+name+"%' UNION "+
                        "SELECT * FROM Z1840898.State WHERE Name ILIKE '%"+name+"%' UNION "+
                        "SELECT * FROM Z1840898.Subcounty WHERE Name ILIKE '%"+name+"%';";

        //execute query
        PGresult * res = PQexec(db,query.c_str());

        //we check the result of thwe query, and act accordingly
        if(PGRES_TUPLES_OK != PQresultStatus(res)){
            cerr << "Error execute query: "<< PQerrorMessage(db) <<endl;
        }else{
            printResult(res);
        }

        cout << "Please enter the name another region you want to load information ( CTRL+D to exit): ";
    }
    //close the connection to the database
    PQfinish(db);
    return 0;
}

/*
 * Function used to properly print the returned results in a table form
 */
void printResult(PGresult* res){
    int nFields,
        nTuples,
        i,
        j;
    string columnName;
    int colSize[6] = {};

    if(res!= NULL){
        /* get the number of fields and number of tuples in the result*/
        nFields = PQnfields(res);
        nTuples = PQntuples(res);

        //get the max width for all the columns
        for (i = 0; i < nFields; i++){
            for (j = 0; j < nTuples; j++){
                if(PQgetlength(res,j,i) > colSize[i]){
                    colSize[i]=PQgetlength(res,j,i);
                    string columnName = PQfname(res,i);
                    if(columnName == "minlat" || columnName == "maxlat" ){
                        colSize[i]+=5;
                    }else if(columnName == "minlong" || columnName == "maxlong"){
                        colSize[i]+=4;
                    }
                }
            }
        }

        //print the name of the table
        for (i = 0; i < nFields; i++){

            cout << " "<<setw(colSize[i]) <<left<< PQfname(res, i) << " |";

        }

        cout << endl;
        //print a separator dashed line
        for (i = 0; i < nFields; i++){
            for(int k=0;k<colSize[i]+2;k++){
                cout << "-";
            }
            cout << '+';
        }
        cout << endl;
        /* next, print out the rows */

        for (i = 0; i < nTuples; i++){

            for (j = 0; j < nFields; j++){
                columnName = PQfname(res, j);
                cout << " ";
                //print out the value in degree format in the proper width
                cout << setw(colSize[j])<<left<<intToDegree(columnName,PQgetvalue(res, i, j));
                cout << " |";
            }
            cout << endl;

        }
    }
    //clear the result
    PQclear(res);
}

/*
 * Funcition to convert an integer number to a degree, minutes and seconds format
 */
string intToDegree(const string& columnName,const string& val){
    int value;
    double  degree,
            minutes,
            seconds;
    //convert only latitude and longitude values, return others values unconverted
    if((columnName == "minlat" || columnName == "maxlat" || columnName == "minlong" || columnName == "maxlong")&&val!=""){
        value=stoi(val);
        //convert value to degree
        degree = abs(value) / 1000000.0; //088797063 / 1000000 = 88
        //convert remaining to minutes
        minutes = (degree-((int)degree))*60.0;
        //convert remaining to seconds
        seconds = (minutes-((int)minutes))*60.0;
        // cout << "SECONDS: "<< seconds << endl;

        //use a stringstream to properly print the values, so with paddd zeros
        //and width of 2 for the degree and minutes, and 5 for the seconds
        stringstream stream;
        stream << fixed <<setw(2)<<setfill('0') << (int)degree <<"º";

        stream << fixed <<setw(2)<<setfill('0') << (int)minutes <<"'";

        stream << fixed <<setw(5)<<setfill('0')<< setprecision(2) << seconds<<"\"";

        //append the north south east and west value based to some criteria
        if(columnName == "minlat" || columnName == "maxlat"){
            if(value>0){
                stream<<"N";
            }else{
                stream<<"S";
            }
        }else if(columnName == "minlong" || columnName == "maxlong"){
            if(value>0){
                stream<<"E";
            }else{
                stream<<"W";
            }
        }

        return stream.str();
    }else{
        return val;
    }
}
