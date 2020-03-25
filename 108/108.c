/* ��BC31�±��� */
/* compile under Borland C++ 3.1 */

/*
����������������ȡ����ʽ�����ʽ(����ʽ)
<exp> -> <term> { <addop> <term> }
<addop> -> + | -
<term> -> <factor> { <mulop> <factor> }
<mulop> -> * | /
<factor> -> ( <exp> ) | Number
*/

#include <stdio.h>
#include <stdlib.h>

char token; /*ȫ�ֱ�־����*/

/*�ݹ���õĺ���ԭ��*/
int exp( void );
int term( void );
int factor( void );

void error( void ) /*���������Ϣ�ĺ���*/
{
	fprintf( stderr, "����\n");
	exit( 1 );
}

void match( char expectedToken ) /*�Ե�ǰ�ı�־����ƥ��*/
{
	if( token == expectedToken ) token = getchar(); /*ƥ��ɹ�����ȡ��һ����־*/
	else error(); /*ƥ�䲻�ɹ����������*/
}
void Message(void)
{
	printf("================================================================\n");
	printf("*               �ݹ�ʵ�ֵ�����������ʽ��ֵ����               *\n");
	printf("****************************************************************\n");
	printf("ʹ�÷���:��Ӽ�����ֱ��������ʽ,�Իس�������.��45*(12-2)[�س�]\n");
	printf("*****************************************************************\n\n");
}
main()
{
	int result;  /*����Ľ��*/
	Message();
	printf(" >> ��������ʽ: ");
	token = getchar(); /*�����һ������*/
	
	result = exp(); /*���м���*/
	if( token == '\n' ) /* �Ƿ�һ�н��� */
		printf( " >> ���ʽ�ļ�����Ϊ : %d\n", result );
	else error(); /* ������������ַ� */
	puts("\n\n                  �밴������˳� ...\n");
	getch();
	return 0;
}

int exp( void )
{
	int temp = term(); /*����ȼӼ��������ȼ���ߵĲ���*/
	while(( token == '+' ) || ( token == '-' ))
		switch( token ) {
		case '+': match('+');     /*�ӷ�*/
			  temp += term();
			  break;
		case '-': match('-');
			  temp -= term(); /*����*/
			  break;
		}
	return temp;
}

int term( void )
{
	int div; /*����*/
	int temp = factor();   /*����ȳ˳��������ȼ���ߵĲ���*/
	while(( token == '*' ) || ( token == '/' ))
		switch( token ) {
		case '*': match('*');  /*�˷�*/
			  temp *= factor();
			  break;
		case '/': match('/');   /*����*/
			  div = factor();
			  if( div == 0 ) /*��Ҫ�жϳ����Ƿ�Ϊ0*/
			  {
			  	fprintf( stderr, "����Ϊ0.\n" );
			  	exit(1);
			  }
			  temp /= div; 
			  break;
		}
	return temp;
}

int factor( void )
{
	int temp; 
	if( token == '(' ) /*�������ŵ�����*/
	{
		match( '(' );
		temp = exp();
		match(')');
	}
	else if ( isdigit( token )) /*ʵ�ʵ�����*/
	{
		ungetc( token, stdin ); /*��������ַ��˻���������*/
		scanf( "%d", &temp ); /*��������*/
		token = getchar();  /*������ǰ�ı�־*/
	}
	else error(); /*��������Ҳ��������*/
	return temp;
}