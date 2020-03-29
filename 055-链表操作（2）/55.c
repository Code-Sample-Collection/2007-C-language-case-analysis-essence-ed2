// 055
#ifndef SQLIST_H
#define SQLIST_H

#define List_INIT_SIZE 100 // 线性表的存储空间初始大小
#define LIST_INCREMENT 10  // 分配增量
#define OK 0
#define ERROR -1
#define OVERFLOW -2
#include <stdio.h>
#include <string.h> // memmove
#define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"

typedef int  ElemType;
typedef int* ElemTypePtr;
typedef struct {
    ElemTypePtr elem; // 存储空间基址
    int length; // 当前长度
    int size;   // 当前存储容量 (sizeof(ElemType)为单位)
} SqList;
typedef SqList* SqListPtr;

int InitList(SqListPtr L) {
    //构建一个线性表L
    L->elem = (ElemTypePtr)malloc(List_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) {
        puts("malloc failed");
        exit(OVERFLOW);
    }
    L->length = 0;
    L->size = List_INIT_SIZE;
    return OK;
} //InitList

void DestoryList(SqListPtr L) {
    if (!L->elem) {
        free(L->elem);
        L->elem = NULL;
    }
    L->length = 0;
    L->size = 0;
} //DestoryList

void ClearList(SqListPtr L) {
    L->elem = NULL;
    L->length = 0;
    L->size = List_INIT_SIZE;
} //ClearList

int ListEmpty(SqListPtr L) {
    return L->length > 0;
} //ListEmpty

int ListLength(SqListPtr L) {
    return L->length;
} //ListLength

int ListInsert(SqListPtr L, int i, ElemType e) {
    ElemTypePtr NewBase; //新的基址
    ElemTypePtr p;
    ElemTypePtr temp;

    // 需满足条件  1 < i < ListLength(L)+1
    if (i < 1 || i > ListLength(L) + 1) return ERROR;
    if (L->length > L->size) { //空间已满
        NewBase = (ElemTypePtr)malloc((L->size + LIST_INCREMENT) * sizeof(ElemType)); //申请新的空间
        if (!NewBase) {
            puts("malloc failed");
            exit(OVERFLOW);
        } else {
            // 复制旧的内容
            memmove(NewBase, L->elem, (L->size * sizeof(ElemType)));
            free(L->elem);
            L->elem = NewBase;
            L->size += LIST_INCREMENT;
            NewBase = NULL;
        }
    }

    p = &(L->elem[i - 1]); //取得 i 的位置，即插入位置
    for (temp = &(L->elem[L->length - 1]); temp > p; --temp) {
        // 将插入点后的所有元素向后移动一位
        *(temp + 1) = *temp;
    }
    *p = e; // 插入新值 e
    (L->length)++;
    return OK;
} //ListInsert

int ListDelete(SqListPtr L, int i, ElemTypePtr e) {
    ElemTypePtr p;
    ElemTypePtr pos;

    if (i < 0 || i > ListLength(L)) {
        return ERROR;
    }
    p = &(L->elem[i - 1]);
    *e = *p;

    pos = &( L->elem[L->length - 1] );
    for (++p; p <= pos; ++p) {
        *(p - 1) = *p;
    }
    (L->length)--;
    return OK;
}
#endif // SQLIST_H


int main() {
    SqListPtr list;
    ElemType e = -1;
    
    InitList(list);
    ListInsert(list, 1, 1);
    ListInsert(list, 2, 2);
    ListInsert(list, 3, 3);
    ListInsert(list, 4, 4);
    ListInsert(list, 5, 5);
    for (int i = 0; i < list->length; i++) {
        printf("%d\n", list->elem[i]);
    }

    ListDelete(list, 2, &e);
    printf("Delete list [2] = %d\n", e);
    for (int i = 0; i < list->length; i++) {
        printf("%d\n", list->elem[i]);
    }
    printf("%d\n", list->length);
    DestoryList(list);

    return 0;
}
