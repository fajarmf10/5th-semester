#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "glTexture.h"

glTexture::glTexture()
{
}

void glTexture::SetActive(int PicID)
{
    glGenTextures( 1, &g_textureID );
	glBindTexture( GL_TEXTURE_2D, g_textureID );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[PicID].width, textureImage[PicID].height,
	               0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[PicID].data );
}

void glTexture::loadTextureInfo(char * bmpFile, int PicID)
{
    getBitmapImageData( bmpFile, &textureImage[PicID] );
}

void glTexture::getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found\n",pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
		printf( "ERROR: getBitmapImageData - Plane count from %s is not 1: %u\n", pFileName, nNumPlanes );

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n", pFileName );

    if( nNumBPP != 24 )
		printf( "ERROR: getBitmapImageData - BPP from %s is not 24: %u\n", pFileName, nNumBPP );

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n", pFileName);

    //
	// Finally, rearrange BGR to RGB
	//

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}

