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
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	v = (float *)malloc(sizeof(float) * 3 * pontos.size());
	n = (float *)malloc(sizeof(float) * 3 * normais.size());
	tex = (float *)malloc(sizeof(float) * 2 * texturas.size());

	for (size_t i = 0; i < pontos.size(); i++){
		v[h] = pontos[i].getX();
		v[h + 1] = pontos[i].getY();
		v[h + 2] = pontos[i].getZ();
		h += 3;
	}

	h = 0;
	for (size_t i = 0; i < normais.size(); i++){
		n[h] = normais[i].getX();
		n[h + 1] = normais[i].getY();
		n[h + 2] = normais[i].getZ();
		h += 3;
	}

	h = 0;
	for (size_t i = 0; i < texturas.size(); i++){
		tex[h] = texturas[i].getX();
		tex[h + 1] = texturas[i].getY();
		h += 2;
	}

	nvertex = pontos.size() * 3;
	nnormais = normais.size() * 3;
	ntexturas = texturas.size() * 2;

	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nvertex, v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nnormais, n, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ntexturas, tex, GL_STATIC_DRAW);

	free(v);
	free(n);
	free(tex);
	criarTextura();
}

void Primitiva::desenhar() {
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nvertex);
}

void Primitiva::criarTextura(){
	string path = "texturas/" + textura;
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)path.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1, &texID); // unsigned int texID - variavel global;
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
}