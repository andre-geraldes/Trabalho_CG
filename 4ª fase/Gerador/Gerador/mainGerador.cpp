#include "main.h"

//Função que gera os pontos do plano:
void plano(float comp, float larg, int cmdh, int cmdv, string filename)
{
	ofstream file(filename);
	float saltoz = (float) comp / cmdv; //Salto em comprimento
	float saltox = (float) larg / cmdh; //Salto em largura 
	float refx = -((float) larg / 2); //Ponto inicial x
	float refz = -((float) comp / 2); //Ponto inicial z
	float xx, zz;
	int i,j;

	Ponto p;
	//Saltos nas texturas
	float saltoTexx = 1.0 / cmdv;
	float saltoTexz = 1.0 / cmdh;


	// Normais e texturas:
	vector<Ponto> normais;
	vector<Ponto> texturas;

	//Numero de pontos:
	file << cmdh * cmdv * 6 << endl;
	//Numero de camadas horiz:
	file << cmdh << endl;
	//Numero de camadas vert:
	file << cmdv << endl;

	for (i = 0; i < cmdh; i++)
	{
		xx = refx + saltox * i;
		for (j = 0; j < cmdv; j++) 
		{
			zz = refz + saltoz * j;

			printf("%f 0 %f\n", xx, zz);
			file << xx << "," << 0 << "," << zz << endl;
			printf("%f 0 %f\n", xx, zz + saltoz);
			file << xx << "," << 0 << "," << zz+saltoz << endl;
			printf("%f 0 %f\n", xx + saltox, zz);
			file << xx + saltox << "," << 0 << "," << zz << endl;
			//Pontos normais:
			p = Ponto::Ponto(0, 1, 0);
			normais.push_back(p);
			normais.push_back(p);
			normais.push_back(p);
			//Pontos texturas:
			p = Ponto::Ponto(1 - (cmdv - j)*saltoTexx, 1 - i*saltoTexz, 0);
			texturas.push_back(p);
			p = Ponto::Ponto(1 - (cmdv - j)*saltoTexx, 1 - (i+1)*saltoTexz, 0);
			texturas.push_back(p);
			p = Ponto::Ponto(1 - (cmdv - (j+1))*saltoTexx, 1 - i*saltoTexz, 0);
			texturas.push_back(p);

			printf("%f 0 %f\n", xx, zz + saltoz);
			file << xx << "," << 0 << "," << zz+saltoz << endl;
			printf("%f 0 %f\n", xx+saltox, zz + saltoz);
			file << xx+saltox << "," << 0 << "," << zz+saltoz << endl;
			printf("%f 0 %f\n", xx + saltox, zz);
			file << xx + saltox << "," << 0 << "," << zz << endl;
			//Pontos normais:
			p = Ponto::Ponto(0, 1, 0);
			normais.push_back(p);
			normais.push_back(p);
			normais.push_back(p);
			//Pontos texturas:
			p = Ponto::Ponto(1 - (cmdv - j)*saltoTexx, 1 - (i + 1)*saltoTexz, 0);
			texturas.push_back(p);
			p = Ponto::Ponto(1 - (cmdv - (j + 1))*saltoTexx, 1 - (i + 1)*saltoTexz, 0);
			texturas.push_back(p);
			p = Ponto::Ponto(1 - (cmdv - (j + 1))*saltoTexx, 1 - i*saltoTexz, 0);
			texturas.push_back(p);
		}
	}
	int nn = normais.size();
	for (i = 0; i < nn; i++){
		file << normais[i].getX() << "," << normais[i].getY() << "," << normais[i].getZ() << endl;
	}
	int nt = texturas.size();
	for (i = 0; i < nt; i++){
		file << texturas[i].getX() << "," << texturas[i].getY() << "," << texturas[i].getZ() << endl;
	}
}

