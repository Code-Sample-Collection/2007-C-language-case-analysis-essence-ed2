/* ����trans���޷�������n�����d��2<��d<��16�����Ʊ�ʾ���ַ���s */
#define M sizeof(unsigned int)*8
int trans(unsigned n, int d, char s[])
{
	static char digits[] ="0123456789ABCDEF"; /* ʮ���������ֵ��ַ� */
	char buf[M+1];
	int j, i = M;
	if(d<2||d>16)
	{
		s[0]='\0';	/* ������Ľ��ƣ���sΪ���ַ��� */
		return 0;	/* ������Ľ��ƣ���������0 */
	}
	buf[i]='\0';
	do
	{
		buf[--i]=digits[n%d];	/*������λ����Ӧ�ַ������Ӧ����������*/
		n/=d;
	}while(n);
	/* ������ڹ��������е��ַ������Ƶ�s */
	for(j=0;(s[j]=buf[i])!='\0';j++,i++);
		/* ���п��������ɼ�д��s[j]=buf[i] */
	return j;
}
/* ���������ڲ��Ժ��� trans() */
main()
{
	unsigned int num = 253;
	int scale[]={2,3,10,16,1};
	char str[33];
	int i;
	clrscr();
	for(i=0;i<sizeof(scale)/sizeof(scale[0]);i++)
	{
		if(trans(num,scale[i],str))
			printf("%5d = %s(%d)\n",num,str,scale[i]);
		else
			printf("%5d => (%d) Error! \n",num,scale[i]);
	}
	printf("\n Press any key to quit...\n");
	getch();
}