#include<time.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include <malloc.h>
#define MAX 4

//char check = 0;
int point=0;    //Score counter
char stack[MAX];  //Stack Array;

int top=-1;       //Stack Top
char *c;          //Holding the letter

//Function Prototype
void play();
void end();
void initgraphics();
void border();
void asktocontinue();
void scroll(int ,int ,int ,char *);
void FIRSTSCREEN(); //prototype
char randomAlpha();


int x,y,len=0,d,m,mx,my,i,j,k,count_s=0,count_f=0,hcount=0;

int flag=0,hlflag=1,spaces=0;
int tcolor=GREEN,acolor=RED;
char name[25];

int a[500],n[500],con=20,i,j;

void play()
{
   cleardevice();
   while(!isFull())
   {

     x = 0;
     y = getmaxy();
     x = rand()%640;
     x = (x+30)%600;
     //x = ((x+320)%600);
     i = randDelay();
     c[0] = randomAlpha();
     c[1] = '\0';
     PUSH(c[0]);
     scroll(x,y,i,c);
   }
   //When game is Over
   while(1)
    {
     setcolor(WHITE);
     outtextxy((getmaxx()/2)-120,(getmaxy()/2)-80,"GAME OVER");
     outtextxy((getmaxx()/2)-120,(getmaxy()/2)-10,"Final Score:");
     sprintf(c,"%d",point);
     outtextxy((getmaxx()/2)+100,(getmaxy()/2)-10,c);
     if(getch()=='\r')
     {
      break;
     }
     else
     {
     continue;
     }
   }
    asktocontinue();

}


int PUSH(char f)
{
	int num;
	if(top==MAX-1)
	{
	 return 0;
	}
	else
	{
	 ++top;
	 stack[top]=f;
	 return 1;
	}
}


int isFull()
{
 if(top==MAX-1)
 return 1;
 else
 return 0;
}


int POP()
{
	int a;
	if(top==-1)
	{
	 return 0;
	//printf("\n\nSTACK IS EMPTY");
	}
	else
	{
	--top;
	return 1;
	}
}



void end()  //Goodbye Screen
{
   int j,i;
   setcolor(WHITE);
   for(i=0;i<2;i++)
   {
    delay(200);
    cleardevice();
   }

  //Tojustify Horizontaly
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  settextstyle(3,0,8);
  setcolor(RED);
  outtextxy(mx/2,150,"GOODBYE");
  setcolor(WHITE);
  settextstyle(1,0,7);
  outtextxy(mx/2,my/2,name);
  getch();
  exit(0);
}



void scroll(int a,int b,int t,char *e)
{
   int i;
   char inchar;

    for( i=0 ;b>-30; i++)
   {
     if(!kbhit())
     {
      setcolor(WHITE);
      circle(a,b,30);
      settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
      outtextxy(a-6,b-15,e);
      delay(t);
      setcolor(BLACK);
      circle(a,b,30);
      settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
      outtextxy(a-6,b-15,e);
      b = b--;
     }
     else
     {
      inchar = getch();
      if(stack[top]==inchar)
      {
       POP();
       point++;
       break;
      }
      else
      {
       continue;
      }
     }

    }
}


void asktocontinue()
{
   char ch,Hname[25];
    FILE *fp;
    int Hscore;
   top = -1;
   cleardevice();
   //FILE HANDLING

   fp = fopen("score.txt","r");
   if(fp)                      //Check if exists
   {
    fscanf(fp,"%s   %d",Hname,&Hscore);
    fclose(fp);

    if(Hscore<point)   //check score if high or not
     {
      fp = fopen("score.txt","w");
      fprintf(fp,"%s   %d",name,point);
      fclose(fp);
     }
   }
   else                        //if not
   {
   fp = fopen("score.txt","w");
   fprintf(fp,"%s   %d",name,point);
   fclose(fp);
   }

   point = 0;
   setcolor(WHITE);
   outtextxy((getmaxx()/2)-180,(getmaxy()/2),"Wish to Play again:(Y/N):");
   get:

   ch=getch();
   if(ch=='y'||ch=='Y')
	 {
	   outtextxy(550,(getmaxy()/2),"Y");
	   getch();
	   //scroll(x,y,i,c);
	   play();
	 }
   else if(ch=='n'||ch=='N')
	 {
	   outtextxy(550,(getmaxy()/2),"N");

	   getch();
	   end();

	 }
	goto get;
}



char randomAlpha()
{
   int a ;
   char d;

   a = rand()%100;
   if(a>50)
   {
    d = 97+(a%26);
   }
   else
   {
    d = 65+(a%26);
   }
   return d;
}



