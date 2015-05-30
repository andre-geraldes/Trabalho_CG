#pragma once

#pragma comment(lib,"devil.lib")
#pragma comment(lib,"glew32.lib")

#include <vector>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

#include "ponto.h"
#include "Transformacao.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Primitiva{

	string nome;
	string textura;
	vector<Primitiva> filhos;
	vector<Ponto> pontos;
	vector<Ponto> normais;
	vector<Ponto> texturas;
	Transformacao transformacao;
	//VBOs
	GLuint buffers[3];
	float *v; //Pontos
	float *n; //Normais
	float *tex; //Texturas
	int nvertex;
	int nnormais;
	int ntexturas;
	//Textura:
	unsigned int t, tw, th;
	unsigned int texID;
	unsigned char *texData;

public:
	Primitiva();
	Primitiva(string n, vector<Primitiva>, vector<Ponto>, Transformacao);
	string getNome(){ return nome; }
	string getTextura(){ return textura; }
	unsigned getTexID() { return texID; }
	vector<Ponto> getPontos() { return pontos; }
	vector<Ponto> getNormais() { return normais; }
	vector<Ponto> getTexturas() { return texturas; }
	vector<Primitiva> getFilhos(){ return filhos; }
	Transformacao getTransformacao(){ return transformacao; }
	void setTextura(string t){ textura = t; }
	void setNome(string n){ nome = n; }
	void setFilho(Primitiva f){ filhos.push_back(f); }
	void setFilhos(vector<Primitiva> f){ filhos.clear(); filhos = f; }
	void setPontos(vector<Ponto> p){ pontos = p; }
	void setNormais(vector<Ponto> n){ normais = n; }
	void setTexturas(vector<Ponto> t){ texturas = t; }
	void setTransformacao(Transformacao t){ transformacao = t; }
	void preparar();
	void desenhar();
	void construir();
	void criarTextura();
	virtual ~Primitiva() {};
}; 