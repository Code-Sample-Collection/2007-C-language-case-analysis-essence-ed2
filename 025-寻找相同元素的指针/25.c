// 025 在已知两个从小到大有序的数组中寻找都出现的第一个元素的指针
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

int *search(int *pa, int *pb, int an, int bn) {
    int *ca, *cb;
    // ca、cb 设定初值
    ca = pa;
    cb = pb;

    while (ca < pa + an && cb < pb + bn) { //两个数组都未考察完
        // 在两个数组中找下一个相等的元素
        if (*ca < *cb) {
            // 数组1的当前元素 < 数组2的当前元素
            ca++; // 调整数组1的当前元素指针
        } else if (*ca > *cb) {
            // 数组1的当前元素 > 数组2的当前元素
            cb++; // 调整数组2的当前元素指针
        } else { // *ca == *cb
            // 数组1的当前元素 == 数组2的当前元素
            // 在前两个数组中找到相等元素
            return ca; // 返回找到的相等元素
        }
    }
    return NULL; // 没找到
}

int main() {
    int *vp, i;
    int a[] = {1, 3, 5, 7,  9, 13, 15, 27, 29, 37};
    int b[] = {2, 4, 6, 8, 10, 13, 14, 27, 29, 37};
    int len_a = (sizeof(a) / sizeof(a[0])),
        len_b = (sizeof(b) / sizeof(b[0]));

    clrscr();
    printf("The elements of array a is:");
    for (i = 0; i < len_a; i++) {
        printf("%3d", a[i]);
    }
    printf("\nThe elements of array b is:");
    for (i = 0; i < len_b; i++) {
        printf("%3d", b[i]);
    }
    printf("\n");

    vp = search(a, b, len_a, len_b);
    if (vp) {
        printf("The first same number in both arrays is %d\n", *vp);
    } else {
        printf("Not found!\n");
    }

    quit();
}