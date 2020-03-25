#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }
void quit() { printf("\n\nPress any key to quit...\n"); _getch(); exit(0); }


long int f(int year, int month) { return (month < 3) ? (year - 1) : year; }
long int g(int month) { return (month < 3) ? (month + 13) : (month + 1); }
long int n(int year, int month, int day) {
    return 1461L * f(year, month) / 4 + 153L * g(month) / 5 + day;
}
int w(int year, int month, int day) { // 返回星期数；从周日(0)开始
    return (int)((n(year, month, day) % 7 - 621049L % 7 + 7) % 7);
}

int main() {
    int sw, leap, i, j, k, wd, day;
    int year; /* 年 */
    char title[] = "SUN MON TUE WED THU FRI SAT";
    int date[12][6][7];
    int day_tbl[][12] = {
        {31,28,31, 30,31,30, 31,31,30, 31,30,31},
        {31,29,31, 30,31,30, 31,31,30, 31,30,31},
    };

    clrscr();
    /* 输入年 */
    printf("Please input the year whose calendar you want to know: "); 
    scanf("%d%*c", &year); /* 输入年份值和掠过值后的回车 */
    sw = w(year, 1, 1);
    leap = year % 4 == 0 && year % 100 || year % 400 == 0; /* 判闰年 */

    /* 日期表置 0 */
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 7; k++) {
                date[i][j][k] = 0;
            }
        }
    }

    for (i = 0; i < 12; i++) {
        /* 一年十二个月 */
        for (wd = 0, day = 1; day <= day_tbl[leap][i]; day++) {
            /* 将第 i+1 月的日期填入日期表 */
            date[i][wd][sw] = day;
            /* 每星期七天，以0至6计数 */
            sw = ++sw % 7;
            if (sw == 0) {
                /* 日期表每七天一行，星期天开始新的一行 */
                wd++;
            }
        }
    }

    printf("\n|==================The Calendar of Year %d =====================|\n|", year);
    for (i = 0; i < 6; i++) {
        /* 先测算第i+1月和第i+7月的最大星期数 */
        for (wd = 0, k = 0; k < 7; k++) {
            /* 日期表的第六行有日期，则 wd!=0 */
            wd += date[i][5][k] + date[i + 6][5][k];
        }
        wd = wd ? 6 : 5;
        printf("%2d  %s  %2d  %s |\n|", i + 1, title, i + 7, title);
    
        for (j = 0; j < wd; j++) {
            printf("   "); /* 输出四个空白符 */
            /* 左栏为第 i+1 月，右栏为第 i+7 月*/
            for (k = 0; k < 7; k++) {
                if (date[i][j][k]) {
                    printf("%4d", date[i][j][k]);
                } else {
                    printf("    ");
                }
            }
            printf("     "); /* 输出十个空白符 */
            for (k = 0; k < 7; k++) {
                if (date[i + 6][j][k]) {
                    printf("%4d", date[i + 6][j][k]);
                } else {
                    printf("    ");
                }
            }
            printf(" |\n|");
        } // for (j = 0; j < wd; j++)
        // scanf("%*c"); /*键入回车输出下一个月的日历 */
    } // for (i = 0; i < 6; i++)
    puts("=================================================================|");

    quit();
}