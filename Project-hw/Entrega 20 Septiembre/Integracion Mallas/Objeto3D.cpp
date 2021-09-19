#include "Objeto3D.h"

Objeto3D::Objeto3D(){
    objmodel_ptr = NULL;
}

void Objeto3D::AbrirMalla(char *malla) {
    objmodel_ptr = nullptr;
    
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ(malla);
        if (!objmodel_ptr)
            exit(0);

        glmUnitize(objmodel_ptr);
        glmFacetNormals(objmodel_ptr);
        glmVertexNormals(objmodel_ptr, 90.0);
    }
}
void Objeto3D::DibujarMalla(float x, float y, float z) {
    glPushMatrix();
        glTranslatef(x,y,z);
        glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}