// 023 各种数组寻址方法
/*
    1. 描述
    2. 输入
    3. 输出：四种数组寻址方法
    4. 测试样例
*/
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define N ( sizeof(a) / sizeof(a[0]) )

int main() {
    int j,  // 游标变量
        *p; // 指针变量
    int a[] = {1, 2, 3, 4, 5};

    clrscr();
    for (j = 0; j < N; j++) {
        // 数组名和下标顺序访问数组的元素
        printf("a[%d]\t= %d\t", j, a[j]);
    }
    printf("\n");
 
    for (p = a; p < a + N; p++) {
        // 让指针顺序指向数组的各元素，遍历数组
        printf("*p\t= %d\t", *p);
    }
    printf("\n");

    for (p = a, j = 0; p + j < a + N; j++) {
        // 指针与游标变量结合，改变游标变量遍历数组
        printf("*(p+%d)\t= %d\t", j, *(p + j));
    }
    printf("\n");

    for (p = a + N - 1, j = N - 1; j >= 0; j--) {
        // 指针与游标变量结合，用指针和下标遍历数组
        printf("p[-%d]\t= %d\t", j, p[-j]);
    }
    printf("\n");

    quit();
}