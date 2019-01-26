#include <iostream>

using namespace std;

int main(){
    int num;
    while(cin >> num){
        if(num == 0){
            cout << 0<<endl;
        }else{
            int digits = 1;

            while((num/10)!=0){
                num /=10;
                digits++;
            }
            cout << digits<<endl;
        }
    }
    return 0;
}
