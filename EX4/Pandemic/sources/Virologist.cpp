#include "Virologist.hpp"

namespace pandemic{
    Virologist& Virologist::treat(City other){
        if(_city == other){
            Player::treat(other);
            return *this;
        }
        if(!(_card.contains(other)) || _board.at(other).get_lvl() == 0){
            throw std::out_of_range{"the action \"treat\" is not possible"};
        }
        Capital capi = _board.at(other);
        Color col = capi.get_color();
        if(_board.is_cure(col)){
             _board.at(other).get_lvl() = 0;
        }
        else{
            _board.at(other).get_lvl()--;
        }
        _card.erase(other);
        return *this;
    }
}