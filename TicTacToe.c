#include <stdio.h>
#include <stdbool.h>

//Purpose: Displays board
void printBoard(int board[], int playerA, int playerB) {
    char const A = 'A';
    char const B = 'B';
    int const NumOfTiles = 9; //Number of possible plays/tiles
    int const BoardSize = 3; //Number of rows and columns
    int tile = 1; //Possible plays [1, 9]
    
    for(tile = 0; tile < NumOfTiles; tile++) {
        if(board[tile] == A || board[tile] == B) { //To display char from an int[]
            printf("  %c", board[tile]);
        } else {
            printf("  %d", board[tile]);
        }
        if((tile + 1) % BoardSize == 0) {
            printf("\n");
        }
    }
    printf("\n");
} 
    
//Purpose: Checks if the requested tile is within the bounds of the board [1, 9]
bool bounds(int requestedTile) {
    if(requestedTile < 1 || requestedTile > 9) {
        return false; //Requested tile is not wihtin bounds
    }
return true; //Requested tile is within bounds
}

//Purpose: Checks if requested tile is occupied already
bool occupiedTiles(int board[], int requestedTile) {
    if(requestedTile != board[requestedTile - 1]){
        return false; //Requested tile is occupied
    }
return true; //Requested tile is not occupied
}

//Purpose: Checks if input is valid & requests a new input until valid
int requestValidInput(int board[], int requestedTile) {
    bool withinBounds = false;
    bool openTile = false;
    
    do {
        withinBounds = bounds(requestedTile);
        openTile = occupiedTiles(board, requestedTile);
        
        if(withinBounds == false) {
            printf("Invalid input, please try again.\n");
        } else if(openTile == false) {
            printf("That position has already been played, please try again.\n");
        } else {
            return requestedTile;
        } 
        scanf("%d", &requestedTile);
    } while (withinBounds == false || openTile == false);
        
return requestedTile;
}


//Purpose: Checks if there is a winner, draw, or if game isn't over
int checkForWinner(int board[], int A, int B) {
    int const BoardSize = 3; //Number of columns/rows of board
    int const NumOfTiles = 9; //Number of possible plays/tiles
    int i = 0, j = 0, k = 0;
    
    //Checks for any rows consisting of only playerA or playerB
    for(i = 0, j = 1, k = 2; k < NumOfTiles; i += 3, j+= 3, k+= 3) {
        if(board[i] == A && board[j] == A && board[k] == A) {
            return A;
        } else if(board[i] == B && board[j] == B && board[k] == B) {
            return B;
        } 
    }
    
    //Checks for any columns consisting of only playerA or playerB
    for(i = 0, j = 3, k = 6; k < NumOfTiles; i++, j++, k++) {
        if(board[i] == A && board[j] == A && board[k] == A) {
            return A; //Player A wins
        } else if(board[i] == B && board[j] == B && board[k] == B) {
            return B; //Player B wins
        } 
    }
    
    //Checks for any diagonals consisting of only playerA or playerB
    for(i = 0, j = 4, k = 8; i < BoardSize; i += 2, k -= 2) {
        if(board[i] == A && board[j] == A && board[k] == A) {
            return A; //Player A wins
        } else if(board[i] == B && board[j] == B && board[k] == B) {
            return B; //Player B wins
        } 
    }
    
    //Checks for if any spaces are still available
    for(i = 0; i < NumOfTiles; i++) {
        if(board[i] == i + 1) {
            return 0; // No winner (not all tiles are played)
        } else {
            continue;
        }
    }
    
return 1; //Draw (all tiles are played, but no winner)
}

int main(void) {
    int const NumOfTiles = 9; //Number of possible plays/tiles 
    char const A = 'A';
    char const B = 'B';
    int playerA = 0, playerB = 0, board[NumOfTiles], playNumber = 1, winner = 0;
    int tile = 1; //Possible plays [1, 9]
    
    for(tile = 0; tile < NumOfTiles; tile++) {
        board[tile] = tile + 1;
    }
    
    do {
        printf("The current state of the Tic-tac-toe Board:\n\n");
        printBoard(board, playerA, playerB);
        if(playNumber % 2 != 0) {
            printf("It is Player %c\'s turn.\n", A);
            printf("Please enter a valid position to play.\n");
            scanf("%d", &playerA);
            playerA = requestValidInput(board, playerA);
            board[playerA - 1] = A;
        } else {
            printf("It is Player %c\'s turn.\n", B);
            printf("Please enter a valid position to play.\n");
            scanf("%d", &playerB);
            playerB = requestValidInput(board, playerB);
            board[playerB - 1] = B;
        }
        playNumber++;
        winner = checkForWinner(board, A, B);
    } while(winner == 0);
    
    if(winner == A || winner == B) {
        printf("Player %c wins!\n\n", winner);
    } else {
        printf("It's a draw!\n\n");
    }
    printBoard(board, playerA, playerB);
    
return 0;
}

