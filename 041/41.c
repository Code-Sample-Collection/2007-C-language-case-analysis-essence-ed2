/*
ѧ���ɼ��������
����һ��ͳ��ѧ�����Է����Ĺ������
��ѧ���ɼ�����һ��ѧ��һ����¼����ʽ�洢���ļ��У�
ÿλѧ����¼��������Ϣ�У�������ѧ�ź͸��Ź��εĳɼ���
����������¼���ܣ�������ſγ̵��ܷ֣�ƽ���֣���������
��ѧ��Ѱ�����¼����ʾ�����ȫ��ѧ���ɼ��Ͱ��ܷ��ɸߵ�����ʾѧ����Ϣ�ȡ�
*/

#include <stdio.h>
#define	SWN		3	/* �γ��� */
#define NAMELEN		20	/* ��������ַ��� */
#define CODELEN		10	/* ѧ������ַ��� */
#define FNAMELEN	80	/* �ļ�������ַ��� */
#define BUFLEN		80	/* ����������ַ��� */
/* �γ����Ʊ� */
char schoolwork[SWN][NAMELEN+1] = {"Chinese","Mathematic","English"};
struct record
{
	char	name[NAMELEN+1];	/* ���� */
	char 	code[CODELEN+1];	/* ѧ�� */
	int 	marks[SWN];		/* ���γ̳ɼ� */
	int total;			/* �ܷ� */
}stu;

struct node
{
	char	name[NAMELEN+1];	/* ���� */
	char 	code[CODELEN+1];	/* ѧ�� */
	int 	marks[SWN];		/* ���γ̳ɼ� */
	int 	total;			/* �ܷ� */
	struct	node *next;		/* ������Ԫָ�� */
}*head;	/* ������ָ�� */

int total[SWN];		/* ���γ��ܷ� */
FILE *stfpt;		/* �ļ�ָ�� */
char stuf[FNAMELEN];	/* �ļ��� */

/* ��ָ���ļ�����һ����¼ */
int readrecord(FILE *fpt,struct record *rpt)
{
	char buf[BUFLEN];
	int i;
	if(fscanf(fpt,"%s",buf)!=1)
		return 0;	/* �ļ����� */
	strncpy(rpt->name,buf,NAMELEN);
	fscanf(fpt,"%s",buf);
	strncpy(rpt->code,buf,CODELEN);
	for(i=0;i<SWN;i++)
		fscanf(fpt,"%d",&rpt->marks[i]);
	for(rpt->total=0,i=0;i<SWN;i++)
		rpt->total+=rpt->marks[i];
	return 1;
}
/* ��ָ���ļ�д��һ����¼ */
writerecord(FILE *fpt,struct record *rpt)
{
	int i;
	fprintf(fpt,"%s\n",rpt->name);
	fprintf(fpt,"%s\n",rpt->code);
	for(i=0;i<SWN;i++)
		fprintf(fpt,"%d\n",rpt->marks[i]);
	return ;
}

/* ��ʾѧ����¼ */
displaystu(struct record *rpt)
{
	int i;
	printf("\nName   : %s\n",rpt->name);
	printf("Code   : %s\n",rpt->code);
	printf("Marks  :\n");
	for(i=0;i<SWN;i++)
		printf("       %-15s : %4d\n",schoolwork[i],rpt->marks[i]);
	printf("Total  : %4d\n",rpt->total);
}

/* ����������ܷ� */
int totalmark(char *fname)
{
	FILE *fp;
	struct record s;
	int count,i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	for(i=0;i<SWN;i++)
		total[i]=0;
	count=0;
	while(readrecord(fp,&s)!=0)
	{
		for(i=0;i<SWN;i++)
			total[i]+=s.marks[i];
		count++;
	}
	fclose(fp);
	return count;	/* ���ؼ�¼�� */
}

/* �б���ʾѧ����Ϣ */
void liststu(char *fname)
{
	FILE *fp;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return ;
	}
	while(readrecord(fp,&s)!=0)
	{
		displaystu(&s);
		printf("\n      Press ENTER to continue...\n");
		while(getchar()!='\n');
	}
	fclose(fp);
	return;
}

