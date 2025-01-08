#include <stdio.h>
const char hrac = "HRAC";
const char pc = "PC";
char hraciPlocha[15][15];

void header() {
    //8 mezer z obou stran
    printf("                                        PISKVORKY                                 \n");
    printf("--|-----------------------------------------------------------------|--\n");
    printf("  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  10|  11|  12|  13|  14|  15|  \n");
}

void resetHry() {

}
void tisteniHry() {
    int i, j;
    for (i = 0; i < 15; i++) {
        printf("--|-----------------------------------------------------------------|--\n");
        printf("%2d|", i + 1);
        for (j = 0; j < 15; j++) {
            printf("  %c|", hraciPlocha[i][j]);
        }
        printf("\n");
    }
    printf("--|-----------------------------------------------------------------|--\n");
}
void tahHrace() {
    int x;
    int y;

    do {
        printf("Je na tahu hrac");
        printf("Zadejte radu:");
        scanf("%d", &x);
        x--;
        printf("Zadejte sloupec:");
        y--;
        scanf("%d", &y);
        if (hraciPlocha[x][y] != ' ') {
            printf("Tah mimo tabulku");
        } else {
            hraciPlocha[x][y] = 'HRAC';
            break;
        }
    } while (hraciPlocha[x][y] != ' ');
}
int main(void) {
    header();
    tisteniHry();
    return 0;
}
