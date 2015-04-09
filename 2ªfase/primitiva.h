#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>

class Primitiva{

	string nome;
	vector<Primitiva> filhos;
	int cmdV;
	int cmdH;
	int cmdL;
	float altura;
	float largura;
	float comprimento;
	Transformacao transformacao;

public:
	Primitiva();
	Primitiva(string, vector<Primitiva>, int, int, int, float, float, float, Transformacao);
	string getNome(){ return nome; }
	vector<Primitiva> getFilhos(){ return filhos; }
	int getcmdV(){ return cmdV; }
	int getcmdH(){ return cmdH; }
	int getcmdL(){ return cmdL; }
	float getAltura(){ return altura; }
	float getLargura(){ return largura; }
	float getComprimento(){ return comprimento; }
	void setNome(string n){ nome = n; }
	void setFilhos(vector<Primitiva> f){ filhos = f; }
	void setcmdV(int v){ cmdV = v; }
	void setcmdH(int h){ cmdH = h; }
	void setcmdL(int l){ cmdL = l; }
	void setAltura(float a){ altura = a; }
	void setLargura(float l){ largura = l; }
	void setComprimento(float c){ comprimento = c; }
	void setTransformacao(Transformacao t){ transformacao = t; }
	virtual ~Primitiva();
}; 