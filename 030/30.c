/* �ַ����������ַ����к���������֪�ַ���s�е������ַ�������������n���ַ���ɵ������ַ����� */
#define N 20
char w[N];
perm(int n, char *s)
{
	char s1[N];
	int i;
	if(n<1)
		printf("%s\n",w); /* һ������������� */
	else
	{
		strcpy(s1,s);	/* ���汾��ο�ʹ�õ��ַ� */
		for(i=0;*(s1+i);i++)	/* ����ѡ����ο����ַ� */
		{
			*(w+n-1)=*(s1+i);/* ��ѡ���ַ������������ɵ��ַ������� */
			*(s1+i)=*s1;
			*s1=*(w+n-1);
			perm(n-1,s1+1);	 /* �ݹ� */
		}
	}
}
main()
{
	int n=2;
	char s[N];
	w[n]='\0';
	clrscr();
	printf("This is a char permutation program!\nPlease input a string:\n");
	scanf("%s",s);
	puts("\nPlease input the char number of permuted:\n");
	scanf("%d",&n);
	puts("The permuted chars are:\n");
	perm(n,s);
	puts("\nPress any key to quit...");
	getch();
}