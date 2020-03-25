#include   <stdio.h> 
#include   <string.h> 
#include   <stdlib.h> 
#include   <conio.h> 
 
/*����ȫ�ֱ���*/ 
#define   TRUE   1 
#define   FALSE   0 
#define   OK   1 
#define   ERROR   0 
#define   NULL   0 
#define   OVERFLOW   -2 
#define   MAXSIZE   100 
#define   stack_init_size   100 
#define   stackincrement   10 
typedef   char   selemType; 
typedef   char   qelemType; 
typedef   char   elemType; 
typedef   int   status; 
char   e;     
char   demon[MAXSIZE];
     
/* ���ͼ����������*/   
typedef   struct   
{   
	selemType   *base; 
	selemType   *top; 
	int   stacksize; 
}sqstack;     
status   initstack   (sqstack   *s) 
{     
	s->base=(selemType   *)malloc(stack_init_size*sizeof(selemType));     
	if(!s->base)   exit   (OVERFLOW); 
	s->top=s->base; 
	s->stacksize=stack_init_size; 
	return   OK; 
}/*����ջ*/ 
status   push   (sqstack   *s,selemType   e) 
{ 
	if(s->top-s->base>=s->stacksize) 
	{ 
		s->base=(elemType*)   realloc(s->base,(s->stacksize+stackincrement)*sizeof(elemType))     
		if(!s->base)   exit(OVERFLOW); 
		s->top=s->base+s->stacksize; 
		s->stacksize+=stackincrement; 
	} 
	*(s->top++)=e; 
	return   OK; 
}/*��ջ*/ 
status   pop(sqstack   *s,selemType   *e) 
{     
	if(s->top==s->base)   return   ERROR; 
	*e=*(--(s->top)); 
	return   OK; 
}/*��ջ*/ 
/*�������ͼ����������*/ 
typedef   struct   qnode 
{ 
	qelemType   data; 
	struct   qnode   *next; 
}qnode,*queueptr; 
typedef   struct 
{ 
	queueptr   front; 
	queueptr   rear; 
}linkqueue; 
status   initqueue(linkqueue   *q) 
{ 
	q->front=q->rear=(queueptr)malloc(sizeof(qnode)); 
	if(!q->front)   exit(OVERFLOW); 
	q->front->next=NULL; 
	return   OK; 
}/*��������*/ 
status   enqueue(linkqueue   *q,qelemType   e) 
{ 
	queueptr   p; 
	p=(queueptr)malloc(sizeof(qnode)); 
	if(!p)   exit(OVERFLOW); 
	p->data=e; 
	p->next=NULL; 
	q->rear->next=p; 
	q->rear=p; 
	return   OK; 
}/*���*/ 
status   dequeue(linkqueue   *q,qelemType   *e) 
{ 
	queueptr   p; 
	if(q->front==q->rear)   return   ERROR; 
	p=q->front->next; 
	*e=p->data; 
	q->front->next=p->next; 
	if(q->rear==p) 
	{ 
		q->rear=q->front; 
	} 
	free(p);
	return   OK;
}/*����*/ 
 /*������Ԫ����ջ������*/
void   tempstack(sqstack   *temps) 
{ 
	int   i=0; 
	char   t; 
	char   c;
	c=demon[i];
	for(i=0;c!='#';i++)/*��������*/
	{
		c=demon[i];
		if(c=='(')/*����������*/
		{
			t=demon[i+1];/*ȡ�����е�����ĸ*/
			push(temps,t);/*��ջ*/
			i++;/*ָ������ĸ*/
			do 
			{ 
				i++; 
				c=demon[i]; 
				push(temps,c)/*��һ��ѭ��������ĸ��ջ*/; 
				push(temps,t);/*�ٽ�����ĸ��ջ*/ 
			}while(c!=')');/*ֱ��������Ԫ��ȫ����ջ*/ 
			pop(temps,&t);/*�������ջ������ĸt��ջ*/ 
			pop(temps,&t);   /*�������ջ��')'��ջ*/ 
		} 
	} 
}/*��ʱջ*/ 

 /*������Ӻ���*/
void   spenqueue(linkqueue   *q,char   key)     
{     
	int   j=0;
	char   a[5]; 
	switch(key)   /*�жϴ�д��ĸ��Ӧ���ַ���*/ 
	{ 
	case'A':strcpy(a,"ase");break; 
	case'B':strcpy(a,"tAdA");break;
	case'C':strcpy(a,"abc");break; 
	case'D':strcpy(a,"def");break; 
	case'E':strcpy(a,"ghi");break; 
	case'F':strcpy(a,"klm");break; 
	case'H':strcpy(a,"mop");break; 
	default:strcpy(a,"???");   /*���ܷ����ħ��������"???"���*/ 
	} 
	while(a[j]!='\0')   /*������黹����ĸ*/ 
	{ 
		enqueue(q,a[j]);/*����*/ 
		j++; 
	} 
}/*�������*/ 
/*������Ӵ�����*/ 
status   sort(sqstack   *s,linkqueue   *q) 
{     
	qnode   b; 
	int   flag=0;/*��д��ĸ����������*/ 
	int   i; 
	for(i=0;demon[   i]!='#';i++)/*��������*/ 
	{ 
		b.data=demon[   i]; 
		if(   ('a'<=b.data&&b.data<='z')||b.data=='?')   /*�����Сд��ĸ����'?'����ֱ�ӽ�ջ*/     
		{ 
			enqueue(q,b.data); 
		} 
		else 
		{ 
			if('A'<=b.data&&b.data<='Z')   /*����Ǵ�д��ĸ,����������ջ����,*/     
			{ 
				spenqueue(q,b.data); 
				flag=1;   /*���ִ�д��ĸ��������1*/ 
			} 
			else 
			{ 
				if(b.data=='(')/*���������*/ 
				{
					do 
					{ 
						pop(s,&e); 
						enqueue(q,e); 
					}while(!(s->top==s->base));   /*ֻҪջ��Ϊ��,���ջ����*/     
					while   (b.data!=')')   /*ֻҪ��ָ��������Ԫ��,�ͼ���������,��֤ԭ�����ڵ�Ԫ�ز��ٽ�ջ*/ 
					{ 
						i++; 
						b.data=demon[i]; 
					} 
				} 
			} 
		} 
	}
	return   flag; 
}/*����*/
/*������*/
status   main() 
{ 
	sqstack   s1; 
	linkqueue   q1; 
	int   k=0; 
	int   flag=1; 
	clrscr(); 
	printf("Please   Input   the   Demon's   Words:\n"); 
	printf("!:   Less   Than   30   Letters:   )\n"); 
	printf("!:   End   with   '#':   )\n\t"); 
	scanf("%s",demon);
	printf("\n***************************************"); 
	initstack(&s1);   /*����ջ*/ 
	initqueue(&q1);   /*������*/ 
	tempstack(&s1);   /*���ú���*/ 
	while   (flag==1)   /*����д�д��ĸ*/ 
	{ 
		k=0; 
		flag=sort(&s1,&q1); 
		while(q1.front!=q1.rear)   /*��дdemon[i   ]*/ 
		{ 
			dequeue(&q1,&e); 
			demon[k]=e;
			k++;
		}
		demon[k]='#';
	}
	demon[k]='\0';
	printf("\n***************************************");
	printf("\nThe   Human   Words:\n\t%s",demon);
	printf("\n***************************************");
}
