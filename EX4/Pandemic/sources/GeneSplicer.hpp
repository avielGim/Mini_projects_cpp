#pragma once
#include "Player.hpp"

namespace pandemic{
    class GeneSplicer: public Player{
    
    public:
        GeneSplicer(Board& board, City city)
            : Player(board, city){}
        
        GeneSplicer& discover_cure(Color);
        const std::string role() {return "GeneSplicer";}

    };
}