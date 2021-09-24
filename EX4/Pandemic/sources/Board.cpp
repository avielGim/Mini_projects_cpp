#include "Board.hpp"

namespace pandemic{
    static std::map<Color, std::string> my_color;
    static std::map<City, std::string> my_city;

    Board::Board(){
        init_enum_city(my_city);
        init_enum_color(my_color);
        init_town();
    }

    void Board::remove_cures(){
        for(uint i = 0; i < NUM_OF_COLOR; i++){
            _cure.at(i) = false;
        }
    }

    int& Board::operator[](City city){
        return _town.at(city).get_lvl();
    }
    
    bool Board::is_clean(){
        for(uint i = 0 ; i < NUM_OF_CITY; i++){
            Capital temp = _town.at(i);
            if(temp.get_lvl() > 0){
                return false;
            }
        }
        return true;
    }

    std::ostream& operator<<(std::ostream& out, const Board& board){
        out << "-----------------------------\n";
        out << "list of the City with the number of cube desease:\n";
        for(uint i = 0; i < NUM_OF_CITY; i++){
            Capital temp = board._town.at(i);
            out << "\t " << i << " - " << (City)(i) << ":\n";
            out << "\t\tCOLOR: " << temp.get_color()<< " , LEVEL: " << temp.get_lvl() << "\n";
        }
        out << "\n-----------------------------\n";
        out << "discovery cure to:";
        for(uint i = 0; i < NUM_OF_COLOR; i++){
            if(board._cure.at(i)){
                out << "\n\t* " << (Color)(i);
            }
        }
        out << "\n-----------------------------\n";
        out << "station research:";
        for (auto const& x : board._res){
            out << "\n\t* " << x;   
        }
        out << "\n-----------------------------\n";
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const City value){
		return out << my_city.at(value);
	}

	std::ostream& operator<<(std::ostream& out, const Color value){	
		return out << my_color.at(value);
	}

