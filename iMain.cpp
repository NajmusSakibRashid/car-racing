#include<math.h>
#include<stdio.h>
#define pi acos(-1)
#include<vector>
#include<iostream>
#include<time.h>
#define LAP 2
#include<windows.h>
#include<mmsystem.h>
#include<string>

using namespace std;

enum {ENGINE,BREAK,COLLISION,STOP};

int _acc=0;

struct _sound{
    int mode;
    char* sndfile[4]={"Car-Driving-B1-www.fesliyanstudios.com[(036206)11-39-27].wav","breaknew.wav","cannon.wav","engine-[AudioTrimmer.com].wav"};
    char* ofsndfile[3]={"cARdriving.wav","breaknew.wav","cannon.wav"};
    clock_t st,ed;
    void turnon(int md)
    {
        if(mode==COLLISION||md==mode)return;
        //cout<<"\n-----------\n";
        PlaySound((LPCSTR)sndfile[md],NULL,SND_LOOP|SND_ASYNC);
        mode=md;
    }
    void turnoff(int md)
    {
        if(md!=mode||mode==COLLISION)return;
        PlaySound((LPCSTR)ofsndfile[1],NULL,SND_FILENAME|SND_ASYNC);
        mode= 4;
    }
    void collision()
    {
        if(mode!=COLLISION){
            PlaySound((LPCSTR)sndfile[2],NULL,SND_FILENAME|SND_ASYNC);
            mode=COLLISION;
            st=clock();
            //return;
        }
    }
    void ofcollision()
    {
        if(mode!=COLLISION)return;
        ed=clock();
        //cout<<"\n"<<ed<<" "<<st<<"-------\n";
        if(2*((ed-st)/(double)CLOCKS_PER_SEC)>1){
            //cout<<"\n"<<ed<<" "<<st<<"-------\n";
            mode=4;
        }
    }

};
_sound sound;

int in,fr,t;
int mode=0;
clock_t t_st=0,t_nw=0,t_end=0,s_st,s_end;

int ind[4];
double di[4],spd[4];

using namespace std;

vector<pair<int,int> >path[4];

struct Block
{
    int x,x1,y,y1,no,X,Y;
};

vector<Block> track;



int grid[1925][50];

bool chkbit(int x,int y)
{
    return grid[y][x/32]&(1<<(x%32));
}

void onbit(int x,int y)
{
    grid[y][x/32]|=(1<<(x%32));
}

int gridcarcol[5][1925][50];

bool chkbitcar(int i,int x,int y)
{
    return gridcarcol[i][y][x/32]&(1<<(x%32));
}

void onbitcar(int i,int x,int y)
{
    gridcarcol[i][y][x/32]|=(1<<(x%32));
}

void offbitcar(int i,int x,int y)
{
    if(x<0||y<0)
        return;
    gridcarcol[i][y][x/32]|=(1<<(x%32));
    gridcarcol[i][y][x/32]^=(1<<(x%32));
}


int i=0,k,start=0;
double ox=0.500000,oy=-265.094342;
//0.500000 -365.094342


/*
	function iDraw() is called again and again by the system.
*/


int ac=0;

struct Car
{
    double x,y,spd;
    int i,m_x,m_y,brek=1,snd=0;
    bool sht=0;
    double dir;
    Car()
    {
        x=135;
        y=300;
        spd=0;
        dir=pi/2;
    }
    void left()
    {
        //if(!spd)return;
        i--;
        dir+=pi/18;
    }
    void right()
    {
        //if(!spd)return;
        i++;
        dir-=pi/18;
    }
    void acc()
    {
        if(spd<0)return;
        _acc=1;
        //sound.turnon(ENGINE);
        //printf("\n---------\n");
        if(spd<(20-10*fr))
            spd+=2;
    }
    void brk()
    {
//        if(brek){
//            PlaySound((LPCSTR)"break.wav",NULL,SND_FILENAME|SND_ASYNC);
//            snd=0;
//            brek=0;
//        }
        if(spd)sound.turnon(BREAK);
        if(spd>5)
            spd-=5;
        else{
            spd=0;
            sound.turnoff(BREAK);
        }
    }
    void updatex()
    {
        x+=spd*cos(dir);
    }
    void updatey()
    {
        y+=spd*sin(dir);
    }
    void updatecx()
    {
        ox-=spd*cos(dir);
    }
    void updatecy()
    {
        oy-=spd*sin(dir);
    }
    double updatedx()
    {
        return x+spd*cos(dir);
    }
    double updatedy()
    {
        return y+spd*sin(dir);
    }
};

Car car;


void update();

//int ind=0;

