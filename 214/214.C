/*
ģ��ɨ����Ϸ  
*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>

union REGS regs;
int size=15;/*���ڱ�ʾÿ������Ĵ�С(�����εı߳�)*/
int pix,piy=50;/*pix,piy�Ǿ����ƫ����*/
char b[2]="1";/*������ʾ������Χ���׵ĸ���*/
int pan[30][16];/*���ڼ�¼����������0��û�С�9�����ס�1~8����Χ�׵ĸ���*/
int pan1[30][16];/*pan1[][]��¼��ǰ�����������0��û�в�����1�����ˡ�2�������*/
int tt;/*��¼ʱ�����*/
int Eflags;/*���ڱ����갴ť����Ч�ԣ�0����Ч��1����Ч��2����������������������¿�ʼ*/

int Msinit();
void Draw(int x,int y,int sizex,int sizey);
void Facedraw(int x,int y,int sizel,int k);
void Dead(int sizel,int x,int y);
void Setmouse(int xmax,int ymax,int x,int y);
int Msread(int *xp,int *yp,int *bup,struct time t1,int k);
void Draw1(int x,int y);
int Open(int x,int y);
float Random();
void Have(int sum,int x,int y,int xx,int yy);
void Help();
void Coread();
void Ddraw2(int x,int y);


