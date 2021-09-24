#pragma once
#include "Player.hpp"

namespace pandemic{
    class Researcher: public Player{

    public:
        Researcher(Board& board, City city)
            : Player(board, city){}
        
        Researcher& discover_cure(Color color);
        const std::string role() {return "Researcher";}
    };
}