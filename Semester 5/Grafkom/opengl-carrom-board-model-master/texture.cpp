
/***************************************************************************

TEXTURE MAPPING OF BITMAP IMAGE IN A CUBE SURFACES

/***************************************************************************/



/**HEADER FILES*/
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*POINT STRUCTURE*/
typedef struct{
	float X;
	float Y;
	float Z;
}Point;

//CUBE POINTS
Point p[8];

//IMAGE DATA
static GLubyte image[6][2048][1768][4];

//a linear array to store image data
static GLubyte linearImage[6][2048*1768*4];


//IMAGE HEIGHT AND WIDTH
unsigned int imagewidth=0, imageheight=0;

//total size of the image file
unsigned long fileSize;


//texture object number
static GLuint texName[6];


/*DISPLAY FUNCTION*/
void DrawWall()
{
    //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //const double a = t*90.0;
	static float i=0;

	i+=1;

	glPushMatrix();



	 glTranslatef(0,42,0);
    //glRotatef(a,1.0,1.0,1.0);

	//enable texture coordinate generation
	glEnable(GL_TEXTURE_2D);

	//sets texturing environment parameter
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//binding texture to texture number
	glBindTexture(GL_TEXTURE_2D, texName[0]);


	//defines a 2 dimentional texture image

	glBegin(GL_QUADS);

	/*texture coordinate associate a particular location in the image with vertices i polygon*/
	glTexCoord2f(0.0, 0.0); glVertex3f(p[0].X, p[0].Y, p[0].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[1].X, p[1].Y, p[1].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[2].X, p[2].Y, p[2].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[3].X, p[3].Y, p[3].Z);

	glEnd();

/*	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
*/
	//same process continues for each side of the cube

	glBindTexture(GL_TEXTURE_2D, texName[1]);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[1]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(p[7].X, p[7].Y, p[7].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[6].X, p[6].Y, p[6].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[5].X, p[5].Y, p[5].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[4].X, p[4].Y, p[4].Z);

	glEnd();

/*	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
*/
	glBindTexture(GL_TEXTURE_2D, texName[2]);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[2]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(p[1].X, p[1].Y, p[1].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[5].X, p[5].Y, p[5].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[6].X, p[6].Y, p[6].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[2].X, p[2].Y, p[2].Z);

	glEnd();


/*	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
*/

	glBindTexture(GL_TEXTURE_2D, texName[3]);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[3]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(p[0].X, p[0].Y, p[0].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[4].X, p[4].Y, p[4].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[7].X, p[7].Y, p[7].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[3].X, p[3].Y, p[3].Z);

	glEnd();

/*	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

*/
	glBindTexture(GL_TEXTURE_2D, texName[4]);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[4]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(p[4].X, p[4].Y, p[4].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[5].X, p[5].Y, p[5].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[1].X, p[1].Y, p[1].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[0].X, p[0].Y, p[0].Z);

	glEnd();

/*	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

*/
	glBindTexture(GL_TEXTURE_2D, texName[5]);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[5]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(p[3].X, p[3].Y, p[3].Z);
	glTexCoord2f(0.0, 10.0); glVertex3f(p[2].X, p[2].Y, p[2].Z);
	glTexCoord2f(10.0,10.0); glVertex3f(p[6].X, p[6].Y, p[6].Z);
	glTexCoord2f(10.0, 0.0); glVertex3f(p[7].X, p[7].Y, p[7].Z);

	glEnd();

	//glFlush();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//glutSwapBuffers();

}


//copying image data(rgb values) to a linear array
void convertToLinearArray()
{
	int len;
	int index;
	for(index=0;index<6;index++)
	{
		len=0;
	for(unsigned int r=0; r<imageheight; r++)
	{

			for(unsigned int c=0; c<imagewidth; c++)
			{
				for(int k=2; k>=0;k--)
				{
					linearImage[index][len++] = image[index][r][c][k];

				}
				linearImage[index][len++] = (GLubyte)255;

			}
	}

	}
}