/*������������*/
main()
{
 int mode=VGAHI,devices=VGA;/*ͼ��ģʽ��ʼ���ı���*/
 char ams;                  /*�������еı�־����*/
 int xms,yms,bms;           /*����״̬����*/
 int i,j,k,k1=0;            /*i,j,k��ѭ������*/
 int x=9,y=9,flags=0;       /*x,y����Ĵ�С*/
 int sum=10;                /*sum ������׵�����Ŀ���Ǹ�x,y�ĺ���*/
 int x1=0,y1=0;             /*���ڼ�¼��굱ǰ��λ��*/
 int x11=0,y11=0;           /*��ʱ�������λ�õ�ֵ*/
 int sizel=10;              /*���Ĵ�С*/
 int cflags=1;      /*���ǲ˵�������־����,û�е���1,����0*/
 struct time t1={0,0,0,0};  /*ʱ��ṹ�壬ͷ�ļ��Ѷ���*/
 int co[3];      /*��ʱ��¼��ʷ��¼*/
 void far *Map;      /*���ڱ������ͼƬ*/
 char name[3][20];     /*�����ַ��������ڼ�¼����*/
 FILE * p;      /*�ļ�ָ�������ļ�����*/

 Msinit();                              /*����ʼ��*/
 /*registerbgidriver(EGAVGA_driver);*/
 initgraph(&devices,&mode,"C:\\tc");      /*ͼ��ģʽ��ʼ��*/

/*ΪͼƬָ������ڴ�*/
if((Map=farmalloc(imagesize(0,0,20,20)))==NULL)/*ͼƬ�Ĵ�С��20*20*/
 {
  printf("Memory ererr!\n");
  printf("Press any key to out!\n");
  exit(1);
 }

 /*���ڼ����ļ��Ƿ�����*/
  while((p = fopen("score.dat", "r")) == NULL) /*������ܴ򿪾��½�һ��*/
   {
  if((p = fopen("score.dat", "w")) == NULL)/*��������½�����ʾ�����Ƴ�*/
  {
   printf("The file cannot open!\n");
   printf("Presss any key to exit!\n");
   getch();
        exit(1);
  }
  /*д���ʼ����*/
  fprintf(p,"%d %d %d,%s\n%s\n%s\n",999,999,999,"xiajia","xiajia","xiajia");
  fclose(p); 
 }
  /*��ʱ������ʷ��¼������co[3]��¼*/
  fscanf(p,"%d %d %d,",&co[0],&co[1],&co[2]);
  for(i=0;i<3;i++)
  fscanf(p,"%s\n",name[i]);
  fclose(p);

 Setmouse(1,1,615,460);  /*�������Ļ��Χ*/
 pix=250-x*size/2;  /*������װ�ť��������*/

bss:    b[0]='1';        /*��Ϸ��ʼ�������������*/
       flags=0;  /*�����������������û�����ã�����Ϊ���߼�����������ʱ����*/
       k=0;
 Eflags=0;
 tt=0;
  cleardevice();/*����*/
  setbkcolor(LIGHTCYAN);
       for(i=0;i<30;i++)       /*�����ʼ��*/
       for(j=0;j<16;j++)
       {
  pan[i][j]=0;
         pan1[i][j]=0;
 }

 for(;;) /*���������׵��������*/
    {
  i=(int)(x*Random());
      j=(int)(y*Random());
      if(pan[i][j]==0)
         {
   pan[i][j]=9;
   k=k+1;
         }
      if(k==sum) break;
    } 

for(i=0;i<x;i++)/*����ͳ�Ƹ�����ܱ����*/
for(j=0;j<y;j++)
  {
  if(pan[i][j]==0)/*ֻ��û���׵Ĳ���Ҫ����*/
    {
      if(i-1>=0 && j-1>=0 && pan[i-1][j-1]==9) pan[i][j]++;
   if(j-1>=0 && pan[i][j-1]==9)     pan[i][j]++;
   if(i+1<x && j-1>=0 && pan[i+1][j-1]==9)  pan[i][j]++;
   if(i-1>=0 && pan[i-1][j]==9)     pan[i][j]++;
   if(i+1<x && pan[i+1][j]==9)     pan[i][j]++;
   if(i-1>=0 && j+1<y && pan[i-1][j+1]==9)  pan[i][j]++;
   if(j+1<y && pan[i][j+1]==9)     pan[i][j]++;
   if(i+1<x && j+1<y && pan[i+1][j+1]==9)   pan[i][j]++;
  }
 }

 if(sum==10)/*������*/
 {
  Draw(170,1,162,200);
  setcolor(1);
  outtextxy(175,5,"Game( )");
  setcolor(4);
  outtextxy(175,5,"     G");
 }/*С*/
 else
  if(sum==40)
  {
   Draw(115,1,272,307);
   setcolor(1);
   outtextxy(120,5,"Game(G)");
   setcolor(4);
   outtextxy(120,5,"     G");
  }/*��*/
     else
      if(sum==99)
    {
     Draw(40,1,470,307);
     setcolor(1);
     outtextxy(45,5,"Game(G)");
     setcolor(4);
     outtextxy(45,5,"     G");
    }/*��*/

 setcolor(1);/*��ʾ��ʾ��Ϣ*/
 outtextxy(100,350,"  : Help.");
 setcolor(4);
 outtextxy(100,350,"H");
 setcolor(1);
 outtextxy(200,350," /    : exit.");
 setcolor(4);
 outtextxy(200,350,"Q");
 outtextxy(220,350,"ESC");
 setcolor(1);
 outtextxy(330,350,"  : cores.");
 setcolor(4);
 outtextxy(330,350,"R");

 Facedraw(250,30,sizel,2);/*��ʾ���ư�ť������*/

 for(i=0;i<x;i++)/*��һ�������������*/
 for(j=0;j<y;j++)
 {
  Draw(i*size+pix,j*size+piy,size,size);
 }

 Have(sum,pix+20,30,x,y);/*����ĳ�ʼ��ʾ*/
 k=0;
 setfillstyle(1, 0);
 bar(460-pix,25,490-pix,40);
 setcolor(4);
 outtextxy(465-pix,30,"000");

/*������һ�����ڽ����û��Ŀ��ƣ���������Ӧ*/
 for(;;)
 {
  ams=Msread(&xms,&yms,&bms,t1,k);/*��ȡ���״̬*/

   /*����һ�����ڱ��沢��¼���ͼƬ*/
  if(flags!=0)
  {
   putimage(x11,y11,Map,COPY_PUT);
  }
  x11=xms;
  y11=yms;
  flags=1;

 /*�������˵�����*/
  if((xms>=pix-10 && xms<=pix+26 && yms>=2 && yms<=14 && bms==1) || ams=='g' || ams=='G')/*���в˵����ж�*/
  {
   Draw(pix-10,14,100,88); /*���˵�*/
   cflags=0;
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,19,"Restar(R)");
   setcolor(4);
   outtextxy(pix-4,19,"       R");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,30,"Easy(E)");
   setcolor(4);
   outtextxy(pix-4,30,"     E");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,41,"Nomall(N)");
   setcolor(4);
   outtextxy(pix-4,41,"       N");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,52,"Hard(H)");
   setcolor(4);
   outtextxy(pix-4,52,"     H");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,63,"Corse(C)");
   setcolor(4);
   outtextxy(pix-4,63,"      C");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,74,"Help(L)");
   setcolor(4);
   outtextxy(pix-4,74,"     L");
   setcolor(1);/*������ʾ�˵���*/
   outtextxy(pix-4,85,"Quit(Q)");
   setcolor(4);
   outtextxy(pix-4,85,"     Q");
   bms=0;
  }/*��ɲ˵������*/

 /*������Ϊ����ȫʵ�������Ʋż��������*/
 if(Eflags==2 && (bms!=0 || ams!=-1))
  {
      goto bss;
   }

 /*����ʵ�ֲ˵��Ĺ��ܣ�ÿһ����Ӧһ���˵���*/
 if(cflags==0)
  {
   if((xms>=pix-6 && xms<=pix+85 && yms>=17 && yms<=28 && bms==1)|| (ams=='r' || ams=='R'))/*����������Ӧ�˵��и���*/
   {
    cflags=1;
    goto bss;
   }
   else
    if((xms>=pix-6 && xms<=pix+85 && yms>=28 && yms<=39 && bms==1) || ams=='e' || ams=='E')
    {
     cflags=1;
     x=9;
     y=9;
     sum=10;
     pix=250-x*size/2;
     goto bss;
    }
    else
      if((xms>=pix-6 && xms<=pix+85 && yms>=39 && yms<=50 && bms==1) || ams=='n' || ams=='N')
     {
      cflags=1;
      x=16;
      y=16;
      sum=40;
      pix=250-x*size/2;
      goto bss;
     }
     else
       if((xms>=pix-6 && xms<=pix+85 && yms>=50 && yms<=61 && bms==1) || ams=='h' || ams=='H')
      {
       cflags=1;
       x=30;
       y=16;
       sum=99;
       pix=250-x*size/2+25;
       goto bss;
      }
      else
        if((xms>=pix-6 && xms<=pix+85 && yms>=61 && yms<=72 && bms==1) || ams=='c' || ams=='C')
       {
        cflags=1;
        Coread();
       }
        else
          if((xms>=pix-6 && xms<=pix+85 && yms>=72 && yms<=83 && bms==1) || ams=='l' || ams=='L')
       {
        cflags=1;
        Help();
       }
       else
         if((xms>=pix-6 && xms<=pix+85 && yms>=83 && yms<=94 && bms==1) || ams=='q' || ams=='Q' || ams==27)
        {
         cflags=1;
         fclose(p);
         closegraph();
         farfree(Map);
         exit(1);
        }
        else
          if(bms!=0)
         {
          cflags=1;
          goto bss;
         }
  }/*�����˵����ܵ�ʵ��*/
 /*��Ц����ť������ʱ���¿�ʼ*/
   if(cflags!=0 && xms >=250-sizel-2 && yms >= 30-sizel-2 && xms<=250+sizel+2 && yms<=30+sizel+2 && bms==1 )
  {
   goto bss;
  }
 
   if(Eflags==0 && cflags!=0 && xms-pix>=0 && yms-piy >=0 && xms<pix+x*size && yms<piy+y*size )/*111�ж�*/
  {
   x1=(int)((xms-pix)/size);/*�������Ŀǰ�İ�ťλ��*/
   y1=(int)((yms-piy)/size);

   if(ams==-1 && bms==1 && pan1[x1][y1]==0)/*����������*/
   {
    if(k==0)/*k�����ж��Ƿ��ǵ�һ�ΰ���.0:����ʱ��1:��ʼ��ʱ*/
    {
     gettime(&t1);
     k=1;
    }
    if(pan[x1][y1]!=9)
    {
     Draw1(x1,y1);
     Open(x,y);
    }
    else
    {
     Dead(sizel,x,y);
     k=0;
    }
   }

   if(ams==-1 && bms==2 && pan1[x1][y1]==0)/*��������Ҽ�*/
   {
    delay(100);
    setcolor(10);
    circle(x1*size+pix+7,y1*size+piy+7,4);
    pan1[x1][y1]=2;
    Have(sum,pix+20,30,x,y);
   }
   else
     if(ams==-1 && bms==2 && pan1[x1][y1]==2)/*��������Ҽ�*/
    {
     delay(100);
     Draw(x1*size+pix,y1*size+piy,size,size);
     pan1[x1][y1]=0;
     Have(sum,pix+20,30,x,y);
    }/*�൱������һ�*/

  if(ams==-1 && bms==3 && pan1[x1][y1]==1)
   {/*�൱�����˫��,��Ч���ж�*/
    i=0;
    if(x1-1>=0 && y1-1>=0 && pan1[x1-1][y1-1]==2) i++;
    if(y1-1>=0 && pan1[x1][y1-1]==2)i++;
    if(x1+1<x && y1-1>=0 && pan1[x1+1][y1-1]==2) i++;
    if(x1-1>=0 && pan1[x1-1][y1]==2) i++;
    if(x1+1<x && pan1[x1+1][y1]==2) i++;
    if(x1-1>=0 && y1+1<y && pan1[x1-1][y1+1]==2) i++;
    if(y1+1<y && pan1[x1][y1+1]==2) i++;
    if(x1+1<x && y1+1<y && pan1[x1+1][y1+1]==2) i++;
    if(i==pan[x1][y1])     /*��Ч*/
       {
      if(x1-1>=0 && y1-1>=0 && pan1[x1-1][y1-1]!=2) 
     {
      if(pan[x1-1][y1-1]!=9) 
       Draw1(x1-1,y1-1);
      else 
       {
        Dead(sizel,x,y); 
         k=0;
       }
     }
      if(y1-1>=0  && pan1[x1][y1-1]!=2)
     {
      if(pan[x1][y1-1]!=9)
       Draw1(x1,y1-1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
       }
     }
      if(x1+1<x && y1-1>=0 && pan1[x1+1][y1-1]!=2) 
     {
      if(pan[x1+1][y1-1]!=9) 
       Draw1(x1+1,y1-1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
       }
     }
      if(x1-1>=0  && pan1[x1-1][y1]!=2) 
     {
      if(pan[x1-1][y1]!=9) 
       Draw1(x1-1,y1);
      else 
        {
         Dead(sizel,x,y);
         k=0;
        }
     }
      if(x1+1<x && pan1[x1+1][y1]!=2) 
     {
      if(pan[x1+1][y1]!=9) 
       Draw1(x1+1,y1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
       }
     }
      if(x1-1>=0 && y1+1<y && pan1[x1-1][y1+1]!=2) 
     {
      if(pan[x1-1][y1+1]!=9)
        Draw1(x1-1,y1+1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
        }
     }
      if(y1+1<y && pan1[x1][y1+1]!=2)
      {
      if(pan[x1][y1+1]!=9) 
       Draw1(x1,y1+1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
       }
     }
      if(x1+1<x && y1+1<y &&pan1[x1+1][y1+1]!=2) 
     {
      if(pan[x1+1][y1+1]!=9) 
       Draw1(x1+1,y1+1);
      else 
       {
        Dead(sizel,x,y);
        k=0;
       }
     }
      Open(x,y);
         }
          }

   /*ʤ������*/
  k1=0;
  for(i=0;i<x;i++)
  for(j=0;j<y;j++)
   if(pan1[i][j]!=1) k1++;

  if(k1==sum)
   {
    for(i=0;i<x;i++)
    for(j=0;j<y;j++)
    if(pan1[i][j]==0) 
     {
      setcolor(10);circle(i*size+pix+7,j*size+piy+7,4);
     }

    Facedraw(250,30,sizel,3);
       
    if(x==9 && tt<co[0])  {j=0;co[0]=tt;i=0;}
    if(x==16 && tt<co[1]) {j=1;co[1]=tt;i=0;}
    if(x==30 && tt<co[2]) {j=2;co[2]=tt;i=0;}

    if(i==0)
    {
     Draw(10,10,300,55);
     setcolor(4);
     outtextxy(20,15,"You break the corse!");
     outtextxy(20,25,"Please input your name(0 - 19):");
     setfillstyle(1, 14);
     bar(20,35,200,50);
     for(i=0;i<19;i++)
     {
      name[j][i]=getch();
      if(name[j][i]==8) i=i-2;
      if(name[j][i]==13) {name[j][i]='\0';break;}
      name[j][i+1]='\0';
      setfillstyle(1, 14);
      bar(20,35,200,50);
      setcolor(1);
      outtextxy(20,40,name[j]);
     }

      if((p = fopen("score.dat", "w")) == NULL)
     {
      printf("The file cannot open!\n");
      exit(1);
     }
      fprintf(p,"%d %d %d,",co[0],co[1],co[2]);
     for(i=0;i<3;i++)
     fprintf(p,"%s\n",name[i]);
     fclose(p);
     Coread();
    }
    getch();
    goto bss;
      }
  }/*����111���ж�*/

  /*������һЩ��ݹ��ܼ��Ķ���*/
     if(ams=='q'||ams=='Q'|| ams==27 ) {fclose(p);closegraph();farfree(Map);exit(1);}   /*�˳��������Ψһ����*/
    if(ams=='c'||ams=='C') goto bss;   /*����*/
    if(ams=='h'||ams=='H') {Help();k=0;}  /*�����ĵ�*/
    if(ams=='r'||ams=='R') {Coread();k=0;} /*�쿴�ɼ�*/

  getimage(xms,yms,xms+20,yms+20,Map);
  Ddraw2(xms,yms);
  delay(10);
      }/*�������ѭ����ȡ����ѭ��*/
}
/*++++++++����������++++++++*/

