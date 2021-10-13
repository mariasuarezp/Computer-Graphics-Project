#include "Textura.h"


Textura::Textura() {
    objmodel_ptr1 = nullptr;
}

//*** Para Textura: abrir malla de objeto a texturizar

void Textura::AbrirMalla(char* malla) {

    if (!objmodel_ptr1)
    {
        objmodel_ptr1 = glmReadOBJ(malla);
        if (!objmodel_ptr1)
            exit(0);

        glmUnitize(objmodel_ptr1);
        glmFacetNormals(objmodel_ptr1);
        glmVertexNormals(objmodel_ptr1, 90.0);
    }
}

void Textura::DibujarMalla(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glmDraw(objmodel_ptr1, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    glPopMatrix();
}

