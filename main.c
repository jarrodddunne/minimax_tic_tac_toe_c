//Copyright Jarrod Dunne 2015
//jddunne.com
//jarrodddunne@gmail.com
//https://github.com/jarroddunne/
//https://www.linkedin.com/pub/jarrod-dunne/90/b14/8a8
//A perfect Tic Tac Toe Player in C using the Minimax Algorithm
#include <stdio.h>

int getPlayerTurn();
void printBoard(int board[9]);
int getWinningMove(int board[9]);
int miniMax(int board[9], int player);
int getComputerMove(int board[9], int player);
int getPlayerMove(int board[9]);

int main() {
    int board[9] = {0};
    int playerTurn = getPlayerTurn();
    int currentTurn;
    for(currentTurn = 0; currentTurn < 9 && getWinningMove(board) == 0; currentTurn++) {
        if((currentTurn+playerTurn) % 2 == 0){
            printBoard(board);
            int computerMove = getComputerMove(board, 3-playerTurn);
            printf("\nComputer chooses to play at %i\n", computerMove);
            board[computerMove] = 3-playerTurn;
        } else {
            printBoard(board);
            int playerMove = getPlayerMove(board);
            board[playerMove] = playerTurn;
        }
    }
    switch(getWinningMove(board)) {
        case 0:
            printf("GAME DRAWN\n");
            break;
        case 1:
            printf("COMPUTER WINS\n");
            break;
        case -1:
            printf("PLAYER WINS\n");
            break;
    }
    printBoard(board);
    return 0;
}

int getPlayerTurn(){
    int playerTurn = 0;
    do {
        printf("Enter player's preferred turn: (1 for first, 2 for second): ");
        scanf("%i",&playerTurn);
        printf("\n");
    } while (playerTurn != 1 && playerTurn != 2);
}

void printBoard(int board[9]){
    int i;
    for(i = 0; i < 9; i++){
        switch(board[i]){
        case 0:
            printf("%i",i);
            break;
        case 1:
            printf("X");
            break;
        case 2:
            printf("O");
            break;
        }
        if(i % 3 != 2){
            printf("|");
        } else {
            printf("\n");
        }
    }
}

int getWinningMove(int board[9]) {
    int winningPositions[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[winningPositions[i][0]] != 0 && board[winningPositions[i][0]] == board[winningPositions[i][1]] && board[winningPositions[i][0]] == board[winningPositions[i][2]]){
            return board[winningPositions[i][2]];
        }
    }
    return 0;
}

int miniMax(int board[9], int currentPlayer) {
    int winner = getWinningMove(board);
    if(winner == currentPlayer){
        return 1;
    } else if(winner == 3-currentPlayer){
        return -1;
    }
    int bestMove = -1;
    int maxScore = -2;
    int move;
    for(move = 0; move < 9; move++) {
        if(board[move] == 0) {
            board[move] = currentPlayer;
            int thisScore = -1 * miniMax(board, 3-currentPlayer);
            if(thisScore > maxScore) {
                maxScore = thisScore;
                bestMove = move;
            }
            board[move] = 0;
        }
    }
    if(bestMove == -1){
        return 0;
    }
    return maxScore;
}

int getComputerMove(int board[9], int computerPlayer) {
    int bestMove = -1;
    int maxScore = -2;
    int move;
    for(move = 0; move < 9; move++) {
        if(board[move] == 0) {
            board[move] = computerPlayer;
            int moveScore = -1 * miniMax(board, 3-computerPlayer);
            board[move] = 0;
            if(moveScore > maxScore) {
                maxScore = moveScore;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

int getPlayerMove(int board[9]) {
    int playerMove = 0;
    do {
        printf("\nInput player's move (0-8): ");
        scanf("%d", &playerMove);
        printf("\n");
    } while (playerMove >= 9 || playerMove < 0 && board[playerMove] == 0);
    return playerMove;
}