/*�����������ʵ�����ĳ�ʼ��*/
int Msinit()
{
 int recored;
 regs.x.ax=0;
 int86 (0x33, & regs, & regs);
 recored=regs.x.ax;
 if(recored==0)
   {
  printf("Mouse not found or Mouse driver not installed.\n");
     return 0;
 }
  else
   return recored;
}

/*��������ӳ�����������һ����ť*/
void Draw(int x,int y,int sizex,int sizey)/* x, yΪ���Ͻ�����sizex,sizeyΪ���Ϳ�*/
{
 int sizx=sizex-1;
 int sizy=sizey-1;
 setcolor(15);/*��������ð�ɫ*/
 line(x,y,x+sizx-1,y);
 line(x,y+1,x+sizx-2,y+1);
 line(x,y,x,y+sizy-1);
 line(x+1,y,x+1,y+sizy-2);
 setcolor(8);/*������������ɫ*/
 line(x+1,y+sizy,x+sizx,y+sizy);
 line(x+2,y+sizy-1,x+sizx,y+sizy-1);
 line(x+sizx-1,y+1,x+sizx-1,y+sizy);
 line(x+sizx,y+2,x+sizx,y+sizy);
 setcolor(7);/*��������û�ɫ*/
 putpixel(x,y+sizy,3);
 putpixel(x+1,y+sizy-1,3);
 putpixel(x+sizx,y,3);
 putpixel(x+sizx-1,y+1,3);
 setfillstyle(1, 7);/*��������û�ɫ,�������ģʽ*/
 bar(x+2,y+2,x+sizx-2,y+sizy-2);
}

