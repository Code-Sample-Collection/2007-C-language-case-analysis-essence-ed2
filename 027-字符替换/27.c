// 027 字符串替换
#include <stdio.h> // puts
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define MAX 50

// 对 s 中出现的 s1 中的字符替换为 s2 中相应的字符
void rep(char *s, char *s1, char *s2) {
    // 顺序访问字符串 s 中的每个字符
    for (char *p; *s; s++) {
        // 检查当前字符是否在字符串 s1 中出现
        for (p = s1; *p && *p != *s; p++) ;
        if (*p) {
            // 当前字符在字符串s1中出现
            // 用字符串s2中的对应字符代替s中的字符
            *s = *(p - s1 + s2);
        }
    }
}

int main() {
    char s[MAX], s1[MAX], s2[MAX];

    clrscr();
    puts("Please input the string for s:");
    scanf("%s", s);
    puts("Please input the string for find:");
    scanf("%s", s1);
    puts("Please input the string for replace:");
    scanf("%s", s2);

    rep(s, s1, s2);
    puts("The string of s after displace is:");
    printf("%s\n", s);

    quit();
}