    void Board::init_town(){
        _cure[Color::Yellow] = false;
        _cure[Color::Blue] = false;
        _cure[Color::Black] = false;
        _cure[Color::Red] = false;
        //YELLOW//
        _town[City::Johannesburg] = Capital{Color::Yellow, 
            City::Kinshasa,City::Khartoum};
        _town[City::Kinshasa] = Capital{Color::Yellow, 
            City::Lagos,City::Khartoum,City::Johannesburg};
        _town[City::Khartoum] = Capital{Color::Yellow, 
            City::Cairo,City::Lagos,City::Kinshasa,City::Johannesburg};
        _town[City::Lagos] = Capital{Color::Yellow, 
            City::SaoPaulo,City::Khartoum,City::Kinshasa};
        _town[City::SaoPaulo] = Capital{Color::Yellow, 
            City::Bogota, City::BuenosAires, City::Lagos, City::Madrid};
        _town[City::BuenosAires] = Capital{Color::Yellow, 
            City::Bogota,City::SaoPaulo};
        _town[City::Bogota] = Capital{Color::Yellow, 
            City::MexicoCity,City::Lima,City::Miami,City::SaoPaulo,City::BuenosAires};
        _town[City::Lima] = Capital{Color::Yellow, 
            City::MexicoCity,City::Bogota,City::Santiago};
        _town[City::Santiago] = Capital{Color::Yellow, 
            City::Lima};
        _town[City::Miami] = Capital{Color::Yellow, 
            City::Atlanta,City::MexicoCity,City::Washington,City::Bogota};
        _town[City::MexicoCity] = Capital{Color::Yellow, 
            City::LosAngeles,City::Chicago,City::Miami,City::Lima,City::Bogota};
        _town[City::LosAngeles] = Capital{Color::Yellow, 
            City::SanFrancisco,City::Chicago,City::MexicoCity,City::Sydney};
        //BLUE//
        _town[City::SanFrancisco] = Capital{Color::Blue, 
            City::LosAngeles,City::Chicago,City::Tokyo,City::Manila};    
        _town[City::Chicago] = Capital{Color::Blue, 
            City::SanFrancisco,City::LosAngeles,City::MexicoCity,City::Atlanta,City::Montreal};
        _town[City::Atlanta] = Capital{Color::Blue, 
            City::Chicago,City::Miami,City::Washington};
        _town[City::Washington] = Capital{Color::Blue, 
            City::Atlanta,City::NewYork,City::Montreal,City::Miami};
        _town[City::Montreal] = Capital{Color::Blue, 
            City::Chicago,City::Washington,City::NewYork};
        _town[City::NewYork] = Capital{Color::Blue, 
            City::Montreal,City::Washington,City::London,City::Madrid};
        _town[City::Madrid] = Capital{Color::Blue, 
            City::London,City::NewYork,City::Paris,City::SaoPaulo,City::Algiers};
        _town[City::London] = Capital{Color::Blue, 
            City::NewYork,City::Madrid,City::Essen,City::Paris};
        _town[City::Paris] = Capital{Color::Blue, 
            City::Algiers,City::Essen,City::Madrid,City::Milan,City::London};
        _town[City::Milan] = Capital{Color::Blue
            ,City::Essen,City::Paris,City::Istanbul};
        _town[City::Essen] = Capital{Color::Blue
            ,City::London,City::Paris,City::Milan,City::StPetersburg};
        _town[City::StPetersburg] = Capital{Color::Blue
            ,City::Essen,City::Istanbul,City::Moscow};
        //BLACK//
        _town[City::Moscow] = Capital{Color::Black
            ,City::StPetersburg,City::Istanbul,City::Tehran}; 
        _town[City::Istanbul] = Capital{Color::Black
            ,City::Milan,City::Algiers,City::StPetersburg,City::Cairo,City::Baghdad,City::Moscow};
        _town[City::Algiers] = Capital{Color::Black
            ,City::Madrid,City::Paris,City::Istanbul,City::Cairo};
        _town[City::Cairo] = Capital{Color::Black
            ,City::Algiers,City::Istanbul,City::Baghdad,City::Khartoum,City::Riyadh};
        _town[City::Riyadh] = Capital{Color::Black
            ,City::Baghdad,City::Cairo,City::Karachi};
        _town[City::Baghdad] = Capital{Color::Black
            ,City::Tehran,City::Istanbul,City::Cairo,City::Riyadh,City::Karachi};
        _town[City::Tehran] = Capital{Color::Black
            ,City::Baghdad,City::Moscow,City::Karachi,City::Delhi};
        _town[City::Karachi] = Capital{Color::Black
            ,City::Tehran,City::Baghdad,City::Riyadh,City::Mumbai,City::Delhi};
        _town[City::Mumbai] = Capital{Color::Black
            ,City::Karachi,City::Delhi,City::Chennai};
        _town[City::Delhi] = Capital{Color::Black
            ,City::Tehran,City::Karachi,City::Mumbai,City::Chennai,City::Kolkata};
        _town[City::Kolkata] = Capital{Color::Black
            ,City::Delhi,City::Chennai,City::Bangkok,City::HongKong};
        _town[City::Chennai] = Capital{Color::Black
            ,City::Mumbai,City::Delhi,City::Kolkata,City::Bangkok,City::Jakarta};
        //RED//
        _town[City::Jakarta] = Capital{Color::Red
            ,City::Chennai,City::Bangkok,City::HoChiMinhCity,City::Sydney};
        _town[City::HoChiMinhCity] = Capital{Color::Red
            ,City::Jakarta,City::Bangkok,City::HongKong,City::Manila};
        _town[City::Bangkok] = Capital{Color::Red
            ,City::Kolkata,City::Chennai,City::Jakarta,City::HoChiMinhCity,City::HongKong};
        _town[City::HongKong] = Capital{Color::Red
            ,City::Bangkok,City::Kolkata,City::HoChiMinhCity,City::Shanghai,City::Manila,City::Taipei};
        _town[City::Shanghai] = Capital{Color::Red
            ,City::Beijing,City::HongKong,City::Taipei,City::Seoul,City::Tokyo};
        _town[City::Beijing] = Capital{Color::Red
            ,City::Shanghai,City::Seoul};
        _town[City::Seoul] = Capital{Color::Red
            ,City::Beijing,City::Shanghai,City::Tokyo};
        _town[City::Tokyo] = Capital{Color::Red
            ,City::Seoul,City::Shanghai,City::Osaka,City::SanFrancisco};
        _town[City::Osaka] = Capital{Color::Red
            ,City::Taipei,City::Tokyo};
        _town[City::Taipei] = Capital{Color::Red
            ,City::Shanghai,City::HongKong,City::Osaka,City::Manila};
        _town[City::Manila] = Capital{Color::Red
            ,City::Taipei,City::SanFrancisco,City::HoChiMinhCity,City::Sydney,City::HongKong};
        _town[City::Sydney] = Capital{Color::Red
            ,City::Jakarta,City::Manila,City::LosAngeles};       
    }

