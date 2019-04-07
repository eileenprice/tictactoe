#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//3x3
//MATT
struct BasicBoard{

};

//black 
//9x9
//should potentially be made up of 9 basic boards? dunno about that though
//LUCAS
struct UltimateBoard{

};

int main() {
	//function prototypes
	struct BasicBoard createBasicTicTacToeBoard();
	struct UltimateBoard createUltimateTicTacToeBoard();
	void printBasicBoard(struct BasicBoard board);
	void printUltimateBoard(struct UltimateBoard board);
	struct UltimateBoard chooseMove(struct BasicBoard board);
	char* getUserSelectionBasic(struct BasicBoard board);
	char* getUserSelectionUltimate(struct UltimateBoard board);
	? checkForWinsBasic(struct BasicBoard board);
	? checkForInnerWinsUltimate(struct UltimateBoard board);
	? checkForFullWinsUltimate(struct UltimateBoard board);
	struct BasicBoard updateBasicBoardWithUserSelection(struct BasicBoard board, char* userSelection);
	struct UltimateBoard updateUltimateBoardWithUserSelection(struct UltimateBoard board, char* userSelection);

	return 0;
}

//returns a 3x3 tic tac toe board with all characters inside initialized to ' '
//MATT
struct BasicBoard createBasicTicTacToeBoard() {

}

//returns a 9x9 tic tac toe board with all characters inside initialized to ' '
//LUCAS
struct UltimateBoard createUltimateTicTacToeBoard() {

}

//prints the basic board in a human-readable format
//MATT
void printBasicBoard(struct BasicBoard board) {

}

//prints the ultimate board in a human-readable format
//LUCAS
void printUltimateBoard(struct UltimateBoard board) {

}

//AI function to choose the best move
//EILEEN
struct UltimateBoard chooseMove(struct BasicBoard board) {

}

//chooses a random space that is not already occupied, fills it with the computer character, and retuns the new board
//LUCAS
struct UltimateBoard chooseRandomMove(struct UltimateBoard board) {

}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//ADIT
char* getUserSelectionBasic(struct BasicBoard board) {

}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//makes sure that the user selects a space that is within the quadrant that is allowed
//NICK
char* getUserSelectionUltimate(struct UltimateBoard board) {

}

//takes an input of the current board and the user selection of where they want to place their character
//places the user character at the appropriate location and returns the new board
//ADIT
struct BasicBoard updateBasicBoardWithUserSelection(struct BasicBoard board, char* userSelection) {

}

//takes an input of the current board and the user selection of where they want to place their character
//places the user character at the appropriate location and returns the new board
//NICK
struct UltimateBoard updateUltimateBoardWithUserSelection(struct UltimateBoard board, char* userSelection) {
	
}

//checks for any 3 in a rows.
//The reason the return type is ? is because I don't know what it should return
//potentially a char that is either 'n' for no wins, 'c' for computer, or 'p' for player?
//but idk if that works so I put a ?
//same for the other two checkforwins functions
//ADIT
? checkForWinsBasic(struct BasicBoard board) {

}

//checks for wins in each quadrant of an UltimateBoard
//LUCAS
? checkForInnerWinsUltimate(struct UltimateBoard board) {

}

//checks for overall win in UltimateBoard (like, 3 won quadrants in a row)
//LUCAS
? checkForFullWinsUltimate(struct UltimateBoard board) {

}