/*������һЩ��ͼ����*/
/*�β�x,yЦ������������,sizel���Ĵ�С(�뾶),
kΪҪ���������ͣ�1���ޡ�2��ƽ����3��Ц*/
void Facedraw(int x,int y,int sizel,int k)
 {Draw(x-sizel-3,y-sizel-3,2*(sizel+4),2*(sizel+4));/*��һ����ť*/
  setcolor(14);
  setfillstyle(1, 14);
  pieslice(x, y, 0, 360, sizel);/*��һ����ɫ��Բ��*/
  setfillstyle(1, 0);
  setcolor(0);
  if(k==1)/*ʧ��*/
  {
  line(x-sizel*7/20,y-sizel*7/20,x-sizel*3/20,y-sizel*3/20);/*���������ʾ�۾�*/
    line(x-sizel*7/20,y-sizel*3/20,x-sizel*3/20,y-sizel*7/20);
    line(x+sizel*3/20,y-sizel*7/20,x+sizel*7/20,y-sizel*3/20);
    line(x+sizel*3/20,y-sizel*3/20,x+sizel*7/20,y-sizel*7/20);
    arc(x,y+sizel,20,160, sizel/2);
 }
  if(k==2)/*ƽ��*/
   {
  bar(x-sizel*7/20,y-sizel*7/20,x-sizel*3/20,y-sizel*3/20);
    bar(x+sizel*3/20,y-sizel*7/20,x+sizel*7/20,y-sizel*3/20);
    arc(x,y,200,340, sizel*3/4);
   }
  if(k==3)/*�ɹ�*/
   {
  bar(x-sizel/2,y-sizel/2,x-sizel*3/20,y-sizel*3/20);
    bar(x+sizel*3/20,y-sizel/2,x+sizel/2,y-sizel*3/20);
    line(x-sizel*3/20,y-sizel/2,x+sizel*3/20,y-sizel/2);
    line(x-sizel/2,y-sizel*5/20,x-sizel,y);
    line(x+sizel/2,y-sizel*5/20,x+sizel,y);
    arc(x,y,200,340, sizel*3/4); /*���*/
   }
}

