#include <iostream>
#include <conio.h>
using namespace std;

enum eDirection{STOP = 0 , UP , DOWN};

void build(const int high, const int wide, int ball_high, int ball_wide, const int arr_right[10] , const int arr_left[10] , const int place_left, const int place_right) {
	system("cls");
	int place_in_array_right = 0;
	int place_in_array_left = 0;
	for (int i{}; i < high; i++) {
		for (int j{}; j < 1; j++) { 
			if (i == 0 || i == high -1) {
				for (int w{}; w < wide; w++)
					cout << "#"; // builds floor and celling
			}
			else {
				cout << "#";
				for (int w{}; w < wide - 2; w++) {
					if (i == ball_high && w == ball_wide)
						cout << "*";// placing ball
					else if (arr_left[place_in_array_left] == i && place_left == w) {
						cout << "|"; // building left player
						place_in_array_left++; // adding 1 to move in array
					}
					else if (arr_right[place_in_array_right] == i && place_right == w) {
						cout << "|";
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

int* creating_player(int num) {
	int* arr = new int[5]; // setting array to have 5 places
	int first_place = num; // setting place in high
	for (int i{}; i <= 5; i++) {
		arr[i] = first_place;  // assigned number to array
		first_place++;
	}
	return arr;// returning place for i 

}

eDirection movement_input() {
	if (_kbhit()) { // waiting until key is being pressed
		switch (_getch()) {
		case 's':
			return DOWN; // assigning DOWN to movement - player 1
			break;
		case 'w':
			return UP; // assigning UP to movement - player 1
			break;
		case 'i':
			return UP; // assigning UP to movement - Player 2
			break;
		case 'k':
			return DOWN; // assigning UP to movement - Player 2
			break;
		}
	}
}

int * snake_move(eDirection& movement, int * players_arr, int first_num_in_arr) {
	int * new_arr{}; // init pointers
	switch (movement) {
	case UP:
		first_num_in_arr++;
		new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake top
		movement = STOP;
		return new_arr; //returning new array to main
		break;
	case DOWN:
		first_num_in_arr--;
		new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake down
		movement = STOP;
		return new_arr; //returning new array to main
		break;
	}
}


int main() {
	int score_player_a{};
	int score_player_b{};
	bool gameover = false;
	//borad high
	const int high = 20;
	//borad wide
	const int wide = 70;
	//ball in the middle for the start
	int ball_high = high / 2;
	int ball_wide = wide / 2;
	int * right_player_x = creating_player(10); // creating first player 
	int * left_player_x = creating_player(10);//creating left player
	int wide_player_right = wide - 3; // placing player in the right side at the right wide
	int wide_player_left = wide - (wide - 1); // placing player in the left side of the right wide
	//asssigned STOP to each time in order for player to stop moving during run time when didnt press a key
	eDirection momvement_player_left = STOP;
	eDirection momvement_player_right = STOP;
	while (!gameover) {
		build(high, wide, ball_high, ball_wide, right_player_x, left_player_x, wide_player_left, wide_player_right);
		momvement_player_left = movement_input();
		momvement_player_left = movement_input();
		if(momvement_player_left != STOP)
			left_player_x = snake_move(momvement_player_right, left_player_x, left_player_x[0]);
		if(momvement_player_right != STOP)
			right_player_x = snake_move(momvement_player_left, right_player_x, right_player_x[0]);
	}
	
}