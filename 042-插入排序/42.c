// 042 插入排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255


// 对数组 R 中的记录 R[1..n] 按递增序进行*插入排序*
void Insert_Sort(int R[], int n) {
    int i, j;

    // 依次插入 R[2], ..., R[n]
    for (i = 2; i <= n; i++) {
        if (R[i] < R[i - 1]) {
            // 若 R[i] 大于等于有序区中所有的 R，
            // 则 R[i] 应在原有位置上
            R[0] = R[i];
            j = i - 1; // R[0] 是哨兵，且是 R[i] 的副本
            do {
                // 从右向左在有序区 R[1..i-1] 中查找 R[i] 的插入位置
                R[j + 1] = R[j]; // 将关键字大于 R[i] 的记录后移
                j--;
            } while (R[0] < R[j]); // 当 R[i] ≥ R[j] 时终止
            R[j + 1] = R[0];       // R[i] 插入到正确的位置上
        }
    } // end for (i = 2; i <= n; i++)
} // void Insert_Sort

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

    Insert_Sort(R, n);

    puts("\nThe sequence after insert sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}