#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SIZE 15
#define HRAC 'x'
#define PC 'o'
#define WIN_COUNT 5

void vytiskVyherce(char hrac)
{
    if (hrac == HRAC)
    {
        printf("Vyhral jsi!");
    }
    else if (hrac = PC)
    {
        printf("Vyhral PC!");
    }
    else
    {
        printf("Remiza");
    }
}

void resetovaniHry(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void tistenyHry(char board[SIZE][SIZE])
{
    // cele sam  :)
    printf("                                     PISKVORKY                                      \n");
    printf("----|--------------------------------------------------------------------------|----\n");
    printf("    |");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%4d|", i + 1);
    }
    printf("\n----|--------------------------------------------------------------------------|----\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%4d|", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            // tohle mi teda napověděl, ale upravil jsem do tak, aby to sedělo k mojemu kodu
            printf("%4c|", board[i][j]);
        }
        printf("\n");
        printf("----|--------------------------------------------------------------------------|----\n");
    }
}

int volnaMista(char board[SIZE][SIZE])
{
    int volno = SIZE * SIZE;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] != ' ')
            {
                volno--;
            }
        }
    }
    return volno;
}
void hracKolo(char board[SIZE][SIZE])
{
    int x, y;

    do
    {
        printf("Zadejte x: ");
        scanf("%d", &x);
        printf("Zadejte y: ");
        scanf("%d", &y);
        x--;
        y--;

        if (board[y][x] != ' ')
        {
            printf("Tam nemuzes!\n");
        }
        else
        {
            board[y][x] = HRAC;
            break;
        }
    } while (board[y][x] != ' ');
}

void pcKolo(char board[SIZE][SIZE])
{
    srand(time(0));
    int x;
    int y;
    if (volnaMista(board) > 0)
    {
        do
        {
            x = rand() % SIZE - 1;
            y = rand() % SIZE - 1;

        } while (board[y][x] != ' ');
        board[y][x] = PC;
    }
    else
    {
        vytiskVyherce(' ');
    }
}
char vyhra(char board[SIZE][SIZE])
{
    int count = 0;
    // kontroluje řádky
    // cele sam!!!!Uplne cele krom toho board[i][j] == board[i][j+1] a diagonal!!!!!!

    // kontroluje řádky
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE - 1; col++)
        {
            if (count == WIN_COUNT)
            {
                return 1;
            }
            else
            {
                char cell = board[row][col];

                if (cell != ' ' &&  cell == board[row][col])
                {
                    count++;
                }
                else
                {
                    count = 0;
                }
            }
        }
    }
    // kontroluje sloupce
    for (int col = 0; col < SIZE; col++)
    {
        for (int row = 0; row < SIZE - 1; row++)
        {
            if (count == WIN_COUNT)
            {
                return 1;
            }
            else
            {
                char cell = board[row][col];

                if (cell != ' ' && cell == board[row][col])
                {
                    count++;
                }
                else
                {
                    count = 0;
                }
            }
        }
    }
    // Kontrola diagonál zleva doprava (\)
    for (int row = 0; row < SIZE - WIN_COUNT + 1; row++)
    {
        for (int col = 0; col < SIZE - WIN_COUNT + 1; col++)
        {
            count = 0;
            char checkedChar = board[row][col];

            if (checkedChar == ' ')
            {
                continue;
            }


            for (int k = 0; k < WIN_COUNT; k++)
            {
                if (board[row + k][col + k] == checkedChar)
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            if (count == WIN_COUNT)
            {
                return 1;
            }
        }
    }

    // Kontrola diagonál zprava doleva (/)
    for (int row = 0; row < SIZE - WIN_COUNT + 1; row++)
    {
        for (int col = WIN_COUNT - 1; col < SIZE; col++)
        {
            count = 0;
            char checkedChar = board[row][col];

            if (checkedChar == ' ')
            {
                continue;
            }

            for (int k = 0; k < WIN_COUNT; k++)
            {
                if (board[row + k][col - k] == checkedChar)
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            if (count == WIN_COUNT)
            {
                return 1;
            }
        }
    }

   return 0;
}

int main()
{
    char board[SIZE][SIZE];
    char vyherce = ' ';

    resetovaniHry(board);
    while (volnaMista(board) != 0)
    {
        tistenyHry(board);
        hracKolo(board);
        if (vyhra(board)) {
	   vyherce = HRAC;
	}
        if (vyherce != ' ' || volnaMista(board) == 0)
        {
            break;
        }
        pcKolo(board);
        if (vyhra(board)) {
	   vyherce = PC;
	}
        if (vyherce != ' ' || volnaMista(board) == 0)
        {
            break;
        }
    }
    tistenyHry(board);
    vytiskVyherce(vyherce);

    return 0;
}