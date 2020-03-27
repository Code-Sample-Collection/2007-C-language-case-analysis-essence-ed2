// 035
#include <stdio.h>  // puts
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

struct ele {
    int no;
    struct ele *link;
};


int main() {
    int n, m, i;
    struct ele *h, *u, *p;

    clrscr();
    puts("共 n 个人，依次报数。报到 m 的人退出。");
    printf("Please input n&m: ");
    scanf("%d%d", &n, &m); // 输入 n 和 m
    h = u = (struct ele *)malloc(sizeof(struct ele)); // 形成首表元
    h->no = 1;
    for (i = 2; i <= n; i++) // 形成其余的n-1个表元
    {
        u->link = (struct ele *)malloc(sizeof(struct ele));
        u = u->link;
        u->no = i; // 第i个表元置编号i
    }
    u->link = h; // 末表元后继首表元，形成环

    puts("\nThe numbers of who will quit the cycle in turn are:");
    while (n) {
        for (i = 1; i < m; i++) {
            // 掠过m－1个表元
            u = u->link;
        }
        p = u->link;       // p指向第m个表元
        u->link = p->link; // 第m个表元从环中脱钩
        printf("%4d", p->no);
        free(p); // 释放第m个表元占用的空间
        n--;
    }

    quit();
}
