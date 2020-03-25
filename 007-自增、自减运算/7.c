/* 自增/自减运算 */
#include <stdio.h>

int main() {
    int a=5, b, c, i=10;
    printf("a = %d, ", a);
    b = a++; printf("b = a++ = %d, ", b);
    c = ++b; printf("c = ++b = %d\n", c);
    printf("a = %d, b = %d, c = %d\n\n", a, b, c);

    printf("i,i++,i++ = %d,%d,%d", i, i++, i++); printf(",\ti = %d\n", i);
    printf(" ++i = %d",  ++i); printf(",\ti = %d\n", i);
    printf(" --i = %d",  --i); printf(",\ti = %d\n", i);
    printf(" i++ = %d",  i++); printf(",\ti = %d\n", i);
    printf(" i-- = %d",  i--); printf(",\ti = %d\n", i);
    printf("-i++ = %d", -i++); printf(",\ti = %d\n", i);
    printf("-i-- = %d", -i--); printf(",\ti = %d\n", i);

    // getchar();
    return 0;
}