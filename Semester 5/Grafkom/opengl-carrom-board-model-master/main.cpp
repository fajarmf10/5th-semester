
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl\glut.h>			// Header File For The GLu32 Library
#include<stdio.h>
#include<bits/stdc++.h>
#include "color.h"
#include "texture.h"
using namespace std;
#define eps 10e-8
void BlankBoard(void);


float RotX=0.0f, RotY=0.0f, RotZ=0.0f;
bool right = 1, left = 0, middle = 0;
float Rotation=0;
float XX=0, YY = 20, ZZ = 25, XXX, ZZZ;
int Flag = 0;
int red=1.0f, green=1.0f, blue=1.0f;
int ScreenX, ScreenY;
int PressCount=0;
bool MouseClicked = false;
bool strikerselected = false;
bool hittingPointSelected = false;
int Timer = 25;
bool StrikerHitted = false;
bool MenPocketed = false;
bool HitNow = false;

GLdouble nx, ny, nz; //near world space.
GLdouble fx, fy, fz; //far world space.


struct Pos{
    float x, y, z;
    float hx, hy, hz;
    float MovingAngle;
}
    STRIKER = {0,0,7,0,0,7,0},
    MENWHITE[10],
    MENBLACK[10],
    RED = {3.7973, 0, 0, 3, 0, 0};
;



void processMouse(int button, int state, int x, int y) {


        //int  specialKey = glutGetModifiers();
       // if ((state == GLUT_DOWN) &&
		//	(specialKey == GLUT_ACTIVE_ALT)) {
        PressCount++;
        MouseClicked = false;
        if (button == GLUT_LEFT_BUTTON){
                if(PressCount==2) {

                    PressCount = 0;
                    MouseClicked = true;

                    GLint viewport[4];
                    GLdouble mvmatrix[16], projmatrix[16];
                    GLint realY; //OpenGL coordinate, not window coordinate.


                    //test for which button, etc.....

                    glGetIntegerv(GL_VIEWPORT, viewport);
                    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
                    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
                    //viewport[3] is height of window in pixels
                    realY = viewport[3]-(GLint)y;

                    //print out mouse point if you wish.

                    gluUnProject((GLdouble)x, (GLdouble)realY, 0.0, mvmatrix, projmatrix, viewport, &nx, &ny, &nz);

                    //Print world space at Z=0.0f
                    //printf("start %lf %lf %lf\n", nx, ny, nz);

                    gluUnProject((GLdouble)x, (GLdouble)realY, 1.0, mvmatrix, projmatrix, viewport, &fx, &fy, &fz);

                    //Print world space at Z=1.0f;
                    //printf("end %lf %lf %lf\n", fx, fy, fz);

                }
		}


		//}
		glutPostRedisplay();
}
void Resize(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix


	//glOrtho(-100, 100, -100, 100, -100, 100);
	gluPerspective(45.0, 640.0f / 480.0f, 10, 500);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	  case 27: //Escape key
			exit(0);
      case '1':
            if(abs(XX+1)<31)
            XX+=1;
            glutPostRedisplay();
            break;
      case '2':
            if(abs(XX-1)<31)
            XX-=1;
            glutPostRedisplay();
            break;
      case '3':
            if(abs(YY+1)<31)
            YY+=1;
            glutPostRedisplay();
            break;
      case '4':
            if(abs(YY-1)<31)
            YY-=1;
            glutPostRedisplay();
            break;
      case '5':
            if(abs(ZZ+1)<31)
            ZZ+=1;
            glutPostRedisplay();
            break;
      case '6':
            if(abs(ZZ-1)<31)
            ZZ-=1;
            glutPostRedisplay();
            break;
      case 'a':
            Rotation+=5;
            if(Rotation>=360)
                Rotation=0;

            glutPostRedisplay();
            break;
      case 'd':
            Rotation-=5;
            if(Rotation<=-360)
                Rotation=0;

            glutPostRedisplay();
            break;

      default:
        break;

    }
}

void DrawOnlyCircle(double cx, double cy, double cz, double r, int num_segments, color_combination Col){
    int ii;
    double theta, p, q, i;
    glBegin(GL_LINE_LOOP);
    glColor3f( Col.r, Col.g, Col.b);
    for(ii=0;ii<num_segments;ii++){
        i = (double)ii/(double)num_segments;
        theta = 2.0f*3.1415926f*i;
        p = r*cosf(theta);
        q = r*sinf(theta);

        if(cx==1) glVertex3f(0, p+cy, q+cz);
        if(cy==1) glVertex3f(p+cx, 0, q+cz);
        if(cz==1) glVertex3f(p+cx, q+cy, 0);
    }
    glEnd();
}

