#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }
void quit() { printf("\n\nPress any key to quit...\n"); _getch(); exit(0); }

#define N 50
int main() {
    int primes[N];
    int pc, m, k;

    clrscr();
    printf("\nThe first %d prime numbers are:\n", N);
    primes[0] = 2; /* 2是第一个质数 */
    pc = 1; /*已有第一个质数 */
    m = 3;  /*被测试的数从3开始 */
    while (pc < N) {
        /* 调整 m 使它为下一个质数 */
        k = 0;
        while (primes[k] * primes[k] <= m) {
            if (m%primes[k] == 0) { /* m 是合数 */
                m += 2; /* 让 m 取下一个奇数 */
                k = 1;  /* 不必用 primes[0]=2 去测试 m，所以 k 从一开始 */
            } else {
                k++; /* 继续用下一个质数去测试 */
            }
        }
        primes[pc++] = m;
        m += 2; /* 除 2 外，其余质数均是奇数 */
    } // while (pc < N)

    /* 输出 primes[0] 至 primes[pc-1] */
    for (k = 0; k < pc; k++) {
        printf("%4d", primes[k]);
    }

    quit();
}