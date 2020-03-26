// 026 阿拉伯数字转罗马数字
#include <stdio.h> // puts
#include <stdlib.h> // exit, atoi
#include <string.h> // strcat
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define ROWS 4
#define COLS 4

void checknum(int val);
void to_roman(int decimal, char roman[]);

int nums[ROWS][COLS] = {
    {1000, 1000, 1000, 1000},
    {900,  500,  400,  100},
    {90,   50,   40,   10},
    {9,    5,    4,    1},
};
char *roms[ROWS][COLS] = {
    { "m", "m",  "m", "m"},
    {"cm", "d", "cd", "c"},
    {"xc", "l", "xl", "x"},
    {"ix", "v", "iv", "i"},
};


int main(int argc, char *argv[]) {
    int low, high;
    char roman[25];

    // 参数检验
    if (argc <= 1) { // 运行程序需带整数参数
        puts("Usage:");
        puts("    roman [dec_num_low=1] dec_num_high");
        exit(0);
    } else if (argc == 2) {
        // 带一个参数
        low = 1;
        high = atoi(argv[1]); // 将第一个参数转换成整数
        checknum(high);
    } else { // argc > 2
        // 带两个及以上参数
        (argc > 3) && puts("[Warning] Too many args!");
        low = atoi(argv[1]);
        high = atoi(argv[2]);
        checknum(low);
        checknum(high);
        if (low > high) {
            low = high;
            high = atoi(argv[1]);
        }
    }

    for ( ; low <= high; low++) {
        to_roman(low, roman);
        printf("%d\t%s\n", low, roman);
    }

    quit();
}

// 检查参数合理性
void checknum(int val) {
    if (val < 1 || val > 9999) {
        puts("The number must be in range 1..9999.");
        exit(-1);
    }
}

// 将整数转换成罗马数字表示
void to_roman(int decimal, char roman[]) {
    roman[0] = '\0';

    for (int power = 0; power < ROWS; power++) {
        for (int index = 0; index < COLS; index++) {
            while (decimal >= nums[power][index]) {
                strcat(roman, roms[power][index]);
                decimal -= nums[power][index];
            }
        }
    }
}