//Função que gera os pontos do paralelipipedo:
void paralelipipedo(float comp, float larg, float alt, int cmdh, int cmdv, int cmdl, string filename) 
{
	ofstream file(filename);
	float saltox = (float) larg / cmdl;
	float saltoz = (float) comp / cmdv;
	float saltoy = (float) alt / cmdh;
	float refx = -((float) larg / 2); //Ponto inicial x
	float refz = -((float) comp / 2); //Ponto inicial z
	float refy = -((float) alt / 2); //Ponto incial y
	float xx, yy, zz;
	int i, j;


	//Plano inferior e superior:
	for (i = 0; i < cmdl; i++)
	{
		xx = refx + saltox * i;
		for (j = 0; j < cmdv; j++)
		{
			zz = refz + saltoz * j;
			//Inferior
			printf("%f %f %f\n", xx, refy, zz);
			file << xx << "," << refy << "," << zz << endl;
			printf("%f %f %f\n", xx + saltox, refy, zz);
			file << xx+saltox << "," << refy << "," << zz << endl;
			printf("%f %f %f\n", xx, refy, zz + saltoz);
			file << xx << "," << refy << "," << zz+saltoz << endl;

			printf("%f %f %f\n", xx, refy, zz + saltoz);
			file << xx << "," << refy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", xx + saltox, refy, zz);
			file << xx+saltox << "," << refy << "," << zz << endl;
			printf("%f %f %f\n", xx + saltox, refy, zz + saltoz);
			file << xx+saltox << "," << refy << "," << zz+saltoz << endl;

			//Superior
			printf("%f %f %f\n", xx, -refy, zz);
			file << xx << "," << -refy << "," << zz << endl;
			printf("%f %f %f\n", xx, -refy, zz + saltoz);
			file << xx << "," << -refy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", xx + saltox, -refy, zz);
			file << xx+saltox << "," << -refy << "," << zz << endl;

			printf("%f %f %f\n", xx, -refy, zz + saltoz);
			file << xx << "," << -refy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", xx + saltox, -refy, zz + saltoz);
			file << xx+saltox << "," << -refy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", xx + saltox, -refy, zz);
			file << xx+saltox << "," << -refy << "," << zz << endl;
		}
	}
	

	//Plano traseiro e frontal:
	for (i = 0; i < cmdh; i++)
	{
		yy = refy + saltoy * i;
		for (j = 0; j < cmdv; j++)
		{
			zz = refz + saltoz * j;
			//Traseiro
			printf("%f %f %f\n", refx, yy, zz);
			file << refx << "," << yy << "," << zz << endl;
			printf("%f %f %f\n", refx, yy + saltoy, zz + saltoz);
			file << refx << "," << yy+saltoy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", refx, yy + saltoy, zz);
			file << refx << "," << yy+saltoy << "," << zz << endl;

			printf("%f %f %f\n", refx, yy, zz);
			file << refx << "," << yy << "," << zz << endl;
			printf("%f %f %f\n", refx, yy, zz + saltoz);
			file << refx << "," << yy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", refx, yy + saltoy, zz + saltoz);
			file << refx << "," << yy+saltoy << "," << zz+saltoz << endl;
			

			//Frontal
			printf("%f %f %f\n", -refx, yy, zz);
			file << -refx << "," << yy << "," << zz << endl;
			printf("%f %f %f\n", -refx, yy + saltoy, zz);
			file << -refx << "," << yy+saltoy << "," << zz << endl;
			printf("%f %f %f\n", -refx, yy + saltoy, zz + saltoz);	
			file << -refx << "," << yy+saltoy << "," << zz+saltoz << endl;

			printf("%f %f %f\n", -refx, yy, zz);
			file << -refx << "," << yy << "," << zz << endl;
			printf("%f %f %f\n", -refx, yy + saltoy, zz + saltoz);
			file << -refx << "," << yy+saltoy << "," << zz+saltoz << endl;
			printf("%f %f %f\n", -refx, yy, zz + saltoz);
			file << -refx << "," << yy << "," << zz+saltoz << endl;
		}
	}
	

	//Plano lateral esquerdo e lateral direito:
	for (i = 0; i < cmdh; i++)
	{	
		yy = refy + saltoy * i;
		for (j = 0; j < cmdl; j++)
		{
			xx = refx + saltox * j;
			//Lateral esquerdo:
			printf("%f %f %f\n", xx, yy, refz);
			file << xx << "," << yy << "," << refz << endl;
			printf("%f %f %f\n", xx, yy + saltoy, refz);
			file << xx << "," << yy+saltoy << "," << refz << endl;
			printf("%f %f %f\n", xx + saltox, yy, refz);
			file << xx+saltox << "," << yy << "," << refz << endl;

			printf("%f %f %f\n", xx, yy + saltoy, refz);
			file << xx << "," << yy+saltoy << "," << refz << endl;
			printf("%f %f %f\n", xx + saltox, yy + saltoy, refz);
			file << xx+saltox << "," << yy+saltoy << "," << refz << endl;
			printf("%f %f %f\n", xx + saltox, yy, refz);
			file << xx+saltox << "," << yy << "," << refz << endl;


			//Lateral direito:
			printf("%f %f %f\n", xx, yy, -refz); 
			file << xx << "," << yy << "," << -refz << endl;
			printf("%f %f %f\n", xx + saltox, yy, -refz); 
			file << xx+saltox << "," << yy << "," << -refz << endl;
			printf("%f %f %f\n", xx, yy + saltoy, -refz); 
			file << xx << "," << yy+saltoy << "," << -refz << endl;

			printf("%f %f %f\n", xx, yy + saltoy, -refz); 
			file << xx << "," << yy+saltoy << "," << -refz << endl;
			printf("%f %f %f\n", xx + saltox, yy, -refz); 
			file << xx+saltox << "," << yy << "," << -refz << endl;
			printf("%f %f %f\n", xx + saltox, yy + saltoy, -refz); 
			file << xx+saltox << "," << yy+saltoy << "," << -refz << endl;
		}
	}

}

