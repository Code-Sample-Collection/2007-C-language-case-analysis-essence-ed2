#include<stdio.h>
#include<math.h>
void main()
{
    double y;
    int x,m,n,yy;
    clrscr();
    puts("========This program shows the curve of cos(x) and a line.========");
    puts("        ******* f(x)=cos(x)    +++++++ g(x)=45*(y-1)+31");

    for(yy=0;yy<=20;yy++) /*���ڵ�һ��y������м��㲢��һ���д�ӡͼ��*/
    {
        y=0.1*yy;                       /*y����Ļ�з�������*/
        m=acos(1-y)*10;       /*m: cos(x)������y���Ӧ����Ļ������*/
        n=45*(y-1)+31;        /*n: ֱ����y���Ӧ��������*/
        for(x=0;x<=62;x++)              /*x: ��Ļ�з�������*/
            if(x==m&&x==n) printf("+");  /*ֱ����cos(x)�ཻʱ��ӡ"+"*/
            else if(x==n) printf("+");   /*��ӡ���ཻʱ��ֱ��ͼ��*/
            else if(x==m||x==62-m) printf("*");  /*��ӡ���ཻʱ��cos(x)ͼ��*/
            else  printf(" ");                  /*���������ӡ�ո�*/
        printf("\n");
    }
    puts(" Press any key to quit...");
    getch();
}
