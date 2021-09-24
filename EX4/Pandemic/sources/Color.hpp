#pragma once
#include <iostream>
#include <string>
#include <map>

namespace pandemic{
    enum Color{
        Yellow,
        Blue,
        Black,
        Red
    };
    
    void init_enum_color(std::map<Color, std::string>& my_color);
    std::ostream& operator<<(std::ostream& out, const Color value);
}
