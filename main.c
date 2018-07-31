#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
 void display();
 void timerd();
 char playagain();
 void move();
 void welcome();
 void quen(int,int);
 void wrongm(int,int,int,int);
 void rulesd();
 void results();
 void inti();
 int check(int,int);
 void timeup();
 clock_t first,last,m;
 int a[8][8],i,j,cou=0,min,sec;
 char msg[50],name[20],chp;

int main()
  { int gdriver =EGA, gmode=1, count;

    initgraph(&gdriver,&gmode,"c:\\tc\\bgi");//initialising graphics
    welcome();//welcome screen
    inti();  //initialising array elements

   sp:     //starting point
    display();
    move();
    display();
    if(min>5)  //max time countdown checker
      { timeup();
	chp=playagain();
       }
     else
	{ if(cou==8)             //finishing condition
	    { last=clock();     //end point clock time
	      results();       //result screen display
	      chp=playagain();    //play again screen
	     }
	   else
	     goto sp;	   //recursive point
	 }

    if(chp=='y')          // resettting & starting again
      { inti();
	goto sp;
       }
     else
       { closegraph();     //closing graph
	 return 0;
	}

    }

void display()
  { char msg[40],c=97;
    clearviewport();
    setcolor(15);
    setfillstyle(1,8);   //setting bar color grey
    bar(130,70,370,310); //base grey bar
    setbkcolor(1);       //setting text color blue
    for(i=0;i<8;i++)     //chess board display
     { setfillstyle(1,15); //setting bar color white
       bar(130+(i*30),70+(i*30),160+(i*30),100+(i*30)); //main diagonal white box
       if(i<6)
	 { bar(190+(i*30),70+(i*30),220+(i*30),100+(i*30));   //1st up diagonal of main diagonal
	   bar(130+(i*30),130+(i*30),160+(i*30),160+(i*30)); // 1st down diagonal of main diagonal
	  }
       if(i<4)
	 { bar(250+(i*30),70+(i*30),280+(i*30),100+(i*30)); //2nd  up diagonal of main diagonal
	   bar(130+(i*30),190+(i*30),160+(i*30),220+(i*30));//2nd  down diagonal of main diagonal
	  }
       if(i<2)
	 { bar(310+(i*30),70+(i*30),340+(i*30),100+(i*30)); //3rd  down diagonal of main diagonal
	   bar(130+(i*30),250+(i*30),160+(i*30),280+(i*30));//3rd  up diagonal of main diagonal
	  }

       sprintf(msg,"%c ",c);          //for initialising X co-ordinate characters
       outtextxy(145+(i*30),60,msg);  // character display A to H at top
       outtextxy(145+(i*30),320,msg); // character display A to H at bottom
       sprintf(msg,"%c ",c+8);        //for initialising Y co-ordinate characters
       outtextxy(120,85+(i*30),msg); // character display I to P at leftside
       outtextxy(380,85+(i*30),msg); // character display I to P at rightside
       c++;
      }
    sprintf(msg,"Queens used: %d",cou);     //displayin no. of queens used
    outtextxy(300,10,msg);
    for(i=0;i<8;i++)
      for(j=0;j<8;j++)
	if(a[i][j]==1)                  //check queen presence in the array
	  quen(i,j);                  //display the queen 2D image


    timerd();
   }

