#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

void explanation();
void games();
static int door;

int Player_HP = 30;
int level[5] = { 5 , 10 , 15 , 20 , 25};
int player_exp;
int X, Y;
int i;

class Monster{
public:
	int locate_x;
	int locate_y;
	int Monster_HP;
int Move_delay = 0;
bool state = false;           // True -> Monster has alive  false -> dead
};

class potion {
public:
	int locate_x;
	int locate_y;
	int delay = 0;
	bool heal = true;		// True -> Heal posion  false -> poison potion
	bool state = false;       // True -> posion has alive  false -> dead
};
int random_pos = 0;   // potion Random index

	int level_ = 0;
int Max = 4;					  // Monster Manage function
int Monster_number = 0;
int Spawn_delay = 0;
int Monster_move = 0;        // Monster Move way (X or Y)
bool Monster_spawn = false;
bool Monster_visible = false;


int main()
{
	srand(time(NULL));

	X = rand() % 10;
	Y = rand() % 30;
	if (X < 5) {
		X = 5;
	}
	if (Y < 15) {
		Y = 15;
	}

	while (true) {
		int choice = 0;

		cout << "┌--------------------------┐\n";
		cout << "┃  Rouge - Lite - Alpha.vr ┃\n";
		cout << "┃  1 . Game Start          ┃\n";
		cout << "┃  2 . How to play?        ┃\n";
		cout << "┃  3 . Exit                ┃\n";
		cout << "└--------------------------┘\n\n";
		while (true) {
			cin >> choice;
			if (choice > 3 || choice < 1) {
				cout << "You put wrong number , try again\n";
				continue;
			}
			else break;
		}

		switch (choice) {
		case 1: games();
			break;
		case 2: explanation();
			break;
		case 3: exit(0);
			break;
		}
	}
}

void explanation() {
	cout << "┌--------------------------┐\n";
	cout << "┃       How to Play?       ┃\n";
	cout << "┃  @ -> You . -> rout      ┃\n";
	cout << "┃  alpabet -> Monster      ┃\n";
	cout << "┃  % -> Item (Hp posion)   ┃\n";
	cout << "┃W -> up A-> left S->down  ┃\n";
	cout << "┃D -> Right                ┃\n";
	cout << "┃This games not existence  ┃\n";
	cout << "┃save funtion , Item(posion┃\n";
	cout << "┃is Heal 10hp but sometime ┃\n";
	cout << "┃decrease 3hp Monster hp is┃\n";
	cout << "┃5 and damage 2 ,and player┃\n";
	cout << "┃damage 2...      attack   ┃\n";
	cout << "┃key is 'K'  and+ is corner┃\n";
	cout << "└--------------------------┘\n\n";
	getchar();
}