    void init_enum_color(std::map<Color, std::string>& my_color){
		my_color[Color::Yellow] = "Yellow";
		my_color[Color::Blue] = "Blue";
		my_color[Color::Black] = "Black";
		my_color[Color::Red] = "Red";
	}

    void init_enum_city(std::map<City, std::string>& my_city){
        //Yellow//
        my_city[City::Johannesburg] = "Johannesburg";
	    my_city[City::Kinshasa] = "Kinshasa";
	    my_city[City::Khartoum] = "Khartoum";
	    my_city[City::Lagos] = "Lagos";
	    my_city[City::SaoPaulo] = "SaoPaulo";
	    my_city[City::BuenosAires] = "BuenosAires";
	    my_city[City::Bogota] = "Bogota";
	    my_city[City::Lima] = "Lima";
	    my_city[City::Santiago] = "Santiago";
	    my_city[City::Miami] = "Miami";
	    my_city[City::MexicoCity] = "MexicoCity";
	    my_city[City::LosAngeles] = "LosAngeles";
		//BLUE//
	    my_city[City::SanFrancisco] = "SanFrancisco";
	    my_city[City::Chicago] = "Chicago";
	    my_city[City::Atlanta] = "Atlanta";
	    my_city[City::Washington] = "Washington";
	    my_city[City::Montreal] = "Montreal";
	    my_city[City::NewYork] = "NewYork";
	    my_city[City::Madrid] = "Madrid";
	    my_city[City::London] = "London";
	    my_city[City::Paris] = "Paris";
	    my_city[City::Milan] = "Milan";
	    my_city[City::Essen] = "Essen";
	    my_city[City::StPetersburg] = "StPetersburg";
		//BLACK//
	    my_city[City::Moscow] = "Moscow";
	    my_city[City::Istanbul] = "Istanbul";
	    my_city[City::Algiers] = "Algiers";
	    my_city[City::Cairo] = "Cairo";
	    my_city[City::Riyadh] = "Riyadh";
	    my_city[City::Baghdad] = "Baghdad";
	    my_city[City::Tehran] = "Tehran";
	    my_city[City::Karachi] = "Karachi";
	    my_city[City::Mumbai] = "Mumbai";
	    my_city[City::Delhi] = "Delhi";
	    my_city[City::Kolkata] = "Kolkata";
	    my_city[City::Chennai] = "Chennai";
		//RED//
	    my_city[City::Jakarta] = "Jakarta";
	    my_city[City::HoChiMinhCity] = "HoChiMinhCity";
	    my_city[City::Bangkok] = "Bangkok";
	    my_city[City::HongKong] = "HongKong";
	    my_city[City::Shanghai] = "Shanghai";
	    my_city[City::Beijing] = "Beijing";
	    my_city[City::Seoul] = "Seoul";
	    my_city[City::Tokyo] = "Tokyo";
	    my_city[City::Osaka] = "Osaka";
	    my_city[City::Taipei] = "Taipei";
	    my_city[City::Manila] = "Manila";
	    my_city[City::Sydney] = "Sydney";
	}
}
