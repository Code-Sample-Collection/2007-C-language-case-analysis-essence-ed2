#include<stdio.h>
void main()
{
    long mul,number,k,ll,kk,n;
    clrscr();
    puts("============================================================");
    puts("||    This program will find the automorphic numbers.     ||");
    puts("|| The defination of a automorphic number is: the mantissa||");
    puts("||     of a natural number's square equals to itself.     ||");
    puts("||       e.g., 25^2=625, 76^2=5776, 9376^2=87909376.      ||");
    puts("============================================================");
    printf("\n >> Please input the scale n you want to find : ");
    scanf("%ld",&n);
    printf("\n >> The automorphic numbers small than %ld are:\n\n",n);
    for(number=0;number<n;number++)
    {
        for(mul=number,k=1;(mul/=10)>0;k*=10);
                   /*��number��λ��ȷ����ȡ���ֽ��г˷�ʱ��ϵ��k*/
        kk=k*10;      /*kkΪ��ȡ���ֻ�ʱ��ϵ��*/
        mul=0;        /*�������nλ*/
        ll=10;        /*llΪ��ȡ������Ӧλʱ��ϵ��*/
        while(k>0)
        {
            mul=(mul+(number%(k*10))*(number%ll-number%(ll/10)))%kk;
                 /*(���ֻ�+��ȡ�������ĺ�Nλ*��ȡ�����ĵ�Mλ)��%kk�ٽ�ȡ���ֻ�*/
            k/=10;               /*kΪ��ȡ������ʱ��ϵ��*/
            ll*=10;
        }
        if(number==mul)         /*�ж���Ϊ�����������*/
            printf("%ld   ",number);
    }
    puts("\n\n >> Press any key to quit...");
    getch();
}
