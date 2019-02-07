#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <list>
#include <queue>
#include <set>
#include <stack>

//using std::ifstream;
//using std::array;
//using std::cout;
//using std::endl;
//using std::vector;
//using std::string;
//using std::map;
//using std::cerr;
using namespace std;

/*
 *
 * In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following steps:

    Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
    Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.

Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?
 */

int solution(vector<string> &L);

int main() {
//
//    vector<string> vec;
//    std::cout << "Hello, World!" << std::endl;
//    array<int,3> arr = {1,2,3};
//
//
//    for(int i=0;i<arr.size();i++){
//        cout << arr.at(i) << " ";
//    }
//    for(int i : arr){
//        cout << i << " ";
//    }
//
//
//    cout << endl;
//
//    string s = "string";
//    vec.push_back("this ");
//    vec.push_back("is ");
//    vec.push_back("a ");
//    vec.push_back(s);
//
//    for(auto str:vec){
//        cout << str;
//    }
//    cout << endl;

//    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//
//    cout << alphabet.find('H');


//    map<string,int> logMap;
//
//    ifstream file;
//    file.open("log.txt");
//
//    if(!file){
//        cerr << "Unable to open the file" << endl;
//        exit(1);
//    }else{
//        string pName;
//        int pStatus;
//
//        file >> pName;
//        file >> pStatus;
//
//        while(!file.eof()) {
//            if (pStatus == 0) {
//                logMap[pName]++;
//            }else if(pStatus == 1){
//                logMap[pName]--;
//            }
//            file >> pName;
//            file >> pStatus;
//        }
//
//        for(auto &x:logMap){
//            ++x.second;
//            cout << x.first << " : " << x.second << endl;
//        }
//        cout << endl;
//        for(auto x:logMap){
//            cout << x.first << " : " << x.second<<endl;
//        }
//        cout << endl;
//
//        // Create a list containing integers
//        std::list<int> l = { 7, 5, 16, 8 };
//
//        // Add an integer to the front of the list
//        l.push_front(25);
//        // Add an integer to the back of the list
//        l.push_back(13);
//
//        // Insert an integer before 16 by searching
//        auto it = std::find(l.begin(), l.end(), 16);
//        if (it != l.end()) {
//            l.insert(it, 42);
//        }
//
//        // Iterate and print values of the list
//        for (int n : l) {
//            std::cout << n << '\n';
//        }
//
//    }
//    string s1 = "2-4A0r7-4k";
//    string s = solution(s1,4);
//    cout << s;


    str.

    return 0;

}

int solution(vector<string> &L) {
    // write your code in C++14 (g++ 6.2.0)
    map<string,int> mailMap;
    for(auto mail: L){

    }
}

string parseMail(string &mail){



//string solution(string &S, int K) {
//    stack<char> stringStack;
//    string newKey;
//
//    for(unsigned i=0;i<S.length();i++) {
//        if (S.at(i) != '-') {
//            stringStack.push(toupper(S.at(i)));
//        }
//    }
//    int i=0;
//    while(!stringStack.empty()){
//        newKey+=(stringStack.top());
//        stringStack.pop();
//        i++;
//        if(i%K==0){
//            newKey+='-';
//        }
//    }
//    // write your code in C++14 (g++ 6.2.0)
//    reverse(newKey.begin(),newKey.end());
//    return newKey;
//}

//this algorithm goes through the whole vector just once, so the time complexity will be
//linear over the input size N.

//The algorithm also odesn't use any additional data structure beside some variables,
//so the space complexity of the algorithm is constant for the input size N
    int solution(vector<int> &A) {
        const int UNMATCHED=-1;
        //we have to int to store which one are the first and
        //second element matched in the sequence
        int firstMatch=UNMATCHED, secondMatch=UNMATCHED;
        //an integer to save the maximum length of a found sequence
        int maxSize=0;
        //and an integer to save the size of the sequence we are currently analyzing
        //We initialize the current size to zero, so that if the vector is empty we can
        //return the matched size to zero
        int currSize=0;

        //we loop over the vector
        for(auto &curr:A){
            //if we haven't initialized the first match, we do it
            if(firstMatch==UNMATCHED){
                //we set the firt match to the current element
                firstMatch=curr;
                //and we set the current size to 1. This is necessary in case the sequence is
                //just a single element. so the maximum size is one
                currSize++;
                //and then we continue, as we are done with the current element
                continue;
            }else if(secondMatch==UNMATCHED && curr !=firstMatch){ //if we already found the first match, we check if we found the second match
                //if the second match is umatched, and is different from the first match, so if we have [ 1 1 2], we don't need to consider
                // 1 as a second match, but just increase the size of the sequence
                //then the current becomes the second match
                secondMatch=curr;
                //and we insert the current sequence size to 2
                currSize++;
                //and we continue, as we are done with the current element
                continue;
            }

            //if we reach here, it means that we already have a first and second match, if so
            //then if the current element is equal to one of them, we increase the current size
            if(curr == firstMatch || curr==secondMatch){
                currSize++;

            }else{//if the are different, we initialyze a new sequence and compare the found length with the maximum one
                //we set the different element to be the new first match
                firstMatch=curr;
                //and set the second to unmatched
                secondMatch=UNMATCHED;
                //if the calculated size is bigger than the maximum, we update the maximum
                if(currSize>maxSize){
                    maxSize=currSize;
                }
                //and rezet the size to one, as we set the firstmatch to curr, so it's already one element in the size
                currSize=1;
            }
        }
        //In case the whole array is composed of just two types of numbers, or if the longest sequence
        //is at the end of the array, as the foor loop updates the maxSize only when we switch to a different
        //kind of sequence. so if 1 2 1 3, it will update the max when finds the 3. but if the sequence is
        // [1 2 1 2 1 2 ], then we won't have a mismatch of the first and second metch, so it need to update when
        //outside the loop
        if(currSize>maxSize){
            maxSize=currSize;
        }

        //we return the maximum size
        return maxSize;
    }