/*������Ĵ������*/
/*x,yҪ�жϵĵ������,sizelΪ���Ĵ�С*/
void Dead(int sizel,int x,int y)
{
 int i,j;/*ѭ������*/
 setcolor(4);
 for(i=0;i<x;i++)
 for(j=0;j<y;j++)
 if(pan[i][j]==9)
 {
  circle(i*size+pix+7,j*size+piy+7,4);
 }/*�ú�ɫ��ԲȦ������׵ķ���*/
 Facedraw(250,30,sizel,1);
 Eflags=1;
}

/*����ĺ�������ʵ�����������ƶ���Χ*/
/*xmax,ymaxΪ���Ͻǵ�����x,y����Ĵ�С*/
void Setmouse(int xmax,int ymax,int x,int y)
{
 int left,right,top,buttom;/*���ĸ���������ȷ���ƶ������ϽǺ����½�*/
 left=xmax;
 right=x;
 top=ymax;
 buttom=y;
 regs.x.ax=7;
 regs.x.cx=left;
 regs.x.dx=right;
 int86(0x33,& regs,& regs);
 regs.x.ax=8;
 regs.x.cx=top;
 regs.x.dx=buttom;
 int86(0x33,& regs,& regs);
}

/*���������������ʵ�����Ķ�ȡ*/
/*xp,yp,bup�ֱ�Ϊ����λ�úͰ������,t1,k��ʱ����ʵ����,t1Ϊ��ʼʱ�䣬kΪ��ʼ���*/
int Msread(int *xp,int *yp,int *bup,struct time t1,int k)
{
 int x0=*xp,y0=*yp,bu0=*bup;
 int xnew,ynew,ch;
 int tt1=0;/*���ڼ�¼ʱ���*/
 struct time t2;
 char ttt[4]="000";
 do
  {
  if(kbhit()) return getch();
      regs.x.ax=3;
      int86(0x33,& regs,& regs);
      xnew=regs.x.cx;
     ynew=regs.x.dx;
     *bup=regs.x.bx;
 /*����������ʾʱ��*/
  if(k==1)/*����Ѿ���ʼ�ͼ���ʱ���*/
        {
   gettime(&t2);
       tt1=(t2.ti_hour- t1.ti_hour)*3600 + (t2.ti_min- t1.ti_min)*60 + t2.ti_sec  - t1.ti_sec;/*�д��Ľ�*/
        if(tt1<=999 && tt!=tt1)/*��ʱ����иı�ʱ������ʾ*/
   {
    tt=tt1;
     ttt[0]=(tt-tt%100)/100+48;
    ttt[1]=(tt%100-tt%10)/10 +48;
    ttt[2]=tt%10+48;
    setfillstyle(1, 0);
    bar(460-pix,25,490-pix,40);
    setcolor(4);
    outtextxy(465-pix,30,ttt);
   }
        }
    }
 while(xnew==x0&&ynew==y0&&*bup==bu0);
 *xp=xnew;
 *yp=ynew;
 return -1;/*����������ʱ����-1,��η��ؼ���ֵ*/
}

