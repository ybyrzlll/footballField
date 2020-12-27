
#include "functionalities.h"
#include<math.h>
#include <iostream>

using namespace std;

PhysicalState::PhysicalState() {
	position =  { 0.0, 0.0, 0.0 };
}

void mDataInit() {
	sphere.position = { 0.0, 0.0, 10.0 };
	sphereCamera.position = { 0.0, 6.0, 22.0 };
	/*sphereCamera.position.x = 0.0;
	sphereCamera.position.y = 2.0;
	sphereCamera.position.z = 5.0;*/


	toLookAt = sphere.position;
}

void cameraPosition(axes point, double distance, double zAngle, double xAngle) {
	/*gluLookAt(point.x + distance * (cos(DEG2GRAD(zAngle)) * cos(DEG2GRAD(xAngle))),
		point.y + distance * (cos(DEG2GRAD(zAngle)) * sin(DEG2GRAD(xAngle))),
		point.z + distance * sin(DEG2GRAD(zAngle)), point.x, point.y, point.z, 0, 0, 1);*/

	gluLookAt(point.x + distance ,
		point.y ,
		point.z + distance , point.x, point.y, point.z, 0, 0, 1);

}

void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates

	switch (key) {
		case '+':
			sphereCamera.position.z += 1.0f;

			break;
		case '-':
			sphereCamera.position.z -= 1.0f;
			break;
		case 'w':
			sphereCamera.position.z -= 1.0f;
			sphere.position.z -= 1.0f;
			//exit(1);
			break;
		case 's':
			sphereCamera.position.z += 1.0f;
			sphere.position.z += 1.0f;
			//exit(1);
			break;
	}

	glutPostRedisplay();
}


void handleSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			sphereCamera.position.y += 1.0f;
			sphere.position.y += 1.0f;
			break;
		case GLUT_KEY_DOWN:
			sphereCamera.position.y -= 1.0f;
			sphere.position.y -= 1.0f;
			break;
		case GLUT_KEY_LEFT:
			sphereCamera.position.x -= 1.0f;
			sphere.position.x -= 1.0f;
			break;
		case GLUT_KEY_RIGHT:
			sphereCamera.position.x += 1.0f;
			sphere.position.x += 1.0f;
			break;
		default:
			break;
	}
	// 刷新
	glutPostRedisplay();
}

void handleUpKeypress(unsigned char key, int x, int y) {
	/*downKeys[key] = false;*/
}



bool LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if (file == NULL ||										// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	//OpenGL中纹理只能使用24位或者32位的TGA图像
	if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	//RGB数据格式转换，便于在OpenGL中使用
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp == 24)									// Was The TGA 24 Bits
	{
		type = GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}