//initialize
void init2()
{

	//clear color black
	//glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);

	//initializing cube points
	p[0].X=-50;p[0].Y=-50;p[0].Z=-50;
	p[1].X=-50;p[1].Y=50;p[1].Z=-50;
	p[2].X=50;p[2].Y=50;p[2].Z=-50;
	p[3].X=50;p[3].Y=-50;p[3].Z=-50;

	p[4].X=-50;p[4].Y=-50;p[4].Z=50;
	p[5].X=-50;p[5].Y=50;p[5].Z=50;
	p[6].X=50;p[6].Y=50;p[6].Z=50;
	p[7].X=50;p[7].Y=-50;p[7].Z=50;


//	copying image data(rgb values) to a linear array
	convertToLinearArray();



	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	//texture object numbers
	glGenTextures(6, texName);

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[0]);


	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[1]);

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[2]);

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[3]);

	glBindTexture(GL_TEXTURE_2D, texName[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[4]);

	glBindTexture(GL_TEXTURE_2D, texName[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imagewidth, imageheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,linearImage[5]);

	//select the texture object number
	//set texture parameter




}


//loads a bitmap image with f_name
int loadImage(char *f_name,int index)
{
	FILE *fp;
	unsigned char blueValue, redValue, greenValue;
	unsigned int r,c;

	//opens the file
	if(!(fp = fopen(f_name, "rb")))
	{
		printf("File Open Error\n");
		return 0;
	}

	//seeking bytes from initial position
	fseek(fp,2,0);

	//reads file size
	fread(&fileSize,4,1,fp);

	//seeking bytes from initial position
	fseek(fp,18,0);

	//reading image height and width
	fread(&imagewidth,4,1,fp);
	fseek(fp,22,0);
	fread(&imageheight,4,1,fp);

//	printf("%d %d\n",imagewidth,imageheight);

	//now starts data reading
	fseek(fp,54,0);

	for(r=0; r<imageheight; r++)
	{
		for(c=0; c<imagewidth; c++)
		{
			fread(&blueValue, sizeof(char), 1, fp);
			fread(&greenValue, sizeof(char), 1, fp);
			fread(&redValue , sizeof(char), 1, fp);

			image[index][r][c][0] = (GLubyte)blueValue;
			image[index][r][c][1] = (GLubyte)greenValue;
			image[index][r][c][2] = (GLubyte)redValue;
			image[index][r][c][3] = (GLubyte)255;

		}
	}

	//end of reading
	fclose(fp);
	return 1;
}


//main function
void Texture()
{


	char file_name[100];


	//pic0
	//opening file with filename
	strcpy(file_name, "pic0.bmp");

	//loading image file
	if(!loadImage(file_name,0))
	{
		printf("\n0File Error\n");
		//return 0;
	}


	//pic1
	//opening file with filename
	strcpy(file_name, "pic1.bmp");

	//loading image file
	if(!loadImage(file_name,1))
	{
		printf("\n1File Error\n");
		//return 0;
	}

	//pic2
	//opening file with filename
	strcpy(file_name, "pic2.bmp");

	//loading image file
	if(!loadImage(file_name,2))
	{
		printf("\n2File Error\n");
		//return 0;
	}

	//pic3
	//opening file with filename
	strcpy(file_name, "pic3.bmp");

	//loading image file
	if(!loadImage(file_name,3))
	{
		printf("\n3File Error\n");
		//return 0;
	}

	//pic4
	//opening file with filename
	strcpy(file_name, "pic4.bmp");

	//loading image file
	if(!loadImage(file_name,4))
	{
		printf("\n4File Error\n");
		//return 0;
	}

	//pic5
	//opening file with filename
	strcpy(file_name, "pic5.bmp");

	//loading image file
	if(!loadImage(file_name,5))
	{
		printf("\n5File Error\n");
		//return 0;
	}

}
