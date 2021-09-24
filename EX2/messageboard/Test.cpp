#include <stdexcept>
#include "doctest.h"
#include "Board.hpp"
#include "Direction.hpp"

/*
this test post ad on the board and check if the read function is as we post - depends on "bad parameters for post" test.
*/
TEST_CASE("good test - read"){
    ariel::Board board;
    // read 0 char  
    CHECK(board.read(100, 200, ariel::Direction::Horizontal, 0) == "");
    CHECK(board.read(100, 200, ariel::Direction::Vertical, 0) == "");
    
    // post "abc" at (100,200) Direction = Horizontal
    board.post(100,200, ariel::Direction::Horizontal, "abcd");       
    // read Horizontal
    CHECK(board.read(100, 201, ariel::Direction::Horizontal, 6) == "bcd___");
    CHECK(board.read(99, 200, ariel::Direction::Horizontal, 4) == "____");
    CHECK(board.read(100, 198, ariel::Direction::Horizontal, 8) == "__abcd__");
    // read Vertical
    CHECK(board.read(100, 200, ariel::Direction::Vertical, 5) == "a____");
    CHECK(board.read(98, 201, ariel::Direction::Vertical, 4) == "__b_");
    CHECK(board.read(101, 200, ariel::Direction::Vertical, 5) == "_____");

    // post "abc" at (50,199) Direction = Horizontal
    board.post(110,200, ariel::Direction::Horizontal, "phone number - 050-9205..."); 
    // read Horizontal
    CHECK(board.read(110, 200, ariel::Direction::Horizontal, 26) == "phone number - 050-9205...");
    CHECK(board.read(110, 210, ariel::Direction::Horizontal, 5) == "er - ");
    CHECK(board.read(110, 215, ariel::Direction::Horizontal, 8) == "050-9205");
    // read Vertical
    CHECK(board.read(108, 200, ariel::Direction::Vertical, 5) == "__p__");
    CHECK(board.read(112, 200, ariel::Direction::Vertical, 3) == "___");
    CHECK(board.read(107, 215, ariel::Direction::Vertical, 6) == "___0__");

    // post "hello world" at (100,200) Direction = Vertical - Overrides the previous letter
    board.post(100,200, ariel::Direction::Vertical, "hello world");      
    // read Horizontal
    CHECK(board.read(100, 200, ariel::Direction::Horizontal, 5) == "hbcd_");
    CHECK(board.read(102, 200, ariel::Direction::Horizontal, 4) == "l___");
    CHECK(board.read(100, 202, ariel::Direction::Horizontal, 4) == "cd__");
    CHECK(board.read(110, 200, ariel::Direction::Horizontal, 5) == "dhone");
    // read Vertical
    CHECK(board.read(100, 200, ariel::Direction::Vertical, 11) == "hello world");
    CHECK(board.read(98, 200, ariel::Direction::Vertical, 3) == "__h");
    CHECK(board.read(104, 200, ariel::Direction::Vertical, 5) == "o wor");
    CHECK(board.read(108, 200, ariel::Direction::Vertical, 5) == "rld__");

    // nothing is post     
    // read Horizontal
    CHECK(board.read(452515, 215215, ariel::Direction::Horizontal, 7) == "_______");
    // read Vertical
    CHECK(board.read(752152, 512342, ariel::Direction::Vertical, 7) == "_______");
}

