#include "main.h"

void plano(float comp, float larg, int cmdh, int cmdv, string filename)
{
	ofstream file(filename);
	float saltoz = (float) comp / cmdv; //Salto em comprimento
	float saltox = (float) larg / cmdh; //Salto em largura 
	float refx = -((float) larg / 2); //Ponto inicial x
	float refz = -((float) comp / 2); //Ponto inicial z
	float xx, zz;
	int i,j;
	
	for (i = 0; i < cmdh; i++)
	{
		xx = refx + saltox * i;
		for (j = 0; j < cmdv; j++) 
		{
			zz = refz + saltoz * j;

			printf("%f 0 %f\n", xx, zz);
			file << xx << "," << 0 << "," << zz << endl;
			printf("%f 0 %f\n", xx+saltox, zz);
			file << xx+saltox << "," << 0 << "," << zz << endl;
			printf("%f 0 %f\n", xx, zz + saltoz);
			file << xx << "," << 0 << "," << zz+saltoz << endl;

			printf("%f 0 %f\n", xx, zz + saltoz);
			file << xx << "," << 0 << "," << zz+saltoz << endl;
			printf("%f 0 %f\n", xx + saltox, zz);
			file << xx+saltox << "," << 0 << "," << zz << endl;
			printf("%f 0 %f\n", xx+saltox, zz + saltoz);
			file << xx+saltox << "," << 0 << "," << zz+saltoz << endl;
		}
	}
}

void paralelipipedo(float comp, float larg, float alt, int cmdh, int cmdv, int cmdl, string filename) {
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

void esfera(double raio, int camadasV, int camadasH, string filename){
	ofstream file(filename);
	float teta = 0; float fi = 0;
	float saltoH = M_PI / camadasH;
	float saltoV = 2 * (M_PI) / camadasV;
	int i, j;
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	
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
			printf("%f %f %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
			printf("%f %f %f\n", x3, y3, z3); file << x3 << "," << y3 << "," << z3 << endl;

			printf("%f %f %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			printf("%f %f %f\n", x4, y4, z4); file << x4 << "," << y4 << "," << z4 << endl;
			printf("%f %f %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;

			teta += saltoV;
		}
		fi += saltoH;
	}
}

void cone(double raio, double altura, double cmdv, double cmdh, string filename){
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

			glColor3f(1, 0, 1);

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

int main(int argc, char **argv) {
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
						cout << "Dados invalidos! - Primitiva nao desenhada" << endl;
					}
				}
			}
		}
	}

	//plano(2, 2, 2, 2, "oi");
	//paralelipipedo(4, 2, 2, 2, 2, 2, "oi");
	//esfera(2, 2, 2, "21");
	return 0;
}