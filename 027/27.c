#include <stdio.h>
#define MAX 50
/* ����repʵ�ֶ�s�г��ֵ�s1�е��ַ��滻Ϊs2����Ӧ���ַ� */
rep(char *s,char *s1,char *s2)
{
	char *p;

	for(;*s;s++)/*˳������ַ���s�е�ÿ���ַ�*/
	{
		for(p=s1;*p&&*p!=*s;p++);/*��鵱ǰ�ַ��Ƿ����ַ���s1�г���*/
		if(*p)*s=*(p-s1+s2);/*��ǰ�ַ����ַ���s1�г��֣����ַ���s2�еĶ�Ӧ�ַ�����s�е��ַ�*/
	}
}
main( )/*ʾ�����*/
{
	char s[MAX];/*="ABCABC";*/
	char s1[MAX],s2[MAX];
	clrscr();
	puts("Please input the string for s:");
	scanf("%s",s);
	puts("Please input the string for s1:");
	scanf("%s",s1);
	puts("Please input the string for s2:");
	scanf("%s",s2);

	rep(s,s1,s2);
	puts("The string of s after displace is:");
	printf("%s\n",s);
	puts("\n Press any key to quit...");
	getch();
}
