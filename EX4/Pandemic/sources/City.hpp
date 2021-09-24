#pragma once
#include "Color.hpp"

namespace pandemic{
	enum City{
		Algiers, Atlanta, 
		Baghdad, Bangkok, Beijing, Bogota, BuenosAires,
		Cairo, Chennai, Chicago,
		Delhi,
		Essen,
		HoChiMinhCity, HongKong,
		Istanbul,
		Jakarta, Johannesburg,		
		Karachi, Khartoum, Kinshasa, Kolkata,
		Lagos, Lima, LosAngeles, London,
		Madrid, Manila, MexicoCity, Miami, Milan, Montreal,
		Moscow, Mumbai,
		NewYork,
		Osaka,
		Paris,
		Riyadh,
		SanFrancisco, Santiago, SaoPaulo, Seoul, Shanghai, StPetersburg, Sydney,
		Taipei, Tehran, Tokyo,
		Washington,
		DEFUALT
	};

	void init_enum_city(std::map<City, std::string>& my_city);
	std::ostream& operator<<(std::ostream& out, const City value);
}