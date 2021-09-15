#include <iostream>
#include <stdexcept>
#include <cmath>
#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;


array<string, 11> unit_name = {"km" , "m" , "cm" , "ton", "kg", "g" , "hour" , "min" , "sec", "USD","ILS"};

/**
 * write file,read from it and check if creating new objects succefuly.
 * then input new file with new unit names and create new objects with the new units.
 * check that no exeption is thrown when the given unit is in the input files.
 */
TEST_CASE("Open, read and new name unit"){
    //create file with the unit from the git.
    ofstream init_file{"unit.txt"};
    init_file << "1 km = 1000 m" << endl;
    init_file << "1 m = 100 cm" << endl;
    init_file << "1 kg = 1000 g" << endl;
    init_file << "1 ton = 1000 kg" << endl;
    init_file << "1 hour = 60 min" << endl;
    init_file << "1 min = 60 sec" << endl;
    init_file << "1 USD = 3.33 ILS" << endl;

    ifstream units_file{"unit.txt"};

    CHECK_NOTHROW(NumberWithUnits::read_units(units_file));

    //good parameters for the constructor
    CHECK_NOTHROW(NumberWithUnits a1(5,"km"));
    CHECK_NOTHROW(NumberWithUnits a2(4.201,"cm"));
    CHECK_NOTHROW(NumberWithUnits a2(4.201,"sec"));
    CHECK_NOTHROW(NumberWithUnits a3(1050,"min"));
    CHECK_NOTHROW(NumberWithUnits a4(1.3,"ILS"));
    //not good - diffrent big and little letters
    CHECK_THROWS(NumberWithUnits a5(5,"Km"));
    CHECK_THROWS(NumberWithUnits a6(5,"mIN"));
    CHECK_THROWS(NumberWithUnits a7(5,"ils"));
    CHECK_THROWS(NumberWithUnits a8(5,"UsD"));
    //the given unit does not exist
    CHECK_THROWS(NumberWithUnits a9(5,"ml"));  
    CHECK_THROWS(NumberWithUnits a10(5,"dolar"));
    CHECK_THROWS(NumberWithUnits a11(5,"s"));

    //add new unit to a new file
    ofstream write_file{"new_unit.txt"};
    write_file << "1 l = 1000 ml" << endl;
    write_file << "1 temp_1 = 6.5 temp_2";
    write_file.close();
    //than create an object with the new unit
    ifstream read_file{"new_unit.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(read_file));
    CHECK_NOTHROW(NumberWithUnits a12(1000,"ml"));
    CHECK_NOTHROW(NumberWithUnits a13(2.2,"l"));
    CHECK_NOTHROW(NumberWithUnits a13(2.2,"temp_1"));
    CHECK_NOTHROW(NumberWithUnits a13(1000,"temp_2"));
    read_file.close();
}

ifstream units_file{"unit.txt"};

/**
 * Export the objects to file with the name "object_1.txt",
 * and then check if they are as we wanted by equal them to string.
 * After that create new objects by input, and use the operator == to check
 * if they are as the object that in the file.
 * check the operator << , >> , ==.
 */
TEST_CASE("Export and create new objects by input"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits write1(502,"m");
    NumberWithUnits write2(4.21,"kg");
    NumberWithUnits write3(4.21,"hour");
    NumberWithUnits write4(74.21,"sec");
    NumberWithUnits write5(63.2,"USD");
    ofstream write_file{"object.txt"}; 
    write_file << write1 << ' ' << write2 << ' ' << write3 << ' ' <<  write4 << ' ' <<  write5;
    write_file.close();
    
    ifstream read_file_string{"object.txt"};
    string input;
    if(read_file_string >> input){
        CHECK(input == "502[m]");
    }
    if(read_file_string >> input){
        CHECK(input == "4.21[kg]");
    }
    if(read_file_string >> input){
        CHECK(input == "4.21[hour]");
    }
    if(read_file_string >> input){
        CHECK(input == "74.21[sec]");
    }
    if(read_file_string >> input){
        CHECK(input == "63.2[USD]");
    }
    read_file_string.close();

    ifstream read_file_unit{"object.txt"};  
    NumberWithUnits read;
    if(read_file_unit >> read){
        CHECK((read == write1) == 1);
    }
    if(read_file_unit >> read){
        CHECK((read == write2) == 1);
    }
    if(read_file_unit >> read){
        CHECK((read == write3) == 1);
    }
    if(read_file_unit >> read){
        CHECK((read == write4) == 1);
    }
    if(read_file_unit >> read){
        CHECK((read == write5) == 1);
    }
    read_file_unit.close();
}

/**
 * Check if all operator throw ecxeption if the two given math calculate
 * are in the same sub unit name.
 * check the functions from the kind "boolean operator" (==, > != ...) 
 * catch exeption - if the subunit are differents.
 */ 
TEST_CASE("doesn't have the same subunit"){
    NumberWithUnits::read_units(units_file);
    for(int i = 0; i < 3; i++){
        double random = rand()+100;
        unsigned long choose_unit = rand()%11;
        if(choose_unit == 10 || choose_unit == 11 ){
            choose_unit -= 3;
        }
        NumberWithUnits t1{random, unit_name.at(choose_unit)};
        NumberWithUnits t2{random, unit_name.at(choose_unit+3)};
        //equal,greater,smaller
        CHECK_THROWS_AS(if(t1 == t2), exception);
        CHECK_THROWS_AS(if(t1 != t2), exception);
        CHECK_THROWS_AS(if(t1 <= t2), exception);
        CHECK_THROWS_AS(if(t1 >= t2), exception);
        CHECK_THROWS_AS(if(t1 < t2), exception);
        CHECK_THROWS_AS(if(t1 > t2), exception);
        //+ += ++
        CHECK_THROWS(t1 + t2);
        CHECK_THROWS(t1 += t2);
        //- -= --
        CHECK_THROWS(t1 - t2);
        CHECK_THROWS(t1 -= t2);
    }
}

/**
 * Good math algorithms - check the outcome of the operators like
 *      -(object1 + object2)
 *      -(object2 + object1)
 *      -(object1 +=  object2)
 */ 
TEST_CASE("Convert units - PLUS"){  
    NumberWithUnits::read_units(units_file);
    NumberWithUnits plus1(3,unit_name.at(0));
    NumberWithUnits plus2(40,unit_name.at(1));

    NumberWithUnits plus3 = plus1 + plus2; 
    NumberWithUnits ans_plus_1{3.04,unit_name.at(0)};
    CHECK((plus3 == ans_plus_1) == 1);

    NumberWithUnits plus4 = plus2 + plus1; 
    NumberWithUnits ans_plus_2{3040,unit_name.at(1)};
    CHECK((plus4 == ans_plus_2) == 1);

    CHECK((ans_plus_1 == ans_plus_1) == 1);   //plus1 + plus2 == plus2 + plus1

    CHECK((plus1 != plus3) == 1);  //plus1 != plus1 + plus2
    CHECK((plus2 < plus4) == 1);   //plus2 < plus2 + plus1
    CHECK((plus3 > plus1) == 1);   //plus1 + plus2 > plus1
    CHECK((plus4 >= plus3) == 1);  //plus1 + plus2 >= plus2 + plus1
    CHECK((plus2 <= plus3) == 1);  //plus2 <=>= plus1 + plus2

    plus4 += plus1;
    NumberWithUnits ans_plus_3{6040,unit_name.at(1)};
    CHECK((plus4 == ans_plus_3) == 1);
}

/**
 * Good math algorithms - check the outcome of the operators like
 *      -(object1 - object2)
 *      -(object2 - object1)
 *      -(object1 -=  object2)
 */ 
TEST_CASE("Convert units - MINUS"){   
    NumberWithUnits::read_units(units_file);
    NumberWithUnits minus1(2,unit_name.at(3)); 
    NumberWithUnits minus2(5000,unit_name.at(5)); 
    NumberWithUnits minus3 = minus1 - minus2;
    NumberWithUnits ans_minus_1{1.995, unit_name.at(3)};
    CHECK((minus3 == ans_minus_1) == 1);

    NumberWithUnits minus4 = minus2 - minus1;
    NumberWithUnits ans_minus_2{-1995000, unit_name.at(5)};
    CHECK((minus4 == ans_minus_2) == 1); 
    NumberWithUnits minus5 = -(minus2 - minus1);
    CHECK((minus5 == ans_minus_2) == 0);

    CHECK((ans_minus_1 != ans_minus_2) == 1);

    CHECK((minus3 == minus2) == 0);
    CHECK((minus2 < minus4) == 0);
    CHECK((minus3 > minus1) == 0);
    CHECK((minus2 >= minus1) == 0);
    CHECK((minus1 <= minus2) == 0);
    minus4 -= minus2;
    NumberWithUnits ans_minus_4{-2, unit_name.at(3)};
    CHECK((minus4 == -minus1) == 1);
}

/**
 * Good math algorithms - check the outcome of the operators like
 *      -(++object1), (object1++)
 *      -(--object1), (object1--)
 *      -("double"*object1), (object1*"double")
 */ 
TEST_CASE("Convert units - POSTFIX, PREFIX and MULTIPLICATION"){  
    NumberWithUnits::read_units(units_file);
    NumberWithUnits C1(90,unit_name.at(7));
    NumberWithUnits C2 = --C1;
    NumberWithUnits ans_1(5340,unit_name.at(8));//
    NumberWithUnits C3 = C1--;
    NumberWithUnits ans_2(5280,unit_name.at(8));//
    NumberWithUnits C4 = ++C1; 
    NumberWithUnits ans_3(89,unit_name.at(7));
    CHECK((C1 == ans_3) == 1);
    NumberWithUnits C5 = C1++; 
    NumberWithUnits ans_4(1.5,unit_name.at(6)); 
    CHECK((C2 == C3) == 1);
    CHECK((C1 > ans_1) == 1);
    CHECK((C3 != ans_2) == 1);

    CHECK((C1 == ans_4) == 1);
    CHECK((C4 > ans_2) == 1);
    CHECK((C2 < C1) == 1);

    ans_4++;
    ans_2--;
    CHECK((ans_4 == NumberWithUnits{2.5,unit_name.at(6)}) == 1);
    CHECK((ans_2 == NumberWithUnits{1.4663888888,unit_name.at(6)}) == 1);

    NumberWithUnits C6 = C1 * 3.3; 
    NumberWithUnits ans_multy_1{297,unit_name.at(7)};
    NumberWithUnits C7 = 2.7 * C1; 
    NumberWithUnits ans_multy_2{243,unit_name.at(7)};
    CHECK((C7 < C6) == 1);
    CHECK((ans_multy_1 == C6) == 1);
    CHECK((ans_multy_2 == C7) == 1);
}
