#include <stdio.h>
#include <malloc.h>
#define  N 7                                         //����N=7����ʾ��7������Ԫ
#define  OVERFLOW  0
#define  OK  1
typedef struct LNode{                              //��������ṹ
	int password;
	int order;
	struct LNode *next;
}LNode,*LinkList;

int  PassW[N]={3,1,7,2,4,8,4};
void  Joseph(LinkList p,int m,int x);          //��������
int main()
{    
	int  i,m;
	LinkList  Lhead,p,q;     //��������ָ������ṹ��ָ��
	Lhead=(LinkList)malloc(sizeof(LNode));  //��ʼ��ͷ�ڵ�
	if(!Lhead)return OVERFLOW;                   //����ռ�ʧ�ܷ���
	Lhead->password=PassW[0];
	Lhead->order=1;
	Lhead->next=NULL;
	p=Lhead;
	for(i=1;i<7;i++){
		if(!(q=(LinkList)malloc(sizeof(LNode))))return OVERFLOW;
		q->password=PassW[i];                      //��ʼ��ѭ���б��е�����ֵ
		q->order=i+1;
		p->next=q;p=q;                 //�´���һ��ָ��ڵ㲢ʹp->nextָ����,��ʹp=q
	}
	p->next=Lhead;                        //ʹp->nextָ��ͷ�ڵ�,�Ӷ��γ�ѭ������
	printf("�������һ�μ���ֵm:  \n");
	scanf("%d",&m);                                      //�û������һ�μ���ֵm
	printf("��һ�μ���ֵm= %d \n",m);
	Joseph(p,m,N);
    return OK;
}
void  Joseph(LinkList p,int m,int x){
	LinkList q;
	int i;
	if(x==0)return;                          //������û�нڵ�Ļ�,����������һ�㺯��
	q=p;
	m%=x;                                  //m��x����,�Ӷ���������еĵڼ�����Ԫ������ڵ�
	if(m==0)m=x;               //��m�պÿ�������x,����m=x,��Ϊ���m=0,�򲻽�����һ��
	//forѭ��,�������޷�ʹqָ��Ҫɾ���ڵ�,pָ�����ĵ�ǰһ�ڵ�,�������޷�����ɾ������  
	for(i=1;i<=m;i++){
		p=q;
		q=p->next;                    //ʹqָ��Ҫɾ���Ľڵ�,pָ��q��ǰһ���ڵ�
	}
	p->next=q->next;                              //��ѭ��������ɾ��qָ��Ľڵ�
	i=q->password;
	printf("%d  ",q->order);                     
	free(q);                                        //�ͷ�qָ��Ŀռ�
	Joseph(p,i,x-1);
}
