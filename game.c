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

// Display the board with row/column headers
void showBoard(char board[MAX_SIZE][MAX_SIZE], int n) {
    printf("   ");
    for (int c = 0; c < n; c++) {
        printf("%d ", c + 1);
    }
    printf("\n");

    for (int r = 0; r < n; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < n; c++) {
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
}

// Check if a move is valid
int isValidMove(char board[MAX_SIZE][MAX_SIZE], int n, int r, int c) {
    return (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == '.');
}

// Place player's move
void playerMove(char board[MAX_SIZE][MAX_SIZE], int n, char symbol) {
    int r, c;
    do {
        printf("Enter row and column (1-%d): ", n);
        scanf("%d %d", &r, &c);
        r--; c--;  // adjust to 0-index
    } while (!isValidMove(board, n, r, c));

    board[r][c] = symbol;
}

// Check win condition (rows, columns, diagonals)
int hasPlayerWon(char board[MAX_SIZE][MAX_SIZE], int n, char symbol) {
    // Rows
    for (int r = 0; r < n; r++) {
        int rowWin = 1;
        for (int c = 0; c < n; c++) {
            if (board[r][c] != symbol) {
                rowWin = 0;
                break;
            }
        }
        if (rowWin) return 1;
    }

    // Columns
    for (int c = 0; c < n; c++) {
        int colWin = 1;
        for (int r = 0; r < n; r++) {
            if (board[r][c] != symbol) {
                colWin = 0;
                break;
            }
        }
        if (colWin) return 1;
    }

    // Main diagonal
    int mainDiag = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != symbol) {
            mainDiag = 0;
            break;
        }
    }
    if (mainDiag) return 1;

    // Anti-diagonal
    int antiDiag = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][n - 1 - i] != symbol) {
            antiDiag = 0;
            break;
        }
    }
    return antiDiag;
}

// Computer move: win/block/random
void computerMove(char board[MAX_SIZE][MAX_SIZE], int n, char symbol, int players) {
    int r, c;

    // Try to win
    for (r = 0; r < n; r++) {
        for (c = 0; c < n; c++) {
            if (isValidMove(board, n, r, c)) {
                board[r][c] = symbol;
                if (hasPlayerWon(board, n, symbol)) return;
                board[r][c] = '.';
            }
        }
    }

    // Try to block
    for (int opp = 0; opp < players; opp++) {
        char oppSym = (opp == 0 ? 'X' : 'O');
        if (oppSym == symbol) continue;

        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                if (isValidMove(board, n, r, c)) {
                    board[r][c] = oppSym;
                    if (hasPlayerWon(board, n, oppSym)) {
                        board[r][c] = symbol;
                        return;
                    }
                    board[r][c] = '.';
                }
            }
        }
    }

    // Otherwise random
    do {
        r = rand() % n;
        c = rand() % n;
    } while (!isValidMove(board, n, r, c));

    board[r][c] = symbol;
}

