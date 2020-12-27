#include <../glut/glut.h>
#include "constants.h"
#include "functionalities.h"
#include<math.h>
#include<iostream>
#include<map>
#include<string>

using namespace std;

//==================================
//contact wechat 774565715
//我是写手，以后可以用中介7成价格给你做每单
//==================================

#include <windows.h>

// ASCII字符总共只有0到127，一共128种字符
#define MAX_CHAR        128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
						// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != ' '; ++str)
		glCallList(lists + *str);
}


int SphereState;
int score;
axes toLookAt;
PhysicalState sphere, sphereCamera;
map<string, TextureImage> textures;
Circle circles[CIRCLE_NUM];
axes shootAngle;

// here we declare an array of vertices for the cube
GLfloat cubeVertexData[108] =
{
	//object vertex coordinates for cube made from triangles
	// Data layout for each line below is:
	// positionX, positionY, positionZ
	//wind counter-clockwise

	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,

	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,

	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	//4
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	//5
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	//6
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f

};

//the texture coordinates - work will skybox texture of this shape +--

GLfloat textureCoordsSkyBox[72] = {
	//face 1
	0.75,0.33,      //    0,1,
	0.75,0.67,     //    1,1,
	0.5,0.33,     //    0,0,
	0.5,0.33,     //    0,0,
	0.75,0.67,    //    1,0,
	0.5,0.67,   //    1,1,

	//face 2
	0.5,1.0, //    1,1,
	0.25,1, //    0,1,
	0.5,0.67, //    1,0,
	0.5,0.67, //    1,0,
	0.25,1.0, //    0,1,
	0.25,0.67, //    1,1,
	//face 3
	0,0.67,//    1,1,
	0,0.33,//    0,1,
	0.25,0.67,//    1,0,
	0.25,0.67,//    1,0,
	0,0.33,//    0,1,
	0.25,0.33,//    0,0,
	//face 4
	0.25,0.0,//    0,1,
	0.5,0.0,//    1,1,
	0.25,0.33,//    0,0,
	0.25,0.33,//    0,0,
	0.5,0.0,//    1,1,
	0.5,0.33,//    0,0,
	//face 5
	0.5,0.67,//    1,0,
	0.25,0.67,//    0,0,
	0.5,0.33,//    1,1,
	0.5,0.33,//    1,1,
	0.25,0.67,//    0,0,
	0.25,0.33,//    0,1,
	//face 6
	0.75,0.33,//    1,1,
	1.0,0.33,//    0,1,
	0.75,0.67,//    1,0,
	0.75,0.67,//    1,0,
	1.0,0.33,//    0,1,
	1.0,0.67//    0,0


};

//the lighting normals - all facing out from each face
GLfloat gCubeVertexdataNormals[108] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f

};

void intersectCircle(Circle &circle) {
	bool ret = false;

	double distance = sqrt(pow(sphere.position.x - circle.position.x, 2) + pow(sphere.position.y - circle.position.y, 2));
	if (distance < circle.radius) {
		ret = true;
	}

	if (ret) {
		score += circle.score;
		
	}
}

bool intersectWall() {
	return abs((WALL_Z - sphere.position.z)) <= BALL_RADIUS - 1.9f;
}

void intersect() {
	if (intersectWall()) {
		for (int i = 0; i < CIRCLE_NUM; i++) {
			intersectCircle(circles[i]);
		}
		cout << score << endl;
		resetPos();
	}
	
}

//stormydays_large.tga
void drawSkyBox() {
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	glPushMatrix();
	glTranslatef(0.0,  20.0f, 0.0);//SKYBOX_SCALE/2.0f
	//glRotatef(90.0, 1.0, 0.0, 0.0);

	glFrontFace(GL_CW); //texture the inside

	//bind your texture here
	glBindTexture(GL_TEXTURE_2D, textures["stormydays_large.tga"].texID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, gCubeVertexdataNormals);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cubeVertexData);
	//   glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordsSkyBox);
	// draw a cube - type - start number - number of vertices to draw (so 3 for single triangle)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);
	glPopMatrix();
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

	glColor4f(1.0, 1.0, 1.0, 0.7);
	/*glBegin(GL_QUADS);
	glVertex2f(80, 90);
	glVertex2f(80, 100);
	glVertex2f(100, 100);
	glVertex2f(100, 90);
	glEnd();*/

	glRasterPos2f(80.0f, 90.0f);
	char tempChar[100] = "score:";
	char strScores[50];
	string tempStr = std::to_string(score) + " ";
	strcpy(strScores, tempStr.c_str());
	drawString(std::strcat(tempChar, strScores));


	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	//////////////////////////
}

