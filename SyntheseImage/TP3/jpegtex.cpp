#include <cstdio>
#include <cstdlib>
/****************************************************************/
/* works on mac using freeglut and xquartz                      */
/* you can install freeglut using homebrew                      */
/* xquartz can be downloaded at http://xquartz.macosforge.org   */
/****************************************************************/
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>

#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif

unsigned char image[256*256*3];
char presse;
int anglex=30,angley=20,x,y,xold,yold;

void affichage();
void clavier(unsigned char touche,int x,int y);
void souris(int boutton, int etat,int x,int y);
void sourismouv(int x,int y);
void redim(int l,int h);
void loadJpegImage(char *fichier);
void text();

const int largimg=256;
const int hautimg=256;

char texture2[largimg*2][hautimg*2][3];



class Point{
    public:
        double x;
        double y;
        double z;
};

const float h = 1.0; //hauteur cylindre
const int n = 6;
const float r = 0.1;
Point pCylindre[2*n];

void creaCylindre(){
    for (int i = 0; i < n; i++){
        float theta = (double) (2*i*M_PI/n);
        std::cout << theta;
        pCylindre[i] = {r * cos(theta), r * sin(theta), h/2.0};
        pCylindre[i+n] = {r * cos(theta), r * sin(theta), -h/2.0};
    }
}

void textFace(){
  for (int i = 0; i < n; i++){
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(pCylindre[i].x, pCylindre[i].y, pCylindre[i].z);
    glTexCoord2f(0.0,1.0);   glVertex3f(pCylindre[(i+1)%n].x, pCylindre[(i+1)%n].y, pCylindre[(i+1)%n].z);
    glTexCoord2f(1.0,1.0);   glVertex3f(pCylindre[(i+1)%n+n].x, pCylindre[(i+1)%n+n].y, pCylindre[(i+1)%n+n].z);
    glTexCoord2f(1.0,0.0);   glVertex3f(pCylindre[i+n].x, pCylindre[i+n].y, pCylindre[i+n].z);
    glEnd();
  }
}


int main(int argc,char **argv)

{
  /* Chargement de la texture */
  loadJpegImage("./calimero.jpg");
  //text();

  /* Creation de la fenetre OpenGL */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(200,200);
  glutCreateWindow("Texture JPEG");

  /* Initialisation de l'etat d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  /* Mise en place de la projection perspective */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1,1.0,5.0);
  glMatrixMode(GL_MODELVIEW);

  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,largimg,hautimg,0,
	       GL_RGB,GL_UNSIGNED_BYTE,image);
  glEnable(GL_TEXTURE_2D);

  /* Mise en place des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutMouseFunc(souris);
  glutMotionFunc(sourismouv);
  glutReshapeFunc(redim);

  /* Entr�e dans la boucle principale glut */
  glutMainLoop();
  return 0;
}



void affichage()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(0.0,0.0,2.5,0.0,0.0,0.0,0.0,1.0,0.0);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
    /*
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5, 0.5);
  glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
  glTexCoord2f(1.0,1.0);   glVertex3f( 0.5,-0.5, 0.5);
  glTexCoord2f(1.0,0.0);   glVertex3f( 0.5, 0.5, 0.5);
  glEnd();

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f( 0.5, 0.5, 0.5);
  glTexCoord2f(0.0,3.0);   glVertex3f( 0.5,-0.5, 0.5);
  glTexCoord2f(3.0,3.0);   glVertex3f( 0.5,-0.5,-0.5);
  glTexCoord2f(3.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f( -0.5, -0.5,-0.5);
  glTexCoord2f(0.0,1.0);   glVertex3f( -0.5,0.5,-0.5);
  glTexCoord2f(0.5,1.0);   glVertex3f(0.5,0.5,-0.5);
  glTexCoord2f(0.5,0.0);   glVertex3f(0.5, -0.5,-0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
  glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5,-0.5);
  glTexCoord2f(1.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
  glTexCoord2f(1.0,0.0);   glVertex3f(-0.5, 0.5, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
  glTexCoord2f(0.0,1.0);   glVertex3f(-0.5, 0.5, 0.5);
  glTexCoord2f(1.0,1.0);   glVertex3f( 0.5, 0.5, 0.5);
  glTexCoord2f(1.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);   glVertex3f(-0.5,-0.5,-0.5);
  glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
  glTexCoord2f(1.0,1.0);   glVertex3f( 0.5,-0.5, 0.5);
  glTexCoord2f(1.0,0.0);   glVertex3f( 0.5,-0.5,-0.5);
  glEnd();
    */

    textFace();
  glutSwapBuffers();

}



void clavier(unsigned char touche,int x,int y)
{
  switch(touche) {
  case 'l':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glutPostRedisplay();
    break;
  case 'n':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glutPostRedisplay();
  break;

  case 27: /* touche ESC */
    exit(0);
  default:
	  break;
  }
}

void souris(int bouton, int etat,int x,int y)
{
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
  {
    presse = 1;
    xold = x;
    yold=y;
  }
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
    presse=0;
}

void sourismouv(int x,int y)
  {
    if (presse)
    {
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay();
    }

    xold=x;
    yold=y;
  }

void redim(int l,int h)
{
  if (l<h)
    glViewport(0,(h-l)/2,l,l);
  else
    glViewport((l-h)/2,0,h,h);
}
void text(){
  for (int i = 0; i < 512; i++){
    for (int j = 0; j < 512; j++){
        if (i<256 && j<256 || i>=256 && j>=256){
            texture2[i][j][0] = image[(i%256)*256*3+(j%256)*3];
            texture2[i][j][1] = image[(i%256)*256*3+(j%256)*3 + 1];
            texture2[i][j][2] = image[(i%256)*256*3+(j%256)*3 + 2];
        } else {
            texture2[i][j][0] = 255;
            texture2[i][j][1] = 255;
            texture2[i][j][2] = 255;
        }
    }
  }
}

void loadJpegImage(char *fichier)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
  }
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=image+3*256*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}