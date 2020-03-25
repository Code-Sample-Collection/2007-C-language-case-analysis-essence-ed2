#include <stdio.h>
#include <windows.h>
void gotoxy(int x, int y) { COORD pos={x,y};SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); }
void clrscr() { system("cls"); }

int main(void) {
    int i, j, x, y;
    clrscr();
    //        0123456789
    printf("\n        * * * 乘法口诀表 * * * \n");

    // 坐标从 {0,0} 开始
    // x 轴 0~9
    x = 6; y = 3;
    for (i = 1; i <= 9; i++) {
        gotoxy(x, y);
        printf("%2d ", i);
        x += 3;
    }

    // y 轴 0~9
    x = 4; y = 4;
    for (i = 1; i <= 9; i++) {
        gotoxy(x, y);
        printf("%2d ", i);
        y++;
    }

    // 填充乘法表项
    x = 6; y = 4;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            gotoxy(x, y);
            printf("%2d ", i*j);
            y++;
        }
        y -= 9;
        x += 3;
    }

    printf("\n");
    return 0;
}