void games() {
	char player[20][75];  // Y -> 가로 X -> 세로
	char input;
	static int x = 0, y = 0;
	bool wall;
	door = rand() % 10;
	Monster Mon[5];
	potion pos[2];
	while (1) {
		input = _getche();								// player movement
		switch (input) {
		case 'w':
			if (x == 0) { x++; }
			player[x--][y]; break;
		case 'd':
			if (y >= 75) { y--; }
			player[x][y++]; break;
		case 's':
			if (x >= 20) { x--; }
			player[x++][y]; break;
		case 'a':
			if (y == 0) { y++; }
			player[x][y--]; break;
		case 'k': break;
		default:
			cout << "you input wrong key , try again \n";
		}
		cout << " ㅡㅡㅡㅡㅡㅡ\n";                          // spawn point
		for (i = 0; i < 3; i++) {
			if (y == door) { wall = false; }				// + -> corner turn
			else wall = true;
			if (x >= 3 && wall == true && x <= 6) { x--; }
			if (x < 0) { x++; }
			if (y >= 10 && x < 7) { y--; }
			else if (y < 0) { y++; }
			cout << "│";
			for (int yy = 0; yy < 10; yy++) {
				if (i == x && yy == y) { cout << "@"; }
				else { cout << "."; }
			}
			cout << "│\n";
		}
		cout << "  ";
		for (i = 0; i < 10; i++) {
			if (i == door) { cout << "+"; }
			else cout << "-";
		}
		cout << "\n";


		for (i = 0; i < 3; i++) {							// a connecting bridge
			for (int j = 0; j <= door + 1; j++) {
				cout << " ";
			}
			if (door == y && (i + 4) == x) {
				cout << "@\n";
			}
			else
				cout << "H\n";
		}

		cout << "  ";									// a second field
		for (i = 0; i <= Y; i++) {
			if (i == door) {
				cout << "+";
			}
			else cout << "-";
		}

		
		for (i = 0; i < 2; i++) {				 // poison create
			if (pos[i].state == true && pos[i].delay >= 100) {
				pos[i].delay = 0;
				pos[i].locate_x = rand() % X;
				pos[i].locate_y = rand() % Y;
				random_pos = rand() % 2;
				if (random_pos == 0) {
					pos[i].heal = true;
				}
				else pos[i].heal = false;
			}
			if (pos[i].state == false && pos[i].delay <= 100) {
				pos[i].delay += rand() % 5;
			}
			else  if (pos[i].state == false && pos[i].delay >= 100) {
				pos[i].state = true;
			}
		}

		if (x <= 7 && x >= 3 && wall) { x++; }
		if (x >= X + 9) { x--; }
		if (y >= Y + 1) { y--; }
		cout << "\n";
		for (i = 0; i <= X; i++) {
			cout << "│";
			for (int j = 0; j <= Y; j++) {
				if (Monster_number != 0) {
					for (int k = 0; k < 5; k++) {
						if (Mon[k].state == true && Mon[k].locate_x == i && Mon[k].locate_y == j && Monster_visible) {
							cout << "S"; j++;
						}
					}
				}
				for (int k = 0; k < 2; k++) {
					if (pos[k].state == true && pos[k].locate_y == j && pos[k].locate_x == i ) {          // posion create
						cout << "%"; j++;
					}
				}
				if (j == y && (i + 8) == x) {
					cout << "@";
				}
				else if (Monster_visible) cout << ".";
				else cout << " ";
			}
			cout << "│";
			cout << "\n";
		}
		cout << "  ";
		for (i = 0; i <= Y; i++) {
			cout << "-";
		}
		cout << "\n";

		if (Monster_number >= Max) {
			Monster_spawn = false;
		}
		else Monster_spawn = true;

		if (x >= 7) Monster_visible = true;
		else Monster_visible = false;

		if (Spawn_delay >= 100 && Monster_spawn) {				// Monster spawner
			for (i = 0; i < 5; i++) {
				if (Mon[i].state == false) {
					Mon[i].locate_x = rand() % X;
					Mon[i].locate_y = rand() % Y;
					Mon[i].Monster_HP = 5;
					Mon[i].state = true;
					Spawn_delay = 0;
					Monster_number++;
					break;
				}
			}
		}
		else if (Monster_spawn) {
			Spawn_delay += rand() % 15;
		}

		for (i = 0; i < 5; i++) {				// Monster Movement function
			if (Mon[i].state && Mon[i].Move_delay >= 100) {
				Mon[i].Move_delay = 0;
				Monster_move = rand() % 4;
				switch (Monster_move) {
				case 0: Mon[i].locate_x++; break;
				case 1: Mon[i].locate_x--; break;
				case 2: Mon[i].locate_y++; break;
				case 3: Mon[i].locate_y--; break;
				}
				if (Mon[i].locate_x >= X) Mon[i].locate_x--;
				if (Mon[i].locate_x < 0) Mon[i].locate_x++;
				if (Mon[i].locate_y >= Y) Mon[i].locate_y--;
				if (Mon[i].locate_y <= 0) Mon[i].locate_y++;
			}
			else if (Mon[i].state) {
				Mon[i].Move_delay += rand() % 15;
			}
		}

		for (i = 0; i < 5; i++) {							 // Monster overlap prevention
			for (int k = 4; k >= 0 && i < k; k--) {
				if (Mon[i].locate_x == Mon[k].locate_x && Mon[i].locate_y == Mon[k].locate_y) {
					if (Mon[i].locate_x <= 1) { Mon[i].locate_x += 2; Mon[i].locate_y += 2; }
					else { Mon[i].locate_x -= 2; Mon[i].locate_y += 2; }
				}
			}


			if (input == 'k' && x - 8 == Mon[i].locate_x && y == Mon[i].locate_y) {
				Mon[i].Monster_HP -= 2;
				if ( Mon[i].Monster_HP >= 0 && Mon[i].state )
				cout << "System : You attacked the Monster  [ Damage : 2 ] [ Monster HP :" << Mon[i].Monster_HP << "]\n";
				else if ( Mon[i].state ) {
					cout << "System : Monster is Dead [ Exp + 3 ]\n";
					player_exp += 3 ;
				}
			}
			if (x - 8 == Mon[i].locate_x && y == Mon[i].locate_y && Mon[i].state == true) {
				cout << "System : You was attack by a Monster [ HP : - 2 ] \n";
				Player_HP -= 2;
			}
		}
		for (i = 0; i < 2; i++) {
			if (pos[i].locate_x + 8 == x && pos[i].locate_y == y && pos[i].state && pos[i].heal) {
					cout << "System : You get a heal potion [ HP + 10 ] \n";
				if (Player_HP <= 20) { Player_HP += 10;}
				else { Player_HP = 30;}
				pos[i].state = false;
			}
			else if (pos[i].locate_x + 8 == x && pos[i].locate_y == y && pos[i].state && pos[i].heal == false) {
				cout << "System : You get a poison potion [ HP - 3 ] \n";
				Player_HP -= 3;
				pos[i].state = false;
			}
		}



		switch (level_) {
		case 0: if (player_exp >= 5) {
			cout << "System : Level Up!! \n ";
			level_++; player_exp = 0;
		} break;
		case 1: if (player_exp >= 10) {
			cout << "System : Level Up!! \n ";
			level_++; player_exp = 0;
		} break;
		case 2: if (player_exp >= 15) {
			cout << "System : Level Up!! \n ";
			level_++; player_exp = 0;
		} break;
		case 3: if (player_exp >= 20) {
			cout << "System : Level Up!! \n ";
			level_++; player_exp = 0;
		} break;
		case 4: if (player_exp >= 25) {
			cout << "System : Level Up!! \n ";
			level_++; player_exp = 0;
		} break;
		};
		cout << "Player Stat : Level [" << level_ + 1 << "]  Exp : [ " << player_exp << " / " << level[level_] << " ] " << " Hp: [ " << Player_HP << " / 30] \n" ;

		for (i = 0; i < 5; i++) {
			if (Mon[i].Monster_HP <= 0) {
				Mon[i].state = false;
			}
			cout << "\n";
		}

		if (Player_HP <= 0) {
			cout << " [ G a m e    O v e r ] \n";
			exit(0);
		}
	}
}
