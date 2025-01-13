#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SIZE 15
int board [SIZE][SIZE];
#define HRAC 'x'
#define PC  'o'
#define WIN_COUNT 5


void resetovaniHry(){

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
        
    }
    

}
void tistenyHry(){
    //cele sam  :)
    printf("                                     PISKVORKY                                      \n");
    printf("----|--------------------------------------------------------------------------|----\n");
    printf("    |");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%4d|", i +1);
    }
    printf("\n----|--------------------------------------------------------------------------|----\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%4d|", i +1);
        for (int j = 0; j < SIZE; j++)
        {
            //tohle mi teda napověděl, ale upravil jsem do tak, aby to sedělo k mojemu kodu
            printf("%4c|", board[i][j]);
        }
        printf("\n");
        printf("----|--------------------------------------------------------------------------|----\n");
    }
    

}

int volnaMista(){
    int volno = SIZE*SIZE;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
        if (board[i][j] != ' '){
            volno--;
        }
        }
    }
    return volno;
}
void hracKolo(){
    int x, y;

do
{
    printf("Zadejte x: ");
    scanf("%d", &x);
    printf("Zadejte y: ");
    scanf("%d", &y);
    x--;
    y--;

    if (board[x][y] != ' '){
        printf("Tam nemuzes!\n");
    }
    else{
        board[x][y] = HRAC;
        break;
    }
} while (board [x][y] != ' ');
}

void pcKolo(){
    srand(time(0));
    int x;
    int y;
    if(volnaMista() > 0){
        do
        {
            x = rand() % SIZE - 1;
            y = rand() % SIZE - 1;
            
        } while (board[x][y] != ' ');
        board[x][y] = PC;
        
    }
    else{
        vytiskVyherce(' ');
    }
}
char vyhra(){
    int count = 0;
    int Row,Col = 0;
    //kontroluje řádky
    //cele sam!!!!Uplne cele krom toho board[i][j] == board[i][j+1] a diagonal!!!!!!

    //kontroluje řádky
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if(count == 4){
                return board[row][col];
            }
            else{
                if(board[row][col] == board[row][col+1]){
                count++;
            }
            else{
                count = 0;
            }
            }
        }
    }
    //kontroluje sloupce
    for (int col = 0; col < SIZE; col++)
    {
        for (int row = 0; row < SIZE; row++)
        {
            if(count == 4){
                return board[row][col];
            }
            else{
                if(board[row][col] == board[row][col]){
                count++;
            }
            else{
                count = 0;
            }
            }
        }
    }
    // Kontrola diagonál zleva doprava (\)
    for (int row = 0; row < SIZE - WIN_COUNT + 1; row++) {
        for (int col = 0; col < SIZE - WIN_COUNT + 1; col++) {
            count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[row + k][col + k] == HRAC) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == WIN_COUNT) {
                return board[row][col];
            }
        }
    }

    // Kontrola diagonál zprava doleva (/)
    for (int row = 0; row < SIZE - WIN_COUNT + 1; row++) {
        for (int col = WIN_COUNT - 1; col < SIZE; col++) {
            count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[row + k][col - k] == HRAC) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == WIN_COUNT) {
                return board[row][col];
            }
        }
    }
    
}
void vytiskVyherce(char i){
if (i == HRAC)
{
    printf("Vyhral si!");
}
else if (i = PC){
    printf("Vyhral PC!");
}
else{
    printf("Remiza");
}

}


    
    

int main (){
char vyherce = ' ';

resetovaniHry();
while (vyherce == ' ' && volnaMista() != 0)
{
    tistenyHry();
    hracKolo();
    vyherce = vyhra();
    if (vyherce != ' ' ||volnaMista()==0){
        break;
    }
    pcKolo();
    vyherce = vyhra();
    if (vyherce != ' ' ||volnaMista()==0){
        break;
    }
}
tistenyHry();
vytiskVyherce(vyherce);


return 0;
}