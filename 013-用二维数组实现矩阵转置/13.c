/* 用二维数组实现矩阵的转置 */
#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }
void quit() { printf("\n\nPress any key to quit...\n"); _getch(); exit(0); }

#define ROW 3
#define COL 4

int main() {
    int matrixA[ROW][COL], matrixB[COL][ROW];
    int i, j;

    clrscr();

    // 读入数组
    printf("Enter elements of the matrixA,");
    printf("%d*%d:\n", ROW, COL);
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    // 复制并转置
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            matrixB[j][i] = matrixA[i][j];
        }
    }

    // 输出转置后的数组
    printf("MatrixB,");
    printf("%d*%d:\n", COL, ROW);
    for (i = 0; i < COL; i++) {
        for (j = 0; j < ROW; j++) {
            printf("%8d", matrixB[i][j]);
        }
        printf("\n");
    }

    quit();
}
