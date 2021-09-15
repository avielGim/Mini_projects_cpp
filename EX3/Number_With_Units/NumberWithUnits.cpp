#include <iostream>
#include "NumberWithUnits.hpp"

namespace ariel{
    std::map<std::string, Units> NumberWithUnits::all;
    
    NumberWithUnits::NumberWithUnits(double new_num, const std::string& new_unit){
        if(NumberWithUnits::all.find(new_unit) == NumberWithUnits::all.end()){
            throw std::out_of_range{"---there is no unit with the name \"" + new_unit + "\" ---"};
        }
        _num = new_num;
        _unit = new_unit;
    }

//////////////////////////////////////////
    void NumberWithUnits::read_units(std::ifstream& file_name){
        std::string line;
        std::string first;
        std::string second;     
        double data_num = 0;
        while(getline(file_name,line)){
            first = line.substr(0,line.find('='));                
            second = line.substr(line.find('=')+1);
            std::istringstream t1(first);
            std::istringstream t2(second);
            t1 >> data_num;
            t1 >> first;
            t2 >> data_num;
            t2 >> second;
            if(data_num > 1){
                find_p_s(first,second,data_num);
            }
            else{
                find_p_s(second,first,1/data_num);
            }
        }
    }
    void NumberWithUnits::find_p_s(const std::string& s1, const std::string& s2, double n){
        if(all.find(s1) == all.end() && all.find(s2) == all.end()){
            all[s1] = Units{1, s1, "no_parent", s2};
            all[s2] = Units{n, s2, s1, "no_son"};
        }
        else if(all.find(s1) != all.end() && all.find(s2) == all.end()){
            find_son(s1,s2,n);
        }
        else{
            find_parent(s1,s2,n);
        }
    }
    void NumberWithUnits::find_parent(const std::string& s1, const std::string& s2, double n){
        Units *temp = &all.at(s2);
        double c = n;
        while(temp->getParent() != "no_parent" && c > 1){
            c = n / temp->getNum();
            temp = &all.at(temp->getParent()); 
        }
        if(temp->getParent() == "no_parent"){
            all[s1] = Units{1, s1, temp->getParent() , temp->getUnit()};
            temp->getNum() = c;
            temp->getParent() = s1;
        }
        else{
            all[s1] = Units{1/c, s1, temp->getUnit(), temp->getSon()};
            Units *hijo = &all.at(temp->getSon());       
            temp->getSon() = s1;
            hijo->getNum() = n;
            hijo->getParent() = s1;
        }
    }
    void NumberWithUnits::find_son(const std::string& s1, const std::string& s2, double n){
        Units *temp = &NumberWithUnits::all.at(s1);
        if(temp->getSon() == "no_son"){
            temp->getSon() = s2;
            all[s2] = Units{n, s2, temp->getUnit(), "no_son"};
        }
        else{
            temp = &all.at(temp->getSon());
            while(temp->getSon() != "no_son" && temp->getNum() < n){
                temp = &all.at(temp->getSon());
            }
            if(temp->getNum() > n){
                Units *pap = &all.at(temp->getParent());
                pap->getSon() = s2;
                temp->getNum() = temp->getNum() / n;
                temp->getParent() = s2;
                all[s2] = Units{n, s2, pap->getUnit(), temp->getUnit()};
            }
            else{       //there is no son
                all[s2] = Units{temp->getNum() / n, s2, temp->getUnit(), "no_son"};
                temp->getSon() = s2;                
            }
        }
    }
//////////////////////////////////////////
    double NumberWithUnits::convert_unit(const std::string& s1, const std::string& s2, double n){
        Units temp = all.at(s2);
        double ans = n;
        while(temp.getSon() != "no_son" && temp.getUnit() != s1){
            temp = all.at(temp.getSon());
            ans *= temp.getNum();
        }
        if(temp.getUnit() == s1){
            return ans;
        }
        temp = all.at(s1);
        ans = n;
        while(temp.getSon() != "no_son" && temp.getUnit() != s2){
            temp = all.at(temp.getSon());
            ans /= temp.getNum();
        }
        if(temp.getUnit() == s2){
            return ans;
        }
        throw std::out_of_range{"Units do not match - [" + s2 + "] cannot be converted to [" + s1 + "]"};
    }
//////////////////////////////////////////
    std::string init_name(std::string name, unsigned int i){
        std::string temp;
        unsigned int index = i;
        for(; index < name.length()-1; index++){
            temp += name.at(index);
        }
        if(name.at(index) != ']'){
            temp += name.at(index);
        }
        return temp;
    }
    void check_word(std::string& name){
        if(name.at(0) == '['){
            name = name = init_name(name,1);
        }
        else if(name.at(name.length()-1) == ']'){
            name = name = init_name(name,0);
        }
    }
//////////////////////////////////////////

