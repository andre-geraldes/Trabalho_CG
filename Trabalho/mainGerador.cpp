#include <stdlib.h>
#include <iostream>
using namespace std;
#include <string>
#include <GL/glut.h>
#include <math.h>

void plano(float comp, float larg, int cmdh, int cmdv, string filename)
{
	float saltoz = comp / cmdv;
	float saltox = larg / cmdh;
	float refx = -(comp / 2);
	float refz = -(larg / 2);
	float i,j;
	
	for (i = refz; i < (larg/2); i += saltox)
	{
		for (j = refx; j < (comp/2); j += saltoz)
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

int main(int argc, char **argv) {

	if (argc > 1){


	}

	plano(4, 2, 4, 2, "ola");
	return 1;
}