void drawOrigin(void) {
	glPushMatrix();
	glTranslatef(0, 0.1, 10);
	glBindTexture(GL_TEXTURE_2D, textures["targetDull.tga"].texID);

	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 1.0f);
	int width = 1.5;
	//glColor3f(1.0, 0, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width, -1.0f, -width);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, -1.0f, width);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, -1.0f, width);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, -1.0f, -width);
	glEnd();
	glPopMatrix();
}


void drawCircle(Circle &circle) {
	glPushMatrix();
	glTranslatef(circle.position.x, circle.position.y, circle.position.z);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	//glRotatef(180.0, 00.0, 0.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[circle.color].texID);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 1.0f);
	double width = circle.radius ;
	glTexCoord2f(-1.0f, 1.0f);
	glVertex3f(-width, -1.0f, -width);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex3f(-width, -1.0f, width);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(width, -1.0f, width);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, -1.0f, -width);
	glEnd();
	glPopMatrix();
}

void drawCircles(void) {

	for (int i = 0; i < CIRCLE_NUM; i++) {
		drawCircle(circles[i]);
	}
}

void footBallMove() {
	if (SphereState == 1) {
		sphere.position.z -= 0.01 * SPEED;
		sphere.position.x += 0.01 * SPEED * sin(shootAngle.x / 180.0f);
		sphere.position.y += 0.01 * SPEED * sin(shootAngle.y / 180.0f);

		sphereCamera.position.z -= 0.01 * SPEED;

		sphere.rotationx -= 1;
	}
}

void drawRedPoint(void) {
	glDisable(GL_TEXTURE_2D);
	glColor4f(255.0, 0.0, 0.0, 1);
	glutSolidSphere(0.1f, 32, 32);
	glEnable(GL_TEXTURE_2D);
}

void drawFootBall(void) {

	

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(sphere.position.x, sphere.position.y, sphere.position.z);
	glRotatef(sphere.rotationx, 1, 0, 0);

	//glBindTexture(GL_TEXTURE_2D, textures["FootballCompleteMap"].texID);
	//glutSolidSphere(BALL_RADIUS, 32, 32);

	GLUquadricObj *quadObj = gluNewQuadric();//创建一个二次曲面物体
	gluQuadricTexture(quadObj, GL_TRUE);        //启用该二次曲面的纹理
	glBindTexture(GL_TEXTURE_2D, textures["FootballCompleteMap.tga"].texID);
	gluSphere(quadObj, 1, 20, 20); //画圆

	glPopMatrix();

}

void drawGround(void) {
	glPushMatrix();
	glTranslatef(0, 0, -10);
	glBindTexture(GL_TEXTURE_2D, textures["grass_diff.tga"].texID);
	
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 1.0f);
	int width = 25;
	//glColor3f(1.0, 0, 0.5);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-width, -1.0f, -width);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-width, -1.0f, width);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(width, -1.0f, width);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(width, -1.0f, -width);
	glEnd();
	glPopMatrix();
}

