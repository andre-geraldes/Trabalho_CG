#include <stdlib.h>
#include <iostream>
using namespace std;
#include <string>
#include <GL/glut.h>
#include <math.h>

void plano(float comp, float larg, int cmdh, int cmdv, string filename)
{
	float saltoz = comp / cmdv; //Salto em comprimento
	float saltox = larg / cmdh; //Salto em largura 
	float refx = -(larg / 2); //Ponto inicial x
	float refz = -(comp / 2); //Ponto inicial z
	float i,j;
	
	for (i = refx; i < (larg/2); i += saltox)
	{
		for (j = refz; j < (comp/2); j += saltoz)
		{
			printf("%f 0 %f\n", i, j);
			printf("%f 0 %f\n", i+saltox, j);
			printf("%f 0 %f\n", i, j + saltoz);

			printf("%f 0 %f\n", i, j + saltoz);
			printf("%f 0 %f\n", i + saltox, j);
			printf("%f 0 %f\n", i+saltox, j + saltoz);
		}
	}
}

void paralelipipedo(float comp, float larg, float alt, int cmdh, int cmdv, int cmdl, string str) {
	float saltox = larg / cmdl;
	float saltoz = comp / cmdv;
	float saltoy = alt / cmdh;
	float refx = -(larg / 2); //Ponto inicial x
	float refz = -(comp / 2); //Ponto inicial z
	float refy = -(alt / 2); //Ponto incial y
	float i, j;


	//Plano inferior e superior:
	for (i = refx; i < (larg / 2); i += saltox)
	{
		for (j = refz; j < (comp / 2); j += saltoz)
		{
			//Inferior
			printf("%f %f %f\n", i, refy, j);
			printf("%f %f %f\n", i + saltox, refy, j);
			printf("%f %f %f\n", i, refy, j + saltoz);

			printf("%f %f %f\n", i, refy, j + saltoz);
			printf("%f %f %f\n", i + saltox, refy, j);
			printf("%f %f %f\n", i + saltox, refy, j + saltoz);

			//Superior
			printf("%f %f %f\n", i, -refy, j);
			printf("%f %f %f\n", i + saltox, -refy, j);
			printf("%f %f %f\n", i, -refy, j + saltoz);

			printf("%f %f %f\n", i, -refy, j + saltoz);
			printf("%f %f %f\n", i + saltox, -refy, j);
			printf("%f %f %f\n", i + saltox, -refy, j + saltoz);
		}
	}
	

	//Plano traseiro e frontal:
	for (i = refy; i < (alt / 2); i += saltoy)
	{
		for (j = refz; j < (comp / 2); j += saltoz)
		{
			//Traseiro
			printf("%f %f %f\n", refx, i, j);
			printf("%f %f %f\n", refx, i + saltoy, j + saltoz);
			printf("%f %f %f\n", refx, i + saltoy, j);

			printf("%f %f %f\n", refx, i, j);
			printf("%f %f %f\n", refx, i, j + saltoz);
			printf("%f %f %f\n", refx, i + saltoy, j + saltoz);
			

			//Frontal
			printf("%f %f %f\n", -refx, i, j);
			printf("%f %f %f\n", -refx, i + saltoy, j + saltoz);
			printf("%f %f %f\n", -refx, i + saltoy, j);

			printf("%f %f %f\n", -refx, i, j);
			printf("%f %f %f\n", -refx, i, j + saltoz);
			printf("%f %f %f\n", -refx, i + saltoy, j + saltoz);
		}
	}
	

	//Plano lateral esquerdo e lateral direito:
	for (i = refy; i < (alt / 2); i += saltoy)
	{
		for (j = refx; j < (larg / 2); j += saltox)
		{
			//Lateral esquerdo:
			printf("%f %f %f\n", j, i, refz);
			printf("%f %f %f\n", j, i + saltoy, refz);
			printf("%f %f %f\n", j + saltox, i, refz);

			printf("%f %f %f\n", j, i + saltoy, refz);
			printf("%f %f %f\n", j + saltox, i + saltoy, refz);
			printf("%f %f %f\n", j + saltox, i, refz);


			//Lateral direito:
			printf("%f %f %f\n", j, i, -refz);
			printf("%f %f %f\n", j, i + saltoy, -refz);
			printf("%f %f %f\n", j + saltox, i, -refz);

			printf("%f %f %f\n", j, i + saltoy, -refz);
			printf("%f %f %f\n", j + saltox, i + saltoy, -refz);
			printf("%f %f %f\n", j + saltox, i, -refz);
		}
	}

}

int main(int argc, char **argv) {

	if (argc > 1){


	}

	paralelipipedo(4, 2, 2, 2, 2, 2, "teste");
	return 1;
}