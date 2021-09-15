#include <iostream>
#include "snowman.hpp"

/* this file demonstrate a program that get 8 digits and all of them between 1-4.
the program will ask from the user to inter correct number and if it, according to settings, 
good number it will print a snowman.
there are 4 try to inter correct number.  
*/

using namespace std;

int test_func(int num){
    try {
        cout << ariel::snowman(num) << endl;   // Exception - not a valid code
        return 0;
    } catch (exception& ex) {
        cout << ex.what() << endl;  // should print "Invalid code '5'"
    }
    cout << "*************\n\n" << endl;
    return 1;
}

int main(){
    int b = 1;
    for(int i = 0; i < 4 && b != 0; i++){
        int user_answer = 0;
        cout << "temp = " + to_string(i) + " left " + to_string(4-i) << endl;
        cout << "enter 8 digits all must be between 1-4 " << endl;
        cin >> user_answer;
        cout << "\n\n*************" << endl;
        b = test_func(user_answer);
        if(b == 0){
            cout << "good number " << endl;
        }
    }
    
    cout << "good bye" << endl;
    return 0;
}