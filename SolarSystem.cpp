/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"

int g_sunX, g_sunY, g_sunR;
int g_planetOrbitR, g_planetR, g_planetSweepAngle;
int g_satelliteOrbitR, g_satelliteR, g_satelliteSweepAngle;

void drawStar(int x, int y, int r) {
    iSetColor(255, 255, 0);
    iFilledCircle(x, y, r);
}

void drawOrbit(int x, int y, int r) {
    iSetColor(255, 255, 255);
    iCircle(x, y, r);
}

void drawPlanet(int starX, int starY, int orbitR, int planetR, int sweepAngle) {
    double pi = 2*acos(0);
    double sweepRadian = sweepAngle * pi / 180;
    int planetX = starX + orbitR * cos(sweepRadian);
    int planetY = starY + orbitR * sin(sweepRadian);

    iSetColor(125, 125, 125);
    iFilledCircle(planetX, planetY, planetR);
}

void drawSatellite(
    int starX,
    int starY,
    int planetOrbitR,
    int planetSweepAngle,
    int satelliteOrbitR,
    int satelliteR,
    int satelliteSweepAngle) {
    double pi = 2*acos(0);
    double planetSweepRadian = planetSweepAngle * pi / 180;
    double satelliteSweepRadian = satelliteSweepAngle * pi / 180 + planetSweepRadian;

    int planetX = starX + planetOrbitR * cos(planetSweepRadian);
    int planetY = starY + planetOrbitR * sin(planetSweepRadian);

    int satelliteX = planetX + satelliteOrbitR * cos(satelliteSweepRadian);
    int satelliteY = planetY + satelliteOrbitR * sin(satelliteSweepRadian);

    iSetColor(62, 62, 62);
    iFilledCircle(satelliteX, satelliteY, satelliteR);
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();

	drawStar(g_sunX, g_sunY, g_sunR);
	drawOrbit(g_sunX, g_sunY, g_planetOrbitR);
	drawPlanet(g_sunX, g_sunY, g_planetOrbitR, g_planetR, g_planetSweepAngle);
	drawSatellite(
        g_sunX,
        g_sunY,
        g_planetOrbitR,
        g_planetSweepAngle,
        g_satelliteOrbitR,
        g_satelliteR,
        g_satelliteSweepAngle
        );

	iSetColor(255, 255, 255);
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
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
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	//place your codes for other keys here
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

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

void movePlanets(){
    const int g_dPlanetSweepAngle = 1;
    const int g_dSatelliteSweepAngle = 10;
    g_planetSweepAngle = (g_planetSweepAngle + g_dPlanetSweepAngle)%360;
    g_satelliteSweepAngle = (g_satelliteSweepAngle + g_dSatelliteSweepAngle)%360;
}

int main()
{
    const int CX_MAX = 800;
    const int CY_MAX = 600;

    // Initialize Sun's position and size.
    g_sunX = CX_MAX/2;
    g_sunY = CY_MAX/2;
    g_sunR = 25;

    // Initialize earth's orbit and radius
    g_planetOrbitR = 100;
    g_planetR = 10;
    g_planetSweepAngle = 0;

    // Initialize moon's orbit and radius
    g_satelliteOrbitR = 40;
    g_satelliteR = 5;
    g_planetSweepAngle = 45;

	//place your own initialization codes here.
	iSetTimer(20, movePlanets);
	iInitialize(CX_MAX, CY_MAX, "Solar system!");

	return 0;
}

