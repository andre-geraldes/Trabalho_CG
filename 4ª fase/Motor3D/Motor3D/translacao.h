#pragma once

#include <vector>
#include "Ponto.h"

using namespace std;

class Translacao{
	float time;
	int tam;
	vector<Ponto> pontosTrans;
	vector<Ponto> pontosCurva;

public:
	Translacao();
	Translacao(float);
	Translacao(float, vector<Ponto>, int);
	vector<Ponto> getPontosTrans(){ return pontosTrans; }
	vector<Ponto> getPontosCurva(){ return pontosCurva; }
	float getTime(){ return time; }
	void setTime(float t) { time = t; }
	void setPontosTrans(vector<Ponto> p){ pontosTrans = p; }
	void setPontosCurva(vector<Ponto> p){ pontosCurva = p; }
	void Translacao::getGlobalCatmullRomPoint(float, float *, vector<Ponto>);
	void Translacao::execCurvas();
	virtual ~Translacao() {};
};