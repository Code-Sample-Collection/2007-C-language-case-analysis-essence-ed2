#include <stdio.h>
#define N 200
#define SCORES 5
#define NUMLEN 10
struct std_type{
	char no[NUMLEN];/*ѧ��*/
	char *name;/*���ַ���ָ��*/
	int scores[SCORES];/*���Ź��εĳɼ�*/
};
struct std_type students[N];
int order[N];
int total[N];

/*[����]����һ��ѧ����Ϣ����*/
int readastu(struct std_type *spt)
{
	int len,j;
	char buf[120];/*�����ַ����Ļ�����*/

	printf("\nNumber   :   ");/*����ѧ��*/
	if(scanf("%s",buf)==1)
		strncpy(spt->no,buf,NUMLEN-1);
	else
		return 0;/*Ctrl+Z��������*/
	printf("Name   :   ");/*��������*/
	if(scanf("%s",buf)==1)
	{
		len=strlen(buf);
		spt->name=(char *)malloc(len+1);/*������������Ŀռ�*/
		strcpy(spt->name,buf);
	}
	else return 0;/*Ctrl+Z��������*/
	printf("Scores   :   ");/*����ɼ�*/
	for(j=0;j<SCORES;j++)
		if(scanf("%d",spt->scores+j)!=1)
			break;
			if(j==0)/*һ���ɼ�Ҳδ����*/
			{
				free(spt->name);/*�ͷŴ��������Ŀռ�*/
				return 0;
			}
			for(;j<SCORES;j++)/*����δ����ĳɼ���0�ִ�֮*/
				spt->scores[j]=0;
			return 1;
	}

/*[����]���һ��ѧ����Ϣ�ĺ���*/
int writeastu(struct std_type *spt)
{
	int i;

	printf("Number   :   %s\n",spt->no);/*���ѧ��*/
	printf("Name     :   %s\n",spt->name);/*�������*/
	printf("Scores   :   ");/*����ɼ�*/
	for(i=0;i<SCORES;i++)
		printf("%4d",spt->scores[i]);
	printf("\n\n");
}

main()
{
	int n,i,j,t;

	clrscr();
	for(n=0;readastu(students+n);n++);
	/*����ð�ݷ���ѧ����Ϣ��������*/
	for(i=0;i<n;i++)
	{
		order[i]=i;/*Ԥ�õ�i�������ѧ��*/
		for(t=0,j=0;j<SCORES;j++)/*���i��ѧ�����ܷ�*/
			t+=students[i].scores[j];
		total[i]=t;
	}
	/*ð������*/
	for(i=0;i<n-1;i++)/*��ɨ��n-1��*/
		for(j=0;j<n-1-i;j++)
			if(total[order[j]]<total[order[j+1]])
			{/*��������*/
			 t=order[j];
			 order[j]=order[j+1];
			 order[j+1]=t;
			}
	for(j=0;j<n;j++)/*���*/
		writeastu(students+order[j]);
	printf("\n Press any key to quit...\n");
	getch();
}
