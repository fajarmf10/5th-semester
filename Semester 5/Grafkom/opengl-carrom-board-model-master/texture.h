/*POINT STRUCTURE*/
typedef struct{
	float X;
	float Y;
	float Z;
}Point;



//IMAGE DATA
static GLubyte image[6][2048][1768][4];

//a linear array to store image data
static GLubyte linearImage[6][2048*1768*4];




//texture object number
static GLuint texName[6];



//main function
void DrawWall();

//copying image data(rgb values) to a linear array
void convertToLinearArray();

//initialize
void init2();

//loads a bitmap image with f_name
int loadImage(char *f_name,int index);


void Texture();

