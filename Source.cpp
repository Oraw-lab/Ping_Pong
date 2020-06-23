#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Board.h"
using namespace std;

bool binary_search(int nums[], int low, int high, int num);

/*
 Routine Description:

	Build the board

Arguments:
	BoardObj board - Getting height and the wide of the board.
	BoardObj Ball - Getting ball position
	Player player1,player1 - using player position to place them in board

Return value -
	Void
*/
void build(const BoardObj board, BoardObj& ball, const Players player1  , const Players player2) {
	system("cls");
	int place_in_array_right = 0; // setting array position to 0 at start of the run
	int place_in_array_left = 0; // setting array position to 0 at start of the run
	for (int i{}; i < board.place_in_x; i++) {
		for (int j{}; j < 1; j++) { 
			if (i == 0 || i == board.place_in_x - 1) {
				for (int w{}; w < board.place_in_y; w++)
					cout << "#"; // builds floor and celling
			}
			else {
				cout << "#";// builds left wall
				for (int w{}; w < board.place_in_y - 2; w++) {
					if (ball.place_in_x == 0) // if ball hits celling moving ball down
						ball.ball_setter_up(BoardObj::DOWN); // setting move to down
					else if (ball.place_in_x == board.place_in_x - 1) // if ball hits floor moving ball UP
						ball.ball_setter_up(BoardObj::UP);
					else if (ball.place_in_y == board.place_in_y - 69) // if ball hits left walls checking if hit player
						if (binary_search(player2.player_position, 0, 5, ball.place_in_x)) // calling binary search to see if ball hits player
							ball.ball_setter_wide(BoardObj::RIGHT); // if it hits moving ball to right side
						else // ball reset
						{
							ball.place_in_x = board.place_in_x / 2; // ball in middle
							ball.place_in_y = board.place_in_y / 2; // ball in middle
							ball.ball_setter_up(BoardObj::DOWN); // ball moving down
						}
					else if (ball.place_in_y == board.place_in_y - 3) { // if ball hits right walls checking if hit player
						if (binary_search(player1.player_position, 0, 5, ball.place_in_x))// calling binary search to see if ball hits player
							ball.ball_setter_wide(BoardObj::LEFT);// if it hits moving ball to LEFT side
						else // ball reset
						{
							ball.place_in_x = board.place_in_x / 2; // ball in middle
							ball.place_in_y = board.place_in_y / 2; // ball in middle
							ball.ball_setter_up(BoardObj::UP); // ball moving UP
						}
					}
					else if (i == ball.place_in_x && w == ball.place_in_y)
						cout << "*";// placing ball
					else if (player2.player_position[place_in_array_left] == i && player2.place_in_wide == w) {
						cout << "|"; // building left player
						place_in_array_left++; // adding 1 to move in left array
					}
					else if (player1.player_position[place_in_array_right] == i && player1.place_in_wide == w) {
						cout << "|"; // building right player
						place_in_array_right++;// adding 1 to move in right array
					}
					else
						cout << " "; //blank spaces for right wall
				}
				cout << "#"; // right wall
			}
			cout << endl; // endline for new row.
		}
	}

}
/*
Routine Description:
	Checking if ball hits players

Arguments:
	nums[] = array of player position
	low = lowest position in the array 
	high = high postion in the array
	num = the number we are looking for
void Value:
	returning ture or false - if ball hits player returning true 

*/
bool binary_search(int nums[], int low , int high , int num) {
	//base case
	if (low > high) 
		return false;
	//pick the middle item
	int middle = low + (high - low) / 2;

	//if number is == to the number we are looking for returning true
	if (nums[middle] == num) 
		return true;

	// if the middle arr number is bigger than the one we look
	// we call binary search but now from the middle of the left side
	if (num < nums[middle]) 
		return binary_search(nums, low, middle - 1, num);
	// if the middle arr number is smaller than the one we look
	// we call binary search but now from the middle of the right side
	else 
		return binary_search(nums, middle + 1, high, num);
}
/*
Routine Description:
	Assign enum to player based on thier pressed key

Arguments:
	Players obj = inorder to change direction setting need to recvice to what player change move
void Value:
	Placing move keys into player objs with & pointer.

*/
void movement_input_player(Players& player1, Players& player2) {
	if (_kbhit()) { // waiting until key is being pressed
		switch (_getch()) {
		case 'k':
			player2.setter_direction('k');// setting Down for player2
			break;
		case 's':
			player1.setter_direction('s');// setting Down for player1
			break;
		case 'i':
			player2.setter_direction('i');// setting UP for player2
			break;
		case 'w':
			player1.setter_direction('w');// setting UP for player1
			break;
		default:
			player1.setter_direction('g'); // in case of player hit wrong key
			player2.setter_direction('g'); // in case of player hit wrong key
			break;
		}
	}
}

int main() {
	bool gameover = false;
	//creating board obj , board x = 20 board y = 70
	BoardObj board(70, 20);
	//creating ball obj , ball in the middle for the start
	BoardObj ball(board.place_in_y/ 2, board.place_in_x/ 2);
	int* right_player_x{}; // creating player1 pointer
	int* left_player_x{};// creating player2 pointer
	// creating 2 players
	Players player1(right_player_x, board.place_in_y - 3);
	Players player2(left_player_x, board.place_in_y - (board.place_in_y - 1));
	delete right_player_x;// deallocating memory of players
	delete left_player_x;// deallocating memory of players
	while (!gameover) {
		ball.ball_movement();
		build(board, ball, player1, player2);
		movement_input_player(player1,player2);
		if (player1.move != Players::STOP)
			player1.player_position = player1.player_move(player1);
		if (player2.move != Players::STOP)
			player2.player_position = player2.player_move(player2);
	}
}