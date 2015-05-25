#include "transformacao.h"

Transformacao::Transformacao(){

	trans = Translacao::Translacao();
	rot = Rotacao::Rotacao();
	esc = Escala::Escala();
}

Transformacao::Transformacao(Translacao t, Rotacao r, Escala e){
	trans = t;
	rot = r;
	esc = e;
}
