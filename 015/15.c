#define N 50
main()
{
	int primes[N];
	int pc,m,k;

	clrscr();
	printf("\n The first %d prime numbers are:\n",N);
	primes[0]=2;/*2�ǵ�һ������*/
	pc             =1;/*���е�һ������*/
	m               =3;/*�����Ե�����3��ʼ*/
	while(pc<N)
	{
	 /*����mʹ��Ϊ��һ������*/
	k=0;
	while(primes[k]*primes[k]<=m)
		if(m%primes[k]==0)
		{/*m�Ǻ���*/
		    m+=2;/*��mȡ��һ������*/
		    k=1;/*������primes[0]=2ȥ����m������k��һ��ʼ*/
		}
		else
		k++;/*��������һ������ȥ����*/
	primes[pc++]=m;
	m+=2;/*��2�⣬����������������*/
	}
	/*���primes[0]��primes[pc-1]*/
	for(k=0;k<pc;k++)
		printf("%4d",primes[k]);
	printf("\n\n Press any key to quit...\n ");
	getch();
}