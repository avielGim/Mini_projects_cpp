#include "Medic.hpp"

namespace pandemic{
    Medic& Medic::drive(City other){
        Capital temp = _board.at(_city);
        if(temp.is_neighbor(other) && Player::diff_city(other)){
            _city = other;
            Color color = _board.at(other).get_color();
            if(_board.is_cure(color)){
                _board.operator[](other) = 0;
            }
            return *this;
        }
        throw std::out_of_range{"the action is not possible"};
    }

    Medic& Medic::fly_direct(City other){
        if(_card.contains(other) && Player::diff_city(other)){
            _city = other;
            _card.erase(other);
            Color color = _board.at(other).get_color();
            if(_board.is_cure(color)){
                _board.operator[](other) = 0;
            }
            return *this;
        }
        throw std::out_of_range{"the action is not possible"};
    }

    Medic& Medic::fly_charter(City other){
        if(_card.contains(_city) && Player::diff_city(other)){
            _card.erase(_city);
            _city = other;
            Color color = _board.at(other).get_color();
            if(_board.is_cure(color)){
                _board.operator[](other) = 0;
            }
            return *this;
        }
        throw std::out_of_range{"the action is not possible"};
    }

    Medic& Medic::fly_shuttle(City other){
        if(_board.is_research(_city) && _board.is_research(other) && Player::diff_city(other)){
            _city = other;
            Color color = _board.at(other).get_color();
            if(_board.is_cure(color)){
                _board.operator[](other) = 0;
            }
            return *this;
        }
        throw std::out_of_range{"the action is not possible"};
    }

    Medic& Medic::treat(City other){
        if(!(Player::diff_city(other)) && _board.at(other).get_lvl() > 0){
            _board.at(other).get_lvl() = 0;
            return *this;
        }
        throw std::out_of_range{"the action \"treat\" is not possible"};
    }
}