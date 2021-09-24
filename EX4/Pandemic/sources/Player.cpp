#include "Player.hpp"
#include <stdexcept>
namespace pandemic{
    
    Player& Player::drive(City other){
        Capital temp = _board.at(_city);
        if(temp.is_neighbor(other) && diff_city(other)){
            _city = other;
            return *this;
        }
        throw std::out_of_range{"the action \"drive\" is not possible"};
    }

    Player& Player::fly_direct(City other){
        if(_card.contains(other) && diff_city(other)){
            _city = other;
            _card.erase(other);
            return *this;
        }
        throw std::out_of_range{"the action \"fly-direct\" is not possible"};    
    }

    Player& Player::fly_charter(City other){
        if(_card.contains(_city) && diff_city(other)){
            _card.erase(_city);
            _city = other;
            return *this;
        }
        throw std::out_of_range{"the action \"fly-charter\" is not possible"};
    }

    Player& Player::fly_shuttle(City other){
        if(_board.is_research(_city) && _board.is_research(other) && diff_city(other)){
            _city = other;
            return *this;
        }
        throw std::out_of_range{"the action \"fly-shuttle\" is not possible"};
    }

    Player& Player::build(){
        if(_board.is_research(_city)){
            return *this;
        }
        if(_card.contains(_city)){
            _board.add_research(_city);
            _card.erase(_city);
            return *this;
        }
        throw std::out_of_range{"the action \"build\" is not possible"};

    }

    Player& Player::discover_cure(Color color){
        if(!(_board.is_research(_city))){
            throw std::out_of_range{"this station is not research station!"};
        }
        if(_board.is_cure(color)){
            return *this;
        }
        std::array<City,MINIMUM_CARDS> arr {};
        uint count = 0;
        for(City temp: _card){
            if(_board.at(temp).get_color() == color && count < MINIMUM_CARDS){
                arr.at(count++) = temp;
            }
        }
        if(count == MINIMUM_CARDS){
            for(uint i = 0; i < count; i++){
                _card.erase(arr.at(i));
            }
            _board.is_cure(color) = true;
            return *this;
        }
        throw std::out_of_range{"there is not enough cards to discover cure!"};
    }

    Player& Player::treat(City other){
        Capital capi = _board.at(_city);
        if(diff_city(other) || _board.at(_city).get_lvl() == 0){
            throw std::out_of_range{"the action \"treat\" is not possible"};
        }
        Color col = _board.at(_city).get_color();
        if(_board.is_cure(col)){
            _board.at(_city).get_lvl() = 0;
        }
        else{
            _board.at(_city).get_lvl()--;
        }
        return *this;
    }

    Player& Player::take_card(City city){
        _card.insert(city);
        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const Player& p){
        Capital capi = p._board.at(p._city);
        out << "you are at the city: " << p._city;
        out << capi;
        out << "--------card---------" << "\n";
        for(auto const& x : p._card){
            out << "\t* " << (int)x << " - " << x << " COLOR: " << p._board.at(x).get_color() << "\n";
        }
        out << "---------------------" << "\n";
        return out;
    }
}