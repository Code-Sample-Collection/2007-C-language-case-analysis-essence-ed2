// 054
#include <stdio.h>
#include <string.h> // strcpy
#define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define N 10

struct node {
    char name[20];
    struct node *link;
};
typedef struct node  Stud;
typedef struct node* StudPtr;


StudPtr creat() {
    StudPtr p, h = NULL, s;
    int i, n;

    printf("Please input the number of linklist: ");
    scanf("%d", &n);
    if (n <= 0) {
        puts("number n should > 0!");
        return h;
    }
    if ((h = (StudPtr )malloc(sizeof(Stud))) == NULL) {
        puts("cannot find space!");
        exit(0);
    }
    h->name[0] = '\0';
    h->link = NULL;
    p = h;
    for (i = 0; i < n; i++) {
        if ((s = (StudPtr )malloc(sizeof(Stud))) == NULL) {
            puts("cannot find space!");
            exit(0);
        }
        p->link = s;
        printf("please input %d student's name: ", i + 1);
        scanf("%s", s->name);
        s->link = NULL;
        p = s;
    }

    return (h);
}

StudPtr search(StudPtr h, char *x) {
    StudPtr p;
    char *y;

    p = h->link;
    while (p != NULL)
    {
        y = p->name;
        if (strcmp(y, x) == 0)
            return (p);
        else
            p = p->link;
    }
    if (p == NULL) puts("data not find!");
    return 0;
}

StudPtr search2(StudPtr h, char *x) {
    StudPtr p, s;
    char *y;

    p = h->link;
    s = h;
    while (p != NULL) {
        y = p->name;
        if (strcmp(y, x) == 0) {
            return (s);
        } else {
            p = p->link;
            s = s->link;
        }
    }
    if (p == NULL) puts("data not find!");
    return 0;
}

void insert(StudPtr p) {
    char stuname[20];
    StudPtr s;

    if ((s = (StudPtr )malloc(sizeof(Stud))) == NULL) {
        puts("cannot find space!");
        exit(0);
    }
    printf("please input the student's name: ");
    scanf("%s", stuname);
    strcpy(s->name, stuname);
    s->link = p->link;
    p->link = s;
}

void del(StudPtr x, StudPtr y) {
    StudPtr s;

    s = y;
    x->link = y->link;
    free(s);
}

void print(StudPtr h) {
    StudPtr p;
    if (NULL==h) {
        puts("No list exist! Create one first.");
        return;
    } else {
        p = h->link;
    }
    printf("Now the link list is:\n");
    while (p != NULL) {
        printf("%s ", &*(p->name));
        p = p->link;
    }
    printf("\n");
}

void menu() {
    clrscr();
    printf("       simple linklise realization of c\n");
    printf("    ||=====================================||\n");
    printf("    ||                                     ||\n");
    printf("    || [1]  create linklist                ||\n");
    printf("    || [2]  seach                          ||\n");
    printf("    || [3]  insert                         ||\n");
    printf("    || [4]  delete                         ||\n");
    printf("    || [5]  print                          ||\n");
    printf("    || [6]  exit                           ||\n");
    printf("    ||                                     ||\n");
    printf("    || if no list exist,create first       ||\n");
    printf("    ||                                     ||\n");
    printf("    ||=====================================||\n");
    printf("      Please input your choose(1-6): ");
}

int main() {
    int choose;
    StudPtr head = NULL, searchpoint, forepoint;
    char fullname[20];

    while (1) {
        menu();
        scanf("%d", &choose);
        clrscr();
        switch (choose) {
            case 1:
                head = creat();
                printf("Linklist created ");
                if (head) {
                    puts("successfully!");
                } else {
                    puts(" failed!");
                }
                break;
            case 2:
                printf("Input the student's name which you want to find: ");
                scanf("%s", fullname);
                searchpoint = search(head, fullname);
                printf("The stud name you want to find is: %s\n", *&searchpoint->name);
                break;
            case 3:
                insert(head);
                print(head);
                break;
            case 4:
                print(head);
                printf("Input the student's name which you want to delete: ");
                scanf("%s", fullname);
                searchpoint = search(head, fullname);
                forepoint = search2(head, fullname);
                del(forepoint, searchpoint);
                print(head);
                puts("Delete successfully!");
                break;
            case 5:
                print(head);
                break;
            case 6:
                puts("\nThank you for your using!");
                quit();
                break;
            default:
                puts("Illegal letter!");
        } // end switch (choose)
        puts("\n\t[Press any key to return...]");
        _getch();
    } // end while (1)
    return 0;
}
