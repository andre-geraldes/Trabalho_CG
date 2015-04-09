#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>

class Primitiva{

	string nome;
	vector<Primitiva> filhos;
	vector<Ponto> pontos;
	Transformacao transformacao;

public:
	Primitiva();
	Primitiva(string, vector<Primitiva>, vector<Ponto>, Transformacao);
	string getNome(){ return nome; }
	vector<Ponto> getPontos() { return pontos; }
	vector<Primitiva> getFilhos(){ return filhos; }
	void setNome(string n){ nome = n; }
	void setFilhos(vector<Primitiva> f){ filhos = f; }
	void setPontos(vector<Pontos> p){ pontos = p; }
	void setTransformacao(Transformacao t){ transformacao = t; }
	virtual ~Primitiva();
}; 