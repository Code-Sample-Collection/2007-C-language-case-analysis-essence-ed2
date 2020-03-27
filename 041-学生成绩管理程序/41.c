// 041 学生成绩管理程序
/*
    学生成绩已以一个学生一个记录的形式存储在文件中，

    每位学生记录包含的信息有：
        + 姓名
        + 学号
        + 各门功课的成绩

    程序具有以下几项功能：
        + 求出各门课程的总分、平均分
        + 按姓名、按学号寻找其记录并显示
        + 浏览全部学生成绩
        + 按总分由高到低显示学生信息
*/
#define SWN 3       // 课程数
#define NAMELEN 20  // 姓名最大字符数
#define CODELEN 10  // 学号最大字符数
#define FNAMELEN 80 // 文件名最大字符数
#define BUFLEN 80   // 缓冲区最大字符数

#include <stdio.h> // puts
#include <string.h> // strncpy
#include <stdlib.h> // malloc, free
#define CLS_AND_GETCH // 需要清屏+按键退出就取消此行的注释
#include "../000-inc/inc.h"


// 课程名称表
char schoolwork[SWN][NAMELEN + 1] = {
    "Chinese", "Mathematic", "English"
};
struct record {
    char name[NAMELEN + 1]; // 姓名
    char code[CODELEN + 1]; // 学号
    int marks[SWN];         // 各课程成绩
    int total;              // 总分
} stu;

struct node {
    char name[NAMELEN + 1]; // 姓名
    char code[CODELEN + 1]; // 学号
    int marks[SWN];         // 各课程成绩
    int total;              // 总分
    struct node *next;      // 后续表元指针
} * head;                   // 链表首指针


// 从指定文件读入一个记录
int readrecord(FILE *fp, struct record *rpt) {
    char buf[BUFLEN];
    int i;

    if (fscanf(fp, "%s", buf) != 1) return 0; // 文件结束
    strncpy(rpt->name, buf, NAMELEN);
    fscanf(fp, "%s", buf);
    strncpy(rpt->code, buf, CODELEN);
    for (i = 0; i < SWN; i++) {
        fscanf(fp, "%d", &rpt->marks[i]);
    }
    for (rpt->total = 0, i = 0; i < SWN; i++) {
        rpt->total += rpt->marks[i];
    }
    return 1;
}

// 对指定文件写入一个记录
void writerecord(FILE *fpt, struct record *rpt) {
    fprintf(fpt, "%s\n", rpt->name);
    fprintf(fpt, "%s\n", rpt->code);
    for (int i = 0; i < SWN; i++) {
        fprintf(fpt, "%d\n", rpt->marks[i]);
    }
}

// 显示学生记录
void displaystu(struct record *rpt) {
    printf("Name : %s\n", rpt->name);
    printf("Code : %s\n", rpt->code);
    printf("Marks:\n");
    for (int i = 0; i < SWN; i++)
        printf("  %-10s: %3d\n", schoolwork[i], rpt->marks[i]);
    printf("Total: %3d\n", rpt->total);
}

// 计算各单科总分
int totalmark(char *fname, int total[]) {
    FILE *fp;
    struct record s;
    int count, i;

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Can't open file %s.\n", fname);
        return 0;
    }

    for (i = 0; i < SWN; i++)
        total[i] = 0;
    count = 0;
    while (readrecord(fp, &s) != 0) {
        for (i = 0; i < SWN; i++)
            total[i] += s.marks[i];
        count++;
    }
    fclose(fp);
    return count; // 返回记录数
}

// 列表显示学生信息
void liststu(char *fname) {
    FILE *fp;
    struct record s;

    if ((fp = fopen(fname, "r")) == NULL)     {
        printf("Can't open file %s.\n", fname);
        return;
    }
    while (readrecord(fp, &s) != 0) {
        displaystu(&s);
        printf("\n\tPress ENTER to continue...\n");
        while (getchar() != '\n') ;
    }
    fclose(fp);
    return;
}

// 构造链表
struct node *makelist(char *fname) {
    FILE *fp;
    struct record s;
    struct node *p, *u, *v, *h;
    int i;

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Can't open file %s.\n", fname);
        return NULL;
    }

    h = NULL;
    p = (struct node *)malloc(sizeof(struct node));
    while (readrecord(fp, (struct record *)p) != 0) {
        v = h;
        while (v && p->total <= v->total)
        {
            u = v;
            v = v->next;
        }
        if (v == h)
            h = p;
        else
            u->next = p;
        p->next = v;
        p = (struct node *)malloc(sizeof(struct node));
    }

    free(p);
    fclose(fp);
    return h;
}

