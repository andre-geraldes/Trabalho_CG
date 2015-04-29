#include "rotacao.h"

Rotacao::Rotacao(){
	time = 0.0;
	eixoX = 0.0;
	eixoY = 0.0;
	eixoZ = 0.0;

}

Rotacao::Rotacao(float b, float c, float d, float t){
	eixoX = b;
	eixoY = c;
	eixoZ = d;
	time = t;
}