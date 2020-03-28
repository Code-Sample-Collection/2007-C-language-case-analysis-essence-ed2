// 044 冒泡排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255

// R（l..n)是待排序的文件，采用自下向上扫描，对R做冒泡排序
void Bubble_Sort(int R[], int n) {
    int exchange; // 交换标志

    for (int i = 1; i < n; i++) { // 最多做 n-1 趟排序
        exchange = FALSE; // 本趟排序开始前，交换标志应为假
        for (int j = n - 1; j >= i; j--) {
            // 对当前无序区 R[i..n] 自下向上扫描
            if (R[j + 1] < R[j]) {
                // 交换记录
                R[0]     = R[j + 1]; // R[0]不是哨兵，仅做暂存单元
                R[j + 1] = R[j];
                R[j]     = R[0];
                exchange = TRUE; // 发生了交换，故将交换标志置为真
            }
        }
        // 本趟排序未发生交换，提前终止算法
        if (!exchange) return;
    } // for (i = 1; i < n; i++)
} // void Bubble_Sort

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

    Bubble_Sort(R, n);

    puts("\nThe sequence after Bubble Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}