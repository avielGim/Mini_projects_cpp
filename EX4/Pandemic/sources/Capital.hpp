#pragma once
#include <set>

#include "City.hpp"

namespace pandemic{
    class Capital{
        Color _color;
        int _lvl;
        std::set<City> _nei;

    public:
        Capital() {}
        Capital(Color color, City a1, City a2 = City::DEFUALT 
                            ,City a3 = City::DEFUALT, City a4 = City::DEFUALT
                            ,City a5 = City::DEFUALT, City a6 = City::DEFUALT);
        int& get_lvl() {return _lvl;}  
        Color get_color() {return _color;}
        bool is_neighbor(City city) {return _nei.contains(city);}

        friend std::ostream& operator<<(std::ostream&, const Capital&);

    };
}