#pragma once

class BoardObj {
public:
	enum eDirection {
		STOP = 0, UP, DOWN, RIGHT, LEFT
	};
	int place_in_y;
	int place_in_x;
	eDirection ball_Up = DOWN;
	eDirection ball_move = RIGHT;
	/*
	Routine Description:
		Setter func for ball_up variable

	Arguments:
		eDirection = where the ball will move
	Return Value:
		void 
	*/
	void ball_setter_up(eDirection _movement) {
		ball_Up = _movement;
	}
	/*
	Routine Description:
		Setter func for ball_move variable

	Arguments:
		eDirection = where the ball will move
	Return Value:
		void
	*/
	void ball_setter_wide(eDirection _momement) {
		ball_move = _momement;
	}
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