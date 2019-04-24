#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
    char boardsCompleted[9];
};

int main() {
	//function prototypes
	struct BasicBoard *createBasicTicTacToeBoard();
	struct UltimateBoard *createUltimateTicTacToeBoard();
	void printBasicBoard(struct BasicBoard *board);
	void printUltimateBoard(struct UltimateBoard *board);
	struct BasicBoard *chooseMove(struct BasicBoard board);
	struct UltimateBoard chooseRandomMove(struct UltimateBoard board);
	char* getUserSelectionBasic(struct BasicBoard board);
	char* getUserSelectionUltimate(struct UltimateBoard board);
	char checkForWinsBasic(struct BasicBoard *board);
	bool checkForInnerWinsUltimate(struct UltimateBoard board);
	char checkForFullWinsUltimate(struct UltimateBoard *board);
	struct BasicBoard updateBasicBoardWithUserSelection(struct BasicBoard board, char* userSelection);
	struct UltimateBoard updateUltimateBoardWithUserSelection(struct UltimateBoard board, char* userSelection);

    int option;
    char buffer[255];
    srand(time(0));
    do {
    printf("Welcome to Ultimate Tic Tac Toe!\n");
        printf("Please select an option.\n");
        printf("1: Normal tic tac toe (Easy)\n");
        printf("2: Normal tic tac toe (Hard)\n");
        printf("3: Ultimate tic tac toe\n");
        printf("4: Quit\n");

        //get option
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &option);

        switch(option) {
            case 1 : {
                //easy
                struct BasicBoard *board = createBasicTicTacToeBoard();

                do {
                    //get user selection, update board with it, and print board
                            // char* userSelection = getUserSelectionBasic(board);
                            // updateBasicBoardWithUserSelection(board, userSelection);

                    int num1;
                    do {
                        num1 = (rand() % (9));
                    } while (board->spaces[num1] != ' ');
                    board->spaces[num1] = 'x';
                    printf("User:\n");
                    printBasicBoard(board);

                    //computer moves and board is printed
                    int num;
                    do {
                        num = (rand() % (9));
                    } while (board->spaces[num] != ' ');
                    board->spaces[num] = 'o';
                    printf("Computer:\n");
                    printBasicBoard(board);
                } while (checkForWinsBasic(board) == ' ');

                if (checkForWinsBasic(board) == 'X') {
                    printf("Congrats, you won!\n");
                }
                else {
                    printf("Sorry, you lost!\n");
                }

                break;
            }

            case 2 : {
                //hard
                struct BasicBoard *board = createBasicTicTacToeBoard();

                do {
                    printBasicBoard(board);
                    //get user selection, update board with it, and print board
                                // char* userSelection = getUserSelectionBasic(board);
                                // updateBasicBoardWithUserSelection(board, userSelection);
                    int num1;
                    do {
                        num1 = (rand() % (9));
                    } while (board->spaces[num1] != ' ');
                    board->spaces[num1] = 'x';
                    printf("User:\n");
                    printBasicBoard(board);

                    //computer moves and board is printed
                    board = chooseMove(*board);
                    printf("Computer:\n");
                    printBasicBoard(board);
                } while (checkForWinsBasic(board) == ' ');

                if (checkForWinsBasic(board) == 'X') {
                    printf("Congrats, you won!\n");
                }
                else {
                    printf("Sorry, you lost!\n");
                }
                break;
            }

            case 3 : {
                //ultimate
                break;
            }

            case 4 : {
                //end
                break;
            }

            default :
                //check for invalid input
                printf("Not a valid option. Please enter a number between 1-9.\n");
                option = 0;
        }
    } while (option != 4);

	return 0;
}

//returns a 3x3 tic tac toe board with all characters inside initialized to ' '
//MATT
struct BasicBoard *createBasicTicTacToeBoard()
{
    struct BasicBoard *board = (struct BasicBoard *)malloc(sizeof(struct BasicBoard));
    int x;
    for(x=0; x<9;x++)
    {
        board -> spaces[x] = ' ';
    }
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
        board -> boardsCompleted[x] = ' ';
    }
    return board;
}

