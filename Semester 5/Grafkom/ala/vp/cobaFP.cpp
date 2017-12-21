#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "IL/il.h"
#include "glm.h"
#include "glmint.h"
#include "glTexture.h"
#include<math.h>

double jarak=2;
double sudut=0,
eyex,
eyey=2,
eyez,
centery=0, centerx, centerz,
posx=0,
posz=0;

double perpindahan=0.2;//perpindahan utk klo gerak jalan
int nilai=0;
double posisi=0,
//sudut utk kaki dan tangan
kakikiriatas[12]={45, 45, 30, 10, -10, -40, -30, 0, 30, 45, 60, 60},
kakikananatas[12]={-30, 0, 30, 45, 60, 60, 45, 45, 30, 10, -10, -40},
tangankiri[12]={-90, -60, -45, -30, 30, 45, 60, 45, 0, -30, -45, -60},
tangankanan[12]={60, 45, 0, -30, -45, -60, -90, -60, -45, -30, 30, 45};

double sudutlight=270;

glTexture hTexture;
GLMmodel *sample,*sample1,*sample2,*sample3,*sample4,*sample5,*sample6, *sample7, *sample8,*sample9;
float ratio;

GLfloat pos[4]={-5,1,-5,1.0};
bool tex=true;

void myKeyboard2(unsigned char key, int x, int y)
{
	nilai=0;
	glutPostRedisplay ();
}
void myKeyboard(unsigned char key, int x, int y)
{

   /* if (key== '1'){//1
		//sudut+=5;
		sudutlight-=5;
	}
	else if (key=='2'){//2
		sudut-=5;
		sudutlight+=5;
	}*/
    if (key== '3')//1
		sudutlight+=5;
	else if (key=='4')//2
		sudutlight-=5;


	else if (key==100)//d
		sudut+=5;
	else if (key==97)//a
		sudut-=5;
	else if (key==119)//w
	{
		nilai=1;
		posx=posx+perpindahan*cos(sudut*3.14/180);
		posz=posz+perpindahan*sin(sudut*3.14/180);
		posisi+=0.5;
		if(posisi>=12)
			posisi=0;

	}
	else if (key==115)//s
	{
		posx=posx-perpindahan*cos(sudut*3.14/180);
		posz=posz-perpindahan*sin(sudut*3.14/180);

	}

    pos[0]=3*cos((sudutlight)*3.14/180);
    pos[2]=3*sin((sudutlight)*3.14/180);

	eyex=posx+(jarak)*cos((sudut+180)*3.14/180);
	eyez=posz+(jarak)*sin((sudut+180)*3.14/180);

	centerx=posx+jarak*cos((sudut)*3.14/180);
	centerz=posz+jarak*sin((sudut)*3.14/180);

	glutPostRedisplay ();
}


void menu(int id)
{
    if(id==1)
    {
        tex=true;
    }
    else if(id==2)
    {
        tex=false;
    }
}