int f_indx(pair<int,int> a,pair<int,int> b)
{
    double dy=b.second-a.second,dx=b.first-a.first;
    double angle;
    if(dx==0)
    {
        if(dy>0)
            return 0;
        else
            return 18;
    }
    if(dy>=0)
    {
        if(dx>0)
        {
            angle=atan(dy/dx)*18/pi;
            return (9-angle);
        }
        else
        {
            angle=atan(dy/-dx)*18/pi;
            return (int)(27+angle)%36;
        }
    }
    else
    {
        if(dx>0)
        {
            angle=atan(-dy/dx)*18/pi;
            return 9+angle;
        }
        else
        {
            angle=atan(-dy/-dx)*18/pi;
            return 27-angle;
        }
    }
}

int col=1;

int lx[4],ly[4],nc;

double dir_f(int x,int y,int x1,int y1)
{
    double dy=y1-y,dx=x1-x;
    if(dx==0)
    {
        if(dy>0)
            return pi/2;
        return -pi/2;
    }
    if(dx>0)
        return atan(dy/dx);
    return pi-atan(dy/dx);
}

int pos;
char str[100];

int bltrk(int x,int y)
{
    int m_b;
    for(int i=0; i<track.size(); i++)
    {
        if(track[i].x<=x&&x<=track[i].x1&&track[i].y<=y&&y<=track[i].y1)
            m_b=i;
        //if(track[i].x<=opx&&opx<=track[i].x1&&track[i].y<=opy&&opy<=track[i].y1)o_b=i;
    }
    return track[m_b].no;
}

int lap[]= {-1,-1,-1,-1};
bool cnt[]= {1,1,1,1};

void lapcnt(int *lx,int *ly)
{
    int bl;
    for(int i=0; i<4; i++)
    {
        bl=bltrk(lx[i],ly[i]);
        if(bl==1)
        {
            if(cnt[i])
            {
                //cout<<"k"<<endl;
                lap[i]++;
                cnt[i]=0;
            }
        }
        else
            cnt[i]=1;
    }
}

int lappl=-1,lbl=10;

void lapcntpl(int x,int y)
{
    int bl=bltrk(x,y);
    if(bl!=lbl)
    {
        if(bl==1&&lbl==10)
            lappl++;
        if(lbl==1&&bl==10)
            lappl--;
    }
    lbl=bl;
}

bool pos_f(int x,int y,int opx,int opy,int i)
{
    if(lap[i]>lappl)
        return 1;
    else if(lappl>lap[i])
        return 0;

    if(x<0)
        x=0;
    if(y<0)
        y=0;
    if(x>1440)
        x=1440;
    if(y>1824)
        y=1824;
    int m_b,o_b;
    for(int i=0; i<track.size(); i++)
    {
        if(track[i].x<=x&&x<=track[i].x1&&track[i].y<=y&&y<=track[i].y1)
            m_b=i;
        if(track[i].x<=opx&&opx<=track[i].x1&&track[i].y<=opy&&opy<=track[i].y1)
            o_b=i;
    }
    if(m_b==o_b)
    {
        return ((track[m_b].X*x+track[m_b].Y*y)<=(track[m_b].X*opx+track[m_b].Y*opy));
    }
    return track[m_b].no<=track[o_b].no;
}

int g_st=0,_once;

double dx,dy,fric=.07,g_t;

//applause

int l_once;

void initialize()
{
    l_once=1;
    //PlaySound((LPCSTR)"engine.wav",NULL,SND_FILENAME|SND_ASYNC);
    sound.mode=4;
    _once=1;
    start=0;
    g_st=0;
    lappl=-1;
    lbl=10;
    for(int i=0; i<4; i++)
    {
        lap[i]=-1;
        ind[i]=0;
        di[i]=0;
        spd[i]=0;
        cnt[i]=1;
    }
//    cnt=1;
    col=1;
    car.x=135;
    car.y=300;
    ox=.5;
    oy=-265.094342;
    fric=.07;
    car.dir=pi/2;
    car.i=0;
}

# include "iGraphics.h"
# include "progect_igraphix.h"

int g[]= {1,0,0,1},bl[]= {0,0,1,0};
int snd=1,ts,tn,e_once=1;

int bt=0,stp=1;
double lspd;

double asb(double a)
{
    if(a<0)return -a;
    return a;
}

int dwn=0,ku,kudrift,once=1;

int _drift,dr_c;

