// 037 停机文件字符数
#include <stdio.h>  // puts, fgetc
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

int main() {
    char fname[80]; // 存储文件名
    FILE *rfp;
    long count = 0; // 文件字符计数器

    clrscr();
    printf("Please input the file's name: ");
    scanf("%s", fname);
    if ((rfp = fopen(fname, "r")) == NULL) {
        printf("Can't open file %s.\n", fname);
        exit(1);
    }
    while (fgetc(rfp) != EOF) count++;
    fclose(rfp); // 关闭文件

    printf("There are %ld characters in file '%s'.\n", count, fname);
    quit();
}
