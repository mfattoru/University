/************************************************************************************
 * source code for the DataBlock.cc class file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/24/2018
 ***********************************************************************************/

#include "DataBlock.h"

/*******************************************************************************
 * Operator overload for the << operator.
 * the operator takes two operands, an ostream and a DataBlock, and redirect to
 * ostream the string contained in data. If the string is equal to a newline,
 * composed by the characters backslash and n (\n) the program redirects a newline
 * to to the ostream.
 ******************************************************************************/
ostream &operator << (ostream &os,const DataBlock& d){
    if(d.data == "\\n"){
        os << '\n';
    }
    else{
        os << d.data << " ";
    }
    return os;
}
