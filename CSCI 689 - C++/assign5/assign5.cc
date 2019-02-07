#include <iostream>
#include "String.h"

using std::cout;
using std::endl;

// Prototypes

void test_relationship(const String& s1, const String& s2);

String function1(const String & first, const String & second);
String function2(const String first, const String second);

int main(void)
{
    String s1;

    cout << "*** Test 1 ***" << endl;
    cout << "s1 has length " << s1.length() << endl << endl;

    String s2 = "Warm";

    cout << "*** Test 2 ***" << endl;
    // Test length member and C string initialization
    cout << "s2 has length " << s2.length() << endl << endl;

    cout << "*** Test 3 ***" << endl;
    // Test string output
    cout << "Hot " << s2 << " Cold" << endl << endl;

    cout << "*** Test 4 ***" << endl;
    // Test truncation on initialization overflow
    String s3 = "This string is really long. It is supposed to be long.  \
So long, in fact, that it will be longer than will \
fit into a normal string variable.";

    cout << s3 << endl;
    cout << "Length: " << s3.size() << endl << endl;

    cout << "*** Test 5 ***" << endl;
    if(s1.empty())
        cout << "s1 is empty  ";
    else
        cout << "s1 is not empty  ";

    if(s2.empty())
        cout << "s2 is empty  " << endl << endl;
    else
        cout << "s2 is not empty  " << endl << endl;

    String s4 = "calypso";
    String s5 = "keep";
    String s6 = "keepsake";
    String s7 = "spring";

    cout << "*** Test 6 ***" << endl << endl;
    // Test left operand longer but less than right operand
    test_relationship(s4, s5);

    cout << "*** Test 7 ***" << endl << endl;
    // Test left operand shorter but greater than right operand
    test_relationship(s5, s4);

    cout << "*** Test 8 ***" << endl << endl;
    // Test left operand shorter but less than right operand
    test_relationship(s5, s7);

    cout << "*** Test 9 ***" << endl << endl;
    // Test left operand longer but greater than right operand
    test_relationship(s7, s5);

    cout << "*** Test 10 ***" << endl << endl;
    // Test left operand substring of right operand
    test_relationship(s5, s6);

    cout << "*** Test 11 ***" << endl << endl;
    // Test right operand substring of left operand
    test_relationship(s6, s5);

    cout << "*** Test 12 ***" << endl << endl;
    // Test equal operands
    test_relationship(s6, s6);

    String s8 = "melancholy";
    String s9 = "Momentary";
    cout << "*** Test 13 ***" << endl << endl;
    // Test upper/lower case comparison
    test_relationship(s8, s9);


    String s10 = "most";

    cout << "*** Test 14 ***" << endl << endl;
    // Test reading a character
    cout << "Character 2 in " << s10 << " is " << s10[2] << endl;

    cout << "*** Test 15 ***" << endl << endl;
    // Test writing a character
    cout << s10 << " is changed to ";
    s10[2] = 'a';
    cout << s10 << endl;

    cout << "*** Test 16 ***" << endl << endl;
    // Copy constructor

    String s11 = "look";
    String s12 = s11;
    s12[0] = 'b';
    cout << "Take a " << s11 << "." << endl;

    cout << "*** Test 17 ***" << endl << endl;
    // Assignment operator

    String s13 = "moat";
    String s14 = "coat";

    s13 = s14;

    s14[2] = 's';

    cout << s13 << " " << s14 << endl;

    cout << "*** Test 18 ***" << endl << endl;
    // Assignment operator
    String s15 = "No problem";

    s15 = s15;

    String s16 = "Memory leak";

    cout << s15 << endl;
//
    cout << "*** Test 19 ***" << endl << endl;
    // Assignment operator
    s16 = "Right.";
    String s17;
    String s18 = "Wrong";

    s18 = s17 = s16;

    cout << s18 << endl;
//
    cout << "*** Test 20 ***" << endl << endl;
    // Character concatenation

    String s19;

    s19 = s19 + 'T' + 'h' + 'i' + 'n' + 'k' + '!';
    cout << s19 << endl;

    cout << "*** Test 21 ***" << endl << endl;
    // String concatenation

    String s20 = "Delta";
    String s21 = "Gamma";
    String s22;

    s22 = s20 + s21;

    cout << s20 << " " << s21 << " " << s22 << endl;

    cout << "*** Test 22 ***" << endl << endl;
    // String return
    String s23 = "Bibbidy";
    String s24 = "Bobbidy";
    String s25;

    s25 = function1(s23, s24);

    cout << s25 << endl;

    s25 = function2(s23, s24);

    cout << s25 << endl;

}


String function1(const String & first, const String & second)
{
    String result = first + " " + second + " Boo!";

    return result;
}

String function2(const String first, const String second)
{
    String result = first + " " + second + " Too!";

    return result;
}

void test_relationship(const String& first, const String& second)
{
    // Compare the two strings in every way possible
    // and print out the results


    cout << "Comparing \"" << first <<"\" and \"" << second <<  "\"" << endl;

    // Less than
    cout << "   <    ";
    if(first < second)   cout << "Yes" << endl;
    else                 cout << "No" << endl;

    // Less than or equal
    cout << "   <=   ";
    if(first <= second)  cout << "Yes" << endl;
    else                 cout << "No" << endl;

    // Greater than
    cout << "   >    ";
    if(first > second)   cout << "Yes" << endl;
    else                 cout << "No" << endl;

    // Greater than
    cout << "   >=   ";
    if(first >= second)  cout << "Yes" << endl;
    else                 cout << "No" << endl;

    // Equality
    cout << "   ==   ";
    if(first == second)  cout << "Yes" << endl;
    else                 cout << "No" << endl;

    // Inequality
    cout << "   !=   ";
    if(first != second)  cout << "Yes" << endl;
    else                 cout << "No" << endl;

    cout << endl;
}
