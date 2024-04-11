#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// the size of the window measured in pixels
#define dim 300
#define M_PI 3.14159265358979323846
struct ObjPoint {
    double x, y, z;
}p[12];
double n;

unsigned char prevKey;

enum EObiect { cubw, cubs, sferaw, sferas, triangle, cube } ob;
void InitialCube() {
    GLfloat vertices[8][3] = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 1, 1}
    };
    for (int i = 4; i <= 11; i++) {
        p[i].x = vertices[i - 4][0];
        p[i].y = vertices[i - 4][1];
        p[i].z = vertices[i - 4][2];
    }
}
void DisplayAxe() {
    int X, Y, Z;
    X = Y = 200;
    Z = 200;

    glLineWidth(2);

    // Ox axis - green
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(X, 0, 0);
    glEnd();

    // Oy axis - blue
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Y, 0);
    glEnd();

    // Oz axis - red
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, Z);
    glEnd();

    glLineWidth(1);
}

// wireframe cube
void Display1() {
    glColor3f(1, 0, 0);
    glutWireCube(1);
}

// solid cube
void Display2() {
    glColor3f(1, 0, 0);
    glutSolidCube(1);
}

// wireframe sphere
void Display3() {
    glColor3f(0, 0, 1);
    glutWireSphere(1, 10, 10);
}

// solid sphere
void Display4() {
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 10, 10);
}
void Display5() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(p[1].x, p[1].y, p[1].z);
    glVertex3f(p[2].x, p[2].y, p[2].z);
    glVertex3f(p[3].x, p[3].y, p[3].z);
    glEnd();
}
void Display6() {
    glClearDepth(0.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    GLfloat vertices[8][3];
    for (int i = 4; i <= 11; i++) {
        vertices[i - 4][0] = p[i].x;
        vertices[i - 4][1] = p[i].y;
        vertices[i - 4][2] = p[i].z;
    }
    GLfloat colors[6][3] = {
        {0, 1, 1},
        {1, 0, 0},
        {0, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    GLuint faces[6][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {0, 4, 7, 3},
        {1, 5, 6, 2},
        {1, 5, 4, 0},
        {3, 7, 6, 2}
    };
    for (int i = 0; i < 6; i++) {
        glColor3fv(colors[i]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j]]);
        }
        glEnd();
    }
    glDisable(GL_DEPTH_TEST);
    glClearDepth(1.0);
}

void DisplayObiect()
{
    switch (ob)
    {
    case cubw:
        Display1();
        break;
    case cubs:
        Display2();
        break;
    case sferaw:
        Display3();
        break;
    case sferas:
        Display4();
        break;
    case triangle:
        Display5();
        break;
    case cube:
        Display6();
        break;
    default:
        break;
    }
}

// the rotation with 10 degrees about the Ox axis
void DisplayX() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 1, 0, 0);
}

// the rotation with 10 degrees about the Oy axis
void DisplayY() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 1, 0);
}

// the rotation with 10 degrees about the Oz axis
void DisplayZ() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 0, 1);
}

// translation by 0.2, 0.2, 0.2
void DisplayT() {
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.2, 0.2, 0.2);
}

// scaling by 1.2, 1.2, 1.2
void DisplayS() {
    glMatrixMode(GL_MODELVIEW);
    glScalef(1.2, 1.2, 1.2);
}

void Init(void) {
    glClearColor(1, 1, 1, 1);
    glLineWidth(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 30, -30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
}


void rotatePointY(ObjPoint& point, double angle) {
    angle = angle * M_PI / 180.0;
    double newX = cos(angle) * point.x + sin(angle) * point.z;
    double newZ = -sin(angle) * point.x + cos(angle) * point.z;
    point.x = newX;
    point.z = newZ;
}
void rotatePointZ(ObjPoint& point, double angle) {
    angle = angle * M_PI / 180.0;
    double newX = cos(angle) * point.x + sin(angle) * point.y;
    double newY = -sin(angle) * point.x + cos(angle) * point.y;
    point.x = newX;
    point.y = newY;
}
void rotatePointX(ObjPoint& point, double angle) {
    angle = angle * M_PI / 180.0;
    double newY = cos(angle) * point.y + sin(angle) * point.z;
    double newZ = -sin(angle) * point.y + cos(angle) * point.z;
    point.y = newY;
    point.z = newZ;
}

void DisplayQ() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    glPushMatrix();
    double angle = 0;
    if (p[1].z != 0)
        angle = atan(p[1].x / p[1].z);
    angle = -angle*180/M_PI;
    glRotatef(angle, 0.0, 1.0, 0.0);
    Display5();
    rotatePointY(p[1], angle);
    rotatePointY(p[2], angle);
    rotatePointY(p[3], angle);
    p[1].x = 0;
    glPopMatrix();
}

