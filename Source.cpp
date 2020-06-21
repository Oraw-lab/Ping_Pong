#include <iostream>
#include <conio.h>

using namespace std;

enum eDirection{STOP = 0 , UP , DOWN, RIGHT, LEFT};

class BoardObj{
public:
	int place_in_y;
	int place_in_x;
	eDirection ball_Up = DOWN;
	eDirection ball_move = LEFT;
	/*
	Routine Description:
		Constructor of BoardObj Class
		board and ball is are members in this class

	Arguments:
		int y = wide of board
		int x = high of board
	Return Value:
		New BoardObj

	*/
	BoardObj(int y, int x) {
		place_in_y = y;
		place_in_x = x;
	}

	/*
	Routine Description:
		Move ball object in board

	Arguments:
		Void
	Return Value:
		Void

	*/
	void ball_movement() {
		switch (ball_Up)
		{
		case DOWN:
			switch (ball_move)
			{
			case LEFT:
				place_in_y = place_in_y--; // Move Left
				place_in_x = place_in_x++; // Move DOWN
				break;
			case RIGHT:
				place_in_y = place_in_y++; // Move Right
				place_in_x = place_in_x++; // Move DOWN
				break;
			}
			break;
		case UP:
			switch (ball_move)
			{
			case LEFT:
				place_in_y = place_in_y--;// Move Left
				place_in_x = place_in_x--;// Move UP
				break;
			case RIGHT:
				place_in_y = place_in_y++;// Move Right
				place_in_x = place_in_x--;// Move UP
				break;
			}
			break;
		}

	}
};

class Players {
public:
	int * player_position;
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
		}
	}
};
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
						ball.ball_Up = DOWN;
					else if (ball.place_in_x == board.place_in_x - 1) // if ball hits floor moving ball UP
						ball.ball_Up = UP;
					else if (ball.place_in_y == board.place_in_y - 69) // if ball hits left walls moving ball RIGHT
						ball.ball_move = RIGHT;
					else if (ball.place_in_y == board.place_in_y - 1)// if ball hits right walls moving ball LEFT
						ball.ball_move = LEFT;
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
			player1.move = STOP; // in case of player hit wrong key
			player2.move = STOP; // in case of player hit wrong key
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
		if (player1.move != STOP)
			player1.player_position = player1.player_move(player1);
		if (player2.move != STOP) 
			player2.player_position = player2.player_move(player2);
	}
}