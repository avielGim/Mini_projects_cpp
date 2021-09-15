
#include <iostream>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits km{3, "km"};   // 2 kilometers
    NumberWithUnits m{200, "m"};   // 2 kilometers
    NumberWithUnits cm{5000, "cm"};   // 2 kilometers
    cout << "********************" << endl;
    cout << "3[km] + 5000[cm] = " << km+cm << endl;
    cout << "200[m] + 3[km] = " << m+km << endl;
    cout << "3[km] += 200[m] = " << (km += m) << endl;
    cout << "km need to be after change - 3.2[km] and it = " << km << endl;
    cout << "********************" << endl;
    NumberWithUnits ton{4, "ton"};   // 2 kilometers
    NumberWithUnits kg{15000, "kg"};   // 2 kilometers
    NumberWithUnits g{1000000, "g"};   // 2 kilometers 
    cout << "15,000[kg] - 1,000,000[g]= " << (kg - g) << endl;
    cout << "15000[kg] - 4[ton] = " << kg-ton << endl;
    cout << "15000[kg] -= 4[ton] = " << (kg -= ton) << endl;
    cout << "ton need to be after change - 11000[kg] and it = " << kg << endl;
    cout << "********************" << endl;
    NumberWithUnits USD{2, "USD"};   // 2 kilometers
    NumberWithUnits ILS{6.66, "ILS"};   // 2 kilometers
    cout << "2[USD]++ = " << (USD++) << endl;
    cout << "3[USD] + 6.66[ILS] = " << USD+ILS << endl;
    cout << "2[USD] + 6.66[ILS] = " << ((--USD) + ILS) << endl;
    cout << "********************" << endl;

    try {
        cout << (kg+USD) << endl;  
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
    }
    cout << "End of my program!" << endl;
    return 0;
}
