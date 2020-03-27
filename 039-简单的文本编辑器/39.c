// 039
#include <stdio.h>
#include <stdlib.h> // free, exit, malloc
#include <string.h> // strlen, strcpy
#define MAXLEN 80
#define MAXLINE 200

void edit(), replace(), insert(), delete (), quit();
void save(char *fname);
void print_help(int full_help);

char buffer[MAXLEN],
fname[120];
char *lineptr[MAXLINE];
// FILE *fp;

char comch[] = "EeRrIiDdQq"; // 命令符
void (*comfun[])() = { // 对应处理函数
    edit, 
    replace, 
    insert, 
    delete, 
    quit
};
int modified = 0, // 正文被修改标志
    last;         // 当前正文行数
char *g_chpt;     // 输入命令行字符指针


int main() {
    int j;

    last = 0;
    while (1) {
        print_help(1);
        gets(buffer); // 读入命令行
        for (
            g_chpt = buffer;
            *g_chpt == ' ' || *g_chpt == '\t';
            g_chpt++
        ) ; // 掠过空白符
        if (*g_chpt == '\0') continue; // 空行重新输入
    
        for (
            j = 0;
            comch[j] != '\0' && comch[j] != *g_chpt;
            j++
        ) ; // 查命令符
        if (comch[j] == '\0') continue; // 非法命令符
    
        g_chpt++; // 掠过命令符，指向参数
        (*comfun[j / 2])(); // 执行对应函数
        fprintf(stdout, "The text is:\n");
        for (j = 0; j < last; j++) // 显示正文
            fputs(lineptr[j], stdout);
    }
    return 0;
}

void print_help(int full_help) {
    puts("");
    puts("Input a command: [e,r,i,d,q].");
    if (full_help) {
        puts("  E\t\t—— 指定要编辑的文件");

        printf("  R K M N\t");
        puts("—— 用 K 行正文替代原文中 M 至 N 行");

        printf("  I K M \t");
        puts("—— 将 K 行正文插入到原文第 M 行后");

        printf("  D M N \t");
        puts("—— 将原文中 M 至 N 行删去");

        puts("  Q\t\t—— 结束编辑");
        // puts("  H\t—— 显示帮助");
    }
}

// 询问是否保存并退出程序
void quit() {
    int c;

    if (modified) { // 正文被修改 
        printf("Save? (y/n): ");
        while (
            !(((c = getchar()) >= 'a' && c <= 'z') || 
             (c >= 'A' && c <= 'Z'))
        ) ;
        if (c == 'y' || c == 'Y') save(fname); // 保存被修改过的正文 
    }
    for (c = 0; c < last; c++) free(lineptr[c]); // 释放内存
    exit(0);
}

void insert() {
    int k, m, i;

    sscanf(g_chpt, "%d%d", &k, &m); // 读入参数
    // 检查参数合理性
    if (m < 0 || m > last || last + k >= MAXLINE) {
        puts("[insert] Error!");
        (m < 0) && printf("m=%d < 0; ", m);
        (m > last) && printf("m=%d > last=%d; ", m, last);
        (last + k >= MAXLINE) && printf("(last+k)=%d >= MAXLINE=%d; ", last + k, MAXLINE);
        puts("\n");
        return;
    }

    for (i = last; i > m; i--) // 后继行向后移 
        lineptr[i + k - 1] = lineptr[i - 1];
    //  读入k行正文，并插入 
    for (i = 0; i < k; i++) {
        fgets(buffer, MAXLEN, stdin);
        lineptr[m + i] = (char *)malloc(strlen(buffer) + 1);
        strcpy(lineptr[m + i], buffer);
    }
    last += k;    //  修正正文行数 
    modified = 1; //  正文被修改 
}

void delete () {
    int i, j, m, n;

    sscanf(g_chpt, "%d%d", &m, &n);  //  读入参数 
    if (m <= 0 || m > last || n < m) { //  检查参数合理性 
        puts("[delete] Error!");
        (m <= 0) && printf("m=%d <= 0; ", m);
        (m > last) && printf("m=%d > last=%d; ", m, last);
        (n < m) && printf("n=%d < m=%d; ", n, m);
        puts("\n");
        return;
    }

    if (n > last)
        n = last;            // 修正参数 
    for (i = m; i <= n; i++) // 删除正文 
        free(lineptr[i - 1]);
    for (i = m, j = n + 1; j <= last; i++, j++)
        lineptr[i - 1] = lineptr[j - 1];
    last = i - 1; //  修正正文行数 
    modified = 1; //  正文被修改 
}

void replace() {
    int k, m, n, i, j;

    sscanf(g_chpt, "%d%d%d", &k, &m, &n); // 读入参数 
    if (
        m <= 0 || 
        m > last || 
        n < m || 
        last - (n - m + 1) + k >= MAXLINE
    ) { //  检查参数合理性 
        puts("[replace] Error!");
        (m <= 0) && printf("m=%d <= 0; ", m);
        (m > last) && printf("m=%d > last=%d; ", m, last);
        (n < m) && printf("n=%d < m=%d; ", n, m);
        ((last-(n-m +1)+k) >= MAXLINE) &&
            printf("(last-(n-m +1)+k) >= MAXLINE; ");
        puts("\n");
        return;
    }

    // 先完成删除 
    if (n > last)
        n = last;            //  修正参数 
    for (i = m; i <= n; i++) //  删除正文 
        free(lineptr[i - 1]);
    for (i = m, j = n + 1; j <= last; i++, j++)
        lineptr[i - 1] = lineptr[j - 1];
    last = i - 1;

    // 以下完成插入 
    for (i = last; i >= m; i--)
        lineptr[i + k - 1] = lineptr[i - 1];
    for (i = 0; i < k; i++) {
        fgets(buffer, MAXLEN, stdin);
        lineptr[m + i - 1] = (char *)malloc(strlen(buffer) + 1);
        strcpy(lineptr[m + i - 1], buffer);
    }
    last += k;    // 修正正文行数 
    modified = 1; // 正文被修改 
}

//  保存文件 
void save(char *fname) {
    FILE *fp;

    if ((fp = fopen(fname, "w")) == NULL) {
        puts("[save] Error!");
        fprintf(stderr, "Can't open %s.\n", fname);
        exit(1);
    }
    for (int i = 0; i < last; i++) {
        fputs(lineptr[i], fp);
        free(lineptr[i]);
    }
    fclose(fp);
}

//  编辑命令 
void edit() {
    int i;
    FILE *fp;

    i = sscanf(g_chpt, "%s", fname); // 读入文件名 
    if (i != 1) {
        printf("Enter file name: ");
        scanf("%s", fname);
    }

    // 读打开 
    if ((fp = fopen(fname, "r")) == NULL) {
        fp = fopen(fname, "w"); //  如不存在，则创建文件 
        fclose(fp);
        fp = fopen(fname, "r"); //  重新读打开 
    }

    i = 0;
    while (fgets(buffer, MAXLEN, fp) == buffer) {
        lineptr[i] = (char *)malloc(strlen(buffer) + 1);
        strcpy(lineptr[i++], buffer);
    }
    fclose(fp);
    last = i;
}