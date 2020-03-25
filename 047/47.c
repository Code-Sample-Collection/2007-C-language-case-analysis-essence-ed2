#include <stdio.h>
#define MAX 255
int R[MAX];

void Heapify(int s,int m)
{ /*��R[1..n]���жѵ�������temp���ݴ浥Ԫ */
     int j,temp;
     temp=R[s];
     j=2*s;
     while (j<=m)
     {
	  if (R[j]>R[j+1]&&j<m) j++;
	  if (temp<R[j]) break;
	  R[s]=R[j];
          s=j;
          j=j*2;
     }/* end of while */
     R[s]=temp;
} /* end of Heapify */

void BuildHeap(int n)
{ /* ��һ����������н���һ���� */
   int i;
   for(i=n/2;i>0;i--)
      Heapify(i,n);
}


void Heap_Sort(int n)
{ /* ��R[1..n]���ж����򣬲�����R[0]���ݴ浥Ԫ */
    int i;
    BuildHeap(n); /* ��R[1-n]���ɳ�ʼ�� */
    for(i=n;i>1;i--)
    { /* �Ե�ǰ������R[1..i]���ж����򣬹���n-1�ˡ� */
    	R[0]=R[1]; R[1]=R[i];R[i]=R[0]; /* ���Ѷ��Ͷ������һ����¼���� */
    	Heapify(1,i-1); /* ��R[1..i-1]���µ���Ϊ�ѣ�����R[1]����Υ�������� */
    } /* end of for */
} /* end of Heap_Sort */
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
	Heap_Sort(n);
	puts("\nThe sequence after Big heap_sort is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	puts("\n Press any key to quit...");
	getch();
	
}