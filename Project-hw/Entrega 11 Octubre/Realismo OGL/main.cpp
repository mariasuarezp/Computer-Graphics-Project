//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm/glm.h"
#include "Objeto3D.h"
#include "FreeImage/FreeImage.h"
#include "Textura.h"
#define dist 0.2
#define dst 0.5

//-----------------------------------------------------------------------------

class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader* shader;
    cwc::glShader* shader1; //Para la textura
    GLuint ProgramObject;
    clock_t time0, time1;
    float timer010;  // timer counting 0->1->0
    bool bUp;        // flag if counting up or down.
    GLuint texid;
    Objeto3D* Modelo3D[6];
    GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
    Textura* objetoTextura[2];
    bool camera;
    float cx, cy, cz; //Distancias
    bool upC, downC, leftC, rightC, forwardC, backwardC; // Movimiento camara
    float px, py, pz;
    bool upP, downP, leftP, rightP, forwardP, backwardP; // Movimiento objeto


public:
    myWindow() {}

    void initialize_textures(void)
    {
        int w, h;
        GLubyte* data = 0;
        //data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
        //std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./Mallas/bank_tahta.jpg", 0),
            "./Mallas/bank_tahta.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    //Movimiento de la camara
    void posCamera() {
        if (upC)
            cy -= dist;
        else if (downC)
            cy += dist;
        else if (leftC)
            cx += dist;
        else if (rightC)
            cx -= dist;
        else if (forwardC)
            cz += dist;
        else if (backwardC)
            cz -= dist;   
    }

    //Movimiento del objeto 
    void posObject() {
        if (upP)
            cy -= dist;
        else if (downP)
            cy += dist;
        else if (leftP)
            cx += dist;
        else if (rightP)
            cx -= dist;
        else if (forwardP)
            cz += dist;
        else if (backwardP)
            cz -= dist;
    }

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
      posCamera();
      glTranslatef(cx, cy, cz); // Distancias
      if (shader) shader->begin();
         //glRotatef(timer010*360, 0.5, 1.0f, 0.1f);
         glTranslatef(0, 0, -15);
         // Piso
         glPushMatrix();
            glTranslatef(0, -10, 0);
             glScalef(10.0, 0.01, 20.0);
             glutSolidCube(5);
         glPopMatrix();

         //Dibujar Casas 1
         glPushMatrix();
         glScalef(4, 4, 4);
         //glRotatef(90, 0, 1, 0);
         //Frente
         Modelo3D[0]->DibujarMalla(-3, -1.5, -7);
         Modelo3D[0]->DibujarMalla(-4, -1.5, -7);
         Modelo3D[0]->DibujarMalla(-5, -1.5, -7);
         Modelo3D[0]->DibujarMalla(0, -1.5, 6);
         Modelo3D[0]->DibujarMalla(0.8, -1.5, 6);

         glPopMatrix();

         //Dibujar Casas 2
         glPushMatrix();
            glScalef(4, 4, 4);
            glRotatef(90, 0, 1, 0);
            //Izquierda
            
            Modelo3D[0]->DibujarMalla(-4, -1.5, -3);
            Modelo3D[0]->DibujarMalla(-3, -1.5, -3);
            Modelo3D[0]->DibujarMalla(-2, -1.5, -3);
            Modelo3D[0]->DibujarMalla(-1, -1.5, -3);
            Modelo3D[0]->DibujarMalla(0, -1.5, -3);
            Modelo3D[0]->DibujarMalla(1, -1.5, -3);
            Modelo3D[0]->DibujarMalla(2, -1.5, -3);
            Modelo3D[0]->DibujarMalla(3, -1.5, -3);
         glPopMatrix();

         //Dibujar Casas 3
         glPushMatrix();
         glScalef(4, 4, 4);
         glRotatef(-90, 0, 1, 0);
         //Izquierda

         Modelo3D[0]->DibujarMalla(-4, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(-3, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(-2, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(-1, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(0, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(1, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(2, -1.5, 4.3);
         Modelo3D[0]->DibujarMalla(3, -1.5, 4.3);
         glPopMatrix();

         //Dibujar Casas 4
         glPushMatrix();
         glScalef(4, 4, 4);
         glRotatef(-90, 0, 1, 0);
         //Derecha
         Modelo3D[0]->DibujarMalla(-3, -1.5, 0);
         Modelo3D[0]->DibujarMalla(-2, -1.5, 0);
         Modelo3D[0]->DibujarMalla(-1, -1.5, 0);
         Modelo3D[0]->DibujarMalla(0, -1.5, 0);
         Modelo3D[0]->DibujarMalla(1, -1.5, 0);
         Modelo3D[0]->DibujarMalla(2, -1.5, -0);
         Modelo3D[0]->DibujarMalla(3, -1.5, 0);
         Modelo3D[0]->DibujarMalla(4, -1.5, -0);
         Modelo3D[0]->DibujarMalla(5, -1.5, 0);
         glPopMatrix();

         //Dibujar Casas 5
         glPushMatrix();
         glScalef(4, 4, 4);
         glRotatef(90, 0, 1, 0);
         //Derecha
         Modelo3D[0]->DibujarMalla(-5, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(-4, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(-3, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(-2, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(-1, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(0, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(1, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(2, -1.5, 1.5);
         Modelo3D[0]->DibujarMalla(3, -1.5, 1.5);
         glPopMatrix();

         //Objeto Artificial

         //Dibujar Postes (Izquierda)
         glPushMatrix();
            Modelo3D[1]->DibujarMalla(-9, -9, -5);
            Modelo3D[1]->DibujarMalla(-9, -9, 10);
            Modelo3D[1]->DibujarMalla(-9, -9, 30);
         glPopMatrix();

         //Dibujar Postes (Derecha)
         glPushMatrix();
            Modelo3D[1]->DibujarMalla(-3, -9, -10);
            Modelo3D[1]->DibujarMalla(-3, -9, 5);
            Modelo3D[1]->DibujarMalla(-3, -9, 20);
         glPopMatrix();

         //Dibujar mansion (Adicional)
         glPushMatrix();
         glScalef(5, 5, 5);
         //glRotatef(90, 0, 1, 0);
         //Izquierda
         Modelo3D[3]->DibujarMalla(-3, -1, 5);
         glPopMatrix();

         //Dibujar mansion  (Adicional)
         glPushMatrix();
             glScalef(5, 5, 5);
             glRotatef(0, 0, 1, 0);
             //Derecha
             Modelo3D[3]->DibujarMalla(-1, -1, -6);
         glPopMatrix();

         //Dibujar hombre muerto (Adicional)
         glPushMatrix();
         //glScalef(5, 5, 5);
         glRotatef(90, 0, 1, 0);
         Modelo3D[4]->DibujarMalla(-8, -9.8, -5);
         glPopMatrix();

         //Dibujar arboles (objeto natural)
         glPushMatrix();
         //glScalef(5, 5, 5);
         //glRotatef(90, 0, 1, 0);
         Modelo3D[2]->DibujarMalla(-10, -9, 19);
         Modelo3D[2]->DibujarMalla(-10, -9, 24);
         Modelo3D[2]->DibujarMalla(-10, -9, 28);
         glPopMatrix();

         //Dibujar persona (Objeto interactivo)
         glPushMatrix();
         posObject();
         glTranslatef(px, py, pz); // Distancias
         //glScalef(5, 5, 5);
         //glRotatef(0, 0, 1, 0);
         Modelo3D[5]->DibujarMalla(-5, -9, 3);
         glPopMatrix();

     
      if (shader) shader->end();

      //*** Para Textura: llamado al shader para objetos texturizados
      if (shader1) shader1->begin();

      glPushMatrix();
      glTranslatef(1.5f, 0.0f, 0.0f);
      glBindTexture(GL_TEXTURE_2D, texid);

      //Dibujar Baston (Objeto creado en blender por la tribu y objeto con textura)
      //objetoTextura[0]->DibujarMalla(-5, 0, 3);
      glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        objetoTextura[0]->DibujarMalla(-5, -8, -9.9);
      glPopMatrix();
      glPopMatrix();

      if (shader1) shader1->end();

      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
        cx = cy = cz = 0;
        px = py = pz = 0;
        upC = downC = leftC = rightC = forwardC = backwardC = false;
        upP = downP = leftP = rightP = forwardP = backwardP = false;
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

        //*** Para Textura: abre los shaders para texturas
        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
        if (shader1 == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader1->GetProgramObject();
        }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      //Objeto Artificial Adicional
      Modelo3D[0] = new Objeto3D();
      Modelo3D[0]->AbrirMalla("./Mallas/JÜDENSTRASSE_31.obj");

      //Objeto Artificial 
      Modelo3D[1] = new Objeto3D();
      Modelo3D[1]->AbrirMalla("./Mallas/elPoste.obj");

      //Objeto Natural
      Modelo3D[2] = new Objeto3D();
      Modelo3D[2]->AbrirMalla("./Mallas/Gledista_Triacanthos.obj");

      // Objeto Artificial Adicional
      Modelo3D[3] = new Objeto3D();
      Modelo3D[3]->AbrirMalla("./Mallas/Graceview Mansion.obj");

      //Objeto Adicional
      Modelo3D[4] = new Objeto3D();
      Modelo3D[4]->AbrirMalla("./Mallas/Corpse.obj");

      //Objeto interactivo
      Modelo3D[5] = new Objeto3D();
      Modelo3D[5]->AbrirMalla("./Mallas/BaseMesh_Man_Simple.obj");

      //Objeto con textura y objeto creado por la tribu en Blender
      objetoTextura[0] = new Textura();
      objetoTextura[0]->AbrirMalla("./Mallas/baston1.obj");

      //*** Para Textura: abrir archivo de textura
      initialize_textures();
      DemoLight();
    }

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 

        switch (cAscii) {
        case 27:
            this->Close();
            break;
        case 'w':
            this->upC = true;
            break;
        case 's':
            this->downC = true;
            break;
        case 'a':
            this->leftC = true;
            break;
        case 'd':
            this->rightC = true;
            break;
        case 'e':
            this->forwardC = true;
            break;
        case 'q':
            this->backwardC = true;
            break;

        case 'i':
            this->upP = true;
            break;
        case 'k':
            this->downP = true;
            break;
        case 'j':
            this->leftP = true;
            break;
        case 'l':
            this->rightP = true;
            break;
        case 'o':
            this->forwardP = true;
            break;
        case 'u':
            this->backwardP = true;
            break;

        };
	}

	virtual void OnKeyUp(int nKey, char cAscii)
	{
        switch (cAscii) {
        case 27:
            this->Close();
            break;
        case 'w':
            this->upC = false;
            break;
        case 's':
            this->downC = false;
            break;
        case 'a':
            this->leftC = false;
            break;
        case 'd':
            this->rightC = false;
            break;
        case 'e':
            this->forwardC = false;
            break;
        case 'q':
            this->backwardC = false;
            break;

        case 'i':
            this->upP = false;
            break;
        case 'k':
            this->downP = false;
            break;
        case 'j':
            this->leftP = false;
            break;
        case 'l':
            this->rightP = false;
            break;
        case 'o':
            this->forwardP = false;
            break;
        case 'u':
            this->backwardP = false;
            break;
        };
    }
     

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     /*GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0};
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     */
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     /*GLfloat light_Ka[] = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};*/

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     /*glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);*/
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

