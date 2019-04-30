#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <fmod.h>
#include <fmod_errors.h>

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

struct UltimateMove
{
    int quadrant;
    int move;
};

int main() {
    //FMOD stuff
    FMOD_RESULT result;
    FMOD::Studio::System* system = NULL;

    result = FMOD::Studio::System::create(&system); // Create the Studio System object.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    // Initialize FMOD Studio, which will also initialize FMOD Low Level
    result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
	//function prototypes
	struct BasicBoard *createBasicTicTacToeBoard();
	struct UltimateBoard *createUltimateTicTacToeBoard();
	void printBasicBoard(struct BasicBoard*);
	void printUltimateBoard(struct UltimateBoard*);
    struct BasicBoard computerMove(struct BasicBoard);
    struct UltimateMove* computerMoveUltimate(struct UltimateBoard, int);
	int getUserSelectionBasic(struct BasicBoard board);
	struct UltimateMove* getUserSelectionUltimate(struct UltimateBoard, int);
	char checkForWinsBasic(struct BasicBoard*);
	bool checkForInnerWinsUltimate(struct UltimateBoard);
	char checkForFullWinsUltimate(struct UltimateBoard*);
    char updateBoardsCompleted(struct UltimateBoard *boardMatrix, struct BasicBoard *board);

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
                    int userSelection = getUserSelectionBasic(*board);
                    board->spaces[userSelection] = 'x';
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
                    int userSelection = getUserSelectionBasic(*board);
                    board->spaces[userSelection] = 'x';
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
                int previousUserSelection = 0;
                int previousComputerSelection = -1;
                do {
                    //get user selection and print board
                    struct UltimateMove *userMove = getUserSelectionUltimate(*board, previousComputerSelection);
                    // *board = getUserSelectionUltimate(*board, previousComputerSelection);
                    board->boards[userMove->quadrant]->spaces[userMove->move] = 'x';
                    previousUserSelection = userMove->move;

                    printf("User:\n");
                    printUltimateBoard(board);

                    updateBoardsCompleted(board, board->boards[userMove->quadrant]);

                    //computer moves and board is printed
                    struct UltimateMove *computerMove = computerMoveUltimate(*board, previousUserSelection);
                    board->boards[computerMove->quadrant]->spaces[computerMove->move] = 'o';

                    printf("\nComputer:\n");
                    printUltimateBoard(board);
                    previousComputerSelection = computerMove->move;
                    printf("previousComputerSelection: %d\n", previousComputerSelection);
                    updateBoardsCompleted(board, board->boards[computerMove->quadrant]);

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

struct UltimateMove* computerMoveUltimate(struct UltimateBoard board, int quadrant) {
    int getBoardMappingFromCoordinates(char* );
    bool isQuadrantFull(struct UltimateBoard , int );

    int num;
    if(isQuadrantFull(board, quadrant)) {
        printf("quandrant is full!\n");
        do {
            num = (rand() % (9));
        } while (isQuadrantFull(board, quadrant));
        quadrant = num;
    }
    
    do {
        num = (rand() % (9));
    } while (board.boards[quadrant]->spaces[num] != ' ');

    struct UltimateMove *move = malloc(sizeof(struct UltimateMove));
    move->quadrant = quadrant;
    move->move = num;
    return move;
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
<<<<<<< HEAD
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
=======
int getUserSelectionBasic(struct BasicBoard board) {
    int getBoardMappingFromCoordinates(char* );

    char *option = malloc(10*sizeof(char));
    bool keepGoing = true;
    int index;

    do {
        printf("Please enter the coordinates of the space you wish to play in. (e.g., a1 for the upper left-hand corner)\n");
        fgets(option, 10, stdin);
        //remove the trailing newline created by fgets
        option[strcspn(option, "\n")] = 0;

        index = getBoardMappingFromCoordinates(option);

        if(index != -1) {
            if(board.spaces[index] != ' ') {
                printf("Sorry, that space is occupied. Please pick again.\n");
            }
            else {
                keepGoing = false;
            }
        } else {
            printf("That's not a valid space, please try again.\n");
        }
    } while (keepGoing);

    return index;
>>>>>>> 58e50da2f0eb941b23e301004a506f0995d34b54
}

//asks the user which space they would like to fill
//makes sure that the selection the user entered is valid (i.e., the coordinate exists and is not already occupied)
//makes sure that the user selects a space that is within the quadrant that is allowed
struct UltimateMove* getUserSelectionUltimate(struct UltimateBoard board, int quadrant) {
    char* getCoordinatesFromBoardMapping(int);
    int getUserSelectionBasic(struct BasicBoard);
    bool isQuadrantFull(struct UltimateBoard, int);
    int getBoardMappingFromCoordinates(char*);

    char *option = malloc(10*sizeof(char));
    bool keepGoing = true;
    int userSelection;

    //if first turn
    if(quadrant == -1) {
        //user may choose any quadrant
        printf("First move, you may choose any quadrant to play in.\n");
        printf("Which quadrant would you like to play in?\n");
        //get preferred quadrant
        fgets(option, 10, stdin);
        //remove the trailing newline created by fgets
        option[strcspn(option, "\n")] = 0;
        //get index from string
        quadrant = getBoardMappingFromCoordinates(option);
    }

    char* coordinates = getCoordinatesFromBoardMapping(quadrant);
    //if designated quadrant is full, user may choose any quadrant
    if(isQuadrantFull(board, quadrant)) {
        do {
            //inform user of situation
            printf("Quandrant %s is full, you may choose any quadrant to play in.\n", coordinates);
            printf("Which quadrant would you like to play in?\n");
            //get preferred quadrant
            fgets(option, 10, stdin);
            //remove the trailing newline created by fgets
            option[strcspn(option, "\n")] = 0;
            //get index from string
            quadrant = getBoardMappingFromCoordinates(option);
        //make sure they choose a valid (not full) quadrant
        } while (isQuadrantFull(board, quadrant));
    }
    
    coordinates = getCoordinatesFromBoardMapping(quadrant);
    //show current quadrant
    printf("You are playing in quadrant %s.\n", coordinates);
    printf("Quadrant %s:\n", coordinates);
    printBasicBoard(board.boards[quadrant]);

    //get input
    userSelection = getUserSelectionBasic(*board.boards[quadrant]);

    //return the 2D coordinates of where we are playing
    struct UltimateMove *move = malloc(sizeof(struct UltimateMove));
    move->quadrant = quadrant;
    move->move = userSelection;
    return move;
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
// 'x' / 'o' = Line Win
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

char* getCoordinatesFromBoardMapping(int boardMapping) {
    if(boardMapping == 0) {
        return "a1";
    } else if(boardMapping == 1) {
        return "b1";
    } else if(boardMapping == 2) {
        return "c1";
    } else if(boardMapping == 3) {
        return "a2";
    } else if(boardMapping == 4) {
        return "b2";
    } else if(boardMapping == 5) {
        return "c2";
    } else if(boardMapping == 6) {
        return "a3";
    } else if(boardMapping == 7) {
        return "b3";
    } else if(boardMapping == 8) {
        return "c3";
    } else
        return "";
}

bool isQuadrantFull(struct UltimateBoard board, int quadrant) {
    return board.boardsCompleted[quadrant] != ' ';
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
    return checkForFullWinsUltimate(boardMatrix);
}