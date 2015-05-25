#pragma once

class Ponto{
	float x;
	float y;
	float z;

public:
	Ponto();
	Ponto(float, float, float);
	float getX(){ return x; };
	float getY(){ return y; };
	float getZ() { return z; };
	void setX(float a) { x = a; };
	void setY(float a) { y = a; };
	void setZ(float a) { z = a; };
	virtual ~Ponto() {};
};