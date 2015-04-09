#include <vector>
#include "Ponto.h"

class Translacao{
	float x;
	float y;
	float z;

public:
	Translacao();
	Translacao(float, float, float);
	float getTransx() { return x; }
	float getTransy() { return y; }
	float getTransz() { return z; }
	void setTransx(float a) { x = a; }
	void setTransy(float b) { y = b; }
	void setTransz(float c) { z = c; }
	virtual ~Translacao();
};