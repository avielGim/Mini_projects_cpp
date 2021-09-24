#pragma once
#include <array>

#include "Capital.hpp"

namespace pandemic{

    const int NUM_OF_CITY = 48;
    const int NUM_OF_COLOR = 4;

    class Board{
        std::array<Capital, NUM_OF_CITY> _town {};
        std::array<bool, NUM_OF_COLOR> _cure {};
        std::set<City> _res;

        void init_town();
        
    public:
        Board();
        bool is_clean();
        void remove_cures();
        void remove_stations() {_res.clear();}
        
        //The addition of my functions 
        Capital& at(City city) {return _town.at(city);}
        bool& is_cure(Color color){return _cure.at(color);}
        bool is_research(City city) {return _res.contains(city);}
        void add_research(City city) {_res.insert(city);}
        void delete_research(City city) {_res.erase(city);}        
        
        //operator
        int& operator[](City);
        friend std::ostream& operator<<(std::ostream&, const Board&);
    };




}