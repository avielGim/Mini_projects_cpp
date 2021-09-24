
#include "Board.hpp"

//using namespace std;

namespace ariel{
    void Board::post(unsigned int row, unsigned int column, Direction dir, std::string str){
        unsigned int i = 0;
        check_limit(row, column, str.length());
        if(dir == Direction::Horizontal){
            check_hori(row, column, str.length());
            for(; i < str.length() ; i++){
                my_map[row][column++] = str.at(i);
            }
            return;
        }
        check_vec(row, column, str.length());
        for(; i < str.length() ; i++){
            my_map[row++][column] = str.at(i);
        }
    }

    std::string Board::read(unsigned int row, unsigned int column, Direction dir, unsigned int len){
        unsigned int i = 0;
        std::string ans;
        if(dir == Direction::Horizontal){
            for(; i < len; i++, column++){
                if(my_map.find(row) == my_map.end() || my_map[row].find(column) == my_map[row].end()){   //check if the map[row][column] exists
                    ans.append("_");  
                }
                else{
                    ans += my_map.at(row).at(column);
                }
            }
            return ans;;
        }
        for(; i < len; i++, row++){
            if(my_map.find(row) == my_map.end() || my_map[row].find(column) == my_map[row].end()){   //check if the map[row][column] exists
                ans.append("_");  
            }
            else{
                ans += my_map.at(row).at(column);
            }
        }
        return ans;
    }

    void Board::show(){
        std::cout << std::endl << "start printing the board... " << std::endl;
        for(unsigned int i = start_x; i < end_x ; i++){
            //std::string row_column;
            for(unsigned int j = start_y; j < end_y ; j++){
                if(my_map.find(i) == my_map.end() || my_map[i].find(j) == my_map[i].end()){    //check if the map[row][column] exists
                    std::cout << "_";  
                }
                else{
                    std::cout << my_map.at(i).at(j); 
                }
            }
            std::cout << std::endl; 
        }
        std::cout << ".end of the board." << std::endl;
    }

    /*update the size of the board*/
    void Board::check_limit(unsigned int x, unsigned int y, unsigned int len){   
        if(x < start_x){
            start_x = x;
        }
        if(y < start_y){
            start_y = y;
        } 
    }

    void Board::check_hori(unsigned int x, unsigned int y, unsigned int len){   
        if(x > end_x){
            end_x = x;
        }
        if(y+len > end_y){
            end_y = y+len;
        }
    }

    void Board::check_vec(unsigned int x, unsigned int y, unsigned int len){   
        if(x+len > end_x){               
            end_x = x+len;
        }
        if(y > end_y){
            end_y = y;
        }
    }  
}

