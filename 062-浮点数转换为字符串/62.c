#include <stdio.h>
#include <string.h> // strcat
#include <stdlib.h> // atoi

#define MAX_CHAR_LEN 255
#define ZH_CHAR_LEN 3
typedef enum {
    NOT_SET,
    NORMAL,
    ALL_ZERO_END,
    ZERO_IN_MID,
} Flag;

// 数字金额转换为大写金额子程序
char* zh(char zh_money[], double x) {
    int i = 0, n = 0, nth = 0;
    Flag flag = NOT_SET;
    char je[MAX_CHAR_LEN] = {0}; // 数字金额的字符变量
    char temp[MAX_CHAR_LEN] = {0};
    char f1[10][3] = {
        "零", "壹", "贰", "叁", "肆",
        "伍", "陆", "柒", "捌", "玖"
    }; // 数字对应的大写数组变量
    char f2[11][3] = {
        "亿", "仟", "佰", "拾", "万",
        "仟", "佰", "拾", "元", "角", "分"
    }; // 每位数字对应单位数组变量

    //  i  => 012 3456;
    // 100 => 100_00.0;  n = 7
    // n-i => 765 4321;
    sprintf(je, "%.01f", 100 * x); // 扩大 100 倍后转为字符串
    n = strlen(je);

    zh_money[0] = '\0'; // 初始化为空字符串
    flag = NORMAL;
    for (i = 0; i < n; i++) {
        //      i => 012 3456;
        //    n-i => 765 4321;
        // 100.00 => 100_00.0;  n = 7
        //    nth => 321 01
        nth = n - i - 4;
        strcpy(temp, &je[i]);  // 复制到临时数组
        if (atoi(temp) == 0) { // 判断第i位后是否全为0
            flag = ALL_ZERO_END;
            break;
        }
        if (je[i] != '0') {
            if (flag == ZERO_IN_MID) { // x十/百/千/... [零] x元/角/分/...
                strncat(zh_money, f1[0], ZH_CHAR_LEN);
            }
            strncat(zh_money, f1[je[i] - '0'], ZH_CHAR_LEN); // 数字串转化字符串
            strncat(zh_money, f2[13 - n + i], ZH_CHAR_LEN);
            flag = NORMAL;
        } else {
            // 判断万位位置
            if (
                5 == nth && (
                    je[i - 1] != '0' || 
                    je[i - 2] != '0' || 
                    je[i - 3] != '0'
                )
            ) strcat(zh_money, "万");
            if (1 == nth) strcat(zh_money, "元"); // 判断个位数的元位置
            flag = ZERO_IN_MID;
        }
    }
    if (flag == ALL_ZERO_END) {
        //   i   => 01234 5678;                01234 5678 9012;
        // n - i => 98765 4321;                32109 8765 4321;
        // 10000 => 10000_00.0; 1_0000_0000 => 10000_0000_00.0;
        //   nth => 54321 01  ;                98765 4321 01
        // 万位数字为 0，加‘万’
        if (5 <= nth && nth < 8) strcat(zh_money, "万"); 
        if (1 <= nth) strcat(zh_money, "元");
        strcat(zh_money, "正"); // 最后不是分位，加“正”
    }
    return zh_money; // 返回大写金额
}

int main() {
    double count = 0.0;
    char zh_money[MAX_CHAR_LEN] = {0}; // 大写金额字符变量
    //clrscr();
    printf("*********************************************************\n");
    printf("*                                                       *\n");
    printf("*           数字金额转换为大写金额程序 Ver.1.0          *\n");
    printf("*                                                       *\n");
    printf("*                                By RZLIN               *\n");
    printf("*                                                       *\n");
    printf("*               请输入要转换的金额：                    *\n");
    printf("*                     ");
    scanf("%lf", &count);
    printf("*           您输入的金额为：%10.2lf 。               *\n", count);
    printf("*                                                       *\n");
    printf("* 转换为大写金额是：%s\n", zh(zh_money, count));
    printf("*                                                       *\n");
    puts("*                请按任意键退出...                      *");
    printf("*********************************************************\n");
    getchar();
    return 0;
}