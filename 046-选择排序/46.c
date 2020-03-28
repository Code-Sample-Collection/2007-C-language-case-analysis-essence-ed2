// 046 选择排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255

void Select_Sort(int R[], int n) {
    for (int i = 1, k = 1; i < n; i++) {
        // 做第 i 趟排序 (1 ≤ i ≤ n-1)
        k = i;
        for (int j = i + 1; j <= n; j++) {
            // 在当前无序区 R[i..n] 中选 key 最小的记录 R[k]
            if (R[j] < R[k]) k = j; // k 记下目前找到的最小关键字所在的位置
        }
        if (k != i) {
            // 交换 R[i] 和 R[k]
            R[0] = R[i]; // R[0] 作暂存单元
            R[i] = R[k];
            R[k] = R[0];
        } // end if
    } // end for
} // end of Select_Sort

int main() {
    int i, n, R[MAX];

    clrscr();
    printf("Please input total element number of the sequence: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) {
        printf("n must more than 0 and less than %d.\n", MAX);
        exit(0);
    }

    printf("Please input the elements one by one: ");
    for (i = 1; i <= n; i++) scanf("%d", &R[i]);
    puts("The sequence you input is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    Select_Sort(R, n);

    puts("\nThe sequence after Select Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}