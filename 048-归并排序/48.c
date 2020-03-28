// 048 归并排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255

// 将两个有序的子文件 R[low..mid) 和 R[mid+1..high] 
// 归并成一个有序的子文件 R[low..high]
void Merge(int arr[], int low, int mid, int high) {
    int i = low, j = mid + 1, p = 0;
    int *R1; // R1是局部向量，若p定义为此类型指针速度更快
    R1 = (int *)malloc((high - low + 1) * sizeof(int));
    if (!R1) { // 申请空间失败
        puts("Insufficient memory available!");
        exit(-1);
    }

    // 两子文件非空时取其小者输出到  R1[p] 上
    while (i <= mid && j <= high) {
        R1[p++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }
    // 若第1个子文件非空，则复制剩余记录到 R1 中
    while (i <= mid) R1[p++] = arr[i++];
    // 若第2个子文件非空，则复制剩余记录到 R1 中
    while (j <= high) R1[p++] = arr[j++];
    // 归并完成后将结果复制回 R[low..high]
    for (p = 0, i = low; i <= high; p++, i++) arr[i] = R1[p]; 
} // end of Merge

// 用分治法对 R[low..high] 进行二路归并排序
void Merge_SortDC(int arr[], int low, int high) { 
    int mid;
    if (low < high) { // 区间长度大于1
        mid = (low + high) / 2; // 分解
        Merge_SortDC(arr, low, mid);      // 递归地对 R[low..mid] 排序
        Merge_SortDC(arr, mid + 1, high); // 递归地对 R[mid+1..high] 排序
        Merge(arr, low, mid, high);  // 组合，将两个有序区归并为一个有序区
    }
} // end of Merge_SortDC

void Merge_Sort(int arr[], int n) {
    Merge_SortDC(arr, 1, n);
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

    Merge_Sort(R, n);

    puts("\nThe sequence after Merge Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}