void g_iDraw()
{
    bt++;
    if(dwn){

        ku=bt;
        dwn=0;
    }
    if(_drift){
        kudrift=bt;
        _drift=0;
    }
    //cout<<bt-ku<<endl;
    if(bt-ku>5){
        if(once&&dr_c<2){
            if(car.spd)sound.turnon(ENGINE);
            else sound.turnon(STOP);
        }
    }
    if(bt-kudrift<2){
        dr_c++;
        if(once&&dr_c>2){
            sound.turnon(BREAK);
            once=0;
        }
        //sound.turnoff(ENGINE);
    }
    else{
        if(dr_c){
            //sound.turnoff(BREAK);
            dr_c=0;
            once=1;
        }
    }
    if(car.spd==0&&lappl<LAP){
        if(e_once){
            //cout<<"\n------------\n";
            sound.turnon(STOP);
            e_once=0;
        }
    }
    else{
        if(sound.mode==4)sound.turnon(ENGINE);
        e_once=1;
    }

    //cout<<dr_c<<endl;
    //if(!car.spd)PlaySound((LPCSTR)".1sec.wav",NULL,SND_FILENAME|SND_ASYNC);
    //place your drawing codes here
    //iClear();
//    if(car.snd&&!car.spd){
//        PlaySound((LPCSTR)".1sec.wav",NULL,SND_FILENAME|SND_ASYNC);
//        //car.snd=0;
//    }
//    if(car.spd==0){
//        sound.turnoff(ENGINE);
//        sound.turnoff(BREAK);
//        //stp=0;
//    }
//    else{
//        stp=1;
//    }

//    if(asb(lspd-car.spd-fric)<.02){
//        //sound.turnoff(BREAK);
//        if(car.spd)sound.turnon(ENGINE);
//    }
//    lspd=car.spd;

    update();
    if(lappl==LAP){
        //sound.mode=BREAK;
        if(_once){
            sound.turnon(BREAK);
            sound.mode=0;
            _once=0;
        }
        //if(fric!=2)PlaySound((LPCSTR)"break.wav",NULL,SND_FILENAME|SND_ASYNC);
        //sound.turnon(BREAK);
        fric=2;
        car.snd=0;
    }
    iShowBMP2(0+ox,0+oy,"background.bmp",-1);
    //iShowBMP2(0+ox,0+oy,"background.bmp",-1);
//    iSetColor(0,0,255);
//    iFilledRectangle(400+ox,400+oy,400,400);


    for(int i=0; i<4; i++)
    {
        k=f_indx(path[i][ind[i]%path[i].size()],path[i][(ind[i]+1)%path[i].size()]);
        for(int k=lx[i]-65; k<=lx[i]+65; k++)
        {
            for(int l=ly[i]-65; l<=ly[i]+65; l++)
            {
                offbitcar(i,k,l);
            }
        }
        iShowBMP2custom(path[i][ind[i]%path[i].size()].first+ox-32,path[i][ind[i]%path[i].size()].second+oy-32,"car65_36s.bmp",0+k*65,0,65,65,0xffffff,i,g[i],bl[i],&in,1,&fr);
        lx[i]=path[i][ind[i]%path[i].size()].first;
        ly[i]=path[i][ind[i]%path[i].size()].second;
    }
    k=(car.i%36<0)?(36+car.i%36):(car.i%36);
//    if(!snd){
//        tn=t;
//        //cout<<tn-ts<<endl;
//        if((tn-ts)>10)snd=1;
//    }
    sound.ofcollision();
    if(iShowBMP2custom(car.x-32,car.y-32,"car65_36s.bmp",0+k*65,0,65,65,0xffffff,1,1,1,&in,0,&fr))
    {
//        if(snd){
//            ts=t;
//            PlaySound((LPCSTR)"cannon.wav",NULL,SND_FILENAME|SND_ASYNC);
//            car.snd=0;
//            snd=0;
//        }

        //cout<<dx<<" "<<dy<<endl;

        if(in!=-1)
        {
            sound.collision();
            col=1;
            dx=(lx[in]-car.x+ox)*((car.spd>5)?car.spd/12:1);
            dy=(ly[in]-car.y+oy)*((car.spd>5)?car.spd/12:1);
            dx/=3;
            dy/=3;
            if(car.x==300)
            {
                //cout<<"\n--------------\n";
                ox+=dx;
            }
            else
                car.x-=dx;
            if(car.y==300)
                oy+=dy;
            else
                car.y-=dy;
        }
        else
        {

            if(col)
            {
                sound.collision();
                if(-10>car.spd&&car.spd>10)
                    car.spd=-car.spd;
                else
                    car.spd=(car.spd>=0)?-10:10;
            }
            col=0;
        }

        //printf("%lf %lf\n",car.x-ox,car.y-oy);
    }
    else
        col=1;
    if(fr&&fric==.07)
    {
        fric=.9;
    }
    else if(fric==.9)
        fric=.07;
    lapcnt(lx,ly);
    lapcntpl(car.x-ox,car.y-oy);

    if(lappl<LAP)
    {
        pos=1;
        for(int i=0; i<4; i++)
        {
            pos+=pos_f(car.x-ox,car.y-oy,lx[i],ly[i],i);

        }
    }
    iSetColor(255,255,255);
    iFilledRectangle(0,0,200,30);
    if(lappl==0&&g_st==0)
    {
        g_st=1;
        t_st=clock();
    }
    if(lappl<LAP)
        t_nw=clock();
    g_t=(t_nw-t_st)/(1.0*CLOCKS_PER_SEC);
    sprintf(str,"Position: %d Time: %.3lfs",pos,g_st?g_t:0);
    iSetColor(255,0,0);
    iText(5,20,str);
    sprintf(str,"Lap: %d Speed: %lf",(lappl<0)?0:lappl,car.spd);
    iText(5,5,str);
    if(lappl==LAP&&car.spd==0)
    {
        if(l_once){
            sound.mode=BREAK;
            sound.turnoff(BREAK);
            l_once=0;
            sound.mode=0;
        }
        iSetColor(0,0,0);
        iFilledRectangle(215,270,170,70);
        iSetColor(255,255,255);
        sprintf(str,"Your final position:%d",pos);
        iText(215,320,str);
        sprintf(str,"Your timing:%.3lfs",g_t);
        iText(225,300,str);
        iText(225,280,"Press Esc to exit.");
    }

//    if(nc!=-1){
//        iFilledRectangle(0,0,50,50);
//        car.dir=dir_f(car.x,car.y,lx[nc],ly[nc]);
//    }



//    iSetColor(0,255,255);
//    iRectangle(200+ox,200+oy,1040,1224);
//    iFilledCircle(200,200,5);
}

