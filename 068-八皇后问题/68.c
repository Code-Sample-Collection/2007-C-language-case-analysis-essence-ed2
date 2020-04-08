#include <math.h>
#include <stdio.h>
#define MAX 8 // 棋子数及棋盘大小MAXxMAX
int board[MAX];

// 打印結果
void show_result() {
    for (int i = 0; i < MAX; i++)
        printf("(%d,%d)", i, board[i]);
    printf("\n");
}

// 检查是否在同一直橫斜线上有其它棋子
int check_cross(int n) {
    for (int i = 0; i < n; i++) {
        if (
            board[i] == board[n] ||
            (n - i) == abs(board[i] - board[n])
        ) return 1;
    }
    return 0;
}

// 放棋子到棋盘上
void put_chess(int n) {
    for(int i = 0; i < MAX; i++) {
        board[n] = i;
        if (!check_cross(n)) {
            if (n == MAX - 1) {
                show_result(); // 找到其中一种放法了...打印結果
            } else {
                put_chess(n + 1);
            }
        }
    }
}

int main() {
    puts("The possible placements are:");
    put_chess(0);
    return 0;
}