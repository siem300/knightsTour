#include <cstdio>
#include <iostream>
using namespace std;

// Creates a structure for the moves
typedef struct tourMoves{
	int x, y;
}tourMoves;

// Display the solution of the knight tour
void PrintKnightTour(int **tour, int &boardSize){
	int i, j;
	for (i = 0; i < boardSize; i++){
		for (j = 0; j < boardSize; j++){
			cout << tour[i][j] << "\t";
		}
		cout << endl << endl;
	}
	delete(tour);
}

// Checks if the next move is possible
bool checkIfMovePossible(int **tour, tourMoves nextMove, int &boardSize){
	int x = nextMove.x;
	int y = nextMove.y;
	if ((x >= 0 && x < boardSize) && (y >= 0 && y < boardSize) &&(tour[x][y] == 0)){
		return true;
	}
	return false;
}

// This is a recursive function to find the knight tour
bool FindTour(int **tour, int &boardSize, tourMoves moveSetKnight[], tourMoves &currentPosition, int moveCount){
	tourMoves nextMove;
	if (moveCount == boardSize * boardSize - 1){
		// The knight tour is completed
		return true;
	}
	// Try all the possible moves from the current position
	for (int i = 0; i < 8; i++){
		// Creates the next move
		nextMove.x = currentPosition.x + moveSetKnight[i].x;
		nextMove.y = currentPosition.y + moveSetKnight[i].y;
		if (checkIfMovePossible(tour, nextMove, boardSize)){
			// If the move is possible, increment the moveCount and store it in the array
			tour[nextMove.x][nextMove.y] = moveCount + 1;
			if (FindTour(tour, boardSize, moveSetKnight, nextMove, moveCount + 1)){
				return true;
			}
			else{
				// Reset the array index, and try out other posibilities
				tour[nextMove.x][nextMove.y] = 0;
			}
		}
	}

	return false;
}

void StartKnightTour(int &boardSize, int &moveCount){
	// Creates the chessboard
	int **tour;
	tour = new int *[boardSize];
	for (int i = 0; i < boardSize; i++){
		tour[i] = new int[boardSize];
	}

	// Initializes the chess board
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			tour[i][j] = 0;
		}
	}

	// All the moves the knight can make
	tourMoves moveSetKnight[8] = { { 2, 1 }, { 1, 2 }, { -1, 2 }, { -2, 1 }, { -2, -1 }, { -1, -2 }, { 1, -2 }, { 2, -1 } };
	// The start position of the knight
	tourMoves currentPosition = { 0, 0 };

	// Find a knight tour using a recursive function
	if (FindTour(tour, boardSize, moveSetKnight, currentPosition, moveCount)){
		cout << "\nA knight tour has been found\n";
		PrintKnightTour(tour, boardSize);
	}
	else{
		cout << "No knigth tour has been found\n";
	}
}


int main(int argc, char **argv){
	int boardSize;
	// Checks if the correct value is entered
	do{
		cout << "Enter the board size (higher than 4)\n";
		cin >> boardSize;
	} while (boardSize < 5);
	int moveCount = 0;
	StartKnightTour(boardSize, moveCount);
	system("pause");
	cout << endl;
	return 0;
}