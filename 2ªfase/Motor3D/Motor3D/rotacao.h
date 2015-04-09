class Rotacao{
	float angulo;
	float eixoX;
	float eixoY;
	float eixoZ;

public:
	Rotacao();
	Rotacao(float, float, float, float);
	float getAngulo() { return angulo; }
	float geteixoX() { return eixoX; }
	float geteixoY() { return eixoY; }
	float geteixoZ() { return eixoZ; }
	void setAngulo(float a){ angulo = a; }
	void setEixoX(float x){ eixoX = x; }
	void setEixoY(float y){ eixoY = y; }
	void setEixoZ(float z){ eixoZ = z; }
	virtual ~Rotacao();
};