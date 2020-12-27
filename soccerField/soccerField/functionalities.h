
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

//����ṹ�嶨��
typedef struct
{
	GLubyte *imageData;//ͼ������
	GLuint bpp;//�������
	GLuint width;//ͼ����
	GLuint height;//ͼ��߶�
	GLuint texID;//��Ӧ������ID
}TextureImage;

//����TGAͼ����������
bool LoadTGA(TextureImage *texture, char *fileName);


extern axes toLookAt;
extern PhysicalState sphere, sphereCamera;// *determineSphere;
extern Circle circles[CIRCLE_NUM];

void mDataInit();

void cameraPosition(axes point, double distance, double xAngle, double zAngle);




void handleKeypress(unsigned char key, int x, int y);
void handleUpKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);