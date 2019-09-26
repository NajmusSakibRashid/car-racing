//int ox,oy;
//# include "iGraphics.h"
typedef struct
{
    char name[80];
    double score=0;
} player;
player p[4];

char m_str[100],m_str2[100];

int m_bowl;
int m_len;
int m_mode,m_h;
int m_on,m_q;
int m_r,m_x;
char m_l[3][100];
void  sortin(player *p);

//FILE *fptr;
//FILE *fp;
//	char *playerinfo="playerinfo.txt";
//	char *p2="playertst.txt";
//	void fileread(FILE *fptr){
//
//
//	fptr=fopen(playerinfo,"r");
//
//	for(int i=0;i<3;i++)
//    {
//        fgets(m_l[i],100,fptr);
//        //fscanf(fptr,"%s",&p[i].name);
//        sscanf(m_l[i],"%s %d\n",p[i].name,&p[i].score);
//        printf("%d\n",p[i].score);
//    }
//    fclose(fptr);
//
//
//
//	}
//void filewrt()
//{
//    fptr =fopen(playerinfo,"w");
//    for(int i=0;i<=3;i++)
//    {
//        fprintf(fptr,p[i].name);
//        fprintf(fptr," %d",p[i].score);
//        fprintf(fptr,"\n");
//
//    }
//    fclose(fptr);
//
//}

void sortin(player *p)
{
    int i,j;
    //char a[100];
    player c;

    for(i=0; i<4-1; i++)
    {
        for(j=0; j<4-1-i; j++)
        {
            if((p+j)->score>(p+j+1)->score)
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

FILE *fpp;
char stri[1000];

void highscore()
{
    iSetColor(0,0,29);
    iFilledRectangle(100,0,500,320);

    iShowBMP2(100,210,"1st.bmp",0x000000);
    iShowBMP2(100,105,"2nd.bmp",0x000000);
    iShowBMP2(100,0,"3rd.bmp",0x000000);
    if(m_r==1)
    {
        //fileread(fptr);
        sortin(&p[0]);
        fpp=fopen("playerinfo.txt","w");
        for(int i=0; i<4; i++)
        {
            if(i==3)fprintf(fpp,"\n\n%d\n",1<<30);
            else fprintf(fpp,"%s\n%lf\n",p[i].name,p[i].score);
        }
        fclose(fpp);
        m_r=0;
    }


    iSetColor(255,255,255);
    sprintf(stri,"%s %.2lfs",p[0].name,p[0].score);
    iText(200,260,stri);
    sprintf(stri,"%s %.2lfs",p[1].name,p[1].score);
    iText(200,155,stri);
    sprintf(stri,"%s %.2lfs",p[2].name,p[2].score);
    iText(200,55,stri);

//    iText(200,50,"PLAYER:");
//    iText(300,50,m_str2);

    iFilledRectangle(520,30,60,30);
    iSetColor(0,0,0);
    iText(525,35,"CLOSE");
}
void drawmainscrn()
{
    iShowBMP(0,10,"back.bmp");
    iShowBMP2(0,0,"name.bmp",0x000000);

    iSetColor(0,0,0);
    iText(60,550,"ENTER PLAYER'S NAME:");
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
void m_iDraw()
{
    //place your drawing codes here

    iClear();
    drawmainscrn();

    if(m_mode == 1)
    {
        drawcrs(m_len);
        iSetColor(0, 0, 0);
        iText(55, 510, m_str);
    }
//	if(m_on == 1)
//	{
//		iSetColor(255, 255, 255);
//		iText(855, 760, m_bowl);
//	}
//	if(wrt==1){
//            iSetColor(0,0,0);
//            for(int i=0;i<3;i++){
//        iText(10,700-(i*10),p[i].name);
//       // iText(60,700-(i*10),p[i].score);
//            }

    //}
    if(m_on==1)
    {
        // drawgame();
    }
    if(m_h==1)
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
void m_iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void m_iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(mx >= 10 && mx <= 300 && my >= 490 && my <= 530 && m_mode == 0)
        {
            m_mode = 1;
            //mode=1;
        }
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if(mx>=10&&mx<=120&&my>=400&&my<=450)
        {
            PlaySound((LPCSTR)"engine.wav",NULL,SND_FILENAME|SND_ASYNC);
            //m_on=1;
            s_st=clock();
            while(1){
               s_end=clock();
               if(((s_end-s_st)/(double)CLOCKS_PER_SEC)>2)break;
            }
            mode=1;
            initialize();
            strcpy(p[3].name, m_str);
        }
        //PlaySound((LPCSTR)".1sec.wav",NULL,SND_FILENAME|SND_ASYNC);
        //PlaySound((LPCSTR)"Car-Driving-B1-www.fesliyanstudios.com[(036206)11-39-27].wav",NULL,SND_LOOP|SND_ASYNC);
        //place your codes here

    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mx>=10&&mx<=150&&my>=340&&my<=380)
        {
            PlaySound((LPCSTR)"record20190905111143[(000594)12-11-50].wav",NULL,SND_FILENAME|SND_ASYNC);
            m_h=1;
            m_r=1;
        }
        //place your codes here
    }
    //printf("%d\n",w);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mx>=10&&mx<=100&&my>=290&&my<=320)
        {
            //m_q=1;
            exit(0);
        }
        //place your codes here
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mx>=525&&mx<=600&&my>=20&&my<=60)
        {
            PlaySound((LPCSTR)"CSR Racing 2  Menu and Game Theme Music[(000003)12-24-18].wav",NULL,SND_FILENAME|SND_ASYNC);
            m_h=0;

        }
        //place your codes here
    }

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void m_iKeyboard(unsigned char key)
{

    int i;
    if(m_mode == 1)
    {
        if(key == '\r')
        {
            m_mode = 0;
            strcpy(p[3].name, m_str);
            strcpy(m_str2,m_str);
            //printf("%s\n",p[3].name);
            //wrt=1;
//			c++;
            p[3].score=1e20;//player .score is initialized to test it,s value will be taken from game
            for(i = 0; i < m_len; i++)
                m_str[i] = 0;
            m_len = 0;
        }
        else if(key==8)
        {
            //
            {
                m_str[m_len-1]=0;
                m_len--;
                //m_x=0;
            }
        }
        else
        {
            m_str[m_len] = key;
            m_len++;

        }
    }


//	if(key == 'm_x')
//	{
//		//do something with 'm_x'
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
void m_iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_HOME)
    {
        //do something with 'm_x'
        exit(0);
    }

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
//	if(key==GLUT_KEY_F12){
//       //
//            {
//                m_str[m_len-1]=0;
//                m_len--;
//                //m_x=0;
//            }
//	}
    //m_x=1;

//printf("%d",m_x);
    //place your codes for other keys here
}

int m_main()
{
    //place your own initialization codes here.


    m_len = 0;
    m_mode = 0;
    m_on=0;
    m_str[0]= 0;
    m_str2[0]=0;
    m_r=0;
    m_h=0;
    m_x=0;
    //iInitialize(600, 600, "TextInputDemo");
    return 0;
}