// 顺序显示链表各表元
void displaylist(struct node *h) {
    while (h != NULL) {
        displaystu((struct record *)h);
        printf("\n\tPress ENTER to continue...\n");
        while (getchar() != '\n') ;

        h = h->next;
    }
}
// 按学生姓名查找学生记录
int retrievebyn(char *fname, char *key) {
    FILE *fp;
    int c;
    struct record s;

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Can't open file %s.\n", fname);
        return 0;
    }

    c = 0;
    while (readrecord(fp, &s) != 0) {
        if (strcmp(s.name, key) == 0) {
            displaystu(&s);
            c++;
        }
    }
    fclose(fp);
    if (c == 0)
        printf("The student %s is not in the file %s.\n", key, fname);
    return 1;
}

// 按学生学号查找学生记录
int retrievebyc(char *fname, char *key) {
    FILE *fp;
    int c;
    struct record s;

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Can't open file %s.\n", fname);
        return 0;
    }
    c = 0;
    while (readrecord(fp, &s) != 0) {
        if (strcmp(s.code, key) == 0) {
            displaystu(&s);
            c++;
            break;
        }
    }
    fclose(fp);
    if (c == 0)
        printf("The student %s is not in the file %s.\n", key, fname);
    return 1;
}

void print_help() {
    puts("m : mean of the marks.");
    puts("t : total of the marks.");
    puts("n : search record by student's name.");
    puts("c : search record by student's code.");
    puts("l : list all the records.");
    puts("s : sort and list the records by the total.");
    puts("q : quit!");
    puts("h : help!");
}



int main() {
    int i, j, n,
        total[SWN]; // 各课程总分
    char c,
         buf[BUFLEN],
         stuf[FNAMELEN]; // 文件名
    FILE *fp;
    struct record s;

    clrscr();
    printf("Please input the students marks record file's name: ");
    scanf("%s", stuf); getchar(); // eat \n
    if ((fp = fopen(stuf, "r")) == NULL) {
        printf("The file %s doesn't exit, do you want to creat it? (Y/N) ", stuf);
        c = getchar();
        if (c == 'Y' || c == 'y') {
            fp = fopen(stuf, "w");
            printf("Please input the record number you want to write to the file: ");
            scanf("%d", &n);
            for (i = 0; i < n; i++) {
                printf("[%2d] Input the student's name: ", i+1);
                scanf("%s", &s.name);
                printf("[%2d] Input the student's code: ", i+1);
                scanf("%s", &s.code);
                for (j = 0; j < SWN; j++) {
                    printf("[%2d] Input the %-10s mark: ", i + 1, schoolwork[j]);
                    scanf("%d", &s.marks[j]);
                }
                writerecord(fp, &s);
            }
            fclose(fp);
        } // if (c == 'Y' || c == 'y')
    } // if ((fp = fopen(stuf, "r")) == NULL)
    fclose(fp);

    clrscr();
    puts("Now you can input a command to manage the records.");
    print_help();

    while (1) {
        printf("\nPlease input command [m,t,n,c,l,s,q,h]: ");
        scanf("%c", &c); // 输入选择命令
        if (c=='\n') {
            continue;
        } else {
            getchar();
        }
        if (c == 'q' || c == 'Q') {
            puts("\n\tThank you for your using.");
            break; // q，结束程序运行
        }

        switch (c) {
            // 计算平均分
            case 'm': case 'M':
                if ((n = totalmark(stuf, total)) == 0) {
                    puts("Error!");
                    break;
                }
                for (i = 0; i < SWN; i++)
                    printf("%-10s's average is: %.2f.\n", schoolwork[i], (float)total[i] / n);
                break;
            // 计算总分
            case 't': case 'T':
                if ((n = totalmark(stuf, total)) == 0) {
                    puts("Error!");
                    break;
                }
                for (i = 0; i < SWN; i++)
                    printf("%-10s's total mark is: %d.\n", schoolwork[i], total[i]);
                break;
            // 按学生的姓名寻找记录
            case 'n': case 'N':
                printf("Please input the student's name you want to search: ");
                scanf("%s", buf); getchar();
                retrievebyn(stuf, buf);
                break;
            // 按学生的学号寻找记录
            case 'c': case 'C':
                printf("Please input the student's code you want to search: ");
                scanf("%s", buf); getchar();
                retrievebyc(stuf, buf);
                break;
            // 列出所有学生记录
            case 'l': case 'L': liststu(stuf); break;
            // 按总分从高到低排列显示
            case 's': case 'S':
                if ((head = makelist(stuf)) != NULL)
                    displaylist(head);
                break;
            case 'h': case 'H': print_help(); break;
            default: break;
        } // switch (c)
    } // while (1)

    return 0;
} // main()