void DisplayW() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    glPushMatrix();
    double angle = 0;
    if (p[2].y != 0)
        angle = atan(p[2].x / p[2].y);
    angle = -angle * 180 / M_PI;
    glRotatef(-angle, 0.0, 0.0, 1.0);
    Display5();
    rotatePointZ(p[1], angle);
    rotatePointZ(p[2], angle);
    rotatePointZ(p[3], angle);
    glPopMatrix();
}
void DisplayD() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    glPushMatrix();
    glTranslated(0, -p[1].y, -p[1].z);
    Display5();
    p[2].y -= p[1].y;
    p[2].z -= p[1].z;
    p[3].y -= p[1].y;
    p[3].z -= p[1].z;
    p[1].y = 0;
    p[1].z = 0;
    glPopMatrix();
}
void DisplayE() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    glPushMatrix();
    double angle = 0;
    if (p[2].z != 0)
        angle = atan(p[2].y / p[2].z);
    angle = -angle * 180 / M_PI;
    glRotatef(-angle, 1.0, 0.0, 0.0);
    Display5();
    rotatePointX(p[1], angle);
    rotatePointX(p[2], angle);
    rotatePointX(p[3], angle);
    glPopMatrix();
}
void DisplayR() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    glPushMatrix();
    double angle = 0;
    if (p[3].y != 0)
        angle = atan(p[3].x / p[3].y);
    angle = -angle * 180 / M_PI;
    glRotatef(-angle, 0.0, 0.0, 1.0);
    Display5();
    rotatePointZ(p[1], angle);
    rotatePointZ(p[2], angle);
    rotatePointZ(p[3], angle);
    glPopMatrix();
}
void DisplayC() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    Display6();
}
void DisplayV() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    glPushMatrix();
    glRotated(-45, 0, 1, 0);
    Display6();
    for (int i = 4; i <= 11; i++)
        rotatePointY(p[i], -45);
    glPopMatrix();
}
void DisplayB() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    glPushMatrix();
    glRotated(asin(1 / sqrt(3))*180/M_PI, 1, 0, 0);
    Display6();
    for (int i = 4; i <= 11; i++)
        rotatePointX(p[i], -asin(1 / sqrt(3)) * 180 / M_PI);
    glPopMatrix();
}
void DisplayN() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    glPushMatrix();
    glRotated(n, 0, 0, 1);
    Display6();
    for (int i = 4; i <= 11; i++)
        rotatePointZ(p[i], -n);
    glPopMatrix();
}
void DisplayM() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    glPushMatrix();
    glRotated(-asin(1 / sqrt(3)) * 180 / M_PI, 1, 0, 0);
    Display6();
    for (int i = 4; i <= 11; i++)
        rotatePointX(p[i], asin(1 / sqrt(3)) * 180 / M_PI);
    glPopMatrix();
}
void DisplayK() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 1, 0, 0);
    glRotated(-45, 0, 1, 0);
    glScalef(8, 8, 8);
    DisplayAxe();
    glPushMatrix();
    glRotated(45, 0, 1, 0);
    Display6();
    for (int i = 4; i <= 11; i++)
        rotatePointY(p[i], 45);
    glPopMatrix();
}

void Display(void) {
    switch (prevKey)
    {
    case 'a':
        DisplayAxe();
        break;
    case '0':
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(20, 1, 0, 0);
        glRotated(-20, 0, 1, 0);
        break;
    case '1':
        Display1();
        ob = cubw;
        break;
    case '2':
        Display2();
        ob = cubs;
        break;
    case '3':
        Display3();
        ob = sferaw;
        break;
    case '4':
        Display4();
        ob = sferas;
        break;
    case '5':
        Display5();
        ob = triangle;
        break;
    case '6':
        InitialCube();
        Display6();
        ob = cube;
        break;
    case 'x':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayX();
        DisplayAxe();
        DisplayObiect();
        break;
    case 'y':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayY();
        DisplayAxe();
        DisplayObiect();
        break;
    case 'z':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayZ();
        DisplayAxe();
        DisplayObiect();
        break;
    case 't':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayT();
        DisplayAxe();
        DisplayObiect();
        break;
    case 's':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayS();
        DisplayAxe();
        DisplayObiect();
        break;
    case 'q': //rotire pas 1
        DisplayQ();
        ob = triangle;
        break;
    case 'd': //rotire pas 2
        DisplayD();
        ob = triangle;
        break;
    case 'w': //rotire pas 3
        DisplayW();
        ob = triangle;
        break;
    case 'e': //rotire pas 4
        DisplayE();
        ob = triangle;
        break;
    case 'r': //rotire pas 5
        DisplayR();
        ob = triangle;
        break;
    case 'c': // cube pas 1
        DisplayC();
        ob = cube;
        break;
    case 'v': // cube pas 2
        DisplayV();
        ob = cube;
        break;
    case 'b': // cube pas 3
        DisplayB();
        ob = cube;
        break;
    case 'n': // cube pas 4
        DisplayN();
        ob = cube;
        break;
    case 'm': // cube pas 5
        DisplayM();
        ob = cube;
        break;
    case 'k': // cube pas 6
        DisplayK();
        ob = cube;
        break;
    default:
        break;
    }
    glutSwapBuffers();
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
    p[1].x = 1.0;
    p[1].y = 1.0;
    p[1].z = 2.0;
    p[2].x = 1.0;
    p[2].y = 7.0;
    p[2].z = 1.0;
    p[3].x = 7.0;
    p[3].y = 1.0;
    p[3].z = 1.0;
    InitialCube();
    n = 10;

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}
