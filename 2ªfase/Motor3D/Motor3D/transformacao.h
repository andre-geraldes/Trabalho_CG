#pragma once

#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"

class Transformacao{
	Translacao trans;
	Rotacao rot;
	Escala esc;

	public:
		Transformacao();
		Transformacao(Translacao, Rotacao, Escala);
		Translacao getTranslacao() { return trans; }
		Rotacao getRotacao() { return rot; }
		Escala getEscala() { return esc; }
		void setTranslacao(Translacao t){ trans = t; }
		void setRotacao(Rotacao r){ rot = r; }
		void setEscala(Escala e){ esc = e; }
		virtual ~Transformacao() {};

};