#include "mainMotor3D.h"

// Vector com os pontos lidos do ficheiro:
vector<Ponto> pontos;

vector<Primitiva> primitivas;

#define CONST 1.0f;

// Variaveis para utilização do teclado e rato:
float xx = 0, yy = 0, zz = 0, angle = 0.0f, angle1 = 0.0f;
float camX = 0, camY = 3, camZ = 5;
int startX, startY, tracking = 0;

size_t teste = 0;

int alpha = 0, beta = 0, r = 5;

void changeSize(int w, int h) 
{
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

void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xx, yy, zz);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glRotatef(angle1, 1.0f, 0.0f, 0.0f);

	for (size_t j = 0; j < primitivas.size(); j++){

		Transformacao t = primitivas[j].getTransformacao();

		glRotatef(t.getRotacao().getAngulo(), primitivas[j].getTransformacao().getRotacao().geteixoX(), primitivas[j].getTransformacao().getRotacao().geteixoY(), primitivas[j].getTransformacao().getRotacao().geteixoZ());
		//glScalef(t.getEscala().getX(), primitivas[j].getTransformacao().getEscala().getY(), primitivas[j].getTransformacao().getEscala().getZ());
		glTranslatef(t.getTranslacao().getTransx(), primitivas[j].getTransformacao().getTranslacao().getTransy(), primitivas[j].getTransformacao().getTranslacao().getTransz());
		pontos = primitivas[j].getPontos();
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < pontos.size(); i++)
			glVertex3f(pontos[i].getX(), pontos[i].getY(), pontos[i].getZ());
		glEnd();
	}
	
	glEnd();

	glutSwapBuffers();
}

// Funções de processamento do teclado
void normalkeyboard(unsigned char tecla, int x, int y) 
{
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

void specialKeys(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_LEFT: angle -= 5.0f; break;
	case GLUT_KEY_RIGHT: angle += 5.0f; break;
	case GLUT_KEY_UP: angle1 += 5.0f; break;
	case GLUT_KEY_DOWN: angle1 -= 5.0f; break;
	}
}

// Funções de processamento do rato
void processMouseButtons(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {
		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);
}

// Função de processamento do menu
void menu(int op) 
{
	switch (op) {
	case 1: glPolygonMode(GL_FRONT, GL_FILL); break;
	case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
	case 3: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
	glutPostRedisplay();
}

// Função de leitura do ficheiro com os pontos:
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
			p.setX(a);

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			b = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.setY(b);

			pos = linha.find(delimiter);
			token = linha.substr(0, pos);
			c = atof(token.c_str());
			linha.erase(0, pos + delimiter.length());
			p.setZ(c);

			pontos.push_back(p);
		}
		file.close();
	}
	else 
	{
		cout << "Nao foi possivel ler o ficheiro" << endl;
	}
	
}


