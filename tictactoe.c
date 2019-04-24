#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//3x3
//MATT
struct BasicBoard
{
    char spaces[9];
};

//9x9
//should potentially be made up of 9 basic boards? dunno about that though
//LUCAS
struct UltimateBoard
{
    struct BasicBoard *boards[9];
    bool boardsCompleted[9];
};

int main() {
	//function prototypes
	struct BasicBoard *createBasicTicTacToeBoard();
	struct UltimateBoard *createUltimateTicTacToeBoard();
	void printBasicBoard(struct BasicBoard board);
	void printUltimateBoard(struct UltimateBoard board);
	struct BasicBoard chooseMove(struct BasicBoard board);
	struct UltimateBoard chooseRandomMove(struct UltimateBoard board);
	char* getUserSelectionBasic(struct BasicBoard board);
	char* getUserSelectionUltimate(struct UltimateBoard board);
	bool checkForWinsBasic(struct BasicBoard *board);
	bool checkForInnerWinsUltimate(struct UltimateBoard board);
	bool checkForFullWinsUltimate(struct UltimateBoard *board);
	struct BasicBoard updateBasicBoardWithUserSelection(struct BasicBoard board, char* userSelection);
	struct UltimateBoard updateUltimateBoardWithUserSelection(struct UltimateBoard board, char* userSelection);

	return 0;
}

//returns a 3x3 tic tac toe board with all characters inside initialized to ' '
//MATT
struct BasicBoard *createBasicTicTacToeBoard()
{
    struct BasicBoard *board = (struct BasicBoard *)malloc(sizeof(struct BasicBoard));
    return board;
}

//returns a 9x9 tic tac toe board with all characters inside initialized to ' '
//LUCAS
struct UltimateBoard *createUltimateTicTacToeBoard()
{
    struct UltimateBoard *board = (struct UltimateBoard *)malloc(sizeof(struct UltimateBoard));
    int x;
    for(x=0; x<9;x++)
    {
        board -> boards[x] = createBasicTicTacToeBoard();
    }
    return board;
}

//prints the basic board in a human-readable format
//MATT
void printBasicBoard(struct BasicBoard board) {

}

//prints the ultimate board in a human-readable format
//LUCAS
void printUltimateBoard(struct UltimateBoard board)
{
    //Planned Complete Date: Once Matt is done printing the board
}

//AI function to choose the best move
//EILEEN
struct BasicBoard chooseMove(struct BasicBoard board) {

}

//chooses a random space that is not already occupied, fills it with the computer character, and retuns the new board
//LUCAS
struct UltimateBoard chooseRandomMove(struct UltimateBoard board)
{
    //Might not be needed.

}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//ADIT
char* getUserSelectionBasic(struct BasicBoard board) {
	int row;
	char column;
	printf("Please select a row \n");
	scanf("%lf", &row);
	printf("Please select a column \n");
	scanf("%s", &column);
	char Selection = {row, column};
	return &Selection;
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
bool checkForWinsBasic(struct BasicBoard *board)
{
    int checks[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    int x;
    for(x = 0; x < 8; x++)
    {
        if((board -> spaces[checks[x][0]] == 'x' || board -> spaces[checks[x][0]] == 'y') && board -> spaces[checks[x][0]] == board -> spaces[checks[x][1]] == board -> spaces[checks[x][2]])
        {
            return true;
        }
    }
    return false;

}

//checks for wins in each quadrant of an UltimateBoard
//LUCAS
bool checkForInnerWinsUltimate(struct UltimateBoard board)
{
    //Might not be needed
}

//checks for overall win in UltimateBoard (like, 3 won quadrants in a row)
//LUCAS
bool checkForFullWinsUltimate(struct UltimateBoard *board)
{
    int checks[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    int x;
    for(x = 0; x < 8; x++)
    {
        if((board -> boardsCompleted[checks[x][0]] == 'x' || board -> boardsCompleted[checks[x][0]] == 'y') && board -> boardsCompleted[checks[x][0]] == board -> boardsCompleted[checks[x][1]] == board -> boardsCompleted[checks[x][2]])
        {
            return true;
        }
    }
    return false;
}
    int checks[][] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
}
