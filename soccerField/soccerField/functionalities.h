
//#include <GL/glut.h>
#include <../glut/glut.h>
#include<iostream>
#include "constants.h"
using namespace std;

#define DEG2GRAD(x) ((x) * PI/180.0)

#define GRAD2DEG(x) ((x) * 180.0/PI)

extern int SphereState;

struct axes {
	double x, y, z;

	double &operator[](int);
};

struct PhysicalState {
	axes position;
	double rotationx;

	PhysicalState();
	//friend ostream &operator << (ostream &out, PhysicalState &p);
}; 

struct Circle {
	axes position;
	double radius;
	string color;


	Circle();
	//friend ostream &operator << (ostream &out, PhysicalState &p);
};

//纹理结构体定义
typedef struct
{
	GLubyte *imageData;//图像数据
	GLuint bpp;//像素深度
	GLuint width;//图像宽度
	GLuint height;//图像高度
	GLuint texID;//对应的纹理ID
}TextureImage;

//加载TGA图像，生成纹理
bool LoadTGA(TextureImage *texture, char *fileName);


extern axes toLookAt;
extern PhysicalState sphere, sphereCamera;// *determineSphere;
extern Circle circles[CIRCLE_NUM];

void mDataInit();

void cameraPosition(axes point, double distance, double xAngle, double zAngle);




void handleKeypress(unsigned char key, int x, int y);
void handleUpKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);