#include "FieldDoctor.hpp"

namespace pandemic{

    FieldDoctor& FieldDoctor::treat(City other){
        if((_city != other && !( _board.at(_city).is_neighbor(other))) || _board.at(other).get_lvl() == 0){
            throw std::out_of_range{"The disease cannot be treated remotely!"};
        }
        Color col = _board.at(other).get_color();
        if(_board.is_cure(col)){
            _board.at(other).get_lvl() = 0;
        }
        else{
            _board.at(other).get_lvl()--;
        }
        return *this;
    }
}