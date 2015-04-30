#include "Translacao.h"

Translacao::Translacao(){
	time = 0;
}

Translacao::Translacao(float t){
	time = t;
}

Translacao::Translacao(float t, vector<Ponto> vtp, int num) {
	time = t;
	pontosTrans = vtp;
	tam = num;
}

void getCatmullRomPoint(float t, int *indices, float *res, vector<Ponto> transpontos) {
	float res_aux[4];

	float m[4][4] = { { -0.5f, 1.5f, -1.5f, 0.5f },
	{ 1.0f, -2.5f, 2.0f, -0.5f },
	{ -0.5f, 0.0f, 0.5f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f } };

	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
	float t3 = t*t*t, t2 = t*t;

	//T*M
	res_aux[0] = t3*m[0][0] + t2*m[1][0] + t*m[2][0] + m[3][0];
	res_aux[1] = t3*m[0][1] + t2*m[1][1] + t*m[2][1] + m[3][1];
	res_aux[2] = t3*m[0][2] + t2*m[1][2] + t*m[2][2] + m[3][2];
	res_aux[3] = t3*m[0][3] + t2*m[1][3] + t*m[2][3] + m[3][3];

	int i0 = indices[0]; Ponto p0 = transpontos[i0];
	int i1 = indices[1]; Ponto p1 = transpontos[i1];
	int i2 = indices[2]; Ponto p2 = transpontos[i2];
	int i3 = indices[3]; Ponto p3 = transpontos[i3];

	//T*M*P = res
	res[0] = res_aux[0] * p0.getX() + res_aux[1] * p1.getX() + res_aux[2] * p2.getX() + res_aux[3] * p3.getX();
	res[1] = res_aux[0] * p0.getY() + res_aux[1] * p1.getY() + res_aux[2] * p2.getY() + res_aux[3] * p3.getY();
	res[2] = res_aux[0] * p0.getZ() + res_aux[1] * p1.getZ() + res_aux[2] * p2.getZ() + res_aux[3] * p3.getZ();
}

void Translacao::getGlobalCatmullRomPoint(float gt, float *res, vector<Ponto> transpontos) {
	int tamanho = transpontos.size();
	float t = gt * tamanho; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + tamanho - 1) % tamanho;
	indices[1] = (indices[0] + 1) % tamanho;
	indices[2] = (indices[1] + 1) % tamanho;
	indices[3] = (indices[2] + 1) % tamanho;

	getCatmullRomPoint(t, indices, res, transpontos);
}

void Translacao::execCurvas() {
	float res[3];

	for (float gt = 0; gt<1; gt += 0.01){
		getGlobalCatmullRomPoint(gt, res, pontosTrans);

		Ponto p = Ponto::Ponto(res[0], res[1], res[2]);
		pontosCurva.push_back(p);
	}
}


