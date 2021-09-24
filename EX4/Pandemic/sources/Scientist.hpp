#pragma once
#include "Player.hpp"

namespace pandemic{
    class Scientist: public Player{
        int _n;
    public:
        Scientist(Board& board, City city, int n)
            : Player(board, city), _n(n){}

        Scientist& discover_cure(Color);
        const std::string role() {return "Scientist";}
    };
}