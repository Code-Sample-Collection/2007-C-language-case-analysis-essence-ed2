// 047 堆排序
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 255

// 对 R[1..n] 进行堆调整，用 arr[start] 做暂存单元
// siftDown: http://cs.middlesexcc.edu/~schatz/csc236/handouts/heapsort.html
void siftDown(int arr[], int start, int end) {
    int temp = arr[start];
    for (int i = 2 * start; i <= end; i *= 2) {
        if (arr[i] < arr[i+1] && i < end) i++;
        if (temp > arr[i]) break;
        arr[start] = arr[i];
        start = i;
    } // end for
    arr[start] = temp;
} // end of Heapify

// 递归写法
// 对奇数有 bug
// void Heapify_rec(int arr[], int i, int len) {
//     int left = 2*i, right = 2*i + 1, largest = i, temp;
//     if (left < len && arr[left] > arr[largest]) largest = left;
//     if (right < len && arr[right] > arr[largest]) largest = right;
//     if (largest != i) {
//         temp = arr[i];
//         arr[i] = arr[largest];
//         arr[largest] = temp;
//         Heapify_rec(arr, largest, len);
//     }
// } // end of Heapify

void Heapify(int arr[], int start, int end) {
    siftDown(arr, start, end);
}

// 由一个无序的序列建成一个堆
void BuildHeap(int arr[], int n) {
    for (int i = n / 2; i > 0; i--) Heapify(arr, i, n);
}

// 对 R[1..n] 进行堆排序，用 R[0] 做暂存单元
void Heap_Sort(int R[], int n) { 
    BuildHeap(R, n); // 将 R[1-n] 建成初始堆
    // 对当前无序区 R[1..i] 进行堆排序，共做n-1趟
    for (int i = n; i > 1; i--) { 
        // 将堆顶和堆中最后一个记录交换
        R[0] = R[1];
        R[1] = R[i];
        R[i] = R[0];       
        // 将 R[1..i-1] 重新调整为堆，仅有 R[1] 可能违反堆性质
        Heapify(R, 1, i - 1);
    } // end of for
} // end of Heap_Sort

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

    Heap_Sort(R, n);

    puts("\nThe sequence after Heap Sort is:");
    for (i = 1; i <= n; i++) printf("%4d", R[i]);

    quit();
}