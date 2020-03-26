// 029 字符排版函数。将字符行内单词之间的空白字符平均分配插入到单词之间
#include <stdio.h> // puts
#include <string.h> // strcpy
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

#define MAX_LEN 80

void edit(char *s) {
    int i, spaces_num, words_num, state, avg_sp, rem_sp;
    char buf[MAX_LEN], *str;

    for (state = spaces_num = words_num = i = 0; s[i]; i++) {
        if (s[i] == ' ') { 
            // 统计空白个数
            spaces_num++;
            state = 0; // 置 空白符状态
        } else if (!state) {
            words_num++;     // 统计单词个数
            state = 1; // 置 单词状态
        }
    }

    if (words_num <= 1) return; // 单词数不超过 1, 不排版

    avg_sp = spaces_num / (words_num - 1); // 每个间隔平均空白符
    rem_sp = spaces_num % (words_num - 1); // 多余的空白符

    strcpy(buf, s);
    for (str = buf; ; ) {
        // 掠过空白符
        while (*str == ' ') str++; 

        for (; *str && *str != ' ';) *s++ = *str++; // 复制单词
        if (--words_num == 0) return; // 全部单词复制完毕，返回

        //插入间隔空白符
        for (i = 0; i < avg_sp; i++) *s++ = ' ';
        if (rem_sp) { // 处理多余的空白符
            *s++ = ' '; // 插入一个多余空白符
            rem_sp--;
        }
    } // for (str = buf; ; )
} // void edit(char *s)

int main() {
    char buff[MAX_LEN];

    clrscr();
    puts("This is a typeset program!");
    puts("Please input a character line:");
    gets(buff);
    edit(buff);
    printf("\nThe character line after typeset is:\n%s\n", buff);

    quit();
}
// This is a typeset program!
// Please input a character line:
// warning: incompatible implicit declaration of built-in function                 'strcpy'

// The character line after typeset is:
// warning:    incompatible    implicit   declaration   of   built-in   function   'strcpy'