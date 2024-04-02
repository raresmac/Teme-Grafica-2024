#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glut.h"
#include <map>

using namespace std;
unsigned char prevKey;


class GrilaCarteziana {
public:
	int numarLinii;
	int numarColoane;
	double cx;
	double cy;
	double dx;
	double dy;
	double epsilon;
	double radius;

	GrilaCarteziana(int numarLinii, int numarColoane) {
		this->numarLinii = numarLinii;
		this->numarColoane = numarColoane;
		this->epsilon = 0.1;
		this->cx = -1 + this->epsilon;
		this->cy = -1 + this->epsilon;
		this->dx = (2 - 2 * this->epsilon) / (numarColoane - 1);
		this->dy = (2 - 2 * this->epsilon) / (numarLinii - 1);

		this->radius = this->dx / 3;
		this->deseneazaColoane();
		this->deseneazaLinii();
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
			p_y += this->dy;
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
			p_x += this->dx;
		}

		glEnd();
	}

	void deseneazaCerc(double x, double y, double r, int numberOfSegments, double thickness=1, char color='g') {

		double pi = 4 * atan(1.0);
		if(color == 'r')
			glColor3f(1.0, 0.1, 0.1);
		else
			glColor3f(0.2, 0.2, 0.2);

		glLineWidth(thickness);
		glBegin(GL_POLYGON);
		//glVertex2f(x, y);

		for (int i = 0; i <= numberOfSegments; i++) {
			float x_aux = x + (r * cos(i * 2 * pi / numberOfSegments));
			float y_aux = y + (r * sin(i * 2 * pi / numberOfSegments));
			glVertex2f(x_aux, y_aux);
		}

		glEnd();
		glLineWidth(1);
	}

	bool inBorder(int x, int y) {
		if (x < 0 || x >= this->numarColoane || y < 0 || y >= this->numarLinii) {
			return false;
		}
		return true;
	}

	void ScanConvertSegments3(int x0, int y0, int xn, int yn, int width)
	{
		double dx, dy;
		dx = abs(xn - x0);
		dy = abs(yn - y0);

		int d = 2 * dy - dx;
		int dE = 2 * dy;
		int dNE = 2 * (dy - dx);
		int x = x0, y = y0;
		map<int, int> m;
		m[x] = y;

		this->writePixel(x, y);
		for (int i = -width / 2; i < width / 2; i++) {
			if(this->inBorder(x - i, y))
				this->writePixel(x - i, y);
			if (this->inBorder(x + i, y))
				this->writePixel(x + i, y);
			if (this->inBorder(x, y - i))
				this->writePixel(x, y - i);
			if (this->inBorder(x, y + i))
				this->writePixel(x, y + i);
		}

		while (x != xn)
		{
			if (d <= 0) { 
				d += dE; 
				x++; 
			}
			else { 
				d += dNE; 
				x++;
				if (x0 < xn && y0 < yn) {
					y++;
				}
				else {
					y--;
				}
			}
			this->writePixel(x, y);
			for (int i = -width / 2; i < width / 2; i++) {
				if(this->inBorder(x - i, y))
					this->writePixel(x - i, y);
				if (this->inBorder(x + i, y))
					this->writePixel(x + i, y);
				if (this->inBorder(x, y - i))
					this->writePixel(x, y - i);
				if (this->inBorder(x, y + i))
					this->writePixel(x, y + i);
			}
			m[x] = y;
		}

		glColor3f(1.0, 0.1, 0.1);
		glLineWidth(3);
		glBegin(GL_LINES);
		double x1, y1;
		x1 = this->cx + x0 * this->dx;
		y1 = this->cy + y0 * this->dy;
		glVertex2f(x1, y1);

		x1 = this->cx + xn * this->dx;
		y1 = this->cy + yn * this->dy;
		glVertex2f(x1, y1);
		glEnd();
		glLineWidth(1);
	}

	void AfisarePuncteCerc3(int x, int y, map<int, int> M)
	{
		double x1, y1;
		x1 = this->cx + y * this->dx;
		y1 = this->cy + x * this->dy;
		if(this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
		x1 = this->cx - y * this->dx;
		y1 = this->cy + x * this->dy;
		if (this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
		x1 = this->cx - x * this->dx;
		y1 = this->cy - y * this->dy;
		if (this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
		x1 = this->cx - y * this->dx;
		y1 = this->cy - x * this->dy;
		if (this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
		x1 = this->cx + y * this->dx;
		y1 = this->cy - x * this->dy;
		if (this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
		x1 = this->cx + x * this->dx;
		y1 = this->cy - y * this->dy;
		if (this->inBorder(x1, y1))
			deseneazaCerc(x1, y1, this->radius, 10000);
	}

	void ScanConvertCircle4(int R, int width)
	{
		int x = 0, y = R;
		int d = 1 - R;
		int dE = 3, dSE = -2 * R + 5;
		map<int, int> M;
		AfisarePuncteCerc3(x, y, M);
		for (int i = -width / 2; i < width / 2; i++) {
			AfisarePuncteCerc3(x - i, y, M);
			AfisarePuncteCerc3(x + i, y, M);
			AfisarePuncteCerc3(x, y - i, M);
			AfisarePuncteCerc3(x, y + i, M);
		}
		while (y > x && x < R * sqrt(2) / 2)
		{
			if (d < 0)
			{
				d += dE;
				dE += 2;
				dSE += 2;
			}
			else
			{
				d += dSE;
				dE += 2;
				dSE += 4;
				y--;
			}
			x++;
			AfisarePuncteCerc3(x, y, M);
			for (int i = -width / 2; i < width / 2; i++) {
				if(x - i < R * sqrt(2) / 2)
					AfisarePuncteCerc3(x - i, y, M);
				AfisarePuncteCerc3(x + i, y, M);
				AfisarePuncteCerc3(x, y - i, M);
				AfisarePuncteCerc3(x, y + i, M);
			}
		}

		glColor3f(1.0, 0.1, 0.1);
		glPolygonMode(GL_FRONT, GL_LINE);
		deseneazaCerc(this->cx, this->cy, this->radius * R * 3, 10000, 5, 'r');
		glPolygonMode(GL_FRONT, GL_FILL);
	}

	void writePixel(int i, int j) {
		double x = this->cx + i * this->dx;
		double y = this->cy + j * this->dy;
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
	grilaCarteziana->ScanConvertSegments3(0, 15, 15, 10, 3);
	grilaCarteziana->ScanConvertSegments3(0, 0, 15, 7, 1);
}

void display2() {
	int numarLinii = 16;
	int numarColoane = 16;
	GrilaCarteziana* grilaCarteziana = new GrilaCarteziana(numarLinii, numarColoane);
	grilaCarteziana->ScanConvertCircle4(13, 3);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		display1();
		break;
	case '2':
		display2();
		break;
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