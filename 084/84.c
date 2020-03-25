#include<stdio.h>
#include<math.h>
int number[210][5];     /*��ſ��������������ֽ��ĸ�λ����*/
int select[110];        /*���Է��ھ����һ�к����һ�е��������±�*/      
int array[4][5];        /*4X4�ľ���ÿ��0��Ԫ�ش����������Ӧ�������±�*/
int count;              /*������������Ŀ*/
int selecount;          /*���Է��ھ����һ�к����һ�еĿ�����������Ŀ*/
int larray[2][200];     /*�������ǰ������λ������ʱ��������Ӧ������������*/
int lcount[2];
int num(int number);
int ok(int number);
void process(int i);
void copy_num(int i);
int comp_num(int n);
int find1(int i);
int find2(void);
int find0(int num);
void p_array(void);

FILE *fp;
void main()
{
    int i,k,flag,cc=0,i1,i4;
    clrscr();
    if((fp=fopen("Exa70data.dat","w+"))==NULL)
    {
	printf("\n Can't create file Exa70data.dat !\n");
	exit(0);
    }
    printf("there are magic squares with invertable primes as follw:\n");
    for(i=1001;i<9999;i+=2)                 /*�����������Ŀ�������*/
    {
        k=i/1000;
        if(k%2!=0&&k!=5&&num(i))     /*�����������ĵ�һλ����ż����5*/
        {
            number[count][0]=i;      /*��������*/
            process(count++);        /*�ֽ������ĸ�λ����*/
            if(number[count-1][2]%2!=0&&   /*����������������ھ����һ��*/
               number[count-1][3]%2!=0&&   /*�����һ�е���������¼����������*/
               number[count-1][2]!=5&&     /*�±꣬��������1*/
               number[count-1][3]!=5)
                select[selecount++]=count-1;
        }
    }
    larray[0][lcount[0]++]=number[0][0]/100;     /*��ʱ����ĵ�һ�д�ǰ��λ*/
    larray[1][lcount[1]++]=number[0][0]/10;      /*��ʱ����ĵڶ��д�ǰ��λ*/
    for(i=1;i<count;i++)                /*���������ظ���ǰ������λ������ʱ������*/
    {
        if(larray[0][lcount[0]-1]!=number[i][0]/100)
            larray[0][lcount[0]++]=number[i][0]/100;
        if(larray[1][lcount[1]-1]!=number[i][0]/10)
            larray[1][lcount[1]++]=number[i][0]/10;
    }
    for(i1=0;i1<selecount;i1++)                    /*�ڵ�һ������Ļ��Χ�����*/
    {
        array[0][0]=select[i1];                    /*ȡ��Ӧ�������±�*/
        copy_num(0);                               /*���Ʒֽ������*/
        for(array[1][0]=0;array[1][0]<count;array[1][0]++)    /*��ٵڶ���*/
        {
            copy_num(1);                /*���Ʒֽ������*/
            if(!comp_num(2))
                continue;         /*��ÿ�е�ǰ��λ�������������ì�ܣ�����̽��һ����*/
            for(array[2][0]=0;array[2][0]<count;array[2][0]++)     /*��ٵ�����*/
            {
                copy_num(2);           /*���Ʒֽ������*/
                if(!comp_num(3))
                    continue;          /*��ÿ�е�ǰ��λ�������������ì�ܣ�����̽��һ����*/
                for(i4=0;i4<selecount;i4++)     /*�����һ������ķ�Χ�����*/
                {
                    array[3][0]=select[i4];
                    copy_num(3);                /*���Ʒֽ������*/
                    for(flag=1,i=1;flag&&i<=4;i++)    /*�ж�ÿ���Ƿ��������*/
                        if(!find1(i))flag=0;
                    if(flag&&find2())            /*�ж϶Խ����Ƿ�Ϊ��������*/
		    {  	printf("No.%d\n",++cc);
			fprintf(fp,"No.%d\n",cc);
			p_array();
		    }    /*����÷�����*/
                }
            }
        }
    }
    fclose(fp);
    puts("\n Press any key to quit...");
    getch();
}

