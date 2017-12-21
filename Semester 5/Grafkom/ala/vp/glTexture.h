#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
struct BMPImage
{
    int   width;
    int   height;
    char *data;
};


class glTexture
{
    public:
        glTexture();
        void loadTextureInfo(char * bmpFile, int PicID);
        void getBitmapImageData(char *pFileName, BMPImage *pImage);
        void SetActive(int PicID);
    private:
        GLuint g_textureID;
        BMPImage textureImage[10];

};