void iDraw()
{
    if(mode)
        g_iDraw();
    else
        m_iDraw();
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void g_iMouseMove(int mx, int my)
{

    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

void iMouseMove(int mx,int my)
{
    if(mode)
        g_iMouseMove(mx,my);
    else
        m_iMouseMove(mx,my);
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void g_iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        car.sht=1;
        car.m_x=mx;
        car.m_y=my;

    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //place your codes here
        car.sht=0;

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

void iMouse(int button,int state,int mx,int my)
{
    if(mode)
        g_iMouse(button,state,mx,my);
    else
        m_iMouse(button,state,mx,my);
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void g_iKeyboard(unsigned char key)
{
    if(key == 27)
    {
        if(lappl==LAP&&car.spd==0)
        {
            PlaySound((LPCSTR)"CSR Racing 2  Menu and Game Theme Music[(000003)12-24-18].wav",NULL,SND_LOOP|SND_ASYNC);
            mode^=1;
            p[3].score=g_t;
            sortin(&p[0]);
            fpp=fopen("playerinfo.txt","w");
            for(int i=0; i<4; i++)
            {
                if(i==3)
                    fprintf(fpp,"\n\n%d\n",1<<30);
                else
                    fprintf(fpp,"%s\n%lf\n",p[i].name,p[i].score);
            }
            fclose(fpp);
        }
//        ind++;
//        k=f_indx(path[ind],path[ind+1]);
//        cout<<k<<endl;
        //printf("%lf %lf\n",ox,oy);
    }
    //place your codes for other keys here
}

void iKeyboard(unsigned char key)
{
    //printf("%d\n",key);
    //if(key==27)mode^=1;
    if(mode)
        g_iKeyboard(key);
    else
        m_iKeyboard(key);
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

void g_iSpecialKeyboard(unsigned char key)
{
    if(start==0)
    {
        start=1;

        //t_st=clock();
    }

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key == GLUT_KEY_LEFT)
    {
        _drift=1;
        car.acc();
        car.left();
    }
    if(key == GLUT_KEY_RIGHT)
    {
        _drift=1;
        car.acc();
        car.right();
    }
    if(key == GLUT_KEY_UP)
    {
        car.acc();
    }
    if(key == GLUT_KEY_DOWN)
    {
        dwn=1;
        car.brk();
        //car.spd=0;
    }
    //place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{
    //printf("sp %d\n",key);
    if(mode)
    {
        if(lappl<LAP)
            g_iSpecialKeyboard(key);
    }
    else
        m_iSpecialKeyboard(key);
}

void update()
{
    if(!mode)
        return;
    if(car.spd<2&&car.spd>0)car.spd=0;
    if(car.spd<0)
        car.spd+=1;
    else if(car.spd>fric)
        car.spd-=fric;
    else
        car.spd=0;
    double x=car.x-ox,y=car.y-oy;
    if(0.0<=car.updatedx()&&car.updatedx()<=600.0)
    {
        if(300.0<=x&&x<=1140.0)
        {
            car.x=300;
            car.updatecx();
        }
        else
            car.updatex();
    }
    if(0<=car.updatedy()&&car.updatedy()<=600.0)
    {
        if(300.0<=y&&y<=1524.0)
        {
            car.y=300;
            car.updatecy();
        }
        else
            car.updatey();
    }
}

//double di=0;

double slw[]= {.1,.09,.07,.05};

void paths()
{
    t++;
    if(!mode)
        return;
    if(!start)
        return;
//    di+=3;
//    ind=di;
    for(int i=0; i<4; i++)
    {
        if(spd[i]<0)
            continue;
        if(lap[i]==LAP&&spd[i]>0)
        {
            //if(spd[i]<slw[i])spd[i]=0;
            spd[i]-=slw[i];
        }
        else if(spd[i]<2.7)
        {
            spd[i]+=.15;
        }
        di[i]+=spd[i];
        ind[i]=di[i];
    }
}

char scn[100];

void _sound()
{
    if(car.spd)PlaySound((LPCSTR)"2th.wav",NULL,SND_FILENAME|SND_ASYNC);
}

int main()
{
    PlaySound((LPCSTR)"CSR Racing 2  Menu and Game Theme Music[(000003)12-24-18].wav",NULL,SND_LOOP|SND_ASYNC);
    //PlaySound((LPCSTR)"2th.wav",NULL,SND_LOOP|SND_ASYNC);
    //record20190913115029.3gpp
    //
    m_main();
    //iSetTimer(500,paths);
    //place your own initialization codes here.
    iSetTimer(1,paths);
    //iSetTimer(1000,_sound);

//    for(int i=0;i<400;i++){
//        for(int j=0;j<400;j++){
//            onbit(i+400,j+400);
//        }
//    }
    FILE *fp=fopen("col.txt","r"),*fp1=fopen("4path.txt","r"),*fp2=fopen("block.txt","r"),*fp3=fopen("friction.txt","r"),*fp4=fopen("playerinfo.txt","r");
    for(int i=0; i<1925; i++)
    {
        for(int j=0; j<50; j++)
        {
            fscanf(fp,"%d",&grid[i][j]);
        }
    }
    fclose(fp);
    if(fp3==NULL)
    {
        cout<<"error"<<endl;
        return 0;
    }
    for(int i=0; i<1925; i++)
    {
        for(int j=0; j<50; j++)
        {
            fscanf(fp3,"%d",&gridcarcol[4][i][j]);
        }
    }
    fclose(fp3);
    int a,b,k=0,cnt=-1;

    while(fscanf(fp1,"%d%d",&a,&b)==2)
    {
        if(a==0&&b==0)
        {
            cnt++;
            continue;
        }
        path[cnt].push_back(make_pair(a,b));
    }
    fclose(fp1);

    Block bl;

    while(fscanf(fp2,"%d%d%d%d%d%d%d",&bl.x,&bl.y,&bl.x1,&bl.y1,&bl.no,&bl.X,&bl.Y)==7)
    {
        track.push_back(bl);
    }
//    while(fscanf(fp2,"%d%d",&a,&b)==2){
//        //printf("%d\n",k++);
//        path[1].push_back(make_pair(a,b));
//    }
    fclose(fp2);
    //if(fp4==NULL)printf("\n------------\n");
    for(int i=0; i<4; i++)
    {
        fscanf(fp4,"%[^\n]s",p[i].name);
        fgetc(fp4);
        fscanf(fp4,"%lf",&p[i].score);
        fgetc(fp4);
    }
    for(int i=0; i<4; i++)
    {
        printf("%s %lf\n",p[i].name,p[i].score);
    }
    fclose(fp4);
    //printf("\n------------\n");
//    while(fscanf(fp3,"%d%d",&a,&b)==2){
//        //printf("%d\n",k++);
//        path[2].push_back(make_pair(a,b));
//    }
//    fclose(fp3);
//    while(fscanf(fp4,"%d%d",&a,&b)==2){
//        //printf("%d\n",k++);
//        path[3].push_back(make_pair(a,b));
//    }
//    fclose(fp4);

    iInitialize(600, 600, "Car racing");
    return 0;
}
/*
Najmus Sakib Rashid
1000
Anwar Hossain
500
Hasan Mahmud
300
KM Asif
150
*/
