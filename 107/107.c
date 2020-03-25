/* ��BC31�±��� ��VC6.0*/
/* compile under Borland C++ 3.1 or Visual C++ 6.0*/

/*#include "stdafx.h"*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"

#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100/*�洢�ռ��ʼ������*/
#define STACKINCREMENT 20/*�洢�ռ��������*/

typedef struct
{
	int *pBase;/*�ڹ���֮ǰ������֮��,base��ֵΪNULL*/
	int *pTop;/*ջ��ָ��*/
	int StackSize;/*��ǰ�ѷ���Ĵ洢�ռ�,��Ԫ��Ϊ��λ*/
}Stack;

typedef int BOOLEAN;
 
char Operator[8]="+-*/()#";/*�Ϸ��Ĳ������洢���ַ�����*/
char Optr;/*������*/
int Opnd=-1;/*������*/
int Result;/*�������*/

/*���������ȹ�ϵ*/
char PriorityTable[7][7]=
{
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=','o'},
	{'>','>','>','>','o','>','>'},
	{'<','<','<','<','<','o','='},
};

//���ݶ���Ĳ�������
//����һ����ջ,�������ֵΪ0,���ʾ��ʼ��ʧ��
Stack InitStack()/*���Ǹ�Ч�ʵ͵ķ���*/
{
	Stack S;
	S.pBase=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S.pBase)
	{/*�ڴ����ʧ��*/
		printf("�ڴ����ʧ��,������ֹ����\n");
		exit(-1);
	}
	else
	{
		S.pTop=S.pBase;
		S.StackSize=STACK_INIT_SIZE;
	}
	return S;
}
//����ջS,S���ٴ���
void DestoryStack(Stack *S)
{
	if(S->pBase)
	{
		free(S->pBase);
		S->pTop=S->pBase=NULL;
        
	}
}
//��ջ����,����e����S��ջ��Ԫ��
//ע:����Ӧ�õ�����,���Բ����ջ�Ƿ�Ϊ��
int GetTop(Stack S)
{
	return *(S.pTop-1);
}
//����Ԫ��eΪ�µ�ջ��Ԫ��,����ɹ��򷵻�1,���򷵻�0
int Push(Stack *S,int e)
{
	if(S->pTop-S->pBase==S->StackSize)
	{//ջ��,׷�Ӵ洢�ռ�
		S->pBase=(int*)realloc(S->pBase,S->StackSize+STACKINCREMENT*sizeof(int));
		if(!S->pBase)
			return 0;//�洢����ʧ��
		S->pTop=S->pBase+S->StackSize;
		S->StackSize+=STACKINCREMENT;
	}
	*(S->pTop++)=e;
	return 1;
}

int Pop(Stack *S,int *e)
{//��ջ����,��ɾ��S��ջ��Ԫ��,��e ������ֵ,������1;���򷵻�0
	if(S->pTop==S->pBase)
		return 0;
	*e=*--(S->pTop);
	return 1;

}
//������������������ʵ��
//�Ƚ�������ѧ����operator_1,operator_2�ļ�������Ȩ,��������ȹ�ϵ���в�����Ӧ�Ĺ�ϵ������'<','=',��'>'
char CheckPriority(char operator_1,char operator_2)
{
	int i,j;//������ѯ��������ȹ�ϵ����±�
	//char *ptr;
	i=strchr(Operator,operator_1)-Operator;//�ҵ�������������ַ���Operators�е����λ��
	j=strchr(Operator,operator_2)-Operator;
	//����������ȹ�ϵ������Ӧֵ
	return PriorityTable[i][j];
}

