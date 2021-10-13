#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "./glm/glm.h"

class Objeto3D
{
	GLMmodel* objmodel_ptr;
	public:
		Objeto3D();
		void AbrirMalla(char *malla);
		void DibujarMalla(float x, float y, float z);
};

