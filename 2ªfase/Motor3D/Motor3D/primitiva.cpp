#include "primitiva.h"


Primitiva::Primitiva(){
	nome = "";
	transformacao = Transformacao::Transformacao();
	filhos = vector<Primitiva>();
	pontos = vector<Ponto>();
}

Primitiva::Primitiva(string n, vector<Primitiva> f, vector<Ponto> p, Transformacao t ){
	nome = n;
	filhos = f;
	pontos = p;
	transformacao = t;
}