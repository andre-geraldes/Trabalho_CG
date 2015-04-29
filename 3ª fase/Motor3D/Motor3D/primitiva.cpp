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

void Primitiva::construir() {
	int numpontos = pontos.size();

	glBegin(GL_TRIANGLES);
	for (int j = 0; j< numpontos; j++) {
		glVertex3f(pontos.at(j).getX(), pontos.at(j).getY(), pontos.at(j).getZ());
	}
	glEnd();
}

void Primitiva::preparar() {
	int h = 0;

	glEnableClientState(GL_VERTEX_ARRAY);

	v = (float *)malloc(sizeof(float) * 3 * pontos.size());

	for (size_t i = 0; i < pontos.size(); i++){
		v[h] = pontos[i].getX();
		v[h + 1] = pontos[i].getY();
		v[h + 2] = pontos[i].getZ();
		h += 3;
	}
	
	nvertex = h; /*Tamanho de v*/

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nvertex, v, GL_STATIC_DRAW);

	free(v);
}

void Primitiva::desenhar() {
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nvertex);
}