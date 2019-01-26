/************************************************************************************
 * header file for the loader utility
 *
 * This file contains all libraries used for the database loader utility, the
 * header declaration of the functions, and the declaration of the Place class
 * used to filter old records from the input files
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 12/02/2018
 ***********************************************************************************/

#include <iostream>
using std::endl;
using std::cout;
using std::cin;
using std::cerr;

#include <string>
using std::string;
using std::getline;
using std::stoi;
using std::to_string;


#include <algorithm>
using std::transform;

#include <fstream>
using std::ifstream;

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <postgresql/libpq-fe.h>

void parseBoundFile(PGconn* ,ifstream&);
void parseNameFile(PGconn* ,ifstream&);
int  digitsInNumber(int);
void loadProgress();

class Place{
private:
    string  id,
            type,
            year,
            name;
public:
    Place(const string& id,const string& year,const string& type,const string& name){
        this->type=type;
        this->id=id;
        this->year=year;
        this->name=name;
    }
    string getId() const{
        return this->id;
    }

    string getType() const{
        return this->type;
    }

    string getYear() const{
        return this->year;
    }

    string getName() const{
        return this->name;
    }

    Place(const Place &other){
        this->type = other.type;
        this->id=other.id;
        this->name = other.name;
        this->year = other.year;
    }
};
