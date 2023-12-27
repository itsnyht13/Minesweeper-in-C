#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

COORD coord = {0,0};

// Functions
void gotoxy();
void difficulty();
void easydiff();
void normaldiff();
void harddiff();
void initialize_board();
void print_board();
int cell_valid(int x, int y);
void player_guess();
void reveal_cell(int x, int y);
void win();
void lose();
void play_again();

// Variables
int x;
int y;
int row;
int column;
int diff;
int total_bombs;
int player_life = 3;
int board[25][25];
int remaining_cells;




int main(){

    difficulty();

    return 0;
}

void gotoxy(int x, int y){
    coord.X=x;
    coord.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void difficulty(){ // This function tells the user to choose a difficulty of his choice
    diff = 0;
    printf("==============              =============\n");
    printf("\\\\\\           \\____________/           ///\n");
    printf(" \\\\\\                                  ///\n");
    printf("  \\\\\\ >>> WELCOME TO MINESWEPEER <<< ///\n");
    printf("  ///          ____________          \\\\\\\n");
    printf(" ///          /            \\          \\\\\\ \n");
    printf("==============              ==============\n");
    while((diff != 1) && (diff !=2) && (diff != 3)){
        printf("     >>> SELECT YOUR DIFFICULTY <<<\n");
        printf("       \\\\======================//\n");
        printf("       ||  (1) EASY [8x8]     ||\n");
        printf("       |]=====================[|\n");
        printf("       ||  (2) NORMAL [12x12] ||\n");
        printf("       |]=====================[|\n");
        printf("       ||  (3) HARD [20x20]   ||\n");
        printf("       //=====================\\\\\n");
        printf("__________________\n");
        printf("Enter a number: ");
        if (scanf("%d", &diff) !=1 || diff > 3  || diff <= 0 || getchar() != '\n'){ // Check if user input is valid
            system("cls");
            printf("===========================================================\n");
            printf("| Notice: Invalid input, please enter an integer from 1-3 |\n");
            printf("===========================================================\n\n");
            while (getchar() != '\n'); // Discard invalid input
            difficulty();
        }
    system("cls");
    }
    if (diff == 1){
        easydiff();
    }
    else if (diff == 2){
        normaldiff();
    }
    else if (diff == 3){
        harddiff();
    }
}

void easydiff(){
    row = 8;
    column = 8;
    total_bombs = 10;

    initialize_board();
    print_board();
    player_guess();
}

void normaldiff(){
    row = 12;
    column = 12;
    total_bombs = 18;

    initialize_board();
    print_board();
    player_guess();
}

void harddiff(){
    row = 20;
    column = 20;
    total_bombs = 50;

    initialize_board();
    print_board();
    player_guess();
}


// This function Initialize the board, place random bombs and print the current board
void initialize_board(){
    
    // Initiliazing the Board

    int i;
    int j;
    int count;

    for(i=0; i < row; i++){
        for(j=0; j < column; j++){
            board[i][j] = '*'; // Dito banda binago
        }
    }

    // Placing random bombs in the board

    srand(time(NULL));

    count = 0;

    while (count < total_bombs){
        i = rand() % row;
        j = rand() % column;

        if (board[i][j] != '@'){
            board[i][j] = '@';
            count++;
        }
    }
    remaining_cells = row * column - total_bombs;
}


// This functions prints the board of the game 
void print_board(){
    int i;
    int j;
    
    // Printing the board
    printf("\n        ");
    for (i = 0; i < row; i++){
        printf("%-3d", i);
    }

    printf("\n");
    
    for (i = 0; i < column; i++){ // This prints the fist column or numbeing of the game
        printf("|%2d| ", i);
        printf("%s", "||");
        for (j = 0; j < column; j++){ // This prints the board of the game
            if(board[i][j] == '@'){
                printf("%2c ", '*'); // Changes the symbol of the bomb
            }
            else{
                printf("%2c ", board[i][j]);
            }
        }
        printf("||\n");
    }
    printf("\n");
    printf("===================\n");
    printf("| Player Life: %d  |\n", player_life);
    printf("===================\n");

}

// Function for player inputting the positions
void player_guess(){
    while(1){
        int x;
        int y;
        printf("--------------------------\n");
        printf("Enter row or x value: ");
        scanf("%d", &x);
        printf("--------------------------\n");
        printf("Enter column or y value: ");
        scanf("%d", &y);
        system("cls");
        if(x <= -1 || x < row && y <= -1 || y > column || getchar() != '\n'){
            printf("========================================\n");
            printf("| Notice: Invalid Position, Try again. |\n");
            printf("========================================\n");
            while(getchar() != '\n');
            print_board();
        }
        else{
            reveal_cell(x,y);
            print_board();
        }
    }
}

// Checks if the user input is valid 
int cell_valid(int x, int y){
    return x >= 0 && x < row && y >= 0 && y < column;
}


// Checks if the user input the same location as the bombs or empty cells
void reveal_cell(int x, int y){

    if (board[x][y] == ' ' || board[x][y] == '1' || board[x][y] == '2' || board[x][y] == '3' || board[x][y] == '4' || board[x][y] == '5' || board[x][y] == '6'){
        printf("=======================================================\n");
        printf("| Notice: Cell Already Revealed. Enter another value. |\n");
        printf("=======================================================\n");
        return; 
    }
    else if(board[x][y] == 'X'){
        printf("\n=======================================================\n");
        printf("| Notice: Bomb Already Revealed. Enter another value. |\n");
        printf("=======================================================\n");
        return;
    }
    else if (board[x][y] == '@') {
        player_life--;
        printf("===========================================\n");
        printf("| Notice: You hit a bomb! You lose 1 life |\n");
        printf("===========================================\n");
        board[x][y] = 'X';
        if (player_life == 0) {
            lose();
            exit(0);
        }
    }
    else if (board[x][y] == '*') {
        int i, j;
        int count = 0;
        for (i = x - 1; i <= x + 1; i++) {
            for (j = y - 1; j <= y + 1; j++) {
                if (cell_valid(i, j) && board[i][j] == '@') {
                    count++;
                }
            }
        }
        if (count == 0) {
            board[x][y] = ' ';
            remaining_cells--;
            for (i = x - 1; i <= x + 1; i++) {
                for (j = y - 1; j <= y + 1; j++) {
                    if (cell_valid(i, j) && board[i][j] == '*') {
                        reveal_cell(i, j);
                    }
                }
            }
        }
        else {
            board[x][y] = count + '0';
            remaining_cells--;
        }
    }

    if (remaining_cells == 0) {
        print_board();
        win();
        exit(0);

    }

}

// Win Condition
void win(){
    printf("=======================\n");
    printf("\\\\  CONGRATULATIONS //\n");
    printf("//     YOU WIN!     \\\\\n");
    printf("=======================\n");
    play_again();
}


// Lose Condition
void lose(){
    print_board();
    printf("=================\n");
    printf("\\\\  GAME OVER  //\n");
    printf("//  YOU LOSE!  \\\\\n");
    printf("=================\n");
    play_again();
}


// Play Again 
void play_again(){
    char option;

        printf("-------------------------------------------\n");
        printf("(Press Y if yes, Any key if no)\n");
        printf("Do you want to play again?: ");
        scanf(" ");
        scanf("%c", &option);

        if ((option == 'Y') || (option == 'y')){
            player_life = 3;
            system("cls");
            difficulty();
        }
        else{
            system("cls");
            printf("\n");
            gotoxy(13,2);
            printf("||><><><><><><><><><||\n");
            gotoxy(13,3);
            printf("||  THANK YOU FOR   ||\n");
            gotoxy(13,4);
            printf("||    PLAYING!!!    ||\n");
            gotoxy(13,5);
            printf("||><><><><><><><><><||\n\n");
        }

}