#include <stdio.h>
#define MAX 255
int R[MAX];

void Merge(int low,int m,int high)
{/* ��������������ļ�R[low..m)��R[m+1..high]�鲢��һ������� */
     /* ���ļ�R[low..high] */
     int i=low,j=m+1,p=0; /* �ó�ʼֵ */
     int *R1; /* R1�Ǿֲ���������p����Ϊ������ָ���ٶȸ��� */
     R1=(int *)malloc((high-low+1)*sizeof(int));
     if(!R1) /* ����ռ�ʧ�� */
     {
       puts("Insufficient memory available!");
       return;
     }
     while(i<=m&&j<=high) /* �����ļ��ǿ�ʱȡ��С�������R1[p]�� */
       R1[p++]=(R[i]<=R[j])?R[i++]:R[j++];
     while(i<=m) /* ����1�����ļ��ǿգ�����ʣ���¼��R1�� */
       R1[p++]=R[i++];
     while(j<=high) /* ����2�����ļ��ǿգ�����ʣ���¼��R1�� */
       R1[p++]=R[j++];
     for(p=0,i=low;i<=high;p++,i++)
       R[i]=R1[p];/* �鲢��ɺ󽫽�����ƻ�R[low..high] */
} /* end of Merge */


void Merge_SortDC(int low,int high)
{/* �÷��η���R[low..high]���ж�·�鲢���� */
       int mid;
       if(low<high)
       {/* ���䳤�ȴ���1 */
          mid=(low+high)/2; /* �ֽ� */
	  Merge_SortDC(low,mid); /* �ݹ�ض�R[low..mid]���� */
	  Merge_SortDC(mid+1,high); /* �ݹ�ض�R[mid+1..high]���� */
          Merge(low,mid,high); /* ��ϣ��������������鲢Ϊһ�������� */
        }
}/* end of Merge_SortDC */


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
	Merge_SortDC(1,n);
	puts("\nThe sequence after merge_sortDC is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	puts("\n Press any key to quit...");
	getch();
	
}