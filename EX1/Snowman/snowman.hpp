
#include <string>
#include <iostream>
#include <array>
using namespace std;

namespace ariel{
    string snowman(int num);
    void check_num(int num);

    const int TEN = 10;
    const int BIGGER = 44444444;
    const int SMALLER = 11111110;
    const int LENGTH = 99999999;
    
    const int B = 7;
    const int T = 6;
    const int Y = 5;
    const int X = 4;
    const int R = 3;
    const int L = 2;
    const int N = 1;
    const int H = 0; 

    const array<string,X> hat = {" _===_\n", "  ___\n .....\n", "   _\n  /_\\\n", "  ___\n (_*_)\n"}; 
    const array<string,X> nose_mouth = {",", ".", "_", " "};
    const array<string,X> eye = {".", "o", "O", "-"};
    const array<string,X> x_hand = {"<", "\\", "/", " "};
    const array<string,X> y_hand = {">", "/", "\\", " "};
    const array<string,X> torso = {"( : )","(] [)","(> <)","(   )"};
    const array<string,X> basis = {" ( : )\n"," (\" \")\n"," (___)\n"," (   )\n"};
}