    //+
    NumberWithUnits NumberWithUnits::operator+(){
        return NumberWithUnits(+_num, _unit);
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other){
        double new_num = convert_unit(this->_unit, other._unit, other._num);
        new_num += _num;
        return NumberWithUnits{new_num, this->_unit};
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
        double new_num = convert_unit(this->_unit, other._unit, other._num);
        _num += new_num;
        return *this;    
    }
    //prefix
    NumberWithUnits& NumberWithUnits::operator++(){ 
        _num++;
        return *this;
    }
    //postfix
    NumberWithUnits NumberWithUnits::operator++(int){ 
        NumberWithUnits copy = *this;
        _num++;
        return copy;
    }
    //-
    NumberWithUnits NumberWithUnits::operator-(){
        return NumberWithUnits(-_num, _unit);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other){
        double new_num = convert_unit(this->_unit, other._unit, other._num);
        double temp = _num - new_num;
        return NumberWithUnits{temp, this->_unit};
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
        double new_num = convert_unit(this->_unit, other._unit, other._num);
        _num -= new_num;
        return *this; 
    }
    //prefix
    NumberWithUnits& NumberWithUnits::operator--(){ 
        _num--;
        return *this;
    }
    //postfix
    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits copy = *this;
        _num--;
        return copy;
    }
    //*
    NumberWithUnits NumberWithUnits::operator*(double x){
        double new_num = this->_num * x;
        return NumberWithUnits(new_num, this->_unit);
    }
    NumberWithUnits operator*(double x, const NumberWithUnits& other){
        double new_num = other._num * x;
        return NumberWithUnits(new_num, other._unit);
    }

    //bool ==
    bool operator==(const NumberWithUnits& a, const NumberWithUnits& b){
        double new_num = NumberWithUnits::convert_unit(a._unit, b._unit, b._num);
        double ans = a._num - new_num;
        return (ans <= EPS && ans >= -EPS);
    }
    //bool !=
    bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b){
        return (!(a == b));
    }
    //bool <
    bool operator<(const NumberWithUnits& a, const NumberWithUnits& b){
        double new_num = NumberWithUnits::convert_unit(a._unit, b._unit, b._num);
        double temp = a._num - new_num;
        return (temp < -EPS);
    }
    //bool <=
    bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b){
        double new_num = NumberWithUnits::convert_unit(a._unit, b._unit, b._num);
        double temp = a._num - new_num;
        return (temp < EPS);
    }
    //bool >
    bool operator>(const NumberWithUnits& a, const NumberWithUnits& b){
        double new_num = NumberWithUnits::convert_unit(a._unit, b._unit, b._num);
        double temp = a._num - new_num;
        return (temp > EPS);
    }
    //bool >=
    bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b){
        double new_num = NumberWithUnits::convert_unit(a._unit, b._unit, b._num);
        double temp = a._num - new_num;
        return (temp > -EPS);
    }

    //input 
    std::istream& operator>> (std::istream& in, NumberWithUnits& number_unit){
        double new_num = DONT_GET_VALUE;
        std::string new_unit;
        in >> new_num;
        in >> new_unit;
        if(new_unit.length() == 1){
            in >> new_unit; 
        }
        int closer = new_unit.find(']');
        if(closer == -1){
            std::string trash;
            in >> trash;    
        }
        check_word(new_unit);
        if(new_num == DONT_GET_VALUE || NumberWithUnits::all.find(new_unit) == NumberWithUnits::all.end()){
            throw std::out_of_range{"---there is no unit with the name \"" + new_unit + "\" ---"};
        }
        number_unit._num = new_num;
        number_unit._unit = new_unit;
        return in;
    }
    //output
    std::ostream& operator<< (std::ostream& out, const NumberWithUnits& number_unit){
        return (out << number_unit._num << "[" << number_unit._unit << "]");
    }
}