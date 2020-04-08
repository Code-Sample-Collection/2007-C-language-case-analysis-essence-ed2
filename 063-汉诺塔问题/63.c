//////////////////////////////////////////////////////////////////
//                          汉诺塔问题                           //
//////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h> // exit


long step = 0;
void print_step(int n, char a, char c) {
    printf("%4d >>  Move Plate No.%d from Stick %c to Stick %c.\n", ++step, n, a, c);
}

// hanoil 子程序，实现将n个盘子从a移动到c
void hanoil(int n, char a, char b, char c) {
    if (n == 1) { // 递归调用的出口，n=1
        print_step(n, a, c);
    } else {
        hanoil(n - 1, a, c, b); // 递归调用
        print_step(n, a, c);
        hanoil(n - 1, b, a, c);
    }
}

int main() {
    int n;
    char a = 'A';
    char b = 'B';
    char c = 'C';

    printf("This is a hanoil program.\nPlease input number of the plates: ");
    scanf("%d", &n);
    if (n <= 0) {
        puts("n must no less than 1!");
        exit(1);
    }
    puts("The steps of moving plates are:");
    step = 0;
    hanoil(n, a, b, c);

    return 0;
}
