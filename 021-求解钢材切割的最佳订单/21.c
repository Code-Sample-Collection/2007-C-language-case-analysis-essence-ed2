// 021 钢材切割
/*
    1. 描述：编写程序，从订单中选择一组订单对钢材作切割加工，使钢材得到最佳利用。
        约定每一次切割会损耗固定长度的钢材（约定该值为 `DELTA=2`）。
    2. 输入
        + 钢材总长度 `total`
        + 订单数 `n`
        + 各定单需要的钢材长度 `orderlen[i]`
    3. 输出
        + 可以使钢材得到最佳利用的订单号
        + 该订单需要的钢材长度
    4. 测试样例
        + 12, 3, {5, 6, 9} => order 3 length = 9
        + 28, 8, {5,6,7,8,9, 10, 12, 15}
            => (1,5)+(3,7)+(7,12)
            => (2,6)+(4,8)+(6,10)

    NOTE: 程序未通过第二个测试样例，有 bug
*/
#include <stdio.h>
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define N 20
#define DELTA 2

void try(int n, int total, int bestlen);

int bestsele[N];
int sele[N];
int orderlen[N];

int main() {
    //               最佳解用料的初值
    int i, n, total, bestlen = 0;

    clrscr();
    printf("\n Please enter total length of the steel:\n"); // 输入钢材总长
    scanf("%d", &total);
    printf("\n Please enter number of order:\n"); // 输入定单数
    scanf("%d", &n);
    printf("\n Please enter the orders:\n"); // 输入各定单
    for (i = 0; i < n; i++) {
        scanf("%d", &orderlen[i]); // 读入订单
        sele[i] = bestsele[i] = 0; // 置当前选择和最佳选择初值
    }

    // 调用函数求解
    try(n, total, bestlen);

    // 输出结果
    for (i = 0; i < n; i++) {
        if (bestsele[i]) {
            printf("order %d length = %d\n", i + 1, orderlen[i]);
        }
    }

    quit();
}

void try(int n, int total, int bestlen) {
    int i, len;
    for (len = i = 0; i < n; i++) {
        /* 求当前选中的用料量 */
        if (sele[i]) {
            len += orderlen[i] + DELTA;
        }
    }

    if (len - DELTA <= total) {
        /* 注意最后一段可能不需要切割 */
        if (bestlen < len) {
            /* 找到一个更好的解 */
            bestlen = len;
            for (i = 0; i < n; i++) {
                bestsele[i] = sele[i];
            }
        }

        for (i = 0; i < n; i++) {
            /* 对所有未选定单逐一作选中尝试循环 */
            if (!sele[i]) {
                sele[i] = 1;    /* 做选中尝试*/
                try(n, total, bestlen);
                sele[i] = 0;
            }
        }
    } // enf if (len - DELTA <= total)
} // end void try(int n, int total, int bestlen)