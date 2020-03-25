#include <stdio.h>
#define MAX 255
int R[MAX];
void Bubble_Sort(int n)
{ /* R��l..n)�Ǵ�������ļ���������������ɨ�裬��R��ð������ */
     int i,j;
     int exchange; /* ������־ */
     for(i=1;i<n;i++){ /* �����n-1������ */
       exchange=0; /* ��������ʼǰ��������־ӦΪ�� */
       for(j=n-1;j>=i;j--) /* �Ե�ǰ������R[i..n]��������ɨ�� */
        if(R[j+1]<R[j]){/* ������¼ */
          R[0]=R[j+1]; /* R[0]�����ڱ��������ݴ浥Ԫ */
          R[j+1]=R[j];
          R[j]=R[0];
          exchange=1; /* �����˽������ʽ�������־��Ϊ�� */
         }
       if(!exchange) /* ��������δ������������ǰ��ֹ�㷨 */
	     return;
     }
}

void main()
{
	int i,n;
	clrscr();
	puts("Please input total element number of the sequence:");
	scanf("%d",&n);
	if(n<=0||n>MAX)
	{
		printf("n must more than 0 and less than %d.\n",MAX);
		exit(0);
	}
	puts("Please input the elements one by one:");
	for(i=1;i<=n;i++)
		scanf("%d",&R[i]);
	puts("The sequence you input is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	Bubble_Sort(n);
	puts("\nThe sequence after bubble_sort is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	puts("\n Press any key to quit...");
	getchar();
	getchar();
}