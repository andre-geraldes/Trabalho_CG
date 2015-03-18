#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Ponto {
	double x;
	double y;
	double z;
};

vector<Ponto> pontos;

#define CONST 1.0f;
float xx = 0, yy = 0, zz = 0, angle = 0.0f, angle1 = 0.0f;

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0f, -4.0f, 5.0f,
		0.0, 1.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xx, yy, zz);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glRotatef(angle1, 1.0f, 0.0f, 0.0f);
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i<pontos.size(); i++)
		glVertex3f(pontos[i].x, pontos[i].y, pontos[i].z);
	glEnd();

	glutSwapBuffers();
}

// Funções de processamento do teclado
void normalkeyboard(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'a':
	case 'A': xx -= CONST; break;
	case 'd':
	case 'D': xx += CONST; break;
	case 'w':
	case 'W': yy += CONST; break;
	case 's':
	case 'S': yy -= CONST; break;
	case 'e':
	case 'E': zz -= CONST; break;
	case 'q':
	case 'Q': zz += CONST; break;
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: angle -= 5.0f; break;
	case GLUT_KEY_RIGHT: angle += 5.0f; break;
	case GLUT_KEY_UP: angle1 += 5.0f; break;
	case GLUT_KEY_DOWN: angle1 -= 5.0f; break;
	}
}

// Funções de processamento do rato
void mouseMove(int x, int y) {
	angle += x / 400;
	angle1 -= y / 400;
}

// Função de processamento do menu
void menu(int op) {
	switch (op) {
	case 1: glPolygonMode(GL_FRONT, GL_FILL); break;
	case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
	case 3: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
	glutPostRedisplay();
}

void readFile(string filename)
{
	string linha, token, delimiter = ",";
	int pos;
	double a, b, c;
	Ponto p;

	ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, linha))
		{
			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			a = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.x = a;

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			b = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.y = b;

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			c = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.z = c;

			pontos.push_back(p);
		}
		file.close();
	}
	else 
	{
		cout << "Nao foi possivel ler o ficheiro" << endl;
	}
	
}

int main(int argc, char **argv) {
	if (argc>1) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(200, 200);
		glutInitWindowSize(800, 800);
		glutCreateWindow("TP@CG");

		//-------------------------readXML(argv[1]);
		readFile(argv[1]);

		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		glutReshapeFunc(changeSize);

		glutKeyboardFunc(normalkeyboard);
		glutSpecialFunc(specialKeys);

		glutMotionFunc(mouseMove);

		glutCreateMenu(menu);
		glutAddMenuEntry("GL_FILL", 1);
		glutAddMenuEntry("GL_LINE", 2);
		glutAddMenuEntry("GL_POINT", 3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glPolygonMode(GL_FRONT, GL_LINE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glutMainLoop();
	}
	return 1;
}