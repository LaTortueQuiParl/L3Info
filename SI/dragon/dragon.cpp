#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>

class Point
{
    public:
        double x, y, z;
};

void affichage();
void axes();
void clavier(unsigned char touche, int x, int y);
void Init();
void reshape(int x, int y);
void mouse(int button, int state, int x, int y);
void mousemotion(int x,int y);
void loadJpegImage(char *fichier, unsigned char *im, const int l, const int h);

int anglex=30,angley=20,x,y,xold,yold;
char presse;
const int largim = 989;
const int hautim = 1024;
unsigned char gris[largim * hautim * 3];

const float h = 0.5; //hauteur cylindre
const int n = 60;
const float r = 0.5;
Point pCylindre[2*n];

void creaCube();
void creaCylindre();
void creaSphere(int P, int M, int r);

void textFaceCylindre();

int main(int argc, char** argv) {

    loadJpegImage("./textures/gris.jpg", gris, largim, hautim);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(600,400);
    glutInitWindowSize(500,500);
    glutCreateWindow("Dragon");

    /* Initialisation d'OpenGL */
    Init();

    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);

    // Pour les textures
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largim, hautim, 0, GL_RGB, GL_UNSIGNED_BYTE, gris);
    glEnable(GL_TEXTURE_2D);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void affichage() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    creaCylindre();
    textFaceCylindre();

    axes();

    glFlush();
    glutSwapBuffers();
}

void creaCylindre(){
    Point pCylindre[2*n];
    for (int i = 0; i < n; i++){
        double theta = (double) (2.0*i*M_PI/n);
        pCylindre[i] = {r * cos(theta), r * sin(theta), h/2.0};
        pCylindre[i+n] = {r * cos(theta), r * sin(theta), -h/2.0};
    }
}

void textFaceCylindre(){
  for (int i = 0; i < n; i++){
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(pCylindre[i].x, pCylindre[i].y, pCylindre[i].z);
    glTexCoord2f(0.0,1.0);   glVertex3f(pCylindre[(i+1)%n].x, pCylindre[(i+1)%n].y, pCylindre[(i+1)%n].z);
    glTexCoord2f(1.0,1.0);   glVertex3f(pCylindre[(i+1)%n+n].x, pCylindre[(i+1)%n+n].y, pCylindre[(i+1)%n+n].z);
    glTexCoord2f(1.0,0.0);   glVertex3f(pCylindre[i+n].x, pCylindre[i+n].y, pCylindre[i+n].z);
    glEnd();
  }
}

void creaCube(){
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

}

void creaSphere(int P, int M, int r){
    Point pSphere[M * P];
    int k = 0;
    for (int j = 0; j < P; j++){
        double phi = (double) (-(M_PI/2.0) + j *(M_PI/(double) (P-1)));
        for (int i = 0; i < M; i++){
            double theta = (double) (i * 2.0*M_PI/M);
            pSphere[k] = {r*cos(theta)*cos(phi), r*sin(theta)*cos(phi), r*sin(phi)};
            k++;
        }
    }
}

void Init() {
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

      /* Initialisation de l'etat d'OpenGL */
    glShadeModel(GL_FLAT);

    /* Mise en place de la projection perspective */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,1,1.0,5.0);
    glMatrixMode(GL_MODELVIEW);
}

void axes(){
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();
}

void clavier(unsigned char touche,int x,int y) {
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a':
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_FRONT,GL_LINE);
      glutPostRedisplay();
    break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y) {
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y) {
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y) {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }

void loadJpegImage(char *fichier, unsigned char *im, const int l, const int h) {
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
        //glVertex2f(0,1);
        //glTexCoord2f(0,1);
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=l)||(cinfo.image_height!=h)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille %dx%d\n", l, h);
    exit(1);
  }

  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=im;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=im+3*l*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}
