int a[ ]={1,2,3,4,5};
#define N sizeof a/sizeof a[0]
main()
{
	int j,   /*�α����*/
	      *p; /*ָ�����*/
	clrscr();
	for(j=0;j<N;j++)/*���������±�˳����������Ԫ��*/
		printf("a[%d]\t= %d\t",j,a[j]);
	printf("\n");
	for(p=a;p<a+N;p++)/*��ָ��˳��ָ������ĸ�Ԫ�أ���������*/
	printf("*p\t= %d\t",*p);
	printf("\n");/*ָ�����α������ϣ��ı��α������������*/
	for(p=a,j=0;p+j<a+N;j++)
		printf("*(p+%d)\t= %d\t",j,*(p+j));
	printf("\n");/*ָ�����α������ϣ���ָ����±��������*/
	for(p=a+N-1,j=N-1;j>=0;j--)
		printf("p[-%d]\t= %d\t",j,p[-j]);
	printf("\nPress any key to quit...\n");
	getch();
}