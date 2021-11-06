#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>

void affichage();
void axes();
void clavier(unsigned char touche, int x, int y);
void Init();
void reshape(int x, int y);
void mouse(int button, int state, int x, int y);
void mousemotion(int x,int y);

void Jambe();

int anglex=30,angley=20,x,y,xold,yold;
char presse;

int main(int argc, char** argv) {

    //loadJpegImage("./textures/gris.jpeg", gris, largim, hautim);

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
    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void Jambe(){
    glPushMatrix();
        //glTranslatef(0,2.05,0);
        //glRotatef(90,1,0,0);
        glColor3f(0.4,0.7,0);
        //glTranslatef(0,0,-1);
        glutSolidCylinder(0.5,2,30,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,-0.5);
        glColor3f(0.9,0.9,0.4);
        glutSolidSphere(0.5, 30,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-1.5,-0.5);
        glRotatef(90,1,0,0);
        glColor3f(0.4,0.7,0);
        glTranslatef(0,0,-1);
        glutSolidCylinder(0.5,2,30,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-2.75,-0.5);
        glRotated(90,1,0,0);
        glScalef(1.5,1.5,0.5);
        glColor3f(1,0,0);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-2.75,-5);
        glRotated(180,1,0,0);
        //glScalef(1.5,1.5,0.5);
        glTranslated(0,0,-4);
        glColor3f(0,1,0);
        glutSolidCone(0.25,8,30,20);
    glPopMatrix();

}

void affichage() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    glOrtho(10,-10, 10, -10, 5, -5);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    Jambe();

    axes();

    glFlush();
    glutSwapBuffers();
}

void Init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

     /* Initialisation de l'etat d'OpenGL */
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);



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
