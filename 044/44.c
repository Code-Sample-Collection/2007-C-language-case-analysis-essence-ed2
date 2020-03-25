#include <stdio.h>
#define MAX 255
int R[MAX];
int Partition(int i,int j)
{/* ����Partition(R��low��high)ʱ����R[low..high]�����֣�*/
     /* �����ػ�׼��¼��λ�� */
      int pivot=R[i]; /* ������ĵ�1����¼��Ϊ��׼ */
      while(i<j){ /* ���������˽������м�ɨ�裬ֱ��i=jΪֹ */
        while(i<j&&R[j]>=pivot) /* pivot�൱����λ��i�� */
          j--;  /* ��������ɨ�裬���ҵ�1���ؼ���С��pivot.key�ļ�¼R[j] */
        if(i<j) /* ��ʾ�ҵ���R[j]�Ĺؼ���<pivot.key  */
            R[i++]=R[j]; /* �൱�ڽ���R[i]��R[j]��������iָ���1 */
        while(i<j&&R[i]<=pivot) /* pivot�൱����λ��j��*/
            i++; /* ��������ɨ�裬���ҵ�1���ؼ��ִ���pivot.key�ļ�¼R[i] */
        if(i<j) /* ��ʾ�ҵ���R[i]��ʹR[i].key>pivot.key */
            R[j--]=R[i]; /* �൱�ڽ���R[i]��R[j]��������jָ���1 */
       } /* endwhile */
      R[i]=pivot; /* ��׼��¼�ѱ����λ*/
      return i;
} /* end of partition  */

void Quick_Sort(int low,int high)
{ /* ��R[low..high]�������� */
     int pivotpos; /* ���ֺ�Ļ�׼��¼��λ�� */
     if(low<high){/* �������䳤�ȴ���1ʱ�������� */
	pivotpos=Partition(low,high); /* ��R[low..high]������ */
        Quick_Sort(low,pivotpos-1); /* ��������ݹ����� */
        Quick_Sort(pivotpos+1,high); /* ��������ݹ����� */
      }
} /* end of Quick_Sort */


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
	Quick_Sort(1,n);
	puts("\nThe sequence after quick_sort is:");
	for(i=1;i<=n;i++)
		printf("%4d",R[i]);
	puts("\n Press any key to quit...");
	getch();
	
}