void Draw()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    if(tex)
    hTexture.SetActive(1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void Init() {

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
void pohon()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if (!sample) {
    sample = glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\pohon.obj");
    if (!sample) exit(0); //gagal = exit
    glmUnitize(sample);
    glmFacetNormals(sample);
    glmVertexNormals(sample,90.0,GL_TRUE);
    }

    if(tex)
    glmDraw(sample, GLM_SMOOTH |GLM_MATERIAL);
    else
    glmDraw(sample,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}

void marshmallow()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if (!sample6) {
    sample6 = glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\marshmallow.obj");
    if (!sample6) exit(0); //gagal = exit
    glmUnitize(sample6);
    glmFacetNormals(sample6);
    glmVertexNormals(sample6,90.0,GL_TRUE);
    }

    if(tex)
    glmDraw(sample6, GLM_SMOOTH |GLM_MATERIAL);
    else
    glmDraw(sample6,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}

void lollipop()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if (!sample7) {
    sample7 = glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\droid-lollipop.obj");
    if (!sample7) exit(0); //gagal = exit
    glmUnitize(sample7);
    glmFacetNormals(sample7);
    glmVertexNormals(sample7,90.0,GL_TRUE);
    }

    if(tex)
    glmDraw(sample7, GLM_SMOOTH |GLM_MATERIAL);
    else
    glmDraw(sample7,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}

void kolam()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(!sample1)
    {
        sample1=glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\kolam.obj");
        if(!sample1)exit(0);
        glmUnitize(sample1);
        glmFacetNormals(sample1);
        glmVertexNormals(sample1,90.0,GL_TRUE);

    }
    if(tex)
    glmDraw(sample1, GLM_SMOOTH | GLM_TEXTURE|GLM_MATERIAL);
    else
    glmDraw(sample1,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}
void badan()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(!sample4)
    {
        sample4=glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\badan-android.obj");
        if(!sample4)exit(0);
        glmUnitize(sample4);
        glmFacetNormals(sample4);
        glmVertexNormals(sample4,90.0,GL_TRUE);

    }
    if(tex)
    glmDraw(sample4, GLM_SMOOTH | GLM_TEXTURE|GLM_MATERIAL);
    else
    glmDraw(sample4,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}
void tangan()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(!sample5)
    {
        sample5=glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\tangan-kanan-android.obj");
        if(!sample5)exit(0);
        glmUnitize(sample5);
        glmFacetNormals(sample5);
        glmVertexNormals(sample5,90.0,GL_TRUE);

    }
    if(tex)
    glmDraw(sample5, GLM_SMOOTH | GLM_TEXTURE|GLM_MATERIAL);
    else
    glmDraw(sample5,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}
void kaki()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(!sample6)
    {
        sample6=glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\kaki-android.obj");
        if(!sample6)exit(0);
        glmUnitize(sample6);
        glmFacetNormals(sample6);
        glmVertexNormals(sample6,90.0,GL_TRUE);

    }
    if(tex)
    glmDraw(sample6, GLM_SMOOTH | GLM_TEXTURE|GLM_MATERIAL);
    else
    glmDraw(sample6,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}
void taman()
{ // draw thin taman with top=xz-plane, corner at origin
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(!sample2)
    {
        sample2=glmReadOBJ("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\Android Land\\tanah.obj");
        if(!sample2)exit(0);
        glmUnitize(sample2);
        glmFacetNormals(sample2);
        glmVertexNormals(sample2,90.0,GL_TRUE);

    }
    if(tex)
    glmDraw(sample2, GLM_SMOOTH | GLM_TEXTURE|GLM_MATERIAL);
    else
    glmDraw(sample2,GLM_SMOOTH|GLM_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}

void limb(double s1)
{
	//kaki atas
	glPushMatrix();
	glRotated(s1, 0, 0, 1);
	glTranslated(0, -0.2, 0);
	//glScaled(1, 3, 1);
	kaki();

	/*//pindah
	glScaled(1, 0.33, 1);
	glTranslated(0, -0.1, 0);
	glRotated(-s1, 0, 0, 1);

	//kaki bawah
	glRotated(s2, 0, 0, 1);
	glTranslated(0, -0.1, 0);
	glScaled(1, 3, 1);
	glutSolidCube(0.1);*/
	glPopMatrix();
}
void tangan1(double s1)
{
	//kaki atas
	glPushMatrix();
	glRotated(s1, 0, 0, 1);
	glTranslated(0, -0.2, 0);
	//glScaled(1, 3, 1);
	tangan();

	/*//pindah
	glScaled(1, 0.33, 1);
	glTranslated(0, -0.1, 0);
	glRotated(-s1, 0, 0, 1);

	//kaki bawah
	glRotated(s2, 0, 0, 1);
	glTranslated(0, -0.1, 0);
	glScaled(1, 3, 1);
	glutSolidCube(0.1);*/
	glPopMatrix();
}

void android(int a)
{
	glPushMatrix();
	//posisi miringnya badan
	if (a==1)
		glRotated(-20, 0, 0, 1);
	//gambar badan
	glPushMatrix();
	//glScaled(1, 2, 1);
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslated(0,0.5,0);
	badan();
	glPopMatrix();
	/*glutSolidCube(0.2);
	glPopMatrix();


	//kepala
	glPushMatrix();
	glTranslated(0, 0.3, 0);
	glutSolidSphere(0.1, 15, 15);*/
	glPopMatrix();

	//kaki
	glPushMatrix();
	glTranslated(0, -0.03, 0);
	//gambar kaki kiri
	glTranslated(0, 0, -0.15);
	if (a==1)
		tangan1(kakikiriatas[(int)posisi]);
	else
		tangan1(0);
	glTranslated(0, 0, 0.3);
	//gamabr kaki kanan
	if (a==1)
		tangan1(kakikananatas[(int)posisi]);
	else
		tangan1(0);
	glPopMatrix();

	//gambar tangan
	glPushMatrix();
	glTranslated(0, 0.45, 0);
	glTranslated(0, 0, -0.6);
	//tangankiri
	if(a==1)
		tangan1(tangankiri[(int)posisi]);
	else
		tangan1(0);
	glTranslated(0, 0, 1.2);
	//tangan kanan
	if(a==1)
		tangan1(tangankanan[(int)posisi]);
	else
		tangan1(0);
	glPopMatrix();
	glPopMatrix();

}

void display() {
    //mode buffer warna dan 3 dimensi
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //warna latar
    glClearColor(0.5, 0.5, 0.5, 0.0);

    //inisialisasi identity
    glLoadIdentity();
    GLfloat light1_ambient[4] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[4] = { 3.0, 3.0, 1.0, 1.0 };
    GLfloat spot_direction[4] = { 3.0, 3.0, 0.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 3.0);
    glEnable(GL_LIGHT1);

    pos[0]=3*cos((sudutlight)*3.14/180);
    pos[2]=3*sin((sudutlight)*3.14/180);

    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    eyex=posx+(jarak)*cos((sudut+180)*3.14/180);
	eyez=posz+(jarak)*sin((sudut+180)*3.14/180);

	centerx=posx+jarak*cos((sudut)*3.14/180);
	centerz=posz+jarak*sin((sudut)*3.14/180);

	gluLookAt(eyex, eyey, eyez,centerx, centery, centerz,0, 1, 0);
    Draw();

    glPushMatrix();//gambar taman
    glTranslated (0, 0, 2.1);
    glScaled(5, 1, 5);
	taman();


	/*taman(0.02);
	glTranslated (2.1, 0, 0);
	taman(0.02);
	glTranslated (0, 0,-2.1);
	taman(0.02);
	glTranslated (0, 0,-2.1);
	taman(0.02);
	glTranslated (-2.1, 0, 0);
	taman(0.02);
	glTranslated (-2.1, 0, 0);
	taman(0.02);
	glTranslated (0, 0, 2.1);
	taman(0.02);
	glTranslated (0, 0, 2.1);
	taman(0.02);*/
	glPopMatrix();


        glPushMatrix();//gambar pohon
        glTranslated(-2, 1, 0);
        glScaled(4, 4, 4);
        pohon();
        glPopMatrix();

        glPushMatrix();//gambar pohon
        glTranslated(-2, 1, 3);
        glScaled(4, 4, 4);
        pohon();
        glPopMatrix();

        glPushMatrix();//gambar android marshmallow
        glTranslated(0.5, 1, 5.8);
        glRotated(180,0,1,0);
        //glScaled(-1, 0, 0);
        marshmallow();
        glPopMatrix();

        glPushMatrix();//gambar android lollipop
        glTranslated(2.5, 1, -1.6);
        glRotated(180,0,1,0);
        //glScaled(-1, 0, 0);
        lollipop();
        glPopMatrix();

        glPushMatrix();//gambar android lollipop
        glTranslated(-1, 1, -1.6);
        glRotated(180,0,1,0);
        //glScaled(-1, 0, 0);
        lollipop();
        glPopMatrix();


        glPushMatrix();//gambar kolam
        glTranslated(3.5, 0.45, 1.75);
        kolam();
        glPopMatrix();
    light1_ambient[0] =1.0;
    light1_ambient[1]= light1_ambient[2]=0.0;
    light1_ambient[3] =1.0 ;

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_ambient);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_ambient);

    glPushMatrix();
	glTranslated(posx, 0.3, posz);
	glRotatef(-sudut, 0, 1, 0);
	glScaled(0.5, 0.5, 0.5);
	android(nilai);
	glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
void reshape(int w, int h){
    if(h==0) h=1;
    ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(80,ratio,1,300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //inisialisasi mode detail, 3 dimensi dan RGB
    glutInitWindowPosition(300,1);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("FP Grafkom");
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutKeyboardUpFunc(myKeyboard2);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    //hTexture.loadTextureInfo("C:\\Users\\andre.DESKTOP-OPOUQEH\\Desktop\\cobaFPcoba - Copy\\lollipoptexture.bmp", 1);
    Init();
    glutMainLoop();
    return 0;
}