void DrawCircle(double cx, double cy, double cz, double r, int num_segments, color_combination Col){
    int ii;
    double theta, p, q, i;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f( Col.r, Col.g, Col.b);
    for(ii=0;ii<num_segments;ii++){
        i = (double)ii/(double)num_segments;
        theta = 2.0f*3.1415926f*i;
        p = r*cosf(theta);
        q = r*sinf(theta);

        if(cx==1) glVertex3f(0, p+cy, q+cz);
        if(cy==1) glVertex3f(p+cx, 0, q+cz);
        if(cz==1) glVertex3f(p+cx, q+cy, 0);
    }
    glEnd();
}

void DrawTriangle(float x, float z,  color_combination Col)
{
    glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor3f(Col.r,Col.g,Col.b);						// Red
		glVertex3f( -x, 0, 0);					// Top Of Triangle (Front)
		glVertex3f( x, 0, 0);						// Green
		glVertex3f(0, 0, -z);					// Left Of Triangle (Front)
	glEnd();											// Done Drawing The Pyramid
}

void DrawQuad(float x, float y, float z, color_combination Col)
{
    x /= 2; y /= 2; z /= 2;

    glBegin(GL_QUADS);									// Draw A Quad
		glColor3f( Col.r, Col.g, Col.b);						// Set The Color To Green

		glVertex3f(-x, y, z);					// Top Right Of The Quad (Top)
		glVertex3f(x, y, z);					// Top Left Of The Quad (Top)
		glVertex3f(x, y, -z);					// Bottom Left Of The Quad (Top)
		glVertex3f(-x, y, -z);					// Bottom Right Of The Quad (Top)

	glEnd();											// Done Drawing The Quad
}
void DrawQube(float x, float y, float z, color_combination Col)
{
    x /= 2; y /= 2; z /= 2;

    glBegin(GL_QUADS);							// Draw A Quad
		glColor3f( Col.r, Col.g, Col.b);		// Set The Color To Green

		glVertex3f(-x, y, z);					// Top Right Of The Quad (Top)
		glVertex3f(x, y, z);					// Top Left Of The Quad (Top)
		glVertex3f(x, y, -z);					// Bottom Left Of The Quad (Top)
		glVertex3f(-x, y, -z);					// Bottom Right Of The Quad (Top)

		glColor3f( Col.r, Col.g, Col.b);				// Set The Color To Orange

		glVertex3f(-x, -y, z);					// Top Right Of The Quad (Bottom)
		glVertex3f(x, -y, z);					// Top Left Of The Quad (Bottom)
		glVertex3f(x, -y, -z);					// Bottom Left Of The Quad (Bottom)
		glVertex3f(-x, -y, -z);					// Bottom Right Of The Quad (Bottom)

		glColor3f( Col.r, Col.g, Col.b);						// Set The Color To Red

		glVertex3f(-x, -y, z);					// Top Right Of The Quad (Front)
		glVertex3f(x, -y, z);					// Top Left Of The Quad (Front)
		glVertex3f(x, y, z);					// Bottom Left Of The Quad (Front)
		glVertex3f(-x, y, z);					// Bottom Right Of The Quad (Front)

		glColor3f( Col.r, Col.g, Col.b);						// Set The Color To Yellow

		glVertex3f(-x, -y, -z);					// Top Right Of The Quad (Back)
		glVertex3f(x, -y, -z);					// Top Left Of The Quad (Back)
		glVertex3f(x, y, -z);					// Bottom Left Of The Quad (Back)
		glVertex3f(-x, y, -z);					// Bottom Right Of The Quad (Back)

		glColor3f( Col.r, Col.g, Col.b);						// Set The Color To Blue

		glVertex3f(-x, -y, z);					// Top Right Of The Quad (Left)
		glVertex3f(-x, -y, -z);					// Top Left Of The Quad (Left)
		glVertex3f(-x, y, -z);					// Bottom Left Of The Quad (Left)
		glVertex3f(-x, y, z);					// Bottom Right Of The Quad (Left)

		glColor3f( Col.r, Col.g, Col.b);						// Set The Color To Violet

		glVertex3f(x, -y, z);					// Top Right Of The Quad (Right)
		glVertex3f(x, -y, -z);					// Top Left Of The Quad (Right)
		glVertex3f(x, y, -z);					// Bottom Left Of The Quad (Right)
		glVertex3f(x, y, z);					// Bottom Right Of The Quad (Right)

	glEnd();											// Done Drawing The Quad
}
int InitGL()										// All Setup For OpenGL Goes Here
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

