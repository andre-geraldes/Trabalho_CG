#ifndef _MAIN
#define _MAIN

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2.h"
#include "escala.h"
#include "transformacao.h"
#include "primitiva.h"
#include "ponto.h"
#include "rotacao.h"
#include "translacao.h"

#pragma comment(lib,"glew32.lib") 
#pragma comment(lib,"devil.lib")

using namespace tinyxml2;
using namespace std;


// Vectores com os pontos lidos do ficheiro:
vector<Ponto> pontos;
vector<Ponto> normais;
vector<Ponto> texturas;

// Primitivas do sistema solar
vector<Primitiva> primitivas;

#define CONST 1.0f;

// Variaveis para utilização do teclado e rato:
float radius = 5.0f;
float camX = -30, camY = 30, camZ = 20;
float anguloX = 0.0f, anguloY = 0.0f, anguloZ = 0.0f;
float coordX = 0, coordY = 0, coordZ = 0;
int startX, startY, tracking = 0;
int alpha = 0, beta = 0, r = 5;

/* FRAMES PER SECOND */
int timebase = 0, frame = 0;

/* Luz */
string tipo;
float posX, posY, posZ;

#endif