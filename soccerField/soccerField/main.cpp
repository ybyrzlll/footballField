#include <../glut/glut.h>
//#include "constants.h"
#include "functionalities.h"
#include<math.h>

axes toLookAt;
PhysicalState sphere;

void rainBox(double alpha = 0.7) {

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0, alpha); //RED
	glVertex2f(-10.0, -20.0);
	glVertex2f(10.0, -20.0);

	glColor4f(1.0f, 1.0f, 0.0, alpha); //YELLOW
	glVertex2f(10.0, -10.0);
	glVertex2f(-10.0, -10.0);

	glVertex2f(-10.0, -10.0);
	glVertex2f(10.0, -10.0);


	glColor4f(0.0f, 1.0f, 0.0, alpha); //GREEN
	glVertex2f(10.0, 0.0);
	glVertex2f(-10.0, 0.0);
	glEnd();
}


void drawHud(void) {
	//////////////////////////


	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);       //glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);

	//        glDisable(GL_CULL_FACE);

	rainBox();


	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	//////////////////////////
}

GLfloat xRot = 0;
GLfloat yRot = 0;
GLfloat zRot = 0;

void drawTriangle(void) {

	GLfloat x, y, z, angle, x1, y1;
	int iPivot = 1;
	// 保存矩阵状态并旋转
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_FAN);
	// 三角形扇的共享顶点，z轴中心点上方
	glVertex3f(0.0f, 0.0f, 0.75);
	for (angle = 0.0f; angle < (2.0f * PI + PI / 8.0f); angle += (PI / 8.0f)) {
		// 计算下一个顶点的位置
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);
		if ((iPivot % 2) == 0) {
			glColor3f(1.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(0.0f, 1.0f, 1.0f);
		}
		// 增加基准值，下次改变颜色
		++iPivot;
		// 指定三角形扇的下一个顶点
		glVertex2f(x, y);
	}
	glEnd();

	// 绘制一个新的三角形扇，作为覆盖圆锥的底
	glBegin(GL_TRIANGLE_FAN);
	// 三角形扇的共享顶点，中心位于原点
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f * PI + PI / 8.0f); angle += (PI / 8.0f)) {
		// 计算下一个顶点的位置
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);
		if ((iPivot % 2) == 0) {
			glColor3f(0.5f, 0.0f, 0.5f);
		}
		else {
			glColor3f(1.0f, 0.0f, 1.0f);
		}
		// 增加基准值，下次改变颜色
		++iPivot;
		// 指定三角形扇的下一个顶点
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}


void drawFootBall(void) {
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	//glTranslatef(sphere.position.x, sphere.position.y, sphere.position.z);
	glutSolidSphere(BALL_RADIUS, 20, 20);
	glPopMatrix();

}

void display(void) {


	glLoadIdentity(); //Reset the drawing perspective

	/*sphereCamera.xAngle = -90.0f;
	sphereCamera.zAngle = 15.0f;
	sphereCamera.distance = 5.0;
	sphereCamera.distance = 10;*/
	//cameraPosition(toLookAt, 20, 15.0f, -90.0f);

	GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f, 0.7f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 0.0f, -100.0f, 100.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	GLfloat lightColor1[] = { 0.3f, 0.3f, 0.1f, 1.0f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, -1.0f, -1.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective


	



	/*glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);


	glEnable(GL_LIGHTING);*/

	

	//drawHud();
	drawFootBall();
	//drawTriangle();



	glutSwapBuffers();
	glutPostRedisplay();

	//glFlush();
}

void mGLInit(void) {
	glClearColor(137 / 255.0, 206 / 255.0, 255 / 255.0, 0);
	//    glOrtho(0, WIDTH, 0, HEIGHT, 0, 500);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING); //Enable lighting

	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	//glEnable(GL_LIGHT2); //Enable light #2
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH);
	////backgroundMusicPlayer(0);
	////updateDefenderPosition(0);
	glutSetCursor(GLUT_CURSOR_NONE);
	//glEnable(GL_MULTISAMPLE);

}

int main(int argc, char *argv[]) {

	mDataInit();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glutInitWindowPosition(300, 300);
	glutInitWindowSize(1280, 720);
	//glutFullScreen();

	glutCreateWindow("footballGame");
	glutDisplayFunc(&display);
	mGLInit();
	glutMainLoop();

	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleUpKeypress);

	return 0;
}