void Draw1(int x,int y)/*�������������x,y��λ����濪������*/
{
 setfillstyle(1, 7);
 bar(x*size+pix,y*size+piy,x*size+size+pix-1,y*size+size+piy-1);
 
 /*���ĸ����ϻ��ϵ���*/
 /*putpixel(x*size+pix,y*size+piy,8);
 putpixel(x*size+size+pix-1,y*size+size+piy-1,8);
 putpixel(x*size+pix,y*size+size+piy-1,8);
 putpixel(x*size+size+pix-1,y*size+piy,8);*/

 setcolor(8);
 setlinestyle(1, 0, 1);
 rectangle(x*size+pix,y*size+piy,x*size+size+pix-1,y*size+size+piy-1);
 setlinestyle(0, 0, 1);

 if(pan[x][y]!=0)/*û���׵Ļ�������ʾ*/
    {
  b[0]=pan[x][y]+48;
       if(pan[x][y]!=7)/*��ֹ�ֵ���ɫ�ͱ�����ɫ��ͬ*/
  setcolor(pan[x][y]);
  else setcolor(9);
  outtextxy (x*size+pix+3,y*size+piy+3,b);
    }
 pan1[x][y]=1;/*��pan1[][]�б����һ����������*/
}

/*�Կ�����*/
int Open(int x,int y)/*����������pan2[][]��Ŀ����Ϊ�������Կ���Ч��,���ǻ����в���֮��*/
{
 int i,j,k;
 int pan2[30][16]={0};/*pan2[][],��ʱ��¼������Կ����,0û���Կ���,1:�Ѿ��Կ���(30 ������Σ�յļ���������!!!)*/
 for(;;)
 {
  k=0;/*��һ����Ǳ���*/
  for(i=0;i<x;i++)
  for(j=0;j<y;j++)
      {
   if (pan[i][j]==0 && pan1[i][j]==1 && pan2[i][j]==0)/*���������������,û����,�Ѿ���,û���Կ����ͼ���*/
   {
    pan2[i][j]=1;/*����Կ���*/
     k=k+1;
   /*����Χ�ĵ�*/
    if(i-1>=0 && j-1>=0 && pan1[i-1][j-1]==0) Draw1(i-1,j-1); /*���Ϸ�*/
    if(j-1>=0 && pan1[i][j-1]==0) Draw1(i,j-1);       /*�Ϸ�*/
    if(i+1<x && j-1>=0 && pan1[i+1][j-1]==0) Draw1(i+1,j-1);  /*���Ϸ�*/
    if(i-1>=0 && pan1[i-1][j]==0) Draw1(i-1,j);          /*��*/
    if(i+1<x && pan1[i+1][j]==0) Draw1(i+1,j);              /*�ҷ�*/
    if(i-1>=0 && j+1<y && pan1[i-1][j+1]==0) Draw1(i-1,j+1);  /*���·�*/
    if(j+1<y && pan1[i][j+1]==0) Draw1(i,j+1);              /*�·�*/
    if(i+1<x && j+1<y && pan1[i+1][j+1]==0) Draw1(i+1,j+1);   /*���·�*/
   }
       }
  if(k==0) return 0;/*û���µ��Կ���ʱ�˳�*/
 }
}

