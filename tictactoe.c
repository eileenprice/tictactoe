#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//3x3
struct BasicBoard
{
    char spaces[9];
};

//9x9
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
    struct BasicBoard computerMove(struct BasicBoard );
	struct UltimateBoard chooseRandomMove(struct UltimateBoard board);
	struct BasicBoard getUserSelectionBasic(struct BasicBoard board);
	char* getUserSelectionUltimate(struct UltimateBoard board);
	char checkForWinsBasic(struct BasicBoard *board);
	bool checkForInnerWinsUltimate(struct UltimateBoard board);
	char checkForFullWinsUltimate(struct UltimateBoard *board);
	char updateBoardsCompleted(struct UltimateBoard *boardMatrix, struct BasicBoard *board);
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
                printBasicBoard(board);
                do {
                    //get user selection and print board
                    *board = getUserSelectionBasic(*board);
                    printf("User:\n");
                    printBasicBoard(board);
                    //check to see if user won or is full
                    if(checkForWinsBasic(board) != ' ') {
                        break;
                    }

                    //computer moves
                    //random since this is easy mode
                    int num;
                    do {
                        num = (rand() % (9));
                    } while (board->spaces[num] != ' ');
                    board->spaces[num] = 'o';

                    //print board
                    printf("Computer:\n");
                    printBasicBoard(board);
                } while (checkForWinsBasic(board) == ' ');

                char win = checkForWinsBasic(board);

                if (win == 'x') {
                    printf("Congrats, you won!\n");
                }
                else if (win == 'o') {
                    printf("Sorry, you lost!\n");
                }
                else if (win == 'f') {
                    printf("It's a tie!\n");
                }
                else {
                    printf("Something went wrong.\n");
                }

                break;
            }

            case 2 : {
                //hard
                struct BasicBoard *board = createBasicTicTacToeBoard();
                printBasicBoard(board);
                do {
                    //get user selection and print board
                    *board = getUserSelectionBasic(*board);
                    printf("User:\n");
                    printBasicBoard(board);

                    //check to see if user won or is full
                    if(checkForWinsBasic(board) != ' ') {
                        break;
                    }

                    //computer moves and board is printed
                    *board = computerMove(*board);
                    printf("Computer:\n");
                    printBasicBoard(board);

                } while (checkForWinsBasic(board) == ' ');

                //determine who won
                char win = checkForWinsBasic(board);
                if (win == 'x') {
                    printf("Congrats, you won!\n");
                }
                else if (win == 'o') {
                    printf("Sorry, you lost!\n");
                }
                else if (win == 'f') {
                    printf("It's a tie!\n");
                }
                else {
                    printf("Something went wrong.\n");
                }
                break;
            }

            case 3 : {
                //ultimate
                struct UltimateBoard *board = createUltimateTicTacToeBoard();
                printUltimateBoard(board);
                do {
                    //get user selection and print board
                    // *board = getUserSelectionUltimate(*board);
                    printf("User:\n");
                    printUltimateBoard(board);

                    //check to see if user won or is full
                    if(checkForFullWinsUltimate(board) != ' ') {
                        break;
                    }

                    //computer moves and board is printed
                    // *board = computerMoveUltimate(*board);
                    printf("Computer:\n");
                    printUltimateBoard(board);

                } while (checkForFullWinsUltimate(board) == ' ');

                //determine who won
                char win = checkForFullWinsUltimate(board);
                if (win == 'x') {
                    printf("Congrats, you won!\n");
                }
                else if (win == 'o') {
                    printf("Sorry, you lost!\n");
                }
                else if (win == 'f') {
                    printf("It's a tie!\n");
                }
                else {
                    printf("Something went wrong.\n");
                }
                break;
            }

            case 4 : {
                //end
                printf("Thanks for playing!\n");
                break;
            }

            default :
                //check for invalid input
                printf("Not a valid option. Please enter a number between 1-4.\n");
                option = 0;
        }
    } while (option != 4);

	return 0;
}

//returns a 3x3 tic tac toe board with all characters inside initialized to ' '
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
void printBasicBoard(struct BasicBoard *board) {
    int i;
    printf("   a b c\n\n");
    for (i = 0; i < 9; i+=3) {
        printf("%d  %c|%c|%c\n", (i/3)+1, board->spaces[i], board->spaces[i+1], board->spaces[i+2]);
        if(i == 0 || i == 3)
        {
            printf("   -----\n");
        }
    }
    printf("\n");
}