void move()
  { char ch;
    int x[3],y;

    setcolor(15);//setting text color white
    /* getting player move*/
   g1:
    y=0;
    while(y<=2)
      { timerd();
	sprintf(msg,"Enter your move:");
	outtextxy(10,10,msg);
	ch=getch();
	if((ch!=13))
	  x[y]=ch;
	if(ch==8)
	 { x[y]=0;
	   x[y-1]=0;
	   y=y-2;
	   clearviewport();
	   display();
	  }
	if((y>-1)&&(y!=2))
	 { sprintf(msg,"%c ",x[y]);
	   outtextxy(140+(y*20),10,msg);
	  }
	y++;

       }


    if(x[0]=='e'&&x[1]=='e')        //checking for condition to exit the  game
       exit(0);

    if(x[0]=='r'&&x[1]=='r')        //checking for condition to restart the game
      { inti();
	display();
	goto g1;
       }

    if((x[0]<96)||(x[0]>105)||(x[1]<104)||(x[1]>112))  //invalid move checker
      { clearviewport();
	sprintf(msg,"invalid move");
	outtextxy(10,10,msg);
	getch();
	display();
	goto g1;
       }

    i=x[0]-97;
    j=x[1]-105;
    if(a[i][j]==1)  //condition to remove already present queen
      { a[i][j]=0;
	cou--;
       }
     else
       cou+=a[i][j]=check(i,j);//checking queen's clash with another
			       //increasing queen count

    timerd();
   }

int check(int p,int q)
  { int r=1,s,t;
    timerd();
    for(t=0;t<8;t++)
      { if(a[p][t]==1)   //checking vertically
	  { r=0;
	    wrongm(p,q,p,t);
	   }
	if(a[t][q]==1)   //checking horizontally
	  { r=0;
	    wrongm(p,q,t,q);
	   }
       }

   /*checking diagonally upwards towards H I*/
    s=p;
    t=q;
    while(t>=0)
       { if(s<8)
	  if(a[s][t]==1)
	    { r=0;
	      wrongm(p,q,s,t);
	     }
	 s++;
	 t--;
	}

   /*checking diagonally upwards towards A P*/
    s=p;
    t=q;
    while(s>=0)
       { if(t<8)
	  if(a[s][t]==1)
	    { r=0;
	      wrongm(p,q,s,t);
	     }
	 s--;
	 t++;
	}

    /*checking diagonally downwards towards H P*/
    s=p;
    t=q;
    while((s<8)&&(t<8))
       { if(a[s][t]==1)
	   { r=0;
	     wrongm(p,q,s,t);
	    }
	 s++;
	 t++;
	}

    /*checking diagonally upwards towards A I*/
    s=p;
    t=q;
    while((s>-1)&&(t>-1))
       { if(a[s][t]==1)
	    { r=0;
	      wrongm(p,q,s,t);
	     }
	 s--;
	 t--;
	}

    timerd();
    if(r==0)
       getch();  //waiting key for player to see wrong position
    return r;
   }

void wrongm(int w1,int w2,int w3,int w4)  //wrong position display
  { setfillstyle(1,4);//setting box color red
    bar(130+(w1*30),70+(w2*30),160+(w1*30),100+(w2*30));//highlighting wrong ox
    bar(130+(w3*30),70+(w4*30),160+(w3*30),100+(w4*30));//highlighting wrong ox
    quen(w1,w2);
    quen(w3,w4);
    /*flashing wrong position dialogue box*/
    sprintf(msg,"wrong position");
    setfillstyle(1,15);
    bar(600,130,450,100);
    setcolor(4);
    outtextxy(460,115,msg);
    timerd();
   }

/*func to display 2D queen image*/
void quen(int s,int e)
  { setcolor(1);
    line(138+(s*30),92+(e*30),152+(s*30),92+(e*30));//baseline
    line(138+(s*30),92+(e*30),132+(s*30),75+(e*30));//left x stream
    line(152+(s*30),92+(e*30),158+(s*30),75+(e*30));//ri8 x stream
    line(158+(s*30),75+(e*30),150+(s*30),85+(e*30));//adj to ri8 xstream
    line(150+(s*30),85+(e*30),145+(s*30),75+(e*30));//ri8 inner triangular side
    line(132+(s*30),75+(e*30),140+(s*30),85+(e*30));//adj to left xstream
    line(140+(s*30),85+(e*30),145+(s*30),75+(e*30));//left inner triangular side
    setcolor(15);
   }


