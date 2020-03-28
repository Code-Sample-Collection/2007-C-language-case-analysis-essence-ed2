// 043 希尔排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255


// 希尔排序中的一趟排序，d 为当前增量
// 采用插入排序
void ShellPass(int R[], int d, int n) { 
    int i, j;

    for (i = d + 1; i <= n; i++) 
        // 将 R[d+1..n] 分别插入各组当前的有序区
        if (R[i] < R[i - d]) {
            R[0] = R[i]; // R[0] 只是暂存单元，不是哨兵
            j = i - d; 
            do { // 查找 R[i] 的插入位置
                R[j + d] = R[j]; // 后移记录
                j = j - d;       // 查找前一记录
            } while (j > 0 && R[0] < R[j]);
            R[j + d] = R[0]; // 插入 R[i] 到正确的位置上
        } // endif
} // end of ShellPass

void Shell_Sort(int arr[], int n) {
    int increment = n; // 增量初值，不妨设 n>0
    do {
        increment = increment / 3 + 1; // 求下一增量
        ShellPass(arr, increment, n);  // 一趟增量为 increment 的 Shell 插入排序
    } while (increment > 1);
} // ShellSort

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

    Shell_Sort(R, n);

    puts("\nThe sequence after Shell Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}