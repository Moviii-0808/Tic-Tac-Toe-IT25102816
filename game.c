#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 3
#define MAX_SIZE 10

// Function prototypes
void createBoard(char board[MAX_SIZE][MAX_SIZE], int n);
void showBoard(char board[MAX_SIZE][MAX_SIZE], int n);
int isValidMove(char board[MAX_SIZE][MAX_SIZE], int n, int r, int c);
int hasPlayerWon(char board[MAX_SIZE][MAX_SIZE], int n, char symbol);
void playerMove(char board[MAX_SIZE][MAX_SIZE], int n, char symbol);
void computerMove(char board[MAX_SIZE][MAX_SIZE], int n, char symbol, int players);

int main() {
    int boardSize, totalPlayers, gameMode, currentPlayer = 0;
    char board[MAX_SIZE][MAX_SIZE];
    char symbols[MAX_PLAYERS] = {'X', 'O', 'Z'};

    srand(time(NULL));  // seed random

    // Board size input
    printf("Enter board size (3-10): ");
    scanf("%d", &boardSize);
    if (boardSize < 3 || boardSize > MAX_SIZE) {
        printf("Invalid board size!\n");
        return 1;
    }

    // Player mode selection
    printf("Enter number of players (2 or 3): ");
    scanf("%d", &totalPlayers);
    if (totalPlayers < 2 || totalPlayers > MAX_PLAYERS) {
        printf("Invalid number of players!\n");
        return 1;
    }

    // Game mode selection (for 2 players only)
    if (totalPlayers == 2) {
        printf("\nChoose game mode:\n");
        printf("1. User vs User\n");
        printf("2. User vs Computer\n");
        printf("Enter choice: ");
        scanf("%d", &gameMode);
        if (gameMode != 1 && gameMode != 2) {
            printf("Invalid choice!\n");
            return 1;
        }
    } else {
        gameMode = 1;  // 3-player mode always User vs User
    }

    createBoard(board, boardSize);

    int moves = 0, gameOver = 0;
    while (!gameOver) {
        showBoard(board, boardSize);
        printf("Player %d's turn (%c)\n", currentPlayer + 1, symbols[currentPlayer]);

        // User vs Computer logic
        if (gameMode == 2 && totalPlayers == 2 && currentPlayer == 1) {
            computerMove(board, boardSize, symbols[currentPlayer], totalPlayers);
        } else {
            playerMove(board, boardSize, symbols[currentPlayer]);
        }

        moves++;

        // Check win
        if (hasPlayerWon(board, boardSize, symbols[currentPlayer])) {
            showBoard(board, boardSize);
            printf("Player %d wins!\n", currentPlayer + 1);
            gameOver = 1;
        } else if (moves == boardSize * boardSize) {
            showBoard(board, boardSize);
            printf("It's a draw!\n");
            gameOver = 1;
        }

        // Cycle players
        currentPlayer++;
        if (currentPlayer == totalPlayers) currentPlayer = 0;
    }

    return 0;
}

// Initialize the board with '.'
void createBoard(char board[MAX_SIZE][MAX_SIZE], int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            board[r][c] = '.';
        }
    }
}

