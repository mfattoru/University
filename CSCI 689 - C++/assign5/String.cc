/*******************************************************************************
 * Implementation of the String class
 *
 * This source file implements all the functions declared in the String class
 * Header file
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/15/2018
 *
 ******************************************************************************/

#include "String.h"

/*******************************************************************************
 * Default constructor for the String class
 *
 * The default constructor will create a string object with length 0 and
 * empty data.
 *
 ******************************************************************************/

String::String() {
    len = 0;
    data= nullptr;
}

/*******************************************************************************
 * Overloaded constructor for the String class
 *
 * This constructor takes as input a constant pointer to char, and will create
 * a string object with length equal to the length of the input strung, and will
 * copy the imput value in thr data field.
 *
 ******************************************************************************/

String::String(const char *source) {
    len=0;
    for (int i = 0; source[i] != '\0'; i++){
        len++;
    }
    data = new char[len];//(char*)malloc(sizeof(char) * (len +1));

    for(int i=0; i<len;i++){
        data[i]=source[i];
    }
}

/*******************************************************************************
 * destructor for the String class
 *
 * The default destructor will take care of deleting all the memory associated
 * with the String object
 *
 ******************************************************************************/


String::~String(){
    delete[] data;
}

/*******************************************************************************
 * The size method will return the length of the data field of the object
 *
 ******************************************************************************/
int String::size() const{
    return len;
}

/*******************************************************************************
 * The length method will return the length of the data field of the object
 *
 ******************************************************************************/

int String::length() const {
    return len;
}

/*******************************************************************************
 * The empty method will return a boolean value equal to true if the len of
 * the String object is zero, and false if the length of the len field is bigger
 * than zero
 *
 ******************************************************************************/

bool String::empty() const {
    return len==0;
}

/*******************************************************************************
 * Copy constructor for the String Class
 *
 ******************************************************************************/
String::String(const String & other) {
    this->len = other.len;

    data = new char[len];
    for (int i=0;i<len;i++){
        this->data[i]=other.data[i];
    }

}

/*******************************************************************************
 * Copy assignment operator for the String Class
 *
 ******************************************************************************/
String& String::operator = (const String & other){

    if(this != &other){
        delete []data;
        data = new char[other.len];
        len = other.len;
        for(int i=0;i<len;i++){
            data[i]=other.data[i];
        }
    }

    return *this;
}

/*******************************************************************************
 * Move constructor operator for the String Class
 *
 ******************************************************************************/
String::String(String && other){

    len = other.len;
    data = other.data;
    other.data = nullptr;

}

/*******************************************************************************
 * Move assignment operator for the String Class
 *
 ******************************************************************************/
String & String::operator = (String && other){    //move assignment
    //cout << "move assignment" <<endl;

    if(this != &other){
        len = other.len;
        data = other.data;
        other.data= nullptr;
    }
    return *this;
}

/*******************************************************************************
 * Output operator for the String Class
 *
 ******************************************************************************/
ostream & operator << (ostream &ostr,const String s) {
    for(int i=0;i<s.len;i++) {
        ostr << s.data[i];
    }
    return ostr;
}

/*******************************************************************************
 * This method finds the first character position in which the string passed
 * in is different from the current instance. The end of the shorter string
 * is also considered a place where the strings are different.
 * For example:
 *         "cat" and "dog" differ at position 0.
 *         The words "cat" and "catch" differ at position 3.
 *
 ******************************************************************************/
int String::difference(const String &first,const String &second)const {
    int maxLen = first.len;
    if(second.len > maxLen){  //get the maximum length between the two
        maxLen = second.len;
    }

    for(int i=0; i<maxLen;i++){
        if( first.data[i]!=second.data[i]) {
            return i;
        }
    }
    return maxLen;
}

/*******************************************************************************
 * Equality operator for the String Class
 *
 * This operator will return true if the two operands are equal, false otherwise
 *
 ******************************************************************************/
