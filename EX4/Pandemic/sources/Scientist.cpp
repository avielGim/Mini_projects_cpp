#include "Scientist.hpp"

namespace pandemic{
    Scientist& Scientist::discover_cure(Color color){
        if(!(_board.is_research(_city))){
            throw std::out_of_range{"the action \"discover-cure\" is not possible"};
        }
        if(_board.is_cure(color)){
            return *this;
        }
        std::array<City, MINIMUM_CARDS> arr {};
        uint counter = 0;
        for(City temp: _card){
            Capital capi = _board.at(temp);
            if(capi.get_color() == color && counter < _n){
                arr.at(counter++) = temp;
            }
        }
        if(counter == _n){
            for(uint i = 0; i < counter; i++){
                _card.erase(arr.at(i));
            }
            _board.is_cure(color) = true;
            return *this;
        }    
        throw std::out_of_range{"there is not enough card to discover cure!"};   
    }
}
