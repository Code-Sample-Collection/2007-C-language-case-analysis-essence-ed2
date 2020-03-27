// 032 结构体输入输出
#include <stdio.h>  // puts
#include <string.h> // strlen
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define ZIPLEN 10
#define PHONLEN 15

// struct addr类型定义
struct addr {
    char *name;          // 姓名
    char *address;       // 地址
    char zip[ZIPLEN];    // 邮政编码
    char phone[PHONLEN]; // 电话号码
};

int readaddr(struct addr *dpt);
int writeaddr(struct addr *dpt);


int main() {
    struct addr p[100];
    int i, j;

    clrscr();
    for (i = 0; readaddr(p + i); i++) ;
    for (j = 0; j < i; j++) writeaddr(p + j);

    quit();
}

// 用于输入一个通信录函数
int readaddr(struct addr *dpt) {
    int len;
    char buf[120]; // 输入字符串的缓冲区

    printf("\nPlease input the Name: "); // 输入姓名
    if (scanf("%s", buf) == 1) {
        len = strlen(buf);
        dpt->name = (char *)malloc(len + 1); // 申请存储姓名的空间
        strcpy(dpt->name, buf);
    } else {
        return 0; // Ctrl+Z结束输入
    }

    printf("Please input the Address: "); // 输入地址
    if (scanf("%s", buf) == 1)
    {
        len = strlen(buf);
        dpt->address = (char *)malloc(len + 1);
        strcpy(dpt->address, buf);
    }
    else
    {
        free(dpt->name); // 释放存储姓名的空间
        return 0;
    }

    printf("Please input the Zip code: "); // 输入邮编
    if (scanf("%s", buf) == 1) {
        strncpy(dpt->zip, buf, ZIPLEN - 1);
    } else {
        free(dpt->name);
        free(dpt->address);
        return 0;
    }

    printf("Please input the Phone number: "); // 输入电话号码
    if (scanf("%s", buf) == 1) {
        strncpy(dpt->phone, buf, PHONLEN - 1);
    } else {
        free(dpt->name);
        free(dpt->address);
        return 0;
    }

    return 1;
}

// 用于输出通讯录
int writeaddr(struct addr *dpt) {
    printf("Name    : %s\n", dpt->name);    // 输出姓名
    printf("Address : %s\n", dpt->address); // 输出地址
    printf("Zip     : %s\n", dpt->zip);     // 输出邮编
    printf("Phone   : %s\n\n", dpt->phone); // 输出电话号码
}
