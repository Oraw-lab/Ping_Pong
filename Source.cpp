#include <iostream>
#include <conio.h>
using namespace std;

enum eDirection{STOP = 0 , UP , DOWN};

class Boardobj{
public:
	int place_in_y;
	int place_in_x;
	
	Boardobj(int y, int x) {
		place_in_y = y;
		place_in_x = x;
	}
};

class Players {
public:
	int * player_position;
	int place_in_wide;
	int player_score = 0;
	eDirection move = STOP;
	Players(int* ptr, int y) {
		player_position = creating_player(10);
		place_in_wide = y;
	}
	int* creating_player(int num) {
		int* arr = new int[5]; // setting array to have 5 places
		for (int i{}; i < 5; i++) {
			arr[i] = num;  // assigned number to array
			num++;
		}
		return arr;// returning place for i 

	}
	eDirection movement_input_player() {
		if (_kbhit()) { // waiting until key is being pressed
			switch (_getch()) {
			case 'k':
			case 's':
				return DOWN; // assigning DOWN to movement - player 1 - left player
			case 'i':
			case 'w':
				return UP; // assigning UP to movement - player 1 - left player
			default:
				return STOP; // in case of player hit wrong key
			}
		}
	}

	int* player_move(Players player) {
		int* new_arr{}; // init pointers
		int first_num_in_arr{};
		switch (player.move) {
		case UP:
			first_num_in_arr = player.player_position[0];
			first_num_in_arr--;
			new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake top
			player.move = STOP;
			return new_arr; //returning new array to main
		case DOWN:
			first_num_in_arr = player.player_position[0];
			first_num_in_arr++;
			new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake down
			player.move = STOP;
			return new_arr; //returning new array to main
		default:
			return player.player_position;
		}
	}
};
void build(const Boardobj board, Boardobj ball, const Players player1  , const Players player2) {
	system("cls");
	int place_in_array_right = 0;
	int place_in_array_left = 0;
	for (int i{}; i < board.place_in_x; i++) {
		for (int j{}; j < 1; j++) { 
			if (i == 0 || i == board.place_in_x -1) {
				for (int w{}; w < board.place_in_y; w++)
					cout << "#"; // builds floor and celling
			}
			else {
				cout << "#";
				for (int w{}; w < board.place_in_y - 2; w++) {
					if (i == ball.place_in_x && w == ball.place_in_y)
						cout << "*";// placing ball
					else if (player2.player_position[place_in_array_left] == i && player2.place_in_wide == w) {
						cout << "|"; // building left player
						place_in_array_left++; // adding 1 to move in array
					}
					else if (player1.player_position[place_in_array_right] == i && player1.place_in_wide == w) {
						cout << "|"; // building right player
						place_in_array_right++;
					}
					else
						cout << " "; //blank spaces for right wall
				}
				cout << "#"; // right wall
			}
			cout << endl;
		}
	}

}

int main() {
	bool gameover = false;
	//creating board obj , board x = 20 board y = 70
	Boardobj board(70, 20);
	//creating ball obj , ball in the middle for the start
	Boardobj ball(board.place_in_y/ 2, board.place_in_x/ 2);
	int* right_player_x{}; // creating player1 pointer
	int* left_player_x{};// creating player2 pointer
	// creating 2 players
	Players player1(right_player_x, board.place_in_y - 3);
	Players player2(left_player_x, board.place_in_y - (board.place_in_y - 1));
	delete right_player_x;// deallocating memory of players
	delete left_player_x;// deallocating memory of players
	while (!gameover) {
		build(board, ball, player1, player2);
		player1.move = player1.movement_input_player();
		player2.move = player2.movement_input_player();
		if (player1.move != STOP)
			player1.player_position = player1.player_move(player1);
		if (player2.move != STOP) 
			player2.player_position = player2.player_move(player2);
	}
}