int num(int number)              /*�ж��Ƿ��������*/
{
    int j;
    if(!ok(number)) return 0;
    for(j=0;number>0;number/=10)       /*��������Ϊ������*/
        j=j*10+number%10;
    if(!ok(j)) return 0;           /*�жϷ������Ƿ�Ϊ����*/
    return 1;
}

int ok(int number)                /*�ж��Ƿ�Ϊ����*/
{
    int i,j;
    if(number%2==0) return 0;
    j=sqrt((double)number)+1;
    for(i=3;i<=j;i+=2)
        if(number%i==0) return 0;
    return 1;
}

void process(int i)                 /*����i�������ֽ�Ϊ���ֲ���������*/
{
    int j,num;
    num=number[i][0];
    for(j=4;j>=1;j--,num/=10)
        number[i][j]=num%10;
}

void copy_num(int i)        /*��array[i][0]ָ��������ĸ�λ���ָ��Ƶ�array[i]��*/
{
    int j;
    for(j=1;j<=4;j++)
	array[i][j]=number[array[i][0]][j];
}

int comp_num(int n)           /*�ж�array��ÿ�е�ǰnλ�Ƿ���������������ǰnλì��*/
{
    static int ii;           /*���ڲ���̬��������ǰһ�β��ҵ���Ԫ���±�*/
    static int jj;    /*ii:ǰһ�β���ǰ��λ���±꣬jj:ǰһ�β���ǰ��λ���±�*/
    int i,num,k,*p;   /*p:ָ���Ӧ��Ҫʹ�õ�ǰһ���±�ii��jj*/
    int *pcount;      /*pcount:ָ��Ҫʹ�õ���ʱ���������ļ�����*/
    switch(n){               /*����n��ֵѡ���Ӧ��һ����Ʊ���*/
        case 2:pcount=&lcount[0];p=&ii;break;
        case 3:pcount=&lcount[1];p=&jj;break;
        default:return 0;
    }
    for(i=1;i<=4;i++)          /*�����зֱ���д���*/
    {
        for(num=0,k=0;k<n;k++)       /*����ǰnλ���ִ������ֵ*/
            num=num*10+array[k][i];
        if(num<=larray[n-2][*p])     /*��ǰһ�������ҵ���Ԫ�ؽ��бȽ�*/
            for(;*p>=0&&num<larray[n-2][*p];(*p)--);/*��ǰ�β��ҵ���Ԫ�ش�����ǰ��*/
        else
            for(;p<pcount&&num>larray[n-2][*p];(*p)++);  /*���������*/
        if(*p<0||*p>=*pcount)
        {
            *p=0; return 0;
        }
        if(num!=larray[n-2][*p])
            return 0;            /*ǰnλ���ǿ������������ֵ�򷵻�0*/
    }
    return 1;
}

int find1(int i)               /*�ж��з����Ƿ��ǿ�������*/
{
    int num,j;
    for(num=0,j=0;j<4;j++)
        num=num*10+array[j][i];
    return find0(num);
}
int find2(void)                /*�ж϶Խ��߷����Ƿ��ǿ�������*/
{
    int num1,num2,i,j;
    for(num1=0,j=0;j<4;j++)
        num1=num1*10+array[j][j+1];
    for(num2=0,j=0,i=4;j<4;j++,i--)
        num2=num2*10+array[j][i];
    if(find0(num1)) return(find0(num2));
    else return 0;
}

int find0(int num)               /*�����Ƿ�Ϊ����Ҫ��Ŀ�������*/
{
    static int j;
    if(num<=number[j][0])for(;j>=0&&num<number[j][0];j--);
    else for(;j<count&&num>number[j][0];j++);
    if(j<0||j>=count){ j=0;return 0; }
    if(num==number[j][0]) return 1;
    else return 0;
}

void p_array(void)                /*�������*/
{
    int i,j;
    for(i=0;i<4;i++)
    {
	for(j=1;j<=4;j++)
	{
		printf("%d ",array[i][j]);
		fprintf(fp,"%d ",array[i][j]);
	}
	printf("\n");
	fprintf(fp,"\n");
    }
}