//Função que gera os pontos da esfera:
void esfera(double raio, int camadasV, int camadasH, string filename)
{
	ofstream file(filename);
	float teta = 0; float fi = 0;
	float saltoH = M_PI / camadasH;
	float saltoV = 2 * (M_PI) / camadasV;
	int i, j;
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

	// Normais e texturas:
	vector<Ponto> normais;
	vector<Ponto> texturas;
	Ponto p;
	float espv = 1.0 / camadasV;
	float esph = 1.0 / camadasH;
	
	file << camadasH * camadasV * 6 << endl;
	file << camadasH << endl;
	file << camadasV << endl;

	for (i = 0; i < camadasH; i++){
		teta = 0;

		for (j = 0; j < camadasV; j++){
			x1 = raio*sin(fi)*sin(teta);
			y1 = raio*cos(fi);
			z1 = raio*sin(fi)*cos(teta);

			x2 = raio*sin(fi + saltoH)*sin(teta + saltoV);
			y2 = raio*cos(fi + saltoH);
			z2 = raio*sin(fi + saltoH)*cos(teta + saltoV);

			x3 = raio*sin(fi + saltoH)*sin(teta);
			y3 = raio*cos(fi + saltoH);
			z3 = raio*sin(fi + saltoH)* cos(teta);

			x4 = raio*sin(fi)*sin(teta + saltoV);
			y4 = raio*cos(fi);
			z4 = raio*sin(fi)*cos(teta + saltoV);


			printf("%f %f %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			p = Ponto::Ponto(x1/raio,y1/raio,z1/raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j)*espv, 1-i*esph, 0);
			texturas.push_back(p);
			printf("%f %f %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
			p = Ponto::Ponto(x2/raio,y2/raio,z2/raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j - 1)*espv, 1 - (i+1)*esph, 0);
			texturas.push_back(p);
			printf("%f %f %f\n", x3, y3, z3); file << x3 << "," << y3 << "," << z3 << endl;
			p = Ponto::Ponto(x3/raio,y3/raio,z3/raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j)*espv, 1 - (i+1)*esph, 0);
			texturas.push_back(p);


			printf("%f %f %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			p = Ponto::Ponto(x1 / raio, y1 / raio, z1 / raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j)*espv, 1 - i*esph, 0);
			texturas.push_back(p);
			printf("%f %f %f\n", x4, y4, z4); file << x4 << "," << y4 << "," << z4 << endl;
			p = Ponto::Ponto(x4 / raio, y4 / raio, z4 / raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j - 1)*espv, 1 - i*esph, 0);
			texturas.push_back(p);
			printf("%f %f %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
			p = Ponto::Ponto(x2 / raio, y2 / raio, z2 / raio);
			normais.push_back(p);
			p = Ponto::Ponto(1 - (camadasV - j - 1)*espv, 1 - (i + 1)*esph, 0);
			texturas.push_back(p);


			teta += saltoV;
		}
		fi += saltoH;
	}
	int nn = normais.size();
	for (i = 0; i < nn; i++){
		file << normais[i].getX() << "," << normais[i].getY() << "," << normais[i].getZ() << endl;
	}
	int nt = texturas.size();
	for (i = 0; i < nt; i++){
		file << texturas[i].getX() << "," << texturas[i].getY() << "," << texturas[i].getZ() << endl;
	}
}

//Função que gera os pontos do cone:
void cone(double raio, double altura, double cmdv, double cmdh, string filename)
{
	ofstream file(filename);
	double espv = (2 * M_PI) / cmdv;
	double espl = altura / cmdh;
	double dif = raio / cmdh;
	double alfa = 0;
	double alfa1 = espv;


	altura = -(altura / 2);

	//Base
	for (int i = 0; i <= cmdv; i++){
		printf("%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura << "," << raio*cos(alfa) << endl;
		printf("0 %f 0\n", altura); file << 0 << "," << altura << "," << 0 << endl;
		printf("%f %f %f\n", raio*sin(alfa1), altura, raio*cos(alfa1)); file << raio*sin(alfa1) << "," << altura << "," << raio*cos(alfa1) << endl;

		alfa = espv*(i + 1);
		alfa1 = espv*(i + 2);
	}

	//Resto
	for (int i = 0; i < cmdh; i++){

		for (int j = 0; j < cmdv; j++){
			alfa += espv;
			double raionovo = raio - dif;

			printf("%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura << "," << raio*cos(alfa) << endl;
			printf("%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); file << raio*sin(alfa + espv) << "," << altura << "," << raio*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raionovo*sin(alfa), altura + espl, raionovo*cos(alfa)); file << raionovo*sin(alfa) << "," << altura + espl << "," << raionovo*cos(alfa) << endl;

			printf("%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); file << raio*sin(alfa + espv) << "," << altura << "," << raio*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raionovo*sin(alfa + espv), altura + espl, raionovo*cos(alfa + espv)); file << raionovo*sin(alfa + espv) << "," << altura+espl << "," << raionovo*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raionovo*sin(alfa), altura + espl, raionovo*cos(alfa)); file << raionovo*sin(alfa) << "," << altura + espl << "," << raionovo*cos(alfa) << endl;
		}
		raio = raio - dif;
		altura = altura + espl;
	}
}

//Função que gera os pontos do cilindro:
void cilindro(double raio, double altura, int cmdh, int cmdv, string filename)
{
	ofstream file(filename);
	double espv = (2 * M_PI) / cmdv;
	double espl = altura / cmdh;
	double alfa = 0;
	double alfa1 = espv;


	altura = -(altura / 2);

	//Bases
	for (int i = 0; i <= cmdv; i++){
		//Baixo
		printf("%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura << "," << raio*cos(alfa) << endl;
		printf("0 %f 0\n", altura); file << 0 << "," << altura << "," << 0 << endl;
		printf("%f %f %f\n", raio*sin(alfa1), altura, raio*cos(alfa1)); file << raio*sin(alfa1) << "," << altura << "," << raio*cos(alfa1) << endl;

		//Cima
		printf("%f %f %f\n", raio*sin(alfa), -altura, raio*cos(alfa)); file << raio*sin(alfa) << "," << -altura << "," << raio*cos(alfa) << endl;
		printf("%f %f %f\n", raio*sin(alfa1), -altura, raio*cos(alfa1)); file << raio*sin(alfa1) << "," << -altura << "," << raio*cos(alfa1) << endl;
		printf("%f %f %f\n", 0, -altura, 0); file << 0 << "," << -altura << "," << 0 << endl;

		alfa = espv*(i + 1);
		alfa1 = espv*(i + 2);
	}


	//Resto
	for (int i = 0; i < cmdh; i++){
		for (int j = 0; j < cmdv; j++){
			alfa += espv;

			printf("%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura << "," << raio*cos(alfa) << endl;
			printf("%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); file << raio*sin(alfa + espv) << "," << altura << "," << raio*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raio*sin(alfa), altura + espl, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura + espl << "," << raio*cos(alfa) << endl;

			printf("%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); file << raio*sin(alfa + espv) << "," << altura << "," << raio*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raio*sin(alfa + espv), altura + espl, raio*cos(alfa + espv)); file << raio*sin(alfa + espv) << "," << altura + espl << "," << raio*cos(alfa + espv) << endl;
			printf("%f %f %f\n", raio*sin(alfa), altura + espl, raio*cos(alfa)); file << raio*sin(alfa) << "," << altura + espl << "," << raio*cos(alfa) << endl;
		}
		altura = altura + espl;
	}
}

void readPatch(string path) {
	int i, j, pos, ind, np, nv;
	float ponto[3], n;
	string line, token;

	//Abrir ficheiro
	ifstream ifile;
	ifile.open(path, ios::in);

	if (ifile.is_open()) {
		ifile >> np; getline(ifile, line);

		//Get patch
		for (i = 0; i < np && getline(ifile, line); i++) {
			Patch pa = Patch::Patch();
			for (j = 0; j < 16; j++) {
				pos = line.find(",");
				token = line.substr(0, pos);
				ind = atof(token.c_str());
				line.erase(0, pos + 1);

				pa.adicionaIndice(ind);
			}
			patchs.push_back(pa);
		}

		ifile >> nv; getline(ifile, line);

		//Get pontos 
		for (i = 0; i < nv && getline(ifile, line); i++) {
			for (j = 0; j < 3; j++) {
				pos = line.find(",");
				token = line.substr(0, pos);
				n = atof(token.c_str());
				line.erase(0, pos + 1);

				ponto[j] = n;
			}
			vertices.push_back(Ponto::Ponto(ponto[0], ponto[1], ponto[2]));
		}
		ifile.close();
	}
	else {
		printf("Ficheiro %s.patch nao encontrado!\n", path);
	}
}

Ponto calcular(float t, float *p1, float *p2, float *p3, float *p4) {
	float res[3];

	float it = 1.0 - t;

	float b0 = it*it*it;
	float b1 = 3 * t*it*it;
	float b2 = 3 * t*t*it;
	float b3 = t*t*t;

	res[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
	res[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
	res[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];

	return Ponto::Ponto(res[0], res[1], res[2]);
}

void escreveTri(Ponto p1, Ponto p2, Ponto p3, ofstream& file) {
	file << p1.getX() << "," << p1.getY() << "," << p1.getZ() << endl;
	file << p2.getX() << "," << p2.getY() << "," << p2.getZ() << endl;
	file << p3.getX() << "," << p3.getY() << "," << p3.getZ() << endl;
}

Ponto bezier(float u, float v, vector<int> pat) {
	float bz[4][3], res[4][3];
	int i, j = 0, k = 0;

	for (i = 0; i < 16; i++) {
		bz[j][0] = vertices[pat[i]].getX();
		bz[j][1] = vertices[pat[i]].getY();
		bz[j][2] = vertices[pat[i]].getZ();

		j++;

		if (j % 4 == 0) {
			Ponto p = calcular(u, bz[0], bz[1], bz[2], bz[3]);
			res[k][0] = p.getX();
			res[k][1] = p.getY();
			res[k][2] = p.getZ();

			k++;
			j = 0;
		}
	}
	return calcular(v, res[0], res[1], res[2], res[3]);
}

void patchBezier(int tess, int ip, ofstream& file) {
	float inc = 1.0 / tess, u, v, u2, v2;

	for (int i = 0; i < tess; i++) {
		for (int j = 0; j < tess; j++) {
			u = i*inc;
			v = j*inc;
			u2 = (i + 1)*inc;
			v2 = (j + 1)*inc;

			Ponto p0 = bezier(u, v, patchs[ip].getPatch());
			Ponto p1 = bezier(u, v2, patchs[ip].getPatch());
			Ponto p2 = bezier(u2, v, patchs[ip].getPatch());
			Ponto p3 = bezier(u2, v2, patchs[ip].getPatch());

			escreveTri(p0, p2, p3, file);
			escreveTri(p0, p3, p1, file);
		}
	}
}

//Escrever pontos do teapot
void initSupBezier(int tess, string nameFile) {
	ofstream file;
	file.open(nameFile);

	int num = patchs.size();

	for (int i = 0; i < num; i++)
		patchBezier(tess, i, file);
	
	file.close();
}

int main(int argc, char **argv) 
{
	if (argc>1) {
		if (!strcmp(argv[1], "plano") && argc == 7) {
			cout << "Plano:\n" << endl;
			plano(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
		}
		else {
			if (!strcmp(argv[1], "paralelipipedo") && argc == 9) {
				cout << "Paralelipipedo\n" << endl;
				paralelipipedo(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), argv[8]);
			}
			else {
				if (!strcmp(argv[1], "cone") && argc == 7) {
					cout << "Cone\n" << endl;
					cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
				}
				else {
					if (!strcmp(argv[1], "esfera") && argc == 6) {
						cout << "Esfera\n" << endl;
						esfera(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
					}
					else {
						if (!strcmp(argv[1], "cilindro") && argc == 7) {
							cout << "Cilindro\n" << endl;
							cilindro(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
						}
						else {
							char token[7];
							//Reconhecer se é do tipo .patch
							if (argc == 4) {
								string abc = argv[1];
								int pos = abc.find(".");
								abc = abc.substr(pos, pos + 6);
								strcpy_s(token, size_t(7), abc.c_str());
							}
							if (!strcmp(token, ".patch") && argc == 4) {
								cout << argv[1] << endl;
								readPatch(argv[1]);	// Leitura do .patch
								initSupBezier(atoi(argv[2]), argv[3]); //Inteiro para camadas e Nome do Ficheiro a Ser Gerado
							}
								else {
									cout << "Dados invalidos! - Primitiva nao desenhada" << endl;
								}
						}
					}
				}
			}
		}
	}

	return 0;
}