int randDelay()
{
   int a;
   a = rand()%6;
   return a;
}



void border()
{
  setcolor(GREEN);
  rectangle(2,2,mx-2,my-2);
  setcolor(RED);
  rectangle(4,4,mx-4,my-4);
  setcolor(GREEN);
  rectangle(6,6,mx-6,my-6);
  settextstyle(3,0,5);
  outtextxy(180,40,"SPEED MASTER");
  setcolor(YELLOW);
  line(175,88,470,88);
  setcolor(RED);
  line(175,90,470,90);
}


void initgraphics()
{
 d=DETECT;
 initgraph(&d,&m,/*"C:\\TC\\BGI"*/"C:\\TURBOC3\\BGI");
 mx=getmaxx();
 my=getmaxy();
}


void getuser()
 {
  int i;
  char cr;
  cleardevice();
  setcolor(BLUE);
  outtextxy(10,200,"Enter your Name:");
  //printf("\n\nEnter your Name:");
  setcolor(WHITE);
  i=0;
  while(1)
  {
    cr = getch();
    if(cr!='\r')
    {
     name[i] = cr;
     name[i+1] = '\0';
     outtextxy(300,200,name);
     i = i+1;
    }
    else
    {
     break;
    }

  }
  if(strlen(name)<1)  //if no name entered
   strcpy(name,"USER");
 }

//WELCOMING THE USER
 void welcomeuser()
 {
  cleardevice();
  setcolor(GREEN);
  border();
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  settextstyle(3,0,8);
  outtextxy(mx/2,150,"WELCOME");
  setcolor(WHITE);
  settextstyle(1,0,7);
  outtextxy(mx/2,my/2,name);
  setcolor(RED);

  settextstyle(5,0,5);
  outtextxy(mx/2+1,380,"\nPRESS ANY KEY TO PLAY");
  settextjustify(LEFT_TEXT,TOP_TEXT);
  getch();
  cleardevice();
 }

//FUNCTION TO DISPLAY THE VERY FIRST SCREEN OF THE PROGRAM

int menu()
{
char cr;
int z,color;
 z =0;
		setcolor(WHITE);
		color = 0;
		while(!kbhit())
		{
		color = (color+1)%15;
		setcolor(color);
		rectangle(60,330+z,580,380+z);
		}
		while((cr=getch())!='\r')
		{
		    if(cr==(char)72 || cr==(char)80)
		      {
					setcolor(BLACK);
					rectangle(60,330+z,580,380+z);
					if(z>=60)
					 z=0;
					else
					 z = (z+60);
					setcolor(WHITE);
					rectangle(60,330+z,580,380+z);
					color = 0;
					while(!kbhit())
					{
					 color = (color+1)%15;
					 setcolor(color);
					 rectangle(60,330+z,580,380+z);
					}

		      }
		}
		return z;
}

void score()
{
 int color;
 FILE *fp;
 char s[10],n[25];
 cleardevice();
 border();
 settextstyle(1,0,4);
 setcolor(RED);
 outtextxy(230,100,"High Score");
 settextstyle(1,0,3);
 setcolor(WHITE);
 outtextxy(170,150,"NAME");
 outtextxy(400,150,"SCORE ");

 //file handling
 fp = fopen("score.txt","r");
 fscanf(fp,"%s   %s",n,s);
 settextstyle(1,0,4);
 color = 0;
 while(!kbhit())
 {
 color = (color+1)%15;
 setcolor(color);
 outtextxy(170,200,n);
 outtextxy(400,200,s);
 outtextxy(130,330,"Press Any Key to return");
 }
 getch();
 FIRSTSCREEN();
}

void FIRSTSCREEN()
{
  int select;
  clrscr();
  initgraphics();
  border();

  settextstyle(3,0,3);
  setcolor(RED);
  outtextxy(130,200,"Programmed By:");
  settextstyle(1,0,3);
  setcolor(WHITE);
  outtextxy(330,200,"Chirag Maniar");
  outtextxy(250,235," And Nikhil Sankpal");
  settextstyle(1,0,4);
  setcolor(RED);
  outtextxy(230,330,"Start Game");
  outtextxy(230,390,"High Score");

  select = menu();

   if(select!=0)
   {
    score();
   }
}

void main()
{
 int gdriver = DETECT, gmode;
 int x,y,i;

 clrscr();
 initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

 FIRSTSCREEN(); //Game Name and Welcome screen
 getuser();     // Getting User Name
 welcomeuser(); // Welcome user with user's name
 srand(time(NULL));// initialize random number generator , Null for starting point
 play();      // Acutual game
 getch();
 closegraph();  //closing graph
}
