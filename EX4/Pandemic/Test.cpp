#include "doctest.h"
#include <iostream>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

TEST_CASE("init board"){
    Board board_init;
    CHECK(board_init.is_clean() == true);
    CHECK_NOTHROW(board_init[City::Johannesburg] = 3);
    CHECK(board_init[City::Johannesburg] == 3);
    CHECK_NOTHROW(board_init[City::London] = 7);
    CHECK(board_init[City::London] == 7);
    CHECK_NOTHROW(board_init[City::Istanbul] = 1);
    CHECK(board_init[City::Istanbul] == 1);
    CHECK_NOTHROW(board_init[City::Taipei] = 4);
    board_init[City::Taipei] = 12;
    CHECK(board_init[City::Taipei] == 12);

    CHECK(board_init.is_clean() == false);   
}

TEST_CASE("Medic"){
    Board board_play;
    Medic medic{board_play, City::Madrid};
    CHECK(medic.role() == "Medic");
    CHECK_NOTHROW(medic.drive(City::NewYork));
    CHECK_THROWS(medic.drive(City::Paris));
    CHECK_THROWS(medic.fly_direct(City::Paris));
    medic.take_card(City::Paris);
    CHECK_NOTHROW(medic.fly_direct(City::Paris));
    CHECK_THROWS(medic.fly_charter(City::StPetersburg));
    medic.take_card(City::Paris);
    CHECK_NOTHROW(medic.fly_charter(City::StPetersburg));
    CHECK_NOTHROW(medic.drive(City::Moscow));
    medic.take_card(City::Jakarta);
    CHECK_NOTHROW(medic.fly_direct(City::Jakarta));
    CHECK(medic.role() == "Medic");

    OperationsExpert exp{board_play, City::Tokyo};
    CHECK_NOTHROW(exp.build());
    CHECK(exp.role() == "OperationsExpert");

    board_play[City::Moscow] = 1;
    Virologist viro{board_play, City::Manila};
    viro.take_card(City::Moscow);
    CHECK_NOTHROW(viro.treat(City::Moscow));
    CHECK(board_play[City::Moscow] == 0);
    CHECK(viro.role() == "Virologist");
}