void parseGrupo(XMLElement* grupo, Transformacao transf){
	Transformacao trans;
	Translacao tr;
	Rotacao ro;
	Escala es = Escala::Escala(1,1,1);
	float ang1, rotX, rotY, rotZ, transX, transY, transZ, escX, escY, escZ;
	ang1 = rotX = rotY = rotZ = transX = transY = transZ = escX = escY = escZ = 1;

	if (strcmp(grupo->FirstChildElement()->Value(), "grupo") == 0)
		grupo = grupo->FirstChildElement();

	
	//transformações para um grupo
	XMLElement* transformacao = grupo->FirstChildElement();

	for (transformacao; (strcmp(transformacao->Value(), "modelos") != 0); transformacao = transformacao->NextSiblingElement()) {
		if (strcmp(transformacao->Value(), "translacao") == 0){
			if(transformacao->Attribute("X")) transX = stof(transformacao->Attribute("X"));
			else transX = 0;
			if (transformacao->Attribute("Y")) transY = stof(transformacao->Attribute("Y"));
			else transY = 0;
			if (transformacao->Attribute("Z")) transZ = stof(transformacao->Attribute("Z"));
			else transZ = 0;
			tr = Translacao::Translacao(transX, transY, transZ);
		}
		if (strcmp(transformacao->Value(), "rotacao") == 0){
			if (transformacao->Attribute("angulo")) ang1 = stof(transformacao->Attribute("angulo"));
			else ang1 = 0;
			if (transformacao->Attribute("eixoX")) rotX = stof(transformacao->Attribute("eixoX"));
			else rotX = 0;
			if (transformacao->Attribute("eixoY")) rotY = stof(transformacao->Attribute("eixoY"));
			else rotY = 0;
			if (transformacao->Attribute("eixoZ")) rotZ = stof(transformacao->Attribute("eixoZ"));
			else rotZ = 0;
			ro = Rotacao::Rotacao(ang1, rotX, rotY, rotZ);
		}
		if (strcmp(transformacao->Value(), "escala") == 0){
			if (transformacao->Attribute("X")) escX = stof(transformacao->Attribute("X"));
			else escX = 1;
			if (transformacao->Attribute("Y")) escY = stof(transformacao->Attribute("Y"));
			else escY = 1;
			if (transformacao->Attribute("Z")) escZ = stof(transformacao->Attribute("Z"));
			else escZ = 1;
			es.setX(escX);
			es.setY(escY);
			es.setZ(escZ);
		}
		//Actualizacao dos valores em relação ao nodo pai
		tr.setTransx(tr.getTransx() + transf.getTranslacao().getTransx());
		tr.setTransy(tr.getTransy() + transf.getTranslacao().getTransy());
		tr.setTransz(tr.getTransz() + transf.getTranslacao().getTransz());
		ro.setAngulo(ro.getAngulo() + transf.getRotacao().getAngulo());
		ro.setEixoX(ro.geteixoX() + transf.getRotacao().geteixoX());
		ro.setEixoY(ro.geteixoY() + transf.getRotacao().geteixoY());
		ro.setEixoZ(ro.geteixoZ() + transf.getRotacao().geteixoZ());
		es.setX(es.getX() * transf.getEscala().getX());
		es.setY(es.getY() * transf.getEscala().getY());
		es.setZ(es.getZ() * transf.getEscala().getZ());
		trans = Transformacao::Transformacao(tr, ro, es);
	}
		
	//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transformações
	for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
		
		Primitiva p;
		p.setNome(modelo->Attribute("ficheiro"));
		cout << p.getNome() << endl;
		readFile(p.getNome());
		p.setPontos(pontos);
		pontos.clear();

		p.setTransformacao(trans);

		cout << "Translacao: " << trans.getTranslacao().getTransx() << " - " << trans.getTranslacao().getTransy() << " - " << trans.getTranslacao().getTransz() << endl;
		cout << "Rotacao   : " << trans.getRotacao().getAngulo() << " - " << trans.getRotacao().geteixoX() << " - " << trans.getRotacao().geteixoY() << " - " << trans.getRotacao().geteixoZ() << endl;
		cout << "Escala    : " << trans.getEscala().getX() << " - " << trans.getEscala().getY() << " - " << trans.getEscala().getZ() << endl;

		primitivas.push_back(p);
	}

	//faz o mesmo de cima para grupos filhos
	if (grupo->FirstChildElement("grupo")) {
		parseGrupo(grupo->FirstChildElement("grupo"), trans);
	}

	//faz o mesmo de cima para grupos irmãos
	if (grupo->NextSiblingElement("grupo")) {
		parseGrupo(grupo->NextSiblingElement("grupo"), transf);
	}
}

// Função de leitura do ficheiro XML:
void readXML(string filename)
{

	XMLDocument doc;
	doc.LoadFile(filename.c_str());
	
	XMLElement* cena = doc.FirstChildElement("cena");
	XMLElement* grupo = cena->FirstChildElement("grupo");
	
	Transformacao t = Transformacao::Transformacao();
	Escala e;
	e = Escala::Escala(1, 1, 1);
	t.setEscala(e);
	parseGrupo(grupo, t);
	
}

int main(int argc, char **argv) 
{
	if (argc>1) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(800, 800);
		glutCreateWindow("TP@CG");

		//Leitura do ficheiro XML:
		readXML(argv[1]);

		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		glutReshapeFunc(changeSize);

		//Teclado
		glutKeyboardFunc(normalkeyboard);
		glutSpecialFunc(specialKeys);

		//Rato
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		//Criação e opções do menu:
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