#include<stdio.h>
void main()
{
    int x,y,z;
    clrscr();
    puts("****************************************************************");
    puts("*  This program is to solve Problem of Bridegroom and Bride.   *");
    puts("* The Problem is as follows: Someone goes to 3 couples lovers' *");
    puts("* wedding. The bridegrooms are A,B,C and the brides are X,Y,Z. *");
    puts("* He wants to know who marries who and asks them. A says he    *");
    puts("* will marry to X, X says her fiance is C, C says he will marry*");
    puts("* to Z. The man knows that they are all kidding. What they said*");
    puts("* is not true. So try to find who will marry to who?           *");
    puts("****************************************************************");
    puts(" >> The solutions are:");
    printf("---------------------------------------------\n");
    for(x=1;x<=3;x++)          /*���x��ȫ��������ż*/
        for(y=1;y<=3;y++)      /*���y��ȫ��������ż*/
            for(z=1;z<=3;z++)    /*���z��ȫ��������ż*/
                if(x!=1&&x!=3&&z!=3&&x!=y&&x!=z&&y!=z)  /*�ж���ż�Ƿ���������*/
                {
		    printf(" X will marry to %c.\n",'A'+x-1);    /*��ӡ�жϽ��*/
		    printf(" Y will marry to %c.\n",'A'+y-1);
		    printf(" Z will marry to %c.\n",'A'+z-1);
                }
    printf("---------------------------------------------\n");
    printf(" Press any key to quit...");
    getch();
}
