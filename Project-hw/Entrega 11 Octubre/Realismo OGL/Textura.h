#pragma once
#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "./glm/glm.h"


class Textura
{
	GLMmodel* objmodel_ptr1;
	public:
		Textura();
		void AbrirMalla(char* malla);
		void DibujarMalla(float x, float y, float z);
	};


