// 040
/*
    该程序实现统计一个或多个文件的行数、字数和字符数。

    一个行由一个换行符限定，一个字由空格分隔（包括空白符、制表符和换行符），
    字符是指文件中的所有字符。
    
    要求程序另设三个任选的参数，让用户指定他所要的统计。它们是：
        + 1 统计文件行数
        + w 统计文件字数
        + c 统计文件字符数
    若用户未指定任选的参数，则表示三个统计都要。

    运行本程序时的参数按一下格式给出：
        -l -w -c 文件 文件 ... 文件

    其中，前三个任选参数l、w、c的出现与否和出现顺序任意，
    或任意组合在一起出现，如：-lwc，-cwl，-lw，-wl，-lc，-cl，-cw 等。
*/
#if !defined(TRUE) && !defined(FALSE)
#define TRUE  1
#define FALSE 0
#endif

#include <stdio.h>
#include <stdlib.h> // exit

void print_help() {
    puts("To run this program, usage:");
    puts("\tprogram -l -w -c file1 file2 ... filen");
}

int main(int argc, char **argv) {
    FILE *fp;
    int lflg, wflg, cflg;       // l, w, c三个标志
    int isinline, inword;       // 行内和字内标志
    int ccount, wcount, lcount; // 字符、字、行 计数器
    int c;
    char *s;
    lflg = wflg = cflg = FALSE;

    if (argc < 2) {
        print_help();
        exit(0);
    }

    while (--argc >= 1 && (*++argv)[0] == '-') {
        for (s = argv[0] + 1; *s != '\0'; s++) {
            switch (*s) {
                case 'l':
                    lflg = TRUE;
                    break;
                case 'w':
                    wflg = TRUE;
                    break;
                case 'c':
                    cflg = TRUE;
                    break;
                default:
                    print_help();
                    exit(0);
            }
        }
    }
    if (lflg == 0 && wflg == 0 && cflg == 0)
        lflg = wflg = cflg = TRUE;

    lcount = wcount = ccount = 0;
    // 依次统计文件
    while (--argc >= 0) {
        if ((fp = fopen(*argv++, "r")) == NULL) {
            // 以只读方式打开文件
            fprintf(stderr, "Can't open %s.\n", *argv);
            continue;
        }

        inword = isinline = FALSE;
        while ((c = fgetc(fp)) != EOF) {
            if (cflg) ccount++;
            if (wflg) {
                if (c == '\n' || c == ' ' || c == '\t') {
                    inword = FALSE;
                } else if (inword == FALSE) {
                    wcount++;
                    inword = TRUE;
                }
            }
            if (lflg) {
                if (c == '\n') {
                    isinline = FALSE;
                } else if (isinline == FALSE) {
                    lcount++;
                    isinline = TRUE;
                }
            }
        } // while ((c = fgetc(fp)) != EOF)
        fclose(fp); // 关闭文件
    } // while (--argc >= 0)

    if (lflg) printf(" Lines      = %d\n", lcount);
    if (wflg) printf(" Words      = %d\n", wcount);
    if (cflg) printf(" Characters = %d\n", ccount);

    return 0;
}