#include "texture.h"
#include "figuras.h"
#include "Camera.h"

GLfloat Diffuse[] = { 0.5, 0.5, 0.5, 1 };
GLfloat Position[] = { 0, 7, -5, 0};
GLfloat g_lookupdown = 0;

CCamera objCamera;

CTexture text1;

CFiguras sky;

//float movX = 16.39, movY = 1.71, movZ = -3, rotX = 0, rotY = 180, rotZ = 0;

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
	//objCamera.Position_Camera(16.39, 1.71, -3, 16.39, 1.71, 0, 0, 1, 0);
	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);
}

void cubo( ) {
	//Coordenadas del cubo unitario con centro en el origen
	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },
		{ -0.5 ,-0.5, 0.5 },
		{ -0.5 ,-0.5, -0.5 },
		{ 0.5 ,-0.5, -0.5 },
		{ 0.5 ,0.5, 0.5 },
		{ 0.5 ,0.5, -0.5 },
		{ -0.5 ,0.5, -0.5 },
		{ -0.5 ,0.5, 0.5 },
	};

	//Cara frontal
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();

	//Cara derecha
	glBegin(GL_POLYGON);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	//Cara trasera
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

	//Cara izquierda
	glBegin(GL_POLYGON);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();

	//Cara inferior
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
	glEnd();

	//Cara superior
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
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
				glPushMatrix();
					glScalef(0.2, 2, 19.72);
					cubo();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(12.745, 0, -9.86);
					glScalef(25.49, 2, 0.2);
					cubo();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(25.49, 0, 0);
					glScalef(0.2, 2, 19.72);
					cubo();
				glPopMatrix();
			glPopMatrix();

			//Recamara principal
			glPushMatrix();
				glTranslatef(5.01, 0.4, -6.01);
				glPushMatrix();
					glScalef(5.76, 0.8, 0.2);
					cubo();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 2.7, 0);
					glScalef(5.76, 0.2, 0.2);
					cubo();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-2.165, 1.5, 0);
					glScalef(1.43, 2.2, 0.2);
					cubo();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(2.88, 1.5, 0);
					glScalef(1.5, 2.2, 0.2);
					cubo();
				glPopMatrix();
			glPopMatrix();

			//Terreno
			glPushMatrix();
				glColor3f(0.1333, 0.5451, 0.1333);
				glTranslatef(12.745, 0, -9.86);
				glScalef(25.49, 0.01, 19.72);
				cubo();
			glPopMatrix();
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