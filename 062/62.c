#include <stdio.h>
#include <string.h>

char c_je[51];  /*��д����ַ�����*/

char* zh( x )                     /*���ֽ��ת��Ϊ��д����ӳ���*/
double x;                          /*Ҫת���Ľ����*/
{
	int i, n, bz;
	char je[14];        /*���ֽ����ַ�����*/
	char temp[13];
	char f1[10][3] = {"��","Ҽ","��","��","��","��",
	                  "½","��","��","��"}; /*���ֶ�Ӧ�Ĵ�д�������*/
	char f2[11][3] = {"��","Ǫ","��","ʰ","��",
	                  "Ǫ","��","ʰ","Ԫ","��","��"}; /*ÿλ���ֶ�Ӧ��λ�������*/
	sprintf( je, "%.01f", 100*x); /*ת�����ַ�*/
	n = strlen( je );
	c_je[0] = '\0';
	bz  = 1;
	for( i = 0; i < n; i++ )
	{
		strcpy( temp, &je[i] );  /*���Ƶ���ʱ����*/
		if( atoi(temp)==0)    /*�жϵ�iλ���Ƿ�ȫΪ0*/
		{
			bz = 2;
			break;
		}
		if( je[i] != '0' )
		{
			if( bz == 0 )
				strcat( c_je, f1[0] );
			strcat( c_je, f1[je[i] - '0'] ); /*���ִ�ת���ַ���*/
			bz = 1;
			strcat( c_je, f2[13-n+i]);
		}
		else
		{
			if( n-i == 7 && (je[i-1]!='0'||je[i-2]!='0' || je[i-3]!='0')) /*�ж���λλ��*/
				strcat( c_je, "��" );
			if( n-i == 3 ) /*�жϸ�λ����Ԫλ��*/
				strcat( c_je, "Ԫ");
			bz = 0;
		}
	}
	if( bz == 2 )
	{
		if( n-i >= 7 && n-i < 10 )
			strcat( c_je, "��") ; /*��λ����Ϊ0���ӡ���*/
		if( n-i >= 3 )
			strcat( c_je, "Ԫ");
		strcat( c_je, "��" ); /*����Ƿ�λ���ӡ�����*/
	}
	return c_je; /*���ش�д���*/
}

main()
{
	double count;
	//clrscr();
	printf("*********************************************************\n");
	printf("*                                                       *\n");
	printf("*           ���ֽ��ת��Ϊ��д������ Ver.1.0          *\n");
	printf("*                                                       *\n");
	printf("*                                By RZLIN               *\n");
	printf("*                                                       *\n");
	printf("*               ������Ҫת���Ľ�                    *\n");
	printf("*                     ");
	scanf("%lf", &count );
	printf("*           ������Ľ��Ϊ��%10.2lf ��               *\n",count);
	printf("*                                                       *\n");
	printf("*ת��Ϊ��д����ǣ�%s\n", zh( count ) );
	printf("*                                                       *\n");
	puts("*                �밴������˳�...                      *");
	printf("*********************************************************\n");
	getch();
}