void DrawCylinder(float r, float height, color_combination Col){

        glPushMatrix();

            GLUquadricObj* cyl;
            cyl = gluNewQuadric();
            gluQuadricDrawStyle(cyl, GL_SMOOTH);
            DrawCircle(0,1,0,r,180,Col);
            glTranslatef(0,height,0);
            DrawCircle(0,1,0,r,180,Col);
            glRotatef(90,1,0,0);
            glColor3f(Gray50.r, Gray50.g, Gray50.b);
            gluCylinder(cyl, r, r, height, 50, 50);

        glPopMatrix();

}

void drawStriker(){

        glPushMatrix();
            glTranslatef(STRIKER.x, STRIKER.y, STRIKER.z);
            DrawCylinder(0.7,0.2,Green);
        glPopMatrix();

}
void drawRed(){

        glPushMatrix();
            glTranslatef(RED.x, RED.y, RED.z);
            DrawCylinder(0.7,0.1,Red);
        glPopMatrix();


}

bool checkHitObject(float x, float y, float z){

    if(!strikerselected && (abs(STRIKER.y+0.2 - y)<=0.1) && (abs( STRIKER.x - x)<=0.7 && abs(STRIKER.z - z)<=0.7 )){
        //cout << abs( STRIKER.x - x) << " " << abs(STRIKER.z - z) << " " << abs(STRIKER.z - z) << endl;
        glPushMatrix();
            glTranslatef(STRIKER.x,STRIKER.y+0.2,STRIKER.z);
            DrawCircle(0,1,0,0.7,180,Yellow);
            strikerselected = true;
            hittingPointSelected = false;
        glPopMatrix();
        return true;
    }
    if(strikerselected){
        if(!hittingPointSelected){
            if(fabs(y-eps)<=0.55){
                STRIKER.hx = x;
                STRIKER.hy = 0.55+0.1;
                STRIKER.hz = z;
                hittingPointSelected = true;
                strikerselected = false;
                //cout << STRIKER.hx << " " << STRIKER.hy << " " << STRIKER.hz << endl;
                return true;
            }
        }
    }
    return false;
}
void clickRayPoints(){
    float tx, ty, tz;
    for(float t=0;t<=1;t+=0.0001){
        tx = nx + t*(fx-nx);
        ty = ny + t*(fy-ny);
        tz = nz + t*(fz-nz);
        //cout << tx << " " << ty << " " << tz << endl;
        if(checkHitObject(tx,ty,tz)) {
            HitNow = true;
            return;
        }

    }
}

void DrawGLScene()									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();



    gluLookAt(  XX,  YY, ZZ,
                0.0f,  0.0f, 0.0f,
                0.0f, 1.0f, 0.0f
	        );

    //cout << XX << " " << YY << " " << ZZ << endl;
    glRotatef(Rotation, 0, 1, 0);

    DrawWall();

    BlankBoard();

        glTranslatef(0,0.55f,0);
        drawStriker();
        if(MenPocketed==false)
        drawRed();
        else HitNow = false;

    //glPopMatrix();
    if(MouseClicked)
        clickRayPoints();

	glutSwapBuffers();

}
int autoTourFlag = 0;
void autoTour(int value){
    if(HitNow==true){
        if(abs(XX+1)<31 && autoTourFlag==0)
            XX+=1;
        else
            autoTourFlag = 1;
        if(abs(XX-1)<31 && autoTourFlag==1)
            XX-=1;
        else autoTourFlag = 0;

    }
        glutPostRedisplay();
        glutTimerFunc(Timer, autoTour, 0);

}
void HitMen(int value) {

        if(HitNow==true)
        {
        float m = STRIKER.x - RED.x;
        float n = STRIKER.z - RED.z;


        if(StrikerHitted == true)
        {


            float o = RED.x - 8.3;
            float p = RED.z + 8.3;


            if(sqrt(o*o + p*p) <= 0.1f)
            {
                MenPocketed = true;

            }

            if(MenPocketed == false){
                RED.x += 0.1;

                RED.z =  -1.8434*RED.x + 7; // 7 is tangent
                cout << STRIKER.x << " " << STRIKER.z << endl;
                //glutPostRedisplay();
            }

        }

        if(StrikerHitted == false)
        {
            if(sqrt(m*m + n*n) <= 1.5f)
            {
                StrikerHitted = true;

            }


            STRIKER.x += 0.1;
            STRIKER.z =  -1.8434*STRIKER.x + 7; // 7 is tangent
            cout << STRIKER.x << " " << STRIKER.z << endl;

            //glutPostRedisplay();

        }
    }

    glutPostRedisplay();
	glutTimerFunc(Timer, HitMen, 0);

}