void welcome()
  { char ch=97;
    int s=0;
    /*Open screen*/
    sprintf(msg,"welcome to 8 queens puzzle game");
    setbkcolor(15);
    setcolor(1);
    outtextxy(150,150,msg);
    sprintf(msg,"Developed by");
    outtextxy(420,295,msg);
    sprintf(msg,"DreamerzZ");
    outtextxy(430,310,msg);
    getch();    //waiting key

    /*To display rules*/
    rulesd();

    /*To get player's name*/
    sprintf(msg,"Enter your name:");
    outtextxy(200,170,msg);
    while(((ch>96)&&(ch<123))||(ch==32)||(ch==8))
      { ch=getch();
	if(ch!=13)
	 name[s]=ch;
	if(ch==8)
	  { name[s]=0;
	    name[s-1]=0;
	    s=s-2;
	   }
	clearviewport();
	outtextxy(200,170,msg);
	outtextxy(330,170,name);
	s++;
       }
    clearviewport();
   }

/*func to display rules*/
void rulesd()
  { clearviewport();
    setbkcolor(15);
    setcolor(1);
    sprintf(msg,"INSTRUCTIONS");
    outtextxy(255,47,msg);
    sprintf(msg,"-> You have to place 8 queens in a chessboard  ");
    outtextxy(40,70,msg);
    sprintf(msg,"-> To place enter the co-ordinates of the position (eg: a i) ");
    outtextxy(40,90,msg);
    sprintf(msg,"-> To remove from existing place re-enter the co-ordinates ");
    outtextxy(40,110,msg);
    sprintf(msg,"RULES");
    outtextxy(255,147,msg);
    sprintf(msg,"* A queen can cut vertically,horizontally,diagonally");
    outtextxy(40,170,msg);
    sprintf(msg," upto any boxes in any direction as in chess");
    outtextxy(55,180,msg);
    sprintf(msg,"* Queens should be placed in such a way that no queen cuts another queen");
    outtextxy(40,210,msg);
    sprintf(msg,"Press any key to continue ");
    outtextxy(250,250,msg);

    getch();  //waiting key
    clearviewport();

   }

/*func to initialise array variables*/
void inti()
  { for(i=0;i<8;i++)
      for(j=0;j<8;j++)
	a[i][j]=0;
    cou=0;
    first=clock();//starting time
   }

/*func to display result screen*/
void results()
  { clearviewport();
    setbkcolor(15);
    setcolor(1);
    sprintf(msg,"Congratulations %s !!,",name);
    outtextxy(100,150,msg);
    sprintf(msg,"You have sucessfully completed. ");
    outtextxy(150,170,msg);
    min=(last-first)/(CLK_TCK*60);       //minutes calculation
    sec=((last-first)/CLK_TCK)-(min*60); //seconds calculation
    sprintf(msg,"You took %d minutes and %d seconds to compelete. ",min,sec);
    outtextxy(150,190,msg);
    getch();
   }

/*time taken displayer func*/
void timerd()
  { m=clock();
    min=(m-first)/(CLK_TCK*60);
    sec=((m-first)/CLK_TCK)-(min*60);
    setfillstyle(1,8);
    bar(300,20,370,35);
    setcolor(15);
    sprintf(msg," %d : %d ",min,sec);
    outtextxy(302,22,msg);
   }

/*time up indicator func*/
void timeup()
  { setfillstyle(1,7);
    bar(180,150,400,250);
    sprintf(msg,"Time Up %s",name);
    setcolor(4);
    outtextxy(220,200,msg);
    getch();
   }

/*option to play the game again aft completing*/
char playagain()
  { char ch;
    clearviewport();
    sprintf(msg,"Do you want to play again(y/n):");
    setbkcolor(15);
    setcolor(1);
    outtextxy(150,150,msg);
    ch=getch();
    sprintf(msg,"%c",ch);
    outtextxy(397,150,msg);
    getch();
    return ch;
   }
