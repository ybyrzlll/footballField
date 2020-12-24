#include <../glut/glut.h>

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(300, 300);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}