int  main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutCreateWindow("GLUT Shapes");

    InitGL();
    Texture();
	init2();




    glutReshapeFunc(Resize);
    glutDisplayFunc(DrawGLScene);


    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(Timer, HitMen, 0);
    glutTimerFunc(Timer, autoTour, 0);
    glutMouseFunc(processMouse);


    //glClearColor(0,0,0,0);

    glutMainLoop();

    return 0;
}


void BlankBoard(){
   glPushMatrix();
  //Main Board
   DrawQube(20,1,20,DarkBrown);
   glTranslatef(0,0.5,0);

   //Legs of the board
    {

         glPushMatrix();
             glTranslatef(-8,-4, 8);
             DrawQube(1,8,1,DarkBrown);
         glPopMatrix();

         glPushMatrix();
             glTranslatef(-8,-4, -8);
             DrawQube(1,8,1,DarkBrown);
         glPopMatrix();

         glPushMatrix();
             glTranslatef(8,-4, 8);
             DrawQube(1,8,1,DarkBrown);
         glPopMatrix();

        glPushMatrix();
             glTranslatef(8,-4, -8);
             DrawQube(1,8,1,DarkBrown);
         glPopMatrix();
    }


         //White Ground
         DrawQuad(20,0.05,20,Cream);

         glPopMatrix();

         //Left Border
         glPushMatrix();

         glTranslatef(-9.5,0.55,0);
         DrawQube(1,0.5,20,Copper);

         glPopMatrix();

        //Right Border
         glPushMatrix();

         glTranslatef(9.5,0.55,0);
         DrawQube(1,0.5,20,Copper);

         glPopMatrix();

        //Front Border
         glPushMatrix();

         glTranslatef(0,0.55,9.5);
         DrawQube(20,0.5,1,Copper);

         glPopMatrix();

        //Back Border
         glPushMatrix();

         glTranslatef(0,0.55,-9.5);
         DrawQube(20,0.5,1,Copper);

         glPopMatrix();

         //Pocket
         glPushMatrix();

         glTranslatef(-8.3,0.55,-8.3);
         DrawCircle(0,1,0,0.7,180, Black);

         glPopMatrix();

         //Pocket
         glPushMatrix();

         glTranslatef(-8.3,0.55,8.3);
         DrawCircle(0,1,0,0.7,180, Black);

         glPopMatrix();
         //Pocket
         glPushMatrix();

         glTranslatef(8.3,0.55,8.3);
         DrawCircle(0,1,0,0.7,180, Black);

         glPopMatrix();
         //Pocket
         glPushMatrix();

         glTranslatef(8.3,0.55,-8.3);
         DrawCircle(0,1,0,0.7,180, Black);

         glPopMatrix();

         //CenterCircle

         glPushMatrix();

         glTranslatef(0,0.55,0);
         DrawOnlyCircle(0,1,0,3,360, VioletBlue);
         DrawOnlyCircle(0,1,0,3.1,360, VioletBlue);

         glPopMatrix();

         //Center Small Circle
         glPushMatrix();

         glTranslatef(0,0.55,0);
         DrawCircle(0,1,0,1,360, Pink);

         glPopMatrix();

         //Center Star Design
         glPushMatrix();



         glTranslatef(0,0.55,-1);
         for(int i=0; i<12; i++){

                 DrawTriangle(0.3, 2, RedOrange);

                 glTranslatef(0,0,1);
                 glRotatef(30,0,1,0);
                 glTranslatef(0,0,-1);

                 //DrawTriangle(0.3, 2, 1, Scarlet);
         }

         glPopMatrix();

        //Where to strike
        glPushMatrix();
        {

             glBegin(GL_LINES);
             glColor3f(0,0,0);
             glVertex3f(-5.8, 0.55, 7.5);
             glVertex3f(5.8, 0.55, 7.5);
             glEnd();

             glBegin(GL_LINES);
             glColor3f(0,0,0);
             glVertex3f(-5.8, 0.55, 6.5);
             glVertex3f(5.8, 0.55, 6.5);
             glEnd();

             glPushMatrix();
             {
                glTranslatef(-5.8, 0.55, 7);
                DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
             }
             glPopMatrix();

             glPushMatrix();
             {
                 glTranslatef(5.8, 0.55, 7);
                 DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                 DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                 DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
             }
             glPopMatrix();
        }

        glPopMatrix();

        // Lines where to strike
        glPushMatrix();
        {

             glBegin(GL_LINES);
             glColor3f(0,0,0);
             glVertex3f(-5.8, 0.55, -7.5);
             glVertex3f(5.8, 0.55, -7.5);
             glEnd();

             glBegin(GL_LINES);
             glColor3f(0,0,0);
             glVertex3f(-5.8, 0.55, -6.5);
             glVertex3f(5.8, 0.55, -6.5);
             glEnd();

             glPushMatrix();
             {
                glTranslatef(-5.8, 0.55, -7);
                DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
             }
             glPopMatrix();

             glPushMatrix();
             {
                 glTranslatef(5.8, 0.55, -7);
                 DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                 DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                 DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
             }
             glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(90, 0, 1, 0);


                glPushMatrix();
                {

                     glBegin(GL_LINES);
                     glColor3f(0,0,0);
                     glVertex3f(-5.8, 0.55, 7.5);
                     glVertex3f(5.8, 0.55, 7.5);
                     glEnd();

                     glBegin(GL_LINES);
                     glColor3f(0,0,0);
                     glVertex3f(-5.8, 0.55, 6.5);
                     glVertex3f(5.8, 0.55, 6.5);
                     glEnd();

                     glPushMatrix();
                     {
                        glTranslatef(-5.8, 0.55, 7);
                        DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                        DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                        DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
                     }
                     glPopMatrix();

                     glPushMatrix();
                     {
                         glTranslatef(5.8, 0.55, 7);
                         DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                         DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                         DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
                     }
                     glPopMatrix();
                }

                glPopMatrix();

                // Lines where to strike
                glPushMatrix();
                {

                     glBegin(GL_LINES);
                     glColor3f(0,0,0);
                     glVertex3f(-5.8, 0.55, -7.5);
                     glVertex3f(5.8, 0.55, -7.5);
                     glEnd();

                     glBegin(GL_LINES);
                     glColor3f(0,0,0);
                     glVertex3f(-5.8, 0.55, -6.5);
                     glVertex3f(5.8, 0.55, -6.5);
                     glEnd();

                     glPushMatrix();
                     {
                        glTranslatef(-5.8, 0.55, -7);
                        DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                        DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                        DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
                     }
                     glPopMatrix();

                     glPushMatrix();
                     {
                         glTranslatef(5.8, 0.55, -7);
                         DrawCircle(0, 1, 0, 0.5, 180, LightBlue);
                         DrawOnlyCircle(0, 1, 0, 0.5, 180, Black);
                         DrawOnlyCircle(0, 1, 0, 0.51, 180, Black);
                     }
                     glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();

        // Arrows
        glPushMatrix();
        {
            glTranslatef(0,0.55,0);
            glBegin(GL_LINES);
            glVertex3f(2.5,0,2.5);
            glVertex3f(7.5, 0, 7.5);
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(7.5, 0, 7.5);
            glVertex3f(7.5, 0, 7.1);
            glVertex3f(7.8, 0, 7.8);
            glVertex3f(7.1, 0, 7.5);
            glVertex3f(7.5, 0, 7.5);
            glEnd();

        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0,0.55,0);
            glBegin(GL_LINES);
            glVertex3f(-2.5,0,2.5);
            glVertex3f(-7.5, 0, 7.5);
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(-7.5, 0, 7.5);
            glVertex3f(-7.5, 0, 7.1);
            glVertex3f(-7.8, 0, 7.8);
            glVertex3f(-7.1, 0, 7.5);
            glVertex3f(-7.5, 0, 7.5);
            glEnd();

        }
        glPopMatrix();

        glPushMatrix();
        {

            glRotatef(180,0,1,0);

                glPushMatrix();
                {
                    glTranslatef(0,0.55,0);
                    glBegin(GL_LINES);
                    glVertex3f(2.5,0,2.5);
                    glVertex3f(7.5, 0, 7.5);
                    glEnd();

                    glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(7.5, 0, 7.5);
                    glVertex3f(7.5, 0, 7.1);
                    glVertex3f(7.8, 0, 7.8);
                    glVertex3f(7.1, 0, 7.5);
                    glVertex3f(7.5, 0, 7.5);
                    glEnd();

                }
                glPopMatrix();
                glPushMatrix();
                {
                    glTranslatef(0,0.55,0);
                    glBegin(GL_LINES);
                    glVertex3f(-2.5,0,2.5);
                    glVertex3f(-7.5, 0, 7.5);
                    glEnd();

                    glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(-7.5, 0, 7.5);
                    glVertex3f(-7.5, 0, 7.1);
                    glVertex3f(-7.8, 0, 7.8);
                    glVertex3f(-7.1, 0, 7.5);
                    glVertex3f(-7.5, 0, 7.5);
                    glEnd();

                }
                glPopMatrix();
        }
        glPopMatrix();
}
