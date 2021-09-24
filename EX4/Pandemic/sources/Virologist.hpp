#pragma once
#include "Player.hpp"

namespace pandemic{
    class Virologist: public Player{

    public:
        Virologist(Board& board, City city)
            : Player(board, city){}
        
        Virologist& treat(City);
        const std::string role() {return "Virologist";}
    };
}