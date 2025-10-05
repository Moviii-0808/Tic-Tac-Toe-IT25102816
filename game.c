#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 3
#define MAX_SIZE 10

// create the board
void createBoard(char b[MAX_SIZE][MAX_SIZE], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            b[i][j] = '.';
        }
    }
}

// print the board
void showBoard(char b[MAX_SIZE][MAX_SIZE], int n){
    printf("   ");
    for(int c=0;c<n;c++) printf("%d ", c+1);
    printf("\n");
    for(int r=0;r<n;r++){
        printf("%2d ", r+1);
        for(int c=0;c<n;c++){
            printf("%c ", b[r][c]);
        }
        printf("\n");
    }
}

// check if valid position
int isValidMove(char b[MAX_SIZE][MAX_SIZE], int n, int r, int c){
    if(r>=0 && r<n && c>=0 && c<n && b[r][c]=='.')
        return 1;
    return 0;
}

// ask player for move
void playerMove(char b[MAX_SIZE][MAX_SIZE], int n, char sym){
    int r,c;
    do{
        printf("Enter row and col (1-%d): ", n);
        scanf("%d %d", &r, &c);
        r--; c--;
    }while(!isValidMove(b,n,r,c));
    b[r][c] = sym;
}

// check if the player won
int hasPlayerWon(char b[MAX_SIZE][MAX_SIZE], int n, char s){
    // rows
    for(int i=0;i<n;i++){
        int ok=1;
        for(int j=0;j<n;j++){
            if(b[i][j]!=s){ ok=0; break; }
        }
        if(ok) return 1;
    }

    // cols
    for(int j=0;j<n;j++){
        int ok=1;
        for(int i=0;i<n;i++){
            if(b[i][j]!=s){ ok=0; break; }
        }
        if(ok) return 1;
    }

    // diagonals
    int ok1=1, ok2=1;
    for(int i=0;i<n;i++){
        if(b[i][i]!=s) ok1=0;
        if(b[i][n-1-i]!=s) ok2=0;
    }
    if(ok1 || ok2) return 1;
    return 0;
}

// computer move (try win > block > random)
void computerMove(char b[MAX_SIZE][MAX_SIZE], int n, char sym, int players){
    int r,c;

    // try win
    for(r=0;r<n;r++){
        for(c=0;c<n;c++){
            if(isValidMove(b,n,r,c)){
                b[r][c]=sym;
                if(hasPlayerWon(b,n,sym)) return;
                b[r][c]='.';
            }
        }
    }

    // try block
    for(int o=0;o<players;o++){
        char os = (o==0)?'X':'O';
        if(os==sym) continue;
        for(r=0;r<n;r++){
            for(c=0;c<n;c++){
                if(isValidMove(b,n,r,c)){
                    b[r][c]=os;
                    if(hasPlayerWon(b,n,os)){
                        b[r][c]=sym;
                        return;
                    }
                    b[r][c]='.';
                }
            }
        }
    }

    // random
    do{
        r = rand()%n;
        c = rand()%n;
    }while(!isValidMove(b,n,r,c));

    b[r][c]=sym;
}

int main(){
    char board[MAX_SIZE][MAX_SIZE];
    char sym[MAX_PLAYERS]={'X','O','Z'};
    int n, p, mode, cur=0, moves=0, over=0;

    srand(time(NULL));

    printf("Enter board size (3-10): ");
    scanf("%d",&n);
    if(n<3 || n>MAX_SIZE){
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter players (2 or 3): ");
    scanf("%d",&p);
    if(p<2 || p>MAX_PLAYERS){
        printf("Invalid players!\n");
        return 1;
    }

    if(p==2){
        printf("\n1. User vs User\n2. User vs Computer\nEnter: ");
        scanf("%d",&mode);
        if(mode!=1 && mode!=2){
            printf("Invalid!\n");
            return 1;
        }
    } else mode=1;

    createBoard(board,n);

    while(!over){
        showBoard(board,n);
        printf("Player %d (%c)\n", cur+1, sym[cur]);

        if(mode==2 && p==2 && cur==1)
            computerMove(board,n,sym[cur],p);
        else
            playerMove(board,n,sym[cur]);

        moves++;

        if(hasPlayerWon(board,n,sym[cur])){
            showBoard(board,n);
            printf("Player %d wins!\n", cur+1);
            over=1;
        }else if(moves==n*n){
            showBoard(board,n);
            printf("Draw!\n");
            over=1;
        }

        cur++;
        if(cur==p) cur=0;
    }

    return 0;
}
