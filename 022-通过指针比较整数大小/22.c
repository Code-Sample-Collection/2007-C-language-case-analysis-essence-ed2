// 022 指针比较大小
/*
    1. 描述：使用指针比较大小并交换
    2. 输入：三个整数 `x,y,z`
    3. 输出：从小到大赋值给 x,y,z 后输出
    4. 测试样例
        + 1 2 3 => 1 2 3
        + 3 2 1 => 1 2 3
*/
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

void swap(int* px, int* py) {
    int tmp;
    if (*px > *py) { // 通过指向变量的指针引用变量的值
        tmp = *px;
        *px = *py;   // 通过指向变量 x 的指针 px,引用变量 x 的值
        *py = tmp;
    }
}

int main() {
    int x, y, z;  // 定义三个int型变量
    int *xp = &x, // 定义指针变量 xp,并赋值为 x 的地址，使 xp 指向 x
        *yp = &y,
        *zp = &z;

    clrscr();
    printf("Please input x,y,z: ");
    scanf("%d%d%d", xp, yp, zp); // 通过变量的指针，为变量赋值

    swap(xp, yp);
    swap(xp, zp);
    swap(yp, zp);
    printf("x = %d\ty = %d\tz = %d\n", x, y, z);

    quit();
}