//prints the ultimate board in a human-readable format
void printUltimateBoard(struct UltimateBoard *board)
{
    int i,x;
    for (i = 0; i < 9; i+=3)
    {
        for(x = 0; x < 3; x++)
        {
            printf("%c|%c|%c*%c|%c|%c*%c|%c|%c\n", board -> boards[i] -> spaces[3*x], board -> boards[i] -> spaces[3*x+1], board -> boards[i] -> spaces[3*x+2], board -> boards[i+1] -> spaces[3*x], board -> boards[i+1] -> spaces[3*x+1], board -> boards[i+1] -> spaces[3*x+2], board -> boards[i+2] -> spaces[3*x], board -> boards[i+2] -> spaces[3*x+1], board -> boards[i+2] -> spaces[3*x+2]);
            if(x == 0 || x == 1)
            {
                printf("-----*-----*-----\n");
            }
        }
        if(i == 0 || i == 3)
        {
            printf("*****************\n");
        }
    }
}

struct UltimateBoard computerMoveUltimate(struct UltimateBoard board, char* previousUserSelection) {

}

//AI function to choose the best move
int minimax(struct BasicBoard board, char player) {
    char checkForWinsBasic(struct BasicBoard*);

    if(checkForWinsBasic(&board) != ' ') return -1;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,

        if(board.spaces[i] == ' ') {//If legal,
            board.spaces[i] = player;//Try the move
            //determine next player
            char nextPlayer = 'o';
            if(player == 'o') {
                nextPlayer = 'x';
            }

            int thisScore = -minimax(board, nextPlayer);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board.spaces[i] = ' ';//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

struct BasicBoard computerMove(struct BasicBoard board) {
    int minimax(struct BasicBoard, char);
    //move is array index to play in
    int move = -1;
    //score determines how good a move is
    int score = -2;
    //i lets us check each possible move in the board
    int i;
    //iterate over the board
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
    board.spaces[move] = 'o';
    return board;
}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//also updates board with the selection
struct BasicBoard getUserSelectionBasic(struct BasicBoard board) {
    int getBoardMappingFromCoordinates(char* );

    char *option = malloc(10*sizeof(char));
    bool keepGoing = true;

    do {
        printf("Please enter the coordinates of the space you wish to play in. (e.g., a1 for the upper left-hand corner)\n");
        fgets(option, 10, stdin);
        //remove the trailing newline created by fgets
        option[strcspn(option, "\n")] = 0;

        int index = getBoardMappingFromCoordinates(option);

        if(index != -1) {
            if(board.spaces[index] != ' ') {
                printf("Sorry, that space is occupied. Please pick again.\n");
            }
            else {
                board.spaces[index] = 'x';
                keepGoing = false;
            }
        } else {
            printf("That's not a valid space, please try again.\n");
        }
    } while (keepGoing);

    return board;
}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//makes sure that the user selects a space that is within the quadrant that is allowed
//NICK
char* getUserSelectionUltimate(struct UltimateBoard board) {

}

//checks for any 3 in a rows.
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
    if(board -> spaces[0] != ' ' && board -> spaces[1] != ' ' && board -> spaces[2] != ' ' && board -> spaces[3] != ' ' && board -> spaces[4] != ' ' && board -> spaces[5] != ' ' && board -> spaces[6] != ' ' && board -> spaces[7] != ' ' && board -> spaces[8] != ' ')
        return 'f';
    return ' ';
// 'X' / 'O' = Line Win
// ' ' = No Win
}

//checks for overall win in UltimateBoard (like, 3 won quadrants in a row)
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
    // 'x' / 'o' = Line Win
    // ' ' = No Win
}

char updateBoardsCompleted(struct UltimateBoard *boardMatrix, struct BasicBoard *board)
{
    int x;
    for(x=0;x<9;x++)
    {
        if(boardMatrix -> boards[x] == board)
        {
            boardMatrix -> boardsCompleted[x] = checkForWinsBasic(board);
            break;
        }
    }
    return CheckForFullWinsUltimate(boardMatrix);
}

int getBoardMappingFromCoordinates(char* coordinates) {
    if(strcmp(coordinates, "a1") == 0) {
        return 0;
    } else if(strcmp(coordinates, "a2") == 0) {
        return 3;
    } else if(strcmp(coordinates, "a3") == 0) {
        return 6;
    } else if(strcmp(coordinates, "b1") == 0) {
        return 1;
    } else if(strcmp(coordinates, "b2") == 0) {
        return 4;
    } else if(strcmp(coordinates, "b3") == 0) {
        return 7;
    } else if(strcmp(coordinates, "c1") == 0) {
        return 2;
    } else if(strcmp(coordinates, "c2") == 0) {
        return 5;
    } else if(strcmp(coordinates, "c3") == 0) {
       return 8;
    } else {
        return -1;
    }
}