float Random()/*�漴�����ɺ���,������ʱ�����Ŀ�����ڼ�ǿ���������*/
{float aa;
 int i,j;
 struct time t;
 gettime(&t);
 i=t.ti_min+t.ti_hour+t.ti_sec+t.ti_hund;
 for(j=0;j<i;j++)
 rand();
 aa=rand()/32767.0;
 return aa;/*���ز����������(0-1)*/
}

/*������һ����ʾʣ������Ŀ�ĺ���*/
void Have(int sum,int x,int y,int xx,int yy)/*��Ϸ���׵�����Ŀ���ܶ���99��,sum Ϊ�׵�����Ŀ,x,yΪ��ʾ�ĵص�*/
{
 int i,j,k=0;
 char a[3]="1";
 for(i=0;i<xx;i++)
 for(j=0;j<yy;j++)
    {if (pan1[i][j]==2) k++;}/*ͳ��һ������˶���*/
 k=sum-k;/*ʣ���˶���*/
 if(k<0) k=0;
 a[0]=(k-(k%10))/10+48;/*�ַ�ת��*/
 a[1]=k%10+48;
 setfillstyle(1, 0);
 bar(x-5,y-5,x+20,y+10);/*��ԭ��Ϳ��*/
 setcolor(4);
 outtextxy(x,y,a);/*��ʾ��Ŀ*/
}

