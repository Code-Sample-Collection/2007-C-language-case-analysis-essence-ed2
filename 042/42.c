#include <stdio.h>
#define MAX 255
int R[MAX];
void Insert_Sort(int n)
{ /* ������R�еļ�¼R[1..n]����������в�������  */
    int i,j;
    for(i=2;i<=n;i++) /* ���β���R[2]������R[n] */
      if(R[i]<R[i-1])
      {/* ��R[i]���ڵ��������������е�R����R[i] */
                              /* Ӧ��ԭ��λ���� */
        R[0]=R[i];j=i-1; /* R[0]���ڱ�������R[i]�ĸ��� */
        do{ /* ����������������R[1����i-1]�в���R[i]�Ĳ���λ�� */
         R[j+1]=R[j]; /* ���ؼ��ִ���R[i]�ļ�¼���� */
         j--;
         }while(R[0]<R[j]);  /* ��R[i]��R[j]ʱ��ֹ */
        R[j+1]=R[0]; /* R[i]���뵽��ȷ��λ���� */
       }
}

main()
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
	Insert_Sort(n);
	puts("\nThe sequence after insert_sort is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	puts("\n Press any key to quit...");
	getchar();
	getchar();
}
