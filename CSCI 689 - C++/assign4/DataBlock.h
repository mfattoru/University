/************************************************************************************
 * Header file for the DataBlock.h ckass file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/24/2018
 ***********************************************************************************/

#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <string>
using std::string;

#include <fstream>
using std::ostream;


class DataBlock {
    int id;
    string data;
public:
    //constructor with default arguments
    DataBlock(int tid=0,const string &tdata=""){
        id=tid;
        data=tdata;
    }

    /*******************************************************************************
    * Operator overload for the minus than operator.
    * the operator takes two DataBlocks as operands, and returns true if the
    * first is smalles than the second, false otherwise.
    ******************************************************************************/
    bool operator < (const DataBlock& x)const{
        return id < x.id;
    }

    /*******************************************************************************
    * Operator overload for the [] operator.
    * the operator takes an integer as operand, and returns the content of the data
    * string. This index operator is unused, and the design is broken, but those
    * were the requirements of the assignment.
    * we are using two overload, because:
    *           string operator [] (int index) const
    * is used when accessing an element like cout<< elem[]
    * while
    *           string &operator [] (int index)
    *is used when assigning the indexed element like elem[1]="foo"
    ******************************************************************************/
    string operator [] (int index) const{
        return data;
    }
    string &operator [] (int index){
        return data;
    }

    /*******************************************************************************
    * declaring the << operator as friend of the class, so that it can directly
    * access the elements of the class, as if it were a DataBlock class itself
    ******************************************************************************/
    friend ostream& operator<<(ostream &os,const DataBlock& d);
};

ostream& operator<<(ostream &os,const DataBlock& d);

#endif /* DATABLOCK_H */
