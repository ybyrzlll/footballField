#include "functionalities.h"
#include<math.h>

PhysicalState::PhysicalState() {
	position =  { 0.0, 0.0, 0.0 };
}

void mDataInit() {
	sphere.position.x = sphere.position.y = sphere.position.z = 0.0;

	toLookAt = sphere.position;
}

void cameraPosition(axes point, double distance, double zAngle, double xAngle) {
	gluLookAt(point.x + distance * (cos(DEG2GRAD(zAngle)) * cos(DEG2GRAD(xAngle))),
		point.y + distance * (cos(DEG2GRAD(zAngle)) * sin(DEG2GRAD(xAngle))),
		point.z + distance * sin(DEG2GRAD(zAngle)), point.x, point.y, point.z, 0, 0, 1);

}

void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	//if (currentMode != HELP) {
	//	switch (key) {
	//	case '+':
	//		sphereCamera.distance -= 0.1f;
	//		sphereCamera.distance += (sphereCamera.distance < MIN_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
	//		//            cout<<sphereCamera.distance<<endl;

	//		break;
	//	case '-':
	//		sphereCamera.distance += 0.1f;
	//		sphereCamera.distance -= (sphereCamera.distance > MAX_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
	//		//            cout<<sphereCamera.distance<<endl;
	//		break;
	//	}
	//}
	//else {
	//	if (key == 27) {
	//		currentMode = ADJUSTING;
	//	}
	//}
	//downKeys[key] = true;
	//if (currentMode == ADJUSTING) {
	//	switch (key) {
	//	case '\r':
	//		currentMode = AIMING;
	//		break;
	//	case EXIT_KEY: //Escape key
	//		exit(0); //Exit the program
	//	}
	//}
	//if (currentMode == AIMING) {
	//	switch (key) {
	//	case ' ':
	//		currentMode = POWERING;
	//		glutTimerFunc(1000 * 1 / 60.0, incrementPowerMeter, 0);
	//		break;
	//	case 27: //Escape key
	//		currentMode = ADJUSTING;
	//	}
	//}

}

void handleUpKeypress(unsigned char key, int x, int y) {
	/*downKeys[key] = false;*/
}