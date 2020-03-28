// 045 快速排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define MAX 255

// 调用 Partition(R，low，high) 时，对 R[low..high] 做划分
// 并返回基准记录的位置
int Partition(int R[], int i, int j) {                     
    int pivot = R[i]; // 用区间的第 1 个记录作为基准
    while (i < j) { // 从区间两端交替向中间扫描，直至 i=j 为止
        // pivot 相当于在位置i上从右向左扫描，
        // 查找第1个关键字小于 pivot.key 的记录 R[j]
        while (i < j && R[j] >= pivot) j--;
        // 表示找到的 R[j] 的关键字 pivot.key 
        if (i < j) R[i++] = R[j]; // 相当于交换 R[i] 和 R[j]，交换后i指针加1

        // pivot相当于在位置j上从左向右扫描，
        // 查找第1个关键字大于 pivot.key 的记录 R[i]
        while (i < j && R[i] <= pivot) i++;
        // 表示找到了 R[i]，使 R[i].key>pivot.key
        if (i < j) R[j--] = R[i]; // 相当于交换R[i]和R[j]，交换后j指针减1
    } // end while (i < j)
    R[i] = pivot; // 基准记录已被最后定位
    return i;
} // end of partition 

// 对 R[low..high] 快速排序
void _Quick_Sort_Rec(int arr[], int low, int high) {                 
    int pivotpos; // 划分后的基准记录的位置
    if (low < high) { // 仅当区间长度大于 1 时才须排序
        pivotpos = Partition(arr, low, high);     // 对 R[low..high] 做划分
        _Quick_Sort_Rec(arr, low, pivotpos - 1);  // 对左区间递归排序
        _Quick_Sort_Rec(arr, pivotpos + 1, high); // 对右区间递归排序
    }
} // end of Quick_Sort

// 对 arr 快速排序
void Quick_Sort(int arr[], int n) {
    _Quick_Sort_Rec(arr, 1, n);
}

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

    Quick_Sort(R, n);

    puts("\nThe sequence after Quick Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}