void drawWalls(void) {

	glPushMatrix();
	glTranslatef(0, 5, WALL_Z);

	glRotatef(90.0, 90.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures["old_wall_texture_TGA.tga"].texID);

	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 0.0f);
	int width = 25, height = 5;
	//glColor3f(1.0, 0, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width, -1.0f, -height);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, -1.0f, height);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, -1.0f, height);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, -1.0f, -height);
	glEnd();
	glPopMatrix();


	///////// left wall

	glPushMatrix();
	glTranslatef(20, 5, -10);

	glRotatef(90.0, 0, 0, 1.0);

	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 0.0f);
	//glColor3f(1.0, 0, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-height, -1.0f, -width);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(height, -1.0f, -width);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(height, -1.0f, width);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-height, -1.0f, width);
	glEnd();
	glPopMatrix();


	///////// right wall
	glPushMatrix();
	glTranslatef(-20, 5, -10);

	glRotatef(90, 0, 0, 1.0);

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-height, -1.0f, -width );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(height , -1.0f, -width);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(height, -1.0f, width);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-height, -1.0f, width );
	glEnd();
	glPopMatrix();

}

void setOrthographicProjection() {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save the previous matrix which contains the
	//set up for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);       //glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -100.0, 0);
	//set for drawing again
	glMatrixMode(GL_MODELVIEW);
}

//reset your project with this - it simply pops back the previous projection
void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void display(void) {


	glLoadIdentity(); //Reset the drawing perspective

	gluLookAt(sphereCamera.position.x, sphereCamera.position.y, sphereCamera.position.z,
		sphere.position.x, sphere.position.y, sphere.position.z - 20,
		0.0, 1.0, 0.0);

	/*sphereCamera.xAngle = -90.0f;
	sphereCamera.zAngle = 15.0f;
	sphereCamera.distance = 5.0;
	sphereCamera.distance = 10;*/
	//cameraPosition(sphere.position, 60, 15.0f, -90.0f);

	//gluLookAt(0, 40.0, 40.0, sphere.position.x, sphere.position.y, sphere.position.z, 0.0, 1.0, 0.0);
	//gluLookAt(0, 40.0, 40.0, 0, 0, 0, 0.0, 1.0, 0.0);

	GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f, 0.7f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 0.0f, -100.0f, 100.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	GLfloat lightColor1[] = { 0.3f, 0.3f, 0.1f, 1.0f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, -1.0f, -1.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor1);

	//GLfloat lightColor2[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.5, 0.5)
	//GLfloat lightPos2[] = { 0.0f, 100.0f, 0.10f, 1.0f }; //Positioned at (4, 0, 8)
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	//glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective


	



	/*glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);


	glEnable(GL_LIGHTING);*/

	

	drawRedPoint();

	footBallMove();
	drawFootBall();

	drawGround();

	drawWalls();

	drawOrigin();

	drawCircles();

	drawSkyBox();

	intersect();


	//  draw2D
	glPushMatrix();
	glLoadIdentity(); //need this
	setOrthographicProjection();
	drawHud();
	glPopMatrix();
	resetPerspectiveProjection();



	glutSwapBuffers();
	glutPostRedisplay();



	//glFlush();
}

void readTextTure(const char * name) {
	char preIndex[100] = "texture/";
	if (!LoadTGA(&textures[name], std::strcat(preIndex, name)))
		return;
}

void mGLInit(void) {
	//char grass_diff[] = "grass_diff.tga";
	readTextTure("grass_diff.tga");
	readTextTure("FootballCompleteMap.tga");
	readTextTure("fillBarHorizontal.tga");
	readTextTure("old_wall_texture_TGA.tga");
	readTextTure("targetDull.tga");
	readTextTure("targetGreen.tga");
	readTextTure("targetRed.tga");
	readTextTure("targetBlue.tga");
	readTextTure("stormydays_large.tga");

	// 放大
	for (int i = 0; i < 108; i++) {
		cubeVertexData[i] *= SKYBOX_SCALE;
	}

	//glClearColor(137 / 255.0, 206 / 255.0, 255 / 255.0, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色
	//    glOrtho(0, WIDTH, 0, HEIGHT, 0, 500);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 2.0, 120.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[]) {

	int width = 1280, height = 720;

	mDataInit();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glutInitWindowPosition(300, 300);
	glutInitWindowSize(width, height);
	//glutFullScreen();

	glutCreateWindow("footballGame");

	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleUpKeypress);
	glutSpecialFunc(handleSpecialKeypress);

	glutDisplayFunc(&display);
	glutReshapeFunc(reshape);

	mGLInit();

	glutMainLoop();


	return 0;
}

