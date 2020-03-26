// 024 使用指针遍历搜索数组
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

int *find(
    int *apt,   // 已知数表的首元指针
    int n,      // 数表中元素个数
    int key     // 要寻找的值
) {
    int *p;
    for (p = apt; p < apt + n; p++) {
        if (*p == key) {
            return p; // 返回找到元素的指针
        }
    }
    return NULL;
}

int search(
    int *apt,   // 已知数表的首元指针
    int n,      // 数表中元素个数
    int key     // 要寻找的值
) {
    int *p = find(apt, n, key);
    if (p) {
        return p - apt; // 返回找到元素的下标
    } else { // p == NULL
        return -1;
    }
}

int main() {
    int a[] = {
        90, 80, 70, 60, 50, 
        40, 30, 20, 10, 9, 
        8,  7,  6,  5,  42, 
        40, 50, 1,  2,  3,
    };
    int i, key, len = (sizeof(a)/sizeof(a[0]));

    clrscr();
    // 打印数组
    printf("The elements of array a is:\n");
    printf(  "  i  =");
    for (i = 0; i < len; i++) printf("%4d", i);
    printf("\na[i] =");
    for (i = 0; i < len; i++) printf("%4d", a[i]);
    printf("\n");

    // 查找数字
    printf("The address of a[0] is: %d.\n", &a[0]);
    printf("\nPlease input the key number you want to search: ");
    scanf("%d", &key);
    printf(
        "The label number of the key number %d in the array is: %d.\n",
        key, search(a, len, key)
    );
    printf(
        "The point value of the key number %d in the array is: %d.\n",
        key, find(a, len, key)
    );

    quit();
}