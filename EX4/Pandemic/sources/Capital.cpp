#include "Capital.hpp"

namespace pandemic{
    Capital::Capital(Color color, City a1, City a2 
                ,City a3, City a4
                ,City a5, City a6)
            : _color(color), _lvl(0){
                _nei.insert(a1);
                _nei.insert(a2);
                _nei.insert(a3);
                _nei.insert(a3);
                _nei.insert(a4);
                _nei.insert(a5);
                _nei.insert(a6);
        }

    std::ostream& operator<<(std::ostream& out , const Capital& capi){
        out << "\nthe number of the cube: " << capi._lvl;
        out << " COLOR: " << capi._color << "\n";
         out << "--------neighbors---------" << "\n";
        for(auto const& x : capi._nei){
            if(x != City::DEFUALT){
                out << "\t* " << (int)x << " - " << (City)x << "\n";
            }
        }
        return out;
    }
}