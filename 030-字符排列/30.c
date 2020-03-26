// 030 字符串的所有字符排列函数。用已知字符串s中的所有字符，生成由其中 n 个字符组成的所有字符排列
#include <stdio.h>  // puts
#include <string.h> // strcpy
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define MAX_LEN 20

char w[MAX_LEN];
void perm(int n, char *s) {
    char s1[MAX_LEN];
    int i;

    if (n < 1) {
        // 一个排列生成输出
        printf("%s\n", w);
    } else {
        // 存本层次可使用的字符
        strcpy(s1, s);

        // 依次选本层次可用字符
        for (i = 0; *(s1 + i); i++) {
            // 将选用字符填入正在生成的字符排列中
            *(w + n - 1) = *(s1 + i);
            *(s1 + i) = *s1;
            *s1 = *(w + n - 1);
            perm(n - 1, s1 + 1); // 递归
        }
    } // if (n < 1)
} // void perm(int n, char *s)

int main() {
    int n = 2;
    char s[MAX_LEN];
    w[n] = '\0';

    clrscr();
    puts("This is a char permutation program!");
    printf("Please input a string: ");
    scanf("%s", s);
    printf("Please input the char number of permuted: ");
    scanf("%d", &n);

    puts("The permuted chars are:");
    perm(n, s);

    quit();
}