bool String::operator == (const String &other) const{
    int fdp = difference(*this,other);
    return ( fdp ==  this->length() &&  fdp == other.length() );
}

/*******************************************************************************
 * Disequality operator for the String Class
 *
 * This operator will return true if the two operands are not equal, false
 * otherwise
 *
 ******************************************************************************/
bool String::operator != (const String &other) const{
    int fdp = difference(*this,other);
    return (fdp !=  this->length() ||  fdp != other.length());
}

/*******************************************************************************
 * Less than operator for the String Class
 *
 * This operator will return true if the first operand is less than the
 * second operand. In this case the less operand means that a String is smaller
 * than another. The comparison is made character by character
 *
 ******************************************************************************/
bool String::operator < (const String &other) const{
    int fdp = difference(*this,other);
    if ( fdp ==  this->length() &&  this->length() < other.length() ){
        return true;
    }
    else if (this->data[fdp] < other.data[fdp]){
        return true;
    }
    return false;
}

/*******************************************************************************
 * Less than or equal operator for the String Class
 *
 * This operator will return true if the first operand is less than or equal the
 * second operand. In this case the less equal operand means that a String is smaller
 * or equal to the other one. The comparison is made character by character
 *
 ******************************************************************************/
bool String::operator <= (const String &other) const{
    int fdp = difference(*this,other);
    if( ( fdp ==  this->length() &&  fdp == other.length() ) ||
        (this->data[fdp] < other.data[fdp]) ){
        return true;
    }
    return false;
}

/*******************************************************************************
 * Bigger than operator for the String Class
 *
 * This operator will return true if the first operand is bigger than the
 * second operand. In this case the bigger operand means that a String is bigger
 * than another. The comparison is made character by character
 *
 ******************************************************************************/

bool String::operator > (const String &other) const{
    int fdp = difference(*this,other);
    if ( fdp ==  other.length() &&  this->length() > other.length() ){
        return true;
    }
    else if (this->data[fdp] > other.data[fdp]){
        return true;
    }
    return false;
}


/*******************************************************************************
 * Bigger than or equal operator for the String Class
 *
 * This operator will return true if the first operand is bigger than or equal the
 * second operand. In this case the bigger equal operand means that a String is
 * bigger or equal to the other one. The comparison is made character by character
 *
 ******************************************************************************/

bool String::operator >= (const String &other) const{
    int fdp = difference(*this,other);
    if( ( fdp ==  this->length() &&  fdp == other.length() ) ||
            (this->data[fdp] > other.data[fdp]) ){
        return true;
    }
    return false;
}

/*******************************************************************************
 * Indexing operator for the String Class.
 *
 * This operator will return the character located at the index position
 *
 ******************************************************************************/
char String::operator  [] (int index) const{
    return this->data[index];

}

/*******************************************************************************
 * Indexing operator for the String Class.
 *
 * This operator will return a reference to the character located at the index
 * position. This is useful in case of operarot chaining
 *
 ******************************************************************************/
char & String::operator [] (int index) {
    return this->data[index];
}

/*******************************************************************************
 * concatenation operator for the String Class.
 *
 * This operator will return a copy to a new String object, composed by the old
 * string object, plus the input character as trailing character
 *
 ******************************************************************************/
String String::operator + (const char ch) const{
    String ret;
    ret.len = this->len+1;
    ret.data = new char[len+sizeof(ch)];

    for(int i=0;i<len;i++){
        ret.data[i]=data[i];

    }
    ret.data[len]=ch;
    return ret;
}

/*******************************************************************************
 * concatenation operator for the String Class.
 *
 * This operator will return a copy to a new String object, composed by the old
 * string object followed by the input string
 *
 ******************************************************************************/
String String::operator + (const String &other) const{
    String ret;
    ret.len = this->len+other.len;
    ret.data = new char[ret.len];
    int count=0;

    for(int i=0;i<len;i++){
        ret.data[i]=data[i];
    }
    for(int i=len;i<ret.len;i++){
        ret.data[i]=other.data[count];
        count++;
    }
    return ret;

}
