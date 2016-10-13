#include "Main.h"
#include "texture.h"
#include "figuras.h"
#include "Camera.h"

GLfloat Diffuse[] = { 0.5, 0.5, 0.5, 1 };
GLfloat Position[] = { 0, 7, -5, 0};

CCamera objCamera;
GLfloat g_lookupdown = 0;

void InitGL(GLvoid) {
	glClearColor(1, 1, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//Texturas aquí
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//Área de dibujo
	glutSwapBuffers();
}

void animation() {
	glutPostRedisplay();
}

void reshape(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(0, 30, 0, 30, 0, -30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
		case 'W':
			objCamera.Move_Camera(CAMERASPEED + 0.2);
			break;
		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED + 0.2));
			break;
		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
			break;
		case 'd':
		case 'D':
			objCamera.Strafe_Camera(CAMERASPEED + 0.4);
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y) {
	switch (a_keys) {
		case GLUT_KEY_PAGE_UP:
			objCamera.UpDown_Camera(CAMERASPEED);
			break;
		case GLUT_KEY_PAGE_DOWN:
			objCamera.UpDown_Camera(-CAMERASPEED);
			break;
		case GLUT_KEY_UP:
			g_lookupdown -= 1.0f;
			break;
		case GLUT_KEY_DOWN:
			g_lookupdown += 1.0f;
			break;
		case GLUT_KEY_LEFT:
			objCamera.Rotate_View(-CAMERASPEED);
			break;
		case GLUT_KEY_RIGHT:
			objCamera.Rotate_View(CAMERASPEED);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Proyecto Final");
	InitGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}