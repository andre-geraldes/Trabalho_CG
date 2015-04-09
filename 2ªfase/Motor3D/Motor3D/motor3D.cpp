#include "mainMotor3D.h"

// Vector com os pontos lidos do ficheiro:
vector<Ponto> pontos;

vector<Primitiva> primitivas;

#define CONST 1.0f;

// Variaveis para utilização do teclado e rato:
float xx = 0, yy = 0, zz = 0, angle = 0.0f, angle1 = 0.0f;
float camX = 0, camY = 3, camZ = 5;
int startX, startY, tracking = 0;

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

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < pontos.size(); i++)
		glVertex3f(pontos[i].x, pontos[i].y, pontos[i].z);
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

void parseGrupo(XMLElement* grupo, /**/ transf, char familia){
	Transformacao trans;
	Translacao tr;
	Rotacao ro;
	Escala es;


	if (strcmp(grupo->FirstChildElement()->Value(), "grupo") == 0)
		grupo = grupo->FirstChildElement();

	//transformações para um grupo
	XMLElement* transformacao = grupo->FirstChildElement();

	/* Verifica se existem transformcoes antes dos modelos */
	if (strcmp(transformacao->Value(), "modelos") == 0)
		trans = transf;
	else {
		for (transformacao; (strcmp(transformacao->Value(), "modelos") != 0); transformacao = transformacao->NextSiblingElement()) {
			if (strcmp(transformacao->Value(), "translacao") == 0)
				tr = verificaTranslacoes(transformacao);
			//else { tr.setRotacao(transf.getRotacao());}

			if (strcmp(transformacao->Value(), "rotacao") == 0)
				ro = verificaRotacao(transformacao);
			//else { tr.setRotacao(transf.getRotacao());}


			if (strcmp(transformacao->Value(), "escala") == 0)
				es = verificaEscala(transformacao);
			//else { tr.setEscala(transf.getEscala());}
		}
		trans = Transformacao::Transformacao(tr, ro, es);
	}

	//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transformações
	for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
		int flag;
		Primitiva p(modelo->Attribute("ficheiro"));
		cout << p.getNomePrimitiva() << endl;
		flag = readFile(p.getNomePrimitiva());

		if (flag >= 0 && p.getNomePrimitiva().compare("teapot.3d")) {
			p.setImagem(modelo->Attribute("textura"));
			p.setTransformacao(trans);
			p.setTipo(familia);
			int n = primitivas.size();

			if (n > 1 && primitivas[n - 1].getTipo() == 'I' && cc == 'F') {
				primitivas[n - 1].adicionaFilho(p);
			}
			else
				primitivas.push_back(p);

			cout << "TIPO: " << p.getTipo() << endl;
			cout << "Translacao: " << trans.getTranslacao().getTime() << endl;
			cout << "Rotacao   : " << trans.getRotacao().getRx() << " - " << trans.getRotacao().getRy() << " - " << trans.getRotacao().getRz() << endl;
			cout << "Escala    : " << trans.getEscala().getEx() << " - " << trans.getEscala().getEy() << " - " << trans.getEscala().getEz() << endl;
		}
		else {
			p.setTransformacao(trans);
			p.setTipo(familia);

			primitivas.push_back(p);
		}
	}

	//faz o mesmo de cima para grupos filhos
	if (grupo->FirstChildElement("grupo")) {
		cout << "Vou para os Filhos" << endl;
		parseGrupo(grupo->FirstChildElement("grupo"), trans, 'F');
	}

	//faz o mesmo de cima para grupos irmãos
	if (grupo->NextSiblingElement("grupo")) {
		cout << "Vim para os Irmaos" << endl;
		parseGrupo(grupo->NextSiblingElement("grupo"), transf, 'I');
	}
}

// Função de leitura do ficheiro XML:
void readXML(string filename)
{
	XMLDocument doc;
	doc.LoadFile(filename.c_str());

	XMLElement* cena = doc.FirstChildElement("cena");
	XMLElement* grupo = cena->FirstChildElement("grupo");

	parseGrupo(grupo, 'P');
	
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