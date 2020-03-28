// 049 基数排序
#include <stdio.h>
#include <string.h> // strlen
#include <stdlib.h> // atoi
// #define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"
#define MAX 5

typedef struct node {
    int k;
    struct node *next;
} * lnode;


lnode my_input(int *d) {
    lnode head = NULL, temp, terminal = NULL;
    char s[MAX + 1] = {0};
    *d = 0;

    printf("Input the records ('e' to end input): ");
    scanf("%s", s);
    while (s[0] != 'e') {
        temp = (lnode)malloc(sizeof(struct node));
        if (strlen(s) > *d)
            *d = strlen(s);
        temp->k = atoi(s);
        if (head == NULL) {
            head = temp;
            terminal = temp;
        } else {
            terminal->next = temp;
            terminal = temp;
        }
        scanf("%s", s);
    } // while (s[0] != 'e')
    terminal->next = NULL;

    return head;
}

void my_output(lnode h) {
    lnode t = h;
    while (h != NULL) {
        printf("%3d", h->k);
        h = h->next;
    }
    puts("");
    h = t;
}

lnode Radix_Sort(lnode head, int d) {
    lnode p, q, h, t;
    int i, j, x, radix = 1;

    h = (lnode)malloc(10 * sizeof(struct node));
    t = (lnode)malloc(10 * sizeof(struct node));
    for (i = d; i >= 1; i--) {
        for (j = 0; j <= 9; j++) {
            h[j].next = NULL;
            t[j].next = NULL;
        }
        p = head;
        while (p != NULL) {
            x = ((p->k) / radix) % 10;
            if (h[x].next == NULL) {
                h[x].next = p;
                t[x].next = p;
            } else {
                q = t[x].next;
                q->next = p;
                t[x].next = p;
            }
            p = p->next;
        }

        j = 0;
        while (h[j].next == NULL) j++;
        head = h[j].next;
        q = t[j].next;
        for (x = j + 1; x <= 9; x++) {
            if (h[x].next != NULL) {
                q->next = h[x].next;
                q = t[x].next;
            }
        }
        q->next = NULL;
        radix *= 10;
    }
    return head;
}

void my_free(lnode h) {
    lnode temp = h;
    while (temp) {
        h = temp->next;
        free(temp);
        temp = h;
    }
}

int main() {
    lnode h;
    int len;

    clrscr();
    h = my_input(&len);
    puts("The sequence you input is:");
    my_output(h);
    h = Radix_Sort(h, len);
    puts("The sequence after Radix Sort is:");
    my_output(h);
    my_free(h);

    quit();
}