/*�����ǰ�������*/
void Help()
{
 Draw(40,1,560,160);
 setcolor(1);
 outtextxy(300,10,"Help");
 setcolor(4);
 outtextxy(50,30,"Welcome to play this game. The mouse is supplied.");
 outtextxy(50,40,"Please press left button of the mouse where there is no boom.");
 outtextxy(50,50,"If you think there is a boom please press right button.");
 outtextxy(50,60,"You can choose the size of the game with press the right buttons.");
 outtextxy(50,70,"'Big' means 99 booms,'Normal' means 40 booms,'Small' means 10 booms.");
 outtextxy(50,80,"You can press the laugh-face-button or press C to play again.");
 outtextxy(50,90,"When you fail or success you can press any key to play again. ");
 outtextxy(50,100,"Whenever you want to quit this game please press Q. ");
 outtextxy(50,110,"If you find out all booms then you are winning. ");
 setcolor(9);
 outtextxy(50,140,"Press any key to play again.");
 Eflags=2;
}

void Coread()/*����������ڶ�ȡ��¼����ʾ*/
{ 
  int co[3],i;
  char name[3][20];
  char cco[3][4];
  FILE * p;
  for(i=0;i<3;i++)
       cco[i][3]='\0';

  if((p = fopen("score.dat", "rb")) == NULL)
     {
  printf("The file cannot open!\n");
       exit(1);
 }

  fscanf(p,"%d %d %d,",&co[0],&co[1],&co[2]);
  for(i=0;i<3;i++)
     fscanf(p,"%s\n",name[i]);
  fclose(p);
  Draw(10,20,320,90);
  setcolor(1);
  outtextxy(140,30,"HighCore");
  setcolor(2);
  outtextxy(20,50,"Easy");
  outtextxy(20,60,"Normal");
  outtextxy(20,70,"Hard");

  for(i=0;i<3;i++)
 {
  cco[i][0]=(co[i]-co[i]%100)/100+48;
   cco[i][1]=(co[i]%100-co[i]%10)/10 +48;
   cco[i][2]=co[i]%10+48;
 }

  setcolor(3);
  outtextxy(100,50,cco[0]);
  outtextxy(100,60,cco[1]);
  outtextxy(100,70,cco[2]);

  setcolor(5);
  outtextxy(150,50,name[0]);
  outtextxy(150,60,name[1]);
  outtextxy(150,70,name[2]);  

  setcolor(9);
  outtextxy(30,85,"Press any key to play again.");
  Eflags=2;
}

/*������������������,x,y,Ϊ���Ͻ����꣬��СΪ20*20*/
void Ddraw2(int x,int y)
{
 /*����ط���ʱʹ�ü��׹�꣬��������Ժ�ʹ�ø��ӵ�*/
 setcolor(1);
 line(x,y,x,y+18);
 line(x+1,y,x+1,y+18);
 line(x,y,x+12,y+12);
 line(x+1,y,x+13,y+12);
 line(x,y+18,x+4,y+14);
 line(x,y+17,x+4,y+13);
 line(x+4,y+14,x+6,y+20);
 line(x+4,y+13,x+6,y+19);
 line(x+6,y+20,x+10,y+18);
 line(x+6,y+19,x+10,y+17);
 line(x+10,y+18,x+8,y+12);
 line(x+10,y+17,x+8,y+11);
 line(x+8,y+12,x+12,y+12);
 line(x+8,y+11,x+12,y+11);
}

/*ֱ�ӱ�������*/
 
 
