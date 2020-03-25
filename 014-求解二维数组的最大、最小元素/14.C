#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }
void quit() { printf("\n\nPress any key to quit...\n"); _getch(); exit(0); }

#define MAXN 20

int main() {
    int a[MAXN][MAXN];
    int min, /* 存储最小值 */
        max; /* 存储最大值 */
    int row, col, n;

    clrscr();
    printf("Please input the order of the matrix:\n"); /* 输入方阵的阶次 */
    scanf("%d", &n);

    printf("Please input the elements of the matrix,\n");
    printf("from a[0][0] to a[%d][%d]:\n", n - 1, n - 1);
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            scanf("%d", &a[row][col]);
        }
    }
    for (row = 0; row < n; row++) {
        /* 从每行选出最大数 */
        for (max = a[row][0], col = 1; col < n; col++) {
            /*从row行选出最大数 */
            if (max < a[row][col]) {
                max = a[row][col];
            }
        }
        if (0 == row || min > max) {
            /* 保存至 row 行的最小数 */
            min = max;
        }
    }
    printf("The minimum of maximum number is %d\n", min);

    for (row = 0; row < n; row++) {
        /* 每行选出最小数 */
        for (min = a[row][0], col = 1; col < n; col++) { 
            /* 从row行选出最小数 */
            if (min > a[row][col]) {
                min = a[row][col];
            }
        }
        if (0 == row || max < min)  { 
            /* 保存至row行的最大数 */
            max = min;
        }
    }
    printf("The maximum of minimum number is %d\n", max);

    quit();
}