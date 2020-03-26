// 放一些辅助函数
/* 头文件引入 */
#pragma once
#ifndef _INC_INC_H
#define _INC_INC_H

#ifndef _INC_STDLIB
#include <stdlib.h> // system, exit
#endif // end #ifndef _INC_STDLIB

#ifdef CLS_AND_GETCH
#ifndef _INC_CONIO
#include <conio.h> // _getch
#endif
#endif // end #ifdef CLS_AND_GETCH


/* 辅助函数定义 */

// 清屏
void clrscr() {
#ifdef CLS_AND_GETCH
    system("cls");
#endif // end #ifdef CLS_AND_GETCH
} // void clrscr()

// 提示按键并正常退出
void quit() {
#ifdef CLS_AND_GETCH
    printf("\n\nPress any key to quit...\n");
    _getch();
#endif // end #ifdef CLS_AND_GETCH
    exit(0);
} // void quit()

#endif // end #ifndef _INC_INC_H