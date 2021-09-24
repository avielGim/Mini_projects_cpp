/**
 * Demo program for Pandemic exercise - compares the different roles.
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
#include <math.h>
using namespace std;

void init(Board&);
Player* choose_role(Board&);
void make_role(int&);

void move(Player&);
void task(int, Player&);
void show_player(Player&);


int main() {
	Board board;
	init(board);

	Player* one = choose_role(board);
	Player* two = choose_role(board);

	char exit = 'n';
	while(exit == 'n'){
		move(*one);
		move(*two);
		cout << "\ndo you want to exit the game?? [Y/n] " << endl;
		cin >> exit;
	}
	cout << "\n----------------------------------------\n";
	cout << boolalpha;
	cout << "the board is clean? " << board.is_clean() << endl;
	cout << "-----------!!the game is over!!-----------\n" << endl;

	delete one;
	delete two;
	
	return 0;
}

void init(Board& board){
	int random = rand()%48;
	int c = rand()%48;
	for(int i = 0; i < 15; i++){
		board[(City)c] += random;
		random = rand()%10;
		c = rand()%48;
	}
	board[City::BuenosAires] = 5;
}

Player* choose_role(Board& board){
	Player* p;
	City random = (City)(rand()%48);
	int temp = 0;
	make_role(temp);
	if(temp == 1){
		p = new OperationsExpert{board, random};
	}
	else if(temp == 2){
		p = new Dispatcher{board, random};
	}
	else if(temp == 3){
		p = new Scientist{board, random, 4};
	}
	else if(temp == 4){
		p = new Researcher{board, random};
	}
	else if(temp == 5){
		p = new Medic{board, random};
	}
	else if(temp == 6){
		p = new Virologist{board, random};
	}
	else if(temp == 7){
		p = new GeneSplicer{board, random};
	}
	else{
		p = new FieldDoctor{board, random};
	}
	return p;
}

void make_role(int& temp){
	cout << "choose role - " << endl;
	cout << "\t1 - OperationsExpert\n\t2 - Dispatcher\n\t3 - Scientist\n\t4 - Researcher\n\t"; 
	cout << "5 - Medic\n\t6 - Virologist\n\t7 - GeneSplicer\n\t8 -FieldDoctor\n";
	cin >> temp;
}

void move(Player& p){
	City random = (City)(rand()%48);
	cout << "\nyour role is: " << p.role() << endl;
	cout << "you got the card: " << random << endl;
	p.take_card(random);
	int choose = 0;
	while(choose < 10){
		cout << "\nchoose action:\n\t1 - drive \n\t2 - fly direct \n\t3 - fly charter \n\t";
		cout << "4 - fly shuttle\n\t5 - build\n\t6 - discover cure\n\t7 - treat\n\t";
		cout << "8 - print the information of the PLAYER\n\t9 - print the board \n\t10 - finish\n";
		cin >> choose;
		try{
			task(choose , p);
		}
		catch(exception& ex){
			cout << "-----------------\n";
			cout << ex.what() << endl;
			cout << "you finish your moves"<< endl;
			cout << "-----------------\n";
			choose = 10;
		}
	}
}

void task(int choose, Player& p){
	int temp;
	if(choose == 1){
		cout << "choose the number of the city " << endl;
		cout << "---------------------------------\n";
		cin >> temp;
		p.drive((City)temp);
	}
	else if(choose == 2){
		cout << "choose the number of the city " << endl;
		cout << "---------------------------------\n";
		cin >> temp;
		p.fly_direct((City)temp);
	}	
	else if(choose == 3){
		cout << "choose the number of the city " << endl;
		cout << "---------------------------------\n";
		cin >> temp;
		p.fly_charter((City)temp);
	}	
	else if(choose == 4){
		cout << "choose the number of the city " << endl;
		cout << "---------------------------------\n";
		cin >> temp;
		p.fly_shuttle((City)temp);
	}	
	else if(choose == 5){
		p.build();
	}
	else if(choose == 6){
		cout << "choose color:\n\t0 - Yellow\n\t1 - Blue\n\t2 - Black\n\t3 - Red\n";
		cin >> temp;
		p.discover_cure((Color)temp);
	}
	else if(choose == 7){			
		cout << "choose the number of the city " << endl	;
	cout << "---------------------------------\n";
		cin >> temp;
		p.treat((City)temp);
	}	
	else if(choose == 8){
		show_player(p);
	}
	else if(choose == 9){
		p.syso_board();
	}
	cout << "---------!!good job!!--------\n";
}

void show_player(Player& p){
	cout << "\n**********************************\n";
	cout << "the role is: " << p.role() << endl;
	cout << p << endl;
	cout << "**********************************\n";
}	






