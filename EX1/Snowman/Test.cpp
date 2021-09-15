#include <stdexcept>
#include <cmath>
#include <string>
#include "doctest.h"
#include "snowman.hpp"

using namespace std;

string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

/*
1-10 currect number between 11111111 to 44444444  and all numbers between 1-4
first check all the number between 1-4
than add some random number - between 1-4 to verify.
*/
TEST_CASE("good num"){
    CHECK(nospaces(ariel::snowman(11111111)) == nospaces(" _===_\n (.,.) \n<( : )>\n ( : )\n"));  
    /*
     _===_
     (.,.) 
    <( : )>
     ( : )
    */
    CHECK(nospaces(ariel::snowman(22222222)) == nospaces("  ___\n .....\n\\(o.o)/\n (] [) \n (\" \")\n"));
    /*
      ___
     .....
    \(o.o)/
     (] [) 
     (\" \")
    */
    CHECK(nospaces(ariel::snowman(33333333)) == nospaces("   _\n  /_\\\n (O_O) \n/(> <)\\\n (___)\n")); 
    /*
       _
      /_\
     (O_O) 
    /(> <)\
     (___)
    */
    CHECK(nospaces(ariel::snowman(44444444)) == nospaces("  ___\n (_*_)\n (- -) \n (   ) \n (   )\n")); 
    /*
      ___
     (_*_)
     (- -) 
     (   ) 
     (   )
    */
    CHECK(nospaces(ariel::snowman(12341234)) == nospaces(" _===_\n (O.-)/\n<(> <) \n (   )\n")); 
    /*
     _===_
     (O.-)/
    <(> <) 
     (   )
    */
    CHECK(nospaces(ariel::snowman(43214321)) == nospaces("  ___\n (_*_)\n (o_.) \n (] [)\\\n ( : )\n")); 
    /*
      ___
     (_*_)
     (o_.) 
     (] [)\
     ( : )
    */
    CHECK(nospaces(ariel::snowman(33232124)) == nospaces("   _\n  /_\\\n\\(o_O) \n (] [)>\n (   )\n"));
    /*
       _
      /_\
    \(o_O) 
     (] [)>
     (   )
    */
    CHECK(nospaces(ariel::snowman(11114411)) == nospaces(" _===_\n (.,.) \n ( : ) \n ( : )\n")); 
    /*
     _===_
     (.,.) 
     ( : ) 
     ( : )
    */
    CHECK(nospaces(ariel::snowman(32414231)) == nospaces("   _\n  /_\\\n (-..)/\n (> <) \n ( : )\n")); 
    /*
       _
      /_\
     (-..)/
     (> <) 
     ( : )
    */
    CHECK(nospaces(ariel::snowman(24112231)) == nospaces("  ___\n .....\n\\(. .)/\n (> <) \n ( : )\n")); 
    /*
      ___
     .....
    \(. .)/
     (> <) 
     ( : )
    */

}

/*
1-4 check that some exception is thrown
negative number, length number < || > 8, contains number < 1 || number > 4
*/
TEST_CASE("throw exception"){
    CHECK_THROWS(ariel::snowman(-11111111));
    CHECK_THROWS(ariel::snowman(222222222));
    CHECK_THROWS(ariel::snowman(41));
    CHECK_THROWS(ariel::snowman(22202222));
    CHECK_THROWS(ariel::snowman(22272222));
}

//1 - negative number.
TEST_CASE("exception negative number"){
    CHECK_THROWS_AS(ariel::snowman(-21312111) , std::domain_error);
}

//2 - 12 - out_of_range - contains number < 1 || number > 4
TEST_CASE("exception full number"){
    CHECK_THROWS_AS(ariel::snowman(62143213) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(21452312) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(99999999) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(11111110) , std::out_of_range);

    CHECK_THROWS_AS(ariel::snowman(20222222) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(22522222) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(33363333) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(11117111) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(11111811) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(11111191) , std::out_of_range);
    CHECK_THROWS_AS(ariel::snowman(22222225) , std::out_of_range);
}

// loop - 13 - 18 - check at randomly 10 option of every hezka of 10 until 11111111. not incoude
TEST_CASE("exception length"){
    //check numbers between 0-10
    for(int i=0; i<10; i++){
        int random= (rand()%10);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    //check numbers between 10 - 100
    for(int i=0; i< 10; i++){
        int random= (rand()%90 +10);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    //check numbers between 100-1000
    for(int i=0; i<10; i++){
        int random= (rand()%900+100);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    //check number between 1000- 10000
    for(int i=0 ; i<10; i++){
        int random = (rand()%9000 +1000);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    //check number between 10000- 100000
    for(int i=0 ; i<10; i++){
        int random = (rand()%90000 +10000);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    //check number between 100000- 10000000
    for(int i=0 ; i<10; i++){
        int random = (rand()%900000 +100000);
        CHECK_THROWS_AS(ariel::snowman(random) , std::length_error);
    }

    CHECK_THROWS_AS(ariel::snowman(123456789) , std::length_error);
    CHECK_THROWS_AS(ariel::snowman(1234567890) , std::length_error);
}
