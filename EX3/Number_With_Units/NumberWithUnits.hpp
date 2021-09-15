#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class Units{
    double _number;
    std::string _unit_name, _parent, _son;
public:
    Units()
        :_number(0), _unit_name("no_unit"), _parent("no_parent"), _son("no_son") {
    }
    Units(double num, std::string unit, std::string parent, std::string son)
        :_number(num), _unit_name(unit), _parent(parent), _son(son) {
    }
    double& getNum() {return _number;}
    std::string getUnit() {return _unit_name;}
    std::string& getParent() {return _parent;}
    std::string& getSon() {return _son;}
};

namespace ariel{

    const double EPS = 0.001;
    const double DONT_GET_VALUE = 33.12521421;

    static std::map<std::string, Units> all;

    class NumberWithUnits{
        double _num;
        std::string _unit;
        static std::map<std::string, Units> all; //save all the order of the units as Linked_List
   
        static void find_parent(const std::string& s1, const std::string& s2, double n);
        static void find_son(const std::string& s1, const std::string& s2, double n);
        static void find_p_s(const std::string& s1, const std::string& s2, double n);
        
        static double convert_unit(const std::string& s1, const std::string& s2, double n);

    public:
        
        //Constructors
        NumberWithUnits(){
            _num = 0;
            _unit = "";
        }
        NumberWithUnits(double, const std::string&);
        ~NumberWithUnits() {}

        static void read_units(std::ifstream& file_name);

        //+
        NumberWithUnits operator+();//plus unari
        NumberWithUnits operator+(const NumberWithUnits& other);
        NumberWithUnits& operator+=(const NumberWithUnits& other);
        NumberWithUnits& operator++(); //prefix
        NumberWithUnits operator++(int); //postfix

        //-
        NumberWithUnits operator-(); //minus unari
        NumberWithUnits operator-(const NumberWithUnits& other);
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        NumberWithUnits& operator--(); //prefix
        NumberWithUnits operator--(int); //postfix
        
        //*
        NumberWithUnits operator*(double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits& other);

        //boolean {==, !=, <, >}
        friend bool operator==(const NumberWithUnits& a, const NumberWithUnits& b);
        friend bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b);
        friend bool operator<(const NumberWithUnits& a, const NumberWithUnits& b);
        friend bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b);
        friend bool operator>(const NumberWithUnits& a, const NumberWithUnits& b);
        friend bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b);

        //input & output
        friend std::istream& operator>> (std::istream& in, NumberWithUnits& number_unit);//input
        friend std::ostream& operator<< (std::ostream& out, const NumberWithUnits& number_unit);//output    
    };
}

