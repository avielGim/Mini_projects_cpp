#include "Dispatcher.hpp"

namespace pandemic{
    Dispatcher& Dispatcher::fly_direct(City other){
        if(_board.is_research(_city) && Player::diff_city(other)){
            _city = other;
            return *this;
        }
        Player::fly_direct(other);
        return *this;
    }
}