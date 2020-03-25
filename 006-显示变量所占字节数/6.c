/* 输出不同类型所占的字节数 */
#include <stdio.h>

int main() {
    /* sizeof() 是保留字，它的作用是求某类型或某变量类型的字节数，      */
    /* 括号中可以是类型保留字或变量。                                 */
    printf("The bytes of the variables are:\n");

    /* int 型在不同的机器，不同的编译器中的字节数不一样，               */
    /* 一般来说在 TC2.0 编译器中字节数为 2，在 VC 编译器中字节数为 4    */
    printf("int:%d bytes\n", sizeof(int));
    /* char 型的字节数为 1 */
    printf("char:%d byte\n", sizeof(char));
    /* short 型的字节数为 2 */
    printf("short:%d bytes\n", sizeof(short));
    /* long 型的字节数为 4 */
    printf("long:%d bytes\n", sizeof(long));
    /* float 型的字节数为 4 */
    printf("float:%d bytes\n", sizeof(float));
    /* double 型的字节数为 8 */
    printf("double:%d bytes\n", sizeof(double));
    /* long double 型的字节数为 8 或 10 或 12 或 16 */
    printf("long double:%d bytes\n", sizeof(long double));

    getchar();
    return 0;
}