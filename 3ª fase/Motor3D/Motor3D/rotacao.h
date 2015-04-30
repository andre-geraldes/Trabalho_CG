#pragma once

#include <vector>
#include "ponto.h"

class Rotacao{
	float time;
	float eixoX;
	float eixoY;
	float eixoZ;

public:
	Rotacao();
	Rotacao(float, float, float, float);
	float geteixoX() { return eixoX; }
	float geteixoY() { return eixoY; }
	float geteixoZ() { return eixoZ; }
	float getTime() { return time; }
	void setTime(float t) { time = t; }
	void setEixoX(float x){ eixoX = x; }
	void setEixoY(float y){ eixoY = y; }
	void setEixoZ(float z){ eixoZ = z; }
	virtual ~Rotacao() {};
};