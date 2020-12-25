
//#include <GL/glut.h>
#include <../glut/glut.h>
//#include<iostream>
#include "constants.h"

#define DEG2GRAD(x) ((x) * PI/180.0)

#define GRAD2DEG(x) ((x) * 180.0/PI)

struct axes {
	double x, y, z;

	double &operator[](int);
};

struct PhysicalState {
	axes position;

	PhysicalState();
	//friend ostream &operator << (ostream &out, PhysicalState &p);
}; 

extern axes toLookAt;
extern PhysicalState sphere;// *determineSphere;


void mDataInit();

void cameraPosition(axes point, double distance, double xAngle, double zAngle);




void handleKeypress(unsigned char key, int x, int y);
void handleUpKeypress(unsigned char key, int x, int y);