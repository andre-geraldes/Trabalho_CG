class Ponto{
	float x;
	float y;
	float z;

public:
	Ponto();
	Ponto(float, float, float);
	float getX(){ return x; }
	float getY(){ return y; };
	float getZ() { return z; };
	void setX(float a)
	virtual ~Ponto();
}