/* �������� */
struct node *makelist(char *fname)
{
	FILE *fp;
	struct record s;
	struct node *p,*u,*v,*h;
	int i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return NULL;
	}
	h=NULL;
	p=(struct node *)malloc(sizeof(struct node));
	while(readrecord(fp,(struct record *)p)!=0)
	{
		v=h;
		while(v&&p->total<=v->total)
		{
			u=v;
			v=v->next;
		}
		if(v==h)
			h=p;
		else
			u->next=p;
		p->next=v;
		p=(struct node *)malloc(sizeof(struct node));
	}
	free(p);
	fclose(fp);
	return h;
}

/* ˳����ʾ�������Ԫ */
void displaylist(struct node *h)
{
	while(h!=NULL)
	{
		displaystu((struct record *)h);
		printf("\n      Press ENTER to continue...\n");
		while(getchar()!='\n');
		h=h->next;
	}
	return;
}
/* ��ѧ����������ѧ����¼ */
int retrievebyn(char *fname, char *key)
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(readrecord(fp,&s)!=0)
	{
		if(strcmp(s.name,key)==0)
		{
			displaystu(&s);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The student %s is not in the file %s.\n",key,fname);
	return 1;
}

/* ��ѧ��ѧ�Ų���ѧ����¼ */
int retrievebyc(char *fname, char *key)
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(readrecord(fp,&s)!=0)
	{
		if(strcmp(s.code,key)==0)
		{
			displaystu(&s);
			c++;
			break;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The student %s is not in the file %s.\n",key,fname);
	return 1;
}

main()
{
	int i,j,n;
	char c;
	char buf[BUFLEN];
	FILE *fp;
	struct record s;
	clrscr();
	printf("Please input the students marks record file's name: ");
	scanf("%s",stuf);
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("The file %s doesn't exit, do you want to creat it? (Y/N) ",stuf);
		getchar();
		c=getchar();
		if(c=='Y'||c=='y')
		{
			fp=fopen(stuf,"w");
			printf("Please input the record number you want to write to the file: ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
				printf("Input the student's name: ");
				scanf("%s",&s.name);
				printf("Input the student's code: ");
				scanf("%s",&s.code);
				for(j=0;j<SWN;j++)
				{
					printf("Input the %s mark: ",schoolwork[j]);
					scanf("%d",&s.marks[j]);
				}
				writerecord(fp,&s);
			}
			fclose(fp);
		}
	}
	fclose(fp);
	getchar();
	/*clrscr();*/
	puts("Now you can input a command to manage the records.");
	puts("m : mean of the marks.");
	puts("t : total of the marks.");
	puts("n : search record by student's name.");
	puts("c : search record by student's code.");
	puts("l : list all the records.");
	puts("s : sort and list the records by the total.");
	puts("q : quit!");
	while(1)
	{
		puts("Please input command:");
		scanf(" %c",&c);		/* ����ѡ������ */
		if(c=='q'||c=='Q')
		{
			puts("\n Thank you for your using.");
			break;		/* q�������������� */
		}
		switch(c)
		{
			case 'm': /* ����ƽ���� */
			case 'M':
				if((n=totalmark(stuf))==0)
				{
					puts("Error!");
					break;
				}
				printf("\n");
				for(i=0;i<SWN;i++)
					printf("%-15s's average is: %.2f.\n",schoolwork[i],(float)total[i]/n);
				break;
			case 't': /* �����ܷ� */
			case 'T':
				if((n=totalmark(stuf))==0)
				{
					puts("Error!");
					break;
				}
				printf("\n");
				for(i=0;i<SWN;i++)
					printf("%-15s's total mark is: %d.\n",schoolwork[i],total[i]);
				break;
			case 'n': /* ��ѧ��������Ѱ�Ҽ�¼ */
			case 'N':
				printf("Please input the student's name you want to search: ");	
				scanf("%s",buf);
				retrievebyn(stuf,buf);
				break;
			case 'c': /* ��ѧ����ѧ��Ѱ�Ҽ�¼ */
			case 'C':
				printf("Please input the student's code you want to search: ");	
				scanf("%s",buf);
				retrievebyc(stuf,buf);
				break;
			case 'l': /* �г�����ѧ����¼ */
			case 'L':
				liststu(stuf);
				break;
			case 's': /* ���ִܷӸߵ���������ʾ */
			case 'S':
				if((head=makelist(stuf))!=NULL)
					displaylist(head);
				break;
			default: break;
		}
	}
}