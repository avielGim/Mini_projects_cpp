#include "GeneSplicer.hpp"

namespace pandemic{

    GeneSplicer& GeneSplicer::discover_cure(Color color){
        if(!(_board.is_research(_city))){
            throw std::out_of_range{"the action \"discover-cure\" is not possible"};
        }
        if(_board.is_cure(color)){
            return *this;
        }
        std::array<City,MINIMUM_CARDS> arr {};
        uint counter = 0;
        for(City temp: _card){
            if(counter < MINIMUM_CARDS){
                arr.at(counter++) = temp;
            }
        }
        if(counter == MINIMUM_CARDS){
            for(uint i = 0; i < counter; i++){
                _card.erase(arr.at(i));
            }
            _board.is_cure(color) = true;
            return *this;
        }
        throw std::out_of_range{"the action is not possible"};
    }
}

