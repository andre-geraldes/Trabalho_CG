#pragma once

#include <vector>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "ponto.h"
#include "Transformacao.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Primitiva{

	string nome;
	vector<Primitiva> filhos;
	vector<Ponto> pontos;
	Transformacao transformacao;
	GLuint buffers[3];
	int nvertex;
	float *v;

public:
	Primitiva();
	Primitiva(string n, vector<Primitiva>, vector<Ponto>, Transformacao);
	string getNome(){ return nome; }
	vector<Ponto> getPontos() { return pontos; }
	vector<Primitiva> getFilhos(){ return filhos; }
	Transformacao getTransformacao(){ return transformacao; }
	void setNome(string n){ nome = n; }
	void setFilho(Primitiva f){ filhos.push_back(f); }
	void setFilhos(vector<Primitiva> f){ filhos.clear(); filhos = f; }
	void setPontos(vector<Ponto> p){ pontos = p; }
	void setTransformacao(Transformacao t){ transformacao = t; }
	void preparar();
	void desenhar();
	void construir();
	virtual ~Primitiva() {};
}; 