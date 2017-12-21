#include <stdio.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <gl\freeimage.h>
#include "glm.h"

using namespace std;

GLMmodel *tembok, *sample1, *sample2, *sample3, *sample4, *sample5, *sample6, *obj1, *lukisan, *jendela;
float ratio;
float atas[101], kanan[101], maju[101], setX[101], setY[101], setZ[101];
float up[101], Right[101], save[101];
int rotasi[101];
int vObj, vOpt;

void parsingNum(int x)
{
    tekstur[num] = x;
}

void mymenu(int id)
{
    num = id;
    printf("%d\n", num);
    //glutPostRedisplay();
}

void Init()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 440);
    glViewport(0, 0, 640, 440);
}

void lukisanDinding()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!lukisan)
    {
        lukisan = glmReadOBJ("picture/picture.obj");
        if(!lukisan) exit(0);
        glmUnitize(lukisan);
    }
    glTranslated(0, 1, -4);
    glScalef(6, 6, 0);
   // gluLookAt(5.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(lukisan, GL_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
    //glutSwapBuffers();
}

void JendelaDinding()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!jendela)
    {
        jendela = glmReadOBJ("jam/Clock_OBJ.obj");
        if(!jendela) exit(0);
        glmUnitize(jendela);
    }
    glTranslated(0, 1, -3);
    glScalef(2, 2, 2);
    glRotated(90, 1, 1, 0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(jendela, GL_SMOOTH | GLM_TEXTURE );
    glPopMatrix();
    glFlush();
    //glutSwapBuffers();
}

