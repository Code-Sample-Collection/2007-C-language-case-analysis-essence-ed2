// 031 回文数判断
#include <stdio.h>  // puts
#include <string.h> // strlen
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define MAX 50

int cycle(char *s) {
    char *h, *t;

    for (h = s, t = s + strlen(s) - 1; t > h; h++, t--) {
        if (*h != *t) break;
    }
    return t <= h;
}

int main() {
    char s[MAX];

    clrscr();
    while (1) {
        puts("Please input the string you want to judge (input ^ to quit):");
        scanf("%s", s);

        if (s[0] == '^') break;

        if (cycle(s)) {
            printf(" %s is a cycle string.\n", s);
        } else {
            printf(" %s is not a cycle string.\n", s);
        }
    }
    puts("\nThank you for your using,bye bye!");

    return 0;
}
