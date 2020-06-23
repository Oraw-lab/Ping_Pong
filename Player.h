#pragma once

class Players {
public:
	enum eDirection { 
		STOP = 0, UP, DOWN, RIGHT, LEFT 
	};
	int* player_position;
	int place_in_wide;
	int player_score = 0;
	eDirection move = STOP;
	/*
	Routine Description:
		Constructor of Players Class
	Arguments:
		point of intgers - using the pointer to assign a new array to player object
		intger y - setting the wide position of player
	Return Value:
		None - creating a new object in the class
	*/
	Players(int* ptr, int y) {
		player_position = creating_player(5);
		place_in_wide = y;
	}
	/*
	Routine Description:
		Creating array of new position
	Arguments:
		Int num - where to start position

	Return Value:
		int pointer - returning a new adress to the array
	*/
	int* creating_player(int num) {
		int* arr = new int[5]; // setting array to have 5 places
		for (int i{}; i < 5; i++) {
			arr[i] = num;  // assigned number to array
			num++;
		}
		return arr;// returning place for i 

	}
	/*
	Routine Description:
		Changing Array values based of enum of player
	Arguments:
		Players Obj - using player array to deciced what new number will be given to array
	Return Value:
		if player enum is UP or DOWN reutning pointer of array of int
		Default case returning the same array to player.
	*/
	int* player_move(Players& player) {
		int* new_arr{}; // init pointers
		int first_num_in_arr{};
		switch (move) {
		case UP:
			first_num_in_arr = player_position[0];
			first_num_in_arr--;
			new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake top
			move = STOP;
			return new_arr; //returning new array to main
		case DOWN:
			first_num_in_arr = player_position[0];
			first_num_in_arr++;
			new_arr = creating_player(first_num_in_arr); // adding 1 for snake in high to move snake down
			move = STOP;
			return new_arr; //returning new array to main
		default:
			return player_position;

		}
	}
	/*
	Routine Description:
		Setting direction based on the given direction on args
	Arguments:
		Char = Based on key pressed changing postion
	Return Value:
		None = changing the poistion of the player
	*/
	void setter_direction(char key) {
		switch (key)
		{
		case 'w':
			move = UP;// Actual set
			break;
		case 's':
			move = DOWN;// Actual set
			break;
		case 'i':
			move = UP;// Actual set
			break;
		case 'k':
			move = DOWN;// Actual set
			break;
		default:
			move = STOP; // deafult case in case of wrong button
		}
	}
};