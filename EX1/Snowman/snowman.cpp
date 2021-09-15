#include "snowman.hpp"

/* this file contains one big main function that build a snowman.
the function get number with 8 digits, all between 1-4
and make a snow man.
*/

const int LEN = 8;

namespace ariel{
    string snowman(int num){
        check_num(num);
        array<int,LEN> arr = {0};
        for(int i = B; i >= 0; i--){
            int temp = num %TEN;
            if(temp < 1 || temp > 4){
                throw out_of_range{"---all the digits need to be between 1-4---"};
            }
            arr.at(i) = temp;
            num /= TEN;
        }
        string t1;
        string t2 = "(" + eye.at(arr.at(L)-1) + nose_mouth.at(arr.at(N)-1) + eye.at(arr.at(R)-1) + ")";
        if(arr.at(Y) == 2 && arr.at(X) == 2) {
            t1 = x_hand.at(arr.at(X)-1) + t2 + y_hand.at(arr.at(Y)-1) + "\n " + torso.at(arr.at(T)-1) + " \n";
        }
        else if(arr.at(X) == 2) {
            t1 = x_hand.at(arr.at(X)-1) + t2 + " \n " + torso.at(arr.at(T)-1) + y_hand.at(arr.at(Y)-1) + "\n";
        }
        else if(arr.at(Y) == 2) {
            t1 = " " +  t2 + y_hand.at(arr.at(Y)-1) + "\n" + x_hand.at(arr.at(X)-1) + torso.at(arr.at(T)-1) + " \n";
        }
        else {
            t1 = " " +  t2 + " \n" + x_hand.at(arr.at(X)-1) + torso.at(arr.at(T)-1) + y_hand.at(arr.at(Y)-1) + "\n";
        }
        string ans = hat.at(arr.at(H)-1) + t1 + basis.at(arr.at(B)-1);
        return ans; 
    }

    void check_num(int num){
        if(num < 0){
            throw domain_error{"---the number must be positive!---"};
        }
        if(num > LENGTH || num < SMALLER){
            throw length_error{"---insert 8 digits!---"};
        }
        if(num > BIGGER || num == SMALLER){
            throw out_of_range{"---the number need to be between 11111111 to 44444444!---"};
        }
    }

}