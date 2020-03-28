// 051 二项式系数
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

int binom(int n, int i);
int main() {
    int n, i;

    //打印两项式
    puts("NOTE: Entering a figure other than a number will \ncause the program to crash.");
    puts("Formula computation is in B(n,i) N, 1st integer >= 2nd, I, Integer.");
    puts("             n!");
    puts(" B(n,i)= ----------");
    puts("          k!(n-i)!");
    puts("Warning: Program has no error checking!\n");

    printf("Enter two integer n,i : ");
    scanf("%d%d", &n, &i);
    printf("Binomial Coefficiant B(n,i) = %d", binom(n, i));

    quit();
}

int binom(int n, int i) {
    int a, b;
    if ((i == 0) || (n == i)) {
        return 1;
    } else {
        a = binom(n - 1, i);
        b = binom(n - 1, i - 1);
        return a + b;
    }
}
