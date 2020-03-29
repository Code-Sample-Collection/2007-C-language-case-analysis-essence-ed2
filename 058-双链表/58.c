#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strcmp
#define N 10
struct node {
    char name[20];
    struct node *llink, *rlink;
}; // 双链表的结构定义
typedef struct node  DLink;
typedef struct node* DLinkPtr;


// 双链表的创建
DLinkPtr creat(int n) {
    DLinkPtr p, h, s;
    int i;

    if ((h = (DLinkPtr)malloc(sizeof(DLink))) == NULL) {
        printf("cannot find space!\n");
        exit(0);
    }
    h->name[0] = '\0';
    h->llink = NULL;
    h->rlink = NULL;
    p = h;
    for (i = 0; i < n; i++) {
        if ((s = (DLinkPtr)malloc(sizeof(DLink))) == NULL) {
            printf("cannot find space!\n");
            exit(0);
        }
        p->rlink = s;
        printf("Please input the %d man's name: ", i + 1);
        scanf("%s", s->name);
        s->llink = p;
        s->rlink = NULL;
        p = s;
    }
    h->llink = s;
    p->rlink = h;
    return (h);
}

// 查找
DLinkPtr search(DLinkPtr h, char *x) {
    DLinkPtr p;
    char *y;
    p = h->rlink;
    while (p != h)
    {
        y = p->name;
        if (strcmp(y, x) == 0)
            return (p);
        else
            p = p->rlink;
    }
    printf("cannot find data!\n");
}

// 打印输出
void print(DLinkPtr h) {
    DLinkPtr p;

    p = h->rlink;
    printf("\nNow the double list is:\n");
    while (p != h) {
        printf("%s ", &*(p->name));
        p = p->rlink;
    }
    printf("\n");
}

// 删除
void del(DLinkPtr p) {
    (p->rlink)->llink = p->llink;
    (p->llink)->rlink = p->rlink;
    free(p);
}


int main() {
    int number;
    char studname[20];
    DLinkPtr head, searchpoint;

    number = N;
    printf("Please input the size of the list: ");
    scanf("%d", &number);
    head = creat(number);
    print(head);
    printf("Please input the name which you want to find: ");
    scanf("%s", studname);
    searchpoint = search(head, studname);
    printf("the name you want to find is: %s\n", *&searchpoint->name);
    del(searchpoint);
    print(head);
    return 0;
}
