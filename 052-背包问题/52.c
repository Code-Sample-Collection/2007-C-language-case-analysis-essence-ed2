// 052
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 100

struct Bag {
    int weight;
    int value;
} Bag[MAX];


int comb(int arr[], int Weight, int m, int k) {
    int i, j;
    int wei, val;
    int Value = 0;
    
    for (i = m; i >= k; i--) {
        arr[k] = i;
        if (k > 1) {
            comb(arr, Weight, i - 1, k - 1);
        } else {
            wei = 0; // 预值 0
            val = 0;
            for (j = arr[0]; j > 0; j--) {
                // 每一种组合求它们的重量和价值
                wei = wei + Bag[arr[j]].weight;
                val = val + Bag[arr[j]].value;
            }
            if (wei <= Weight && val > Value) // 判断是否满足条件进行附值
                Value = val;
        }
    }
    return Value;
}

int main() {
    int num, subnum, Weight, arr[MAX];

    clrscr();
    printf("输入背包的总个数: ");
    scanf("%d", &num);
    printf("输入背包的重量和价值: Weight, Value\n", num);
    for (int l = 1; l <= num; l++) {
        scanf("%d,%d", &Bag[l].weight, &Bag[l].value);
    }
    printf("输入满足要求背包的个数:\n");
    scanf("%d", &subnum);
    printf("输入满足条件的重量:\n", subnum);
    scanf("%d", &Weight);
    arr[0] = subnum;
    printf("the max value is:%d", comb(arr, Weight, num, subnum));
    quit();
}