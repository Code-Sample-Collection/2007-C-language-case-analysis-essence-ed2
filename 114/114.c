#include "stdlib.h"
#include "math.h"
#include "stdio.h"

#define MAX 255

int Guass(a,b,n)
int n;
double a[],b[];
{
	int *js,l,k,i,j,is,p,q;
	double d,t;
	js=malloc(n*sizeof(int));
	l=1;
	for (k=0;k<=n-2;k++)
	{
		d=0.0;
		/*�����ǻ���Ԫ���֣�����ϵ������A�ĵ�K�У���K��֮�µĲ���ѡ��
		����ֵ����Ԫ���������Խ����ϡ�*/
		for (i=k;i<=n-1;i++)
			for (j=k;j<=n-1;j++)
			{
				t=fabs(a[i*n+j]); /*fabs()������math.h�У���������һ���������ľ���ֵ��*/
				if (t>d) { d=t; js[k]=j; is=i;}
			}
		if (d+1.0==1.0) l=0;  /*��ԪΪ0*/
		/*��Ԫ��Ϊ0��ʱ��*/
		else
		{
			if (js[k]!=k)
				for (i=0;i<=n-1;i++)
				{
					p=i*n+k; q=i*n+js[k];
					t=a[p]; a[p]=a[q]; a[q]=t;
				}
			if (is!=k)
			{
				for (j=k;j<=n-1;j++)
				{
					p=k*n+j; q=is*n+j;
					t=a[p]; a[p]=a[q]; a[q]=t;
				}
				t=b[k]; b[k]=b[is]; b[is]=t;
			}
		}
		if (l==0)
		{
			free(js); printf("fail\n");
			return(0);
		}
		d=a[k*n+k];
		/*����Ϊ��һ������*/
		for (j=k+1;j<=n-1;j++)
		{
			p=k*n+j; a[p]=a[p]/d;
		}
		b[k]=b[k]/d;
		/*����Ϊ����A,B��Ԫ����*/
		for (i=k+1;i<=n-1;i++)
		{
			for (j=k+1;j<=n-1;j++)
			{
				p=i*n+j;
				a[p]=a[p]-a[i*n+k]*a[k*n+j];
			}
			b[i]=b[i]-a[i*n+k]*b[k];
		}
	}

	d=a[(n-1)*n+n-1];
	/*�����޽�������޶��*/
	if (fabs(d)+1.0==1.0)
	{
		free(js); printf("�þ���Ϊ�������\n");
		return(0);
	}
	b[n-1]=b[n-1]/d;
	/*����Ϊ������Ԫ*/
	for (i=n-2;i>=0;i--)
	{
		t=0.0;
		for (j=i+1;j<=n-1;j++)
			t=t+a[i*n+j]*b[j];
		b[i]=b[i]-t;
	}
	js[n-1]=n-1;
	for (k=n-1;k>=0;k--)
		if (js[k]!=k)
		{ t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;}
	free(js);
	return(1);
}

main()
{
	int i,n;
	double A[MAX];
	double B[MAX];
	clrscr();
	puts("This is a program to solve N order linear equation set Ax=B.");
	puts("\n It use Guass Elimination Method to solve the equation set:");
	puts("\n    a(0,0)x0+a(0,1)x1+a(0,2)x2+...+a(0,n-1)xn-1=b0");
	puts("    a(1,0)x0+a(1,1)x1+a(1,2)x2+...+a(1,n-1)xn-1=b1");
	puts("    ......");
	puts("    a(n-1,0)x0+a(n-1,1)x1+a(n-1,2)x2+...+a(n-1,-1)xn-1=bn-1\n");
	printf(" >> Please input the order n (>1): ");
	scanf("%d",&n);
	printf(" >> Please input the %d elements of matrix A(%d*%d) one by one:\n",n*n,n,n);
	for(i=0;i<n*n;i++)
		scanf("%lf",&A[i]);
	printf(" >> Please input the %d elements of matrix B(%d*1) one by one:\n",n,n);
	for(i=0;i<n;i++)
		scanf("%lf",&B[i]);
	if (Guass(A,B,n)!=0) /*����Guass��ȥ��1Ϊ����ɹ�*/
	printf(" >> The solution of Ax=B is x(%d*1):\n",n);

	for (i=0;i<n;i++) /*��ӡ���*/
		printf("x(%d)=%f  ",i,B[i]);
	puts("\n Press any key to quit...");
	getch();
}

