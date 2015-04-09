#include "rotacao.h"

Rotacao::Rotacao(){
	angulo = 0.0;
	eixoX = 0.0;
	eixoY = 0.0;
	eixoZ = 0.0;

}

Rotacao(float a, float b, float c, float d){
	angulo = a;
	eixoX = b;
	eixoY = c;
	eixoZ = d;
}