#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glut.h"

using namespace std;
unsigned char prevKey;


class GrilaCarteziana {
public:
	int numarLinii;
	int numarColoane;
	double cx;
	double cy;
	double dc;
	double de;
	double epsilon;
	double radius;

	GrilaCarteziana(int numarLinii, int numarColoane) {
		this->numarLinii = numarLinii;
		this->numarColoane = numarColoane;
		this->epsilon = 0.1;
		this->cx = -1 + this->epsilon;
		this->cy = -1 + this->epsilon;
		this->dc = (2 - 2 * this->epsilon) / (numarColoane - 1);
		this->de = (2 - 2 * this->epsilon) / (numarLinii - 1);

		this->radius = this->dc / 3;
		this->deseneazaColoane();
		this->deseneazaLinii();
		//this->writePixel(4, 4);
	}

	void deseneazaLinii() {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		double p1_x = this->cx;
		double p_y = this->cy;
		double p2_x = -this->cx;

		for (int i = 1; i <= this->numarLinii; i++) {
			glVertex2f(p1_x, p_y);
			glVertex2f(p2_x, p_y);
			p_y += this->de;
		}

		glEnd();
	}

	void deseneazaColoane() {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		double p_x = this->cx;
		double p1_y = this->cy;
		double p2_y = 1 - this->epsilon;

		for (int i = 1; i <= this->numarColoane; i++) {
			glVertex2f(p_x, p1_y);
			glVertex2f(p_x, p2_y);
			p_x += this->dc;
		}

		glEnd();
	}

	void deseneazaCerc(double x, double y, double r, int numberOfSegments) {

		double pi = 4 * atan(1.0);

		glColor3ub(71, 71, 71);
		glBegin(GL_POLYGON);
		glVertex2f(x, y);

		for (int i = 0; i < numberOfSegments; i++) {
			float x_aux = x + (this->radius * cos(i * 2 * pi / numberOfSegments));
			float y_aux = y + (this->radius * sin(i * 2 * pi / numberOfSegments));
			glVertex2f(x_aux, y_aux);
		}

		glEnd();
	}

	void writePixel(int i, int j) {
		double x = this->cx + i * this->dc;
		double y = this->cy + j * this->de;
		deseneazaCerc(x, y, radius, 10000);
	}
};

void Init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(1);
	glPointSize(3);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void display1() {
	int numarLinii = 16;
	int numarColoane = 16;
	GrilaCarteziana* grilaCarteziana = new GrilaCarteziana(numarLinii, numarColoane);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		display1();
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27)
		exit(0);

	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutDisplayFunc(Display);
	glutMainLoop();

	return 0;
}