//prints the basic board in a human-readable format
//MATT
void printBasicBoard(struct BasicBoard *board) {
    int i;
    for (i = 0; i < 9; i+=3) {
        printf("%c|%c|%c\n", board->spaces[i], board->spaces[i+1], board->spaces[i+2]);
        if(i == 0 || i == 3)
        {
            printf("-----\n");
        }
    }
}

//prints the ultimate board in a human-readable format
//LUCAS
void printUltimateBoard(struct UltimateBoard *board)
{
    int i,x;
    for (i = 0; i < 9; i+=3)
    {
        for(x = 0; x < 3; x++)
        {
            printf("%c|%c|%c*%c|%c|%c*|%c|%c|%c", board -> boards[i] -> spaces[3*x], board -> boards[i] -> spaces[3*x+1], board -> boards[i] -> spaces[3*x+2], board -> boards[i+1] -> spaces[3*x], board -> boards[i+1] -> spaces[3*x+1], board -> boards[i+1] -> spaces[3*x+2], board -> boards[i+2] -> spaces[3*x], board -> boards[i+2] -> spaces[3*x+1], board -> boards[i+2] -> spaces[3*x+2]);
            if(x == 0 || x == 1)
            {
                printf("-----*-----*-----\n");
            }
        }
        if(i == 0 || i == 3)
        {
            printf("-----------------\n");
        }
    }
}

//AI function to choose the best move
//EILEEN
struct BasicBoard* chooseMove(struct BasicBoard board) {
    void computerMove(struct BasicBoard );
    computerMove(board);
    return &board;
}

int minimax(struct BasicBoard board, char player) {
    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board.spaces[i] == ' ') {//If legal,
            board.spaces[i] = player;//Try the move
            int thisScore = -minimax(board, player == 'o' ? 'x' : 'o');
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board.spaces[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(struct BasicBoard board) {
    int minimax(struct BasicBoard, char);
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board.spaces[i] == ' ') {
            board.spaces[i] = 'o';
            int tempScore = -minimax(board, 'x');
            board.spaces[i] = ' ';
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board.spaces[move] = 'x';
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
char checkForWinsBasic(struct BasicBoard *board)
{
    int checks[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    int x;
    for(x = 0; x < 8; x++)
    {
        if((board -> spaces[checks[x][0]] == 'x' || board -> spaces[checks[x][0]] == 'o') && board -> spaces[checks[x][0]] == board -> spaces[checks[x][1]] &&  board -> spaces[checks[x][1]] == board -> spaces[checks[x][2]])
        {
            return board -> spaces[checks[x][0]];
        }
    }
    if(board -> spaces[0] != ' ' && board -> spaces[1] != ' ' &&board -> spaces[2] != ' ' &&board -> spaces[3] != ' ' &&board -> spaces[4] != ' ' &&board -> spaces[5] != ' ' &&board -> spaces[6] != ' ' &&board -> spaces[7] != ' ' &&board -> spaces[8] != ' ')
        return 'f';
    return ' ';
// 'X' / 'O' = Line Win
// ' ' = No Win
}

//checks for wins in each quadrant of an UltimateBoard
//LUCAS
bool checkForInnerWinsUltimate(struct UltimateBoard board)
{
    //Might not be needed
}

//checks for overall win in UltimateBoard (like, 3 won quadrants in a row)
//LUCAS
char checkForFullWinsUltimate(struct UltimateBoard *board)
{
    int checks[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    int x;
    for(x = 0; x < 8; x++)
    {
        if((board -> boardsCompleted[checks[x][0]] == 'x' || board -> boardsCompleted[checks[x][0]] == 'o') && board -> boardsCompleted[checks[x][0]] == board -> boardsCompleted[checks[x][1]] && board -> boardsCompleted[checks[x][1]] == board -> boardsCompleted[checks[x][2]])
        {
            return board -> boardsCompleted[checks[x][0]];
        }
    }
    if(board -> boardsCompleted[0] != ' ' && board -> boardsCompleted[1] != ' ' &&board -> boardsCompleted[2] != ' ' &&board -> boardsCompleted[3] != ' ' &&board -> boardsCompleted[4] != ' ' &&board -> boardsCompleted[5] != ' ' &&board -> boardsCompleted[6] != ' ' &&board -> boardsCompleted[7] != ' ' &&board -> boardsCompleted[8] != ' ')
        return 'f';
    return ' ';
    // 'X' / 'O' = Line Win
    // ' ' = No Win
}
