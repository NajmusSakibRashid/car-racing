
# include "iGraphics.h"
typedef struct
{
    char name[80];
    int score=0;
}player;
player p[4];

char str[100],str2[100];

int bowl;
int len;
int mode,h;
int on,q;
int r,x;
 char l[3][100];
void  sortin(player *p);

FILE *fptr;
FILE *fp;
	char *playerinfo="playerinfo.txt";
	char *p2="playertst.txt";
	void fileread(FILE *fptr){


	fptr=fopen(playerinfo,"r");

	for(int i=0;i<3;i++)
    {
        fgets(l[i],100,fptr);
        //fscanf(fptr,"%s",&p[i].name);
        sscanf(l[i],"%s %d\n",p[i].name,&p[i].score);
        printf("%d\n",p[i].score);
    }
    fclose(fptr);



	}
void filewrt()
{
    fptr =fopen(playerinfo,"w");
    for(int i=0;i<=3;i++)
    {
        fprintf(fptr,p[i].name);
        fprintf(fptr," %d",p[i].score);
        fprintf(fptr,"\n");

    }
    fclose(fptr);
    printf("this is file wrt");
}

void sortin(player *p)
{
    int i,j;
    //char a[100];
    player c;

    for(i=0;i<4-1;i++)
    {
        for(j=0;j<4-1-i;j++)
        {
            if((p+j)->score<(p+j+1)->score)
             {


                c=*(p+j);
                *(p+j)=*(p+j+1);
                *(p+j+1)=c;


            }
        }
    }
}

void drawTextBox()
{
	iSetColor(255, 0, 0);
	iRectangle(50, 500, 250, 30);

}
void drawcrs(int i)
{
    iSetColor(0,0,0);

    iFilledRectangle(52+(i*8),502,2,25);

}
void highscore()
{
   iSetColor(0,0,29);
        iFilledRectangle(100,20,500,300);

        iShowBMP2(100,200,"1st.bmp",0x000000);
        iShowBMP2(270,200,"2nd.bmp",0x000000);
        iShowBMP2(450,200,"3rd.bmp",0x000000);
        if(r==1){
        fileread(fptr);
        sortin(&p[0]);
        filewrt();
        fileread(fptr);
        r=0;}

        for(int i=0;i<3;i++)
        {
            iSetColor(255,255,255);
           iText(120+(i*160),190,l[i]);
        }
        iText(200,50,"PLAYER:");
        iText(300,50,str2);

        iFilledRectangle(520,30,60,30);
        iSetColor(0,0,0);
        iText(525,35,"CLOSE");
}
void drawmainscrn()
{
   iShowBMP(0,10,"back.bmp");
   iShowBMP2(0,0,"name.bmp",0x000000);

	iSetColor(0,0,0);
	iText(60,550,"ENTER PLAYER'S NAME..(PRESS F12 TO ERASE)");
	iFilledRectangle(50,400,80,30);
	iFilledRectangle(50,350,120,30);
	iFilledRectangle(50,300,80,30);

    iSetColor(255,255,255);
	iText(60,410,"PLAY");
	iText(60,360,"HIGH SCORES");
	iText(60,310,"QUIT");

	drawTextBox();
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();
	drawmainscrn();

	if(mode == 1)
	{
	    drawcrs(len);
		iSetColor(0, 0, 0);
		iText(55, 510, str);
	}
//	if(on == 1)
//	{
//		iSetColor(255, 255, 255);
//		iText(855, 760, bowl);
//	}
//	if(wrt==1){
//            iSetColor(0,0,0);
//            for(int i=0;i<3;i++){
//        iText(10,700-(i*10),p[i].name);
//       // iText(60,700-(i*10),p[i].score);
//            }

	//}
	if(on==1)
    {
       // drawgame();
    }
    if(h==1)
    {

       highscore();

    }

//	for(int i=0;i<3;i++){
//        iText(10,700-(i*10),p[i].name);
//       // iText(60,700-(i*10),p[i].score);
//            }


//	iText(200, 200, "Click to activate the box, enter to finish.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if(mx >= 10 && mx <= 300 && my >= 490 && my <= 530 && mode == 0)
		{
			mode = 1;
		}
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    if(mx>=10&&mx<=120&&my>=400&&my<=450)
        {
            on=1;
        }

		//place your codes here

	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    if(mx>=10&&mx<=150&&my>=340&&my<=380)
        {
            h=1;
            r=1;
        }
		//place your codes here
	}
	//printf("%d\n",w);
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    if(mx>=10&&mx<=100&&my>=290&&my<=320)
        {
            q=1;
        }
		//place your codes here
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    if(mx>=525&&mx<=600&&my>=20&&my<=60)
        {
            h=0;

        }
		//place your codes here
	}

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

	int i;
	if(mode == 1)
	{
        if(key == '\r')
		{
			mode = 0;
			strcpy(p[3].name, str);
			strcpy(str2,str);
			printf("%s\n",p[3].name);
           //wrt=1;
//			c++;
            p[3].score=100;//player .score is initialized to test it,s value will be taken from game
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;

		}
	}


//	if(key == 'x')
//	{
//		//do something with 'x'
//		exit(0);
//	}


//    fptr=fopen(playerinfo,"w");
//	for(int i=0;i<=3;i++)
//    {
//        fprintf(fptr,p[i].name);
//        //fprintf(fptr,"\t%d",p[i].score);
//    }
//    fclose(fptr);
	//place your codes for other keys here
//	printf("%d\n",w);

}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_HOME)
	{
		//do something with 'x'
		exit(0);
	}

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key==GLUT_KEY_F12){
       //
            {
                str[len-1]=0;
                len--;
                //x=0;
            }
	}
        //x=1;

//printf("%d",x);
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.


    len = 0;
	mode = 0;
	on=0;
	str[0]= 0;
	str2[0]=0;
	r=0;
	h=0;
	x=0;
	iInitialize(600, 600, "TextInputDemo");
	return 0;
}
