#include "texture.h"
#include "figuras.h"
#include "Camera.h"

GLfloat Diffuse[] = { 0.5, 0.5, 0.5, 1 };
GLfloat Position[] = { 0, 7, -5, 0};
GLfloat g_lookupdown = 0;

CCamera objCamera;

CTexture text1;

CFiguras sky;
CFiguras objeto;

CTexture muro;
CTexture pasto;
CTexture ventana;

void InitGL(GLvoid) {
	glClearColor(0, 0, 0, 0);
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
	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	muro.LoadTGA("muro.tga");
	muro.BuildGLTexture();
	muro.ReleaseImage();

	pasto.LoadTGA("pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	ventana.LoadTGA("ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
		glRotatef(g_lookupdown, 1.0f, 0, 0);

		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

		glPushMatrix();
			//Cielo
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0, 60, 0);
				glColor3f(1, 1, 1);
				sky.skybox(130.0, 130.0, 130.0, text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//Barda Exterior
			glPushMatrix();
				glColor3f(0.25, 0.25, 0.25);
				glTranslatef(0, 1, -9.86);
				objeto.prisma(2, 0.2, 19.72, 0);
				glPushMatrix();
					glTranslatef(12.745, 0, -9.86);
					objeto.prisma(2, 25.49, 0.2, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(25.49, 0, 0);
					objeto.prisma(2, 0.2, 19.72, 0);
				glPopMatrix();
			glPopMatrix();

			//Recamara principal
			glPushMatrix();
				glColor3f(1, 1, 1);
				glPushMatrix();
					glTranslatef(5.01, 0.4, -6.01);
					objeto.prisma(0.8, 5.76, 0.2, muro.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.8, 0);
						objeto.prisma(0.4, 5.76, 0.2, muro.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-2.165, 1.5, 0);
						objeto.prisma(2.2, 1.43, 0.2, muro.GLindex);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(2.13, 1.5, 0);
						objeto.prisma(2.2, 1.5, 0.2, muro.GLindex);
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(2.13, 1.7, -7.99);
					objeto.prisma(3.4, 0.2, 4.16, muro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(5.01, 1.7, -10.07);
					objeto.prisma(3.4, 5.76, 0.2, muro.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(7.89, 1.7, -7.24);
					objeto.prisma(3.4, 0.2, 2.66, muro.GLindex);
				glPopMatrix();
			glPopMatrix();

			//Terreno
			glPushMatrix();
				glColor3f(1, 1, 1);
				glTranslatef(12.745, 0, -9.86);
				objeto.prisma(0.01, 25.49, 19.72, pasto.GLindex);
			glPopMatrix();

			//Ventanas
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, ventana.GLindex);
			glPushMatrix();
				glColor3f(1, 1, 1);
				glTranslatef(4.975, 1.9, -6.01);
				objeto.prisma(2.2, 2.83, 0.1, ventana.GLindex);
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();

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
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
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