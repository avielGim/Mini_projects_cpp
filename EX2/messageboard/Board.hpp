#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include "Direction.hpp"

namespace ariel{
    class Board{
        std::map<unsigned int, std::map<unsigned int,char>> my_map;
        unsigned int start_x, start_y, end_x, end_y;
    public:
        Board() {
            start_x = start_y = 4294967295;
            end_x = end_y = 0;
        }
        void post(unsigned int row, unsigned int column, Direction dir, std::string str);

        std::string read(unsigned int row, unsigned int column, Direction dir, unsigned int len);

        void show();

        void check_limit(unsigned int x, unsigned int y, unsigned int len);

        void check_hori(unsigned int x, unsigned int y, unsigned int len);

        void check_vec(unsigned int x, unsigned int y, unsigned int len);
        
    };
}