void menuBar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!obj1)
    {
        obj1 = glmReadOBJ("menu/navbar.obj");
        if(!obj1) exit(0);
        glmUnitize(obj1);
    }
    lukisanDinding();
    glTranslated(0, -1.125, -1.5);
    glScalef(2.43, 2.5, 1);
    glRotated(90, 1, 0, 0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(obj1, GL_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
    //glutSwapBuffers();
}

void display6()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!sample6)
    {
        sample6 = glmReadOBJ("pot/maceta.obj");
        if(!sample6) exit(0);
        glmUnitize(sample6);
    }
    menuBar();
    setX[11] = setX[12] = 1;
    setY[11] = setY[12] = -2;
    setZ[11] = setZ[12] = -4;
    if(num == 0) glTranslatef(1, -1.9, -4);
    else
        if(num == 11)
        {
            glTranslatef(1+kanan[num], -1.9+atas[num], -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            {
                glTranslatef(1+Right[11], -1.9+up[11], -4+maju[11]);
                if(num != 11 && num != 12) glRotated(rotasi[12], 0, 1, 0);
            }
    if(num == 12)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(0.7, 0.7, 0.7);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample6, GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display5()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!sample5)
    {
        sample5 = glmReadOBJ("Table Bed/Table de nuit_Final.obj");
        if(!sample5) exit(0);
        glmUnitize(sample5);
    }
    display6();
    setX[9] = setX[10] = 0;
    setY[9] = setY[10] = -2;
    setZ[9] = setZ[10] = -4;
    if(num == 0) glTranslatef(0, -2, -4);
    else
        if(num == 9)
        {
            glTranslatef(kanan[num], -2, -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            {
                glTranslatef(Right[9], -2, -4+maju[9]);
                if(num != 9 && num != 10) glRotated(rotasi[10], 0, 1, 0);
            }
    if(num == 10)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(0.5, 0.5, 0.5);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample5, GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display4()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!sample4)
    {
        sample4 = glmReadOBJ("Modern Desktop/ModernDeskOBJ.obj");
        if(!sample4) exit(0);
        glmUnitize(sample4);
    }
    display5();
    setX[7] = setX[8] = 2.5;
    setY[7] = setY[8] = -1.85;
    setZ[7] = setZ[8] = -4.2;
    if(num == 0) glTranslatef(2.5, -1.85, -4);
    else
        if(num == 7)
        {
            glTranslatef(2.5+kanan[num], -1.85, -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            {
                glTranslatef(2.5+Right[7], -1.85, -4+maju[7]);
                if(num != 7 && num != 8) glRotated(rotasi[8], 0, 1, 0);
            }
    if(num == 8)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(1.3, 1.8, 1.3);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample4, GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display3()
{
    glPushMatrix();
    if(!sample3)
    {
        sample3 = glmReadOBJ("Table Lamp/table_lamp.obj");
        if(!sample3) exit(0);
        glmUnitize(sample3);
    }
    display4();
    setX[5] = setX[6] = 2;
    setY[5] = setY[6] = -2;
    setZ[5] = setZ[6] = -4;
    if(num == 0) glTranslatef(2, -2, -4);
    else
        if(num == 5)
        {
            glTranslatef(2+kanan[num], -2+atas[num], -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            {
                glTranslatef(2+Right[5], -2+up[5], -4+maju[5]);
                if(num != 5 && num != 6) glRotated(rotasi[6], 0, 1, 0);
            }
    if(num == 6)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(0.4, 0.4, 0.8);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample3, GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display2()
{
    glPushMatrix();
    if(!sample2)
    {
        sample2 = glmReadOBJ("Bed1/Bed1.obj");
        if(!sample2) exit(0);
        glmUnitize(sample2);
    }
    display3();
    setX[3] = setX[4] = -2;
    setY[3] = setY[4] = -1.45;
    setZ[3] = setZ[4] = -4;
    if(num == 0) glTranslatef(-2, -1.45, -4);
    else
        if(num == 3)
        {
            glTranslatef(-2+kanan[num], -1.45, -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            {
                glTranslatef(-2+Right[3], -1.45, -4+maju[3]);
                if(num != 3 && num != 4) glRotated(rotasi[4], 0, 1, 0);
            }
    if(num == 4)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(1, 2, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample2, GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!sample1)
    {
        sample1 = glmReadOBJ("Book Shelf/bookshelf_comment.obj");
        if(!sample1) exit(0);
        glmUnitize(sample1);
    }
    setX[1] = setX[2] = 2;
    setY[1] = setY[2] = 2.3;
    setZ[1] = setZ[2] = -5.4;
    display2();
    if(num == 0)
    {
        glTranslatef(2, 2, -4);
        glRotated(90, 0, 1, 0);
    }
    else
        if(num == 1)
        {
            glTranslatef(2+kanan[num], 2+atas[num], -4+maju[num]);
            up[num] = atas[num];
            Right[num] = kanan[num];
            glRotated(rotasi[num+1]+90, 0, 1, 0);
        }
        else
            {
                glTranslatef(2+Right[1], 2+up[1], -4+maju[1]);
                if(num != 1 && num != 2) glRotated(rotasi[2]+90, 0, 1, 0);
            }
    if(num == 2)
    {
        glRotated(rotasi[num]+90, 0, 1, 0);
    }
    glScalef(0.7, 0.5, 0.7);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample1, GL_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
    //glutSwapBuffers();
}

void Dinding()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    if(!tembok)
    {
        tembok = glmReadOBJ("tembok/wall.obj");
        if(!tembok) exit(0);
        glmUnitize(tembok);
    }
    display1();
    //JendelaDinding();
    glTranslatef(0, 0.65, -4);
    glRotated(180, 0, 1, 0);
    glScalef(7, 13, 7.5);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(tembok, GL_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void mouseMovement(int x, int y)
{
    //printf("%d %d\n", x, y);
}


void reshape(int w, int h)
{
    if (h == 0) h = 1;
    ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(80, ratio, 1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int onMouse = 1;
void mouseClicks(int button, int state, int x, int y)
{
    int vx, vy;
    double dvx, dvy;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        onMouse = 1;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        onMouse = 2;
    }
    dvx = (double)x/135.0;
    vx = ceil(dvx);
    if(vx < 7) vObj = (vx*2)-1;
    if(vx == 7) vOpt = 0;
    else
        if(vx == 8) vOpt = 1;
    if(y > 620) num = vObj + vOpt;
    if(vx == 9 || vx == 10)
    {
        if(vx == 9) tekstur[num/2] = 0;
        else
            if(vx == 10) tekstur[num/2] = 1;

        parsingNum(tekstur[num/2]);
        if(num == 1 || num == 2) sample1 = false;
        else
            if(num == 3 || num == 4) sample2 = false;
        else
            if(num == 5 || num == 6) sample3 = false;
        else
            if(num == 7 || num == 8) sample4 = false;
        else
            if(num == 9 || num == 10) sample5 = false;
        else
            if(num == 11 || num == 12) sample6 = false;
    }
}

void glutKeyboardFunc(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
    {
        printf("Key is Up\n");
        if(atas[num]+setY[num] < 2.7)atas[num] += 0.1;
    }
    if(key == GLUT_KEY_DOWN)
    {
        printf("Key is Down\n");
        if(atas[num]+setY[num] > -1.9) atas[num] -= 0.1;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        printf("Key is Right\n");
        if(kanan[num]+setX[num] < 4.8)kanan[num] += 0.1;
        if(num % 2 == 0) rotasi[num] += 45;
    }
    if(key == GLUT_KEY_LEFT)
    {
        printf("Key is Left\n");
        if(kanan[num]+setX[num] > -5.2) kanan[num] -= 0.1;
        if(num % 2 == 0) rotasi[num] -= 45;
    }
    if(key == GLUT_KEY_PAGE_UP)
    {
        printf("Zoom In\n");
        if(maju[num]+setZ[num] < -3.8) maju[num] += 0.1;
    }
    if(key == GLUT_KEY_PAGE_DOWN)
    {
        printf("Zoom Out\n");
        if(maju[num]+setZ[num] > -6.3) maju[num] -= 0.1;
    }
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    int param = num%2;
    if(key == '1')
    {
        tekstur[num/2] = 0;
        printf("Tekstur 1\n");
    }
    else
        if(key == '2')
        {
            tekstur[num/2] = 1;
            printf("Tekstur 2\n");
        }
        else
            if(key == '3')
            {
                tembok = false;
                teksturTembok = 0;
            }
            else
                if(key == '4')
                {
                    tembok = false;
                    teksturTembok = 1;
                }
    if(num == 1 || num == 2) sample1 = false;
    else
        if(num == 3 || num == 4) sample2 = false;
    else
        if(num == 5 || num == 6) sample3 = false;
    else
        if(num == 7 || num == 8) sample4 = false;
    else
        if(num == 9 || num == 10) sample5 = false;
    else
        if(num == 11 || num == 12) sample6 = false;
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 101; i++)
    {
        atas[i] = 0.0;
        kanan[i] = 0.0;
        up[i] = 0.0;
        Right[i] = 0.0;
        save[i] = 0.0;
        rotasi[i] = 0;
        maju[i] = 0.0;
        tekstur[i] = 0;
        setX[i] = 0.0;
        setY[i] = 0.0;
        setZ[i] = 0.0;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1350, 700);
    glutCreateWindow("Desain Kamar Tidur");

    int satu = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 1);
    glutAddMenuEntry("Rotasi", 2);

    int dua = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 3);
    glutAddMenuEntry("Rotasi", 4);

    int tiga = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 5);
    glutAddMenuEntry("Rotasi", 6);

    int empat = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 7);
    glutAddMenuEntry("Rotasi", 8);

    int lima = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 9);
    glutAddMenuEntry("Rotasi", 10);

    int enam = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 11);
    glutAddMenuEntry("Rotasi", 12);

    glutCreateMenu(mymenu);
        glutAddSubMenu("Bookshelf", satu);
        glutAddSubMenu("Bed", dua);
        glutAddSubMenu("Table Lamp", tiga);
        glutAddSubMenu("Modern Desktop", empat);
        glutAddSubMenu("Table Bed", lima);
        glutAddSubMenu("Flower Pot", enam);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Dinding);
    glutIdleFunc(Dinding);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMovement);
    glutSpecialFunc(glutKeyboardFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutReshapeFunc(reshape);
    Init();
    glutMainLoop();
}
