#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY ' '
#define SIZE 15
#define BOARD_SIZE SIZE*SIZE

void boardPrinter(char board[SIZE][SIZE], int firstTime) {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = EMPTY;
            }
        }
        printf("                                     PISKVORKY                                      \n");
        printf("----|--------------------------------------------------------------------------|----\n");
        //printf("--|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10| 11| 12| 13| 14| 15|--\n");

        printf("    |");
        for (int i = 0; i < SIZE; ++i) {
            printf("%4d|", i + 1);
        }
        printf("    \n");
        printf("----|--------------------------------------------------------------------------|----\n");


        for (int j = 0; j < SIZE; ++j) {
            printf("%4d|", j);
            for (int i = 0; i < SIZE; ++i) {
                if (firstTime) {
                    printf("    |");
                } else {
                    printf("%4c|", board);
                }
            }
            printf("    \n");
            printf("----|--------------------------------------------------------------------------|----\n");
        }
    }




int playerMove(char Souradnice) {
    int souradnice = 0;

    printf("Souradnice %c: ", Souradnice);
    scanf("%d", &souradnice);
}

int isPositionFree(int rows, int columns) {
    bool isFree = false;
    do {
        if (rows < 0 || rows > SIZE || columns < 0 || columns > SIZE) {
            printf("Souradnice nejsou v platnem rozsahu\n");
        } else {
            isFree = true;
            return 1;
        }
    } while (isFree == false);


}

int main() {
    char playerMoves[SIZE][SIZE];
    boardPrinter(playerMoves, 1);
   /* if (isPositionFree(pX, pY) == 0) {
        printf("Pozice je obsazena\n");
    } else {
        printf("Pozice je volna\n");
    }
    */
    return 0;
}