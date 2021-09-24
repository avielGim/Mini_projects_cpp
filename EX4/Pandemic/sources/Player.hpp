#pragma once
#include "Board.hpp"

namespace pandemic{

    const int MINIMUM_CARDS = 5;

    class Player{
    protected:
        Board& _board;
        City _city;
        std::set<City> _card;

        bool diff_city(City other) {return (_city != other);}

    public:
        Player(Board& board, City city)
            : _city(city),_board(board){}
        virtual Player& drive(City);
        virtual Player& fly_direct(City);
        virtual Player& fly_charter(City);
        virtual Player& fly_shuttle(City);
        virtual Player& build();
        virtual Player& discover_cure(Color);
        virtual Player& treat(City);

        void remove_cards() {_card.clear();}

        Player& take_card(City);
        virtual const std::string role() {return "player";}

        friend std::ostream& operator<<(std::ostream& out, const Player& p); 

        //print the board
        void syso_board() {std::cout << _board << std::endl;}
    };
}