BOOLEAN IsOperator(char ch)
{//�ж�һ���ַ��Ƿ�Ϊ�������
	if(strchr(Operator,ch))
		return TRUE;
	else 
		return FALSE;

}
//�Ӽ��̻������
void GetInput(void)
{
	char Buffer[20];//�������뻺����,�������������λ�������
	char ch;//��ż�������
	int index;//���Buffer���±�
	index=0;
	ch=getch();//�Ӽ��̶���һ���ַ�
	while(ch!=13&&!IsOperator(ch))
	{//���������ַ��ǻس������ǲ�����,ѭ������
		if(ch>='0'&&ch<='9')
		{//���ַ����Ե���Ļ
			printf("%c",ch);
			Buffer[index]=ch;
			index++;

		}
		ch=getch();
	}
	if(ch==13)
		Optr='#';//����ı��ʽ�Իس�������
	else
	{
		Optr=ch;
		printf("%c",ch);

	}
	if(index>0)
	{
		Buffer[index]='\0';
		Opnd=atoi((Buffer));
	}
	else
		Opnd=-1;//����֧�����븺��,��OpndΪ����ʱ,��ʾ������ַ�Ϊ������
}
//��������a+b֮��ı��ʽ,thetaΪ������,a,bΪ������
int Calc(int a,char theta,int b)
{
	switch(theta)
	{
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	default:
		if(b==0)//����Ϊ������
		{
			printf("��������Ϊ");
			return 0;//����0������ʾ
		}
		else
			return a/b;
	}
}
/*���ʽ��ֵ*/
BOOLEAN EvaluateExpression()
{
	int temp;//��ʱ����
	char theta;//��Ų������ı���
	int itheta;//��ų�ջ�Ĳ������ı���add by me
	int a,b;//��ű��ʽ����ʱ���м�ֵ
	int topOpnd;//ջ��������
	char topOptr;//ջ��������
	
	Stack OPTR=InitStack();//������ջ
	Stack OPND=InitStack();//������ջ

	if(!Push(&OPTR,'#'))//������ջ�еĵ�һ��Ϊ#�ַ�
		return FALSE;

	GetInput();//�Ӽ��̻������

	while(Optr!='#'||GetTop(OPTR)!='#')
	{//���Optr>=0,��ʾ�в���������
		if(Opnd>=0)Push(&OPND,Opnd);
		switch(CheckPriority(GetTop(OPTR),Optr))
		{
		case '<'://ջ��Ԫ������Ȩ��
			if(!Push(&OPTR,Optr))return FALSE;
				GetInput();
			break;
		case '='://�����Ų����ռ�������
			Pop(&OPTR,&temp);GetInput();
			break;
		case '>'://��ջ������������ջ
			//����itheta�õ��������ڸ���theta
			Pop(&OPTR,&itheta);
			Pop(&OPND,&b);
			Pop(&OPND,&a);
			theta = (char)( itheta );
			Push(&OPND,Calc(a,itheta,b));
			Opnd=-1;
			break;

		}
	}
	//���㷨��,������ֻ��һ��������Ȼ�������س���ʱ,
	//OPND.pTop==OPND.pBase
	//���OPND.pTop==OPND.pBase����Opnd<0,��˵���û�
	//δ�����κβ����Ͳ�������ֱ������[�س�],����ֱ��
	//�˳�����
	if(OPND.pTop==OPND.pBase&&Opnd<0)
	{
		printf("\n\n��лʹ��!\n");
		exit(1);

	}
	else if(OPND.pTop==OPND.pBase)
		Result=Opnd;
	else
	{
		Result=GetTop(OPND);
		DestoryStack(&OPND);
		DestoryStack(&OPTR);
	}
	return TRUE;

}

void Message(void)
{
	printf("\n����������ʽ��ֵ��ʾ\n");
	printf("-------------------------------\n");
	printf("ʹ�÷���:��Ӽ�����ֱ��������ʽ,�Իس�������.��45*(12-2)[�س�]\n");
	printf("ע0:�������κ�����ֱ�Ӱ�[�س�]��,���˳�����.\n");
	printf("ע1:��������ʱ�����ܳ����ּ������������֮����κ�������������.\n");
	printf("ע2:��������ʱֻ�ܴ�����ȷ�ı��ʽ,��֧�����븺��.\n");
	printf("-------------------------------\n\n");
}
void main(void)
{
	int i;//����һЩ˵������Ϣ
	Message();
	for(i=1;;i++)
	{
		printf("���ʽ%d:",i);
		if(EvaluateExpression())
			printf("=%d\n",Result);
		else
			printf("��������������\n");
		
	}
}
