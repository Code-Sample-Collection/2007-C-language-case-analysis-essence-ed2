
#define ListSize 100 // 假定表空间大小为 100
#include <stdio.h>
#include <stdlib.h>

struct Seqlist {
    int data[ListSize]; // 向量 data 用于存放表结点
    int length;         // 当前的表长度
}; // 以上为定义表结构
typedef struct Seqlist  SeqList;
typedef struct Seqlist* SeqListPtr;


void Error(char *message) {
    printf("错误: %s\n", message);
    exit(1);
}

// 将新结点 x 插入 L 所指的顺序表的第 i 个结点 ai 的位置上
void InsertList(SeqListPtr L, int x, int i) {
    int j;
    if (i < 0 || i > L->length)
        Error("position error"); // 非法位置，退出
    if (L->length >= ListSize)
        Error("overflow");
    for (j = L->length - 1; j >= i; j--)
        L->data[j + 1] = L->data[j];
    L->data[i] = x;
    L->length++;
}

// 从 L 所指的顺序表中删除第 i 个结点 ai
void DeleteList(SeqListPtr L, int i) {
    int j;

    if (i < 0 || i > L->length - 1)
        Error(" position error");
    for (j = i + 1; j < L->length; j++)
        L->data[j - 1] = L->data[j]; // 结点前移
    L->length--;                     // 表长减小
}

void Initlist(SeqListPtr L) {
    L->length = 0;
}

int main() {
    SeqListPtr SEQA;
    int i;

    SEQA = (SeqListPtr)malloc(sizeof(SeqList));
    puts("Original List:");
    Initlist(SEQA);
    for (i = 0; i < ListSize; i++) {
        InsertList(SEQA, i, i);
        printf("%3d", SEQA->data[i]);
    }

    puts("\nDeleteList 99");
    DeleteList(SEQA, 99);
    for (i = 0; i < ListSize - 1; i++) {
        printf("%3d", SEQA->data[i]);
    }
    return 0;
}
