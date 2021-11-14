#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>
#include "Cylindre.h"
#include "Point.h"

//Initialisation Glut
void InitGL(int argc, char** argv);
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void mouse(int button, int state, int x, int y);
void mousemotion(int x,int y);
void fleches(int key, int x, int y);

void axes();

/*Utilisation Courbe Bézier*/
Point Bezier(Point A, Point B, Point C, Point D, double t);
void drawBezier(Point* tab, int nombreIteration, Point pts[]);
void drawLine(Point p1, Point p2);

/*TestDessin*/
void Griffe();
void Pied();
void Cuisse();
void Mollet();
void Queue(int longueur, int nbSegments, int nbPointCercle, double rayon);
void MainDrag();
void Doigt();
void Corps();

int anglex=0,angley=0,x,y,xold,yold;
char presse;
float zoom = 10;

int main(int argc, char** argv) {

    //loadJpegImage("./textures/gris.jpeg", gris, largim, hautim);

    /* Initialisation d'OpenGL */
    InitGL(argc, argv);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void InitGL(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(680,400);
    glutCreateWindow("Dragon Yann MOURELON & Daniel PINSON");
    glClearColor(1.0,1.0,1.0,0.0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(fleches);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
}

void affichage() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(zoom,-zoom, zoom, -zoom, zoom/2, -zoom/2);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    //Jambe();

    //Queue(10, 5, 10,2);

    //MainDrag();

    Corps();
    //Doigt();

    axes();

    glutSwapBuffers();
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
    case 'z':
        zoom-=.1f;
        glutPostRedisplay();
    break;
    case 'Z':
        zoom+=.1f;
        glutPostRedisplay();
    break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void fleches(int key, int x, int y){
    switch(key){
        case GLUT_KEY_RIGHT:
            anglex=anglex+5;
            glutPostRedisplay();
        break;
        case GLUT_KEY_LEFT:
            anglex=anglex-5;
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            angley=angley+5;
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            angley=angley-5;
            glutPostRedisplay();
        break;
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

  //Point(0,1,0), Point(1,1,0),Point(0,0,0),Point(1,0,0)
Point Bezier(Point A, Point B, Point C, Point D, double t){
    Point P;
    P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 -t), 2) * B.x + 3 * (1-t) * pow(t, 2)* C.x + pow (t, 3)* D.x;
    P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 -t), 2) * B.y + 3 * (1-t) * pow(t, 2)* C.y + pow (t, 3)* D.y;
    P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 -t), 2) * B.z + 3 * (1-t) * pow(t, 2)* C.z + pow (t, 3)* D.z;
    return P;
}

void drawBezier(Point* tab, int nombreIteration, Point pts[]){
    glColor3f(0.0,0.0,0.0);
    Point POld = tab[0];
    int i=0;
    for(double t = 0.0;t < 1.0; t +=(float)(1/(float)(nombreIteration))) {
        Point P = Bezier(tab[0], tab[1], tab[2], tab[3],  t);
        drawLine(POld, P);
        POld = P;
        pts[i] = POld;
        i++;
    }
    Point P = Bezier(tab[0], tab[1], tab[2], tab[3],  1.0);
    drawLine(POld, P);
}

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
    glFlush();
}

void Griffe(){
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(.5,.5,.5);
        glVertex3d(2,0,0);
        glVertex3d(0,0,1);
        glVertex3d(0,0,-1);
        glVertex3d(0,1,0);
        glVertex3d(0,0,1);
    glEnd();
}

void Pied(){
    Point p[16] = {
        Point(0,0,0.25),
        Point(0,0,-0.25),
        Point(1,0,-1),
        Point(3.5,0,-(0.5+sqrt(0.75))),
        Point(4,0,-0.5),
        Point(4,0,0.5),
        Point(3.5,0,(0.5+sqrt(0.75))),
        Point(1,0,1),
        Point(0,1,0.25),
        Point(0,1,-0.25),
        Point(1,1,-1),
        Point(3.5,1,-(0.5+sqrt(0.75))),
        Point(4,1,-0.5),
        Point(4,1,0.5),
        Point(3.5,1,(0.5+sqrt(0.75))),
        Point(1,1,1),
    };
    glColor3d(1.,0.,1.);
    glBegin(GL_POLYGON);
        for(int i=0;i<8;i++){
            glVertex3d(p[i].x,p[i].y,p[i].z);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=8;i<16;i++){
            glVertex3d(p[i].x,p[i].y,p[i].z);
        }
    glEnd();
    for(int i=0;i<8;i++){
        glBegin(GL_QUADS);
            glVertex3d(p[i].x,p[i].y,p[i].z);
            glVertex3d(p[(i+1)%8].x,p[(i+1)%8].y,p[(i+1)%8].z);
            glVertex3d(p[(i+1)%8+8].x,p[(i+1)%8+8].y,p[(i+1)%8+8].z);
            glVertex3d(p[i+8].x,p[i+8].y,p[i+8].z);
        glEnd();
    }

    /*Ajout Griffes*/
    //Griffe Gauche
    glPushMatrix();
        glTranslated(3.75,0,((0.5+sqrt(0.75))+0.5)/2);
        glRotated(-30,0,1,0);
        glScaled(1,1,0.5);
        Griffe();
    glPopMatrix();
    //Griffe Droite
    glPushMatrix();
        glTranslated(3.75,0,-((0.5+sqrt(0.75))+0.5)/2);
        glRotated(30,0,1,0);
        glScaled(1,1,0.5);
        Griffe();
    glPopMatrix();
    //Griffe centre
    glPushMatrix();
        glTranslated(4,0,0);
        glScaled(1,1,0.5);
        Griffe();
    glPopMatrix();
}

void Cuisse(){
    glPushMatrix();//Cuisse
        glTranslated(0,-3,0);
        glRotated(-90,1,0,0);
        glutSolidCylinder(1.25,3,20,20);
    glPopMatrix();
    glPushMatrix();//Genou
        glTranslated(0,-3,0);
        glutSolidSphere(1.25,20,20);
    glPopMatrix();
}

void Mollet(){
    glColor3d(0.84,0.51,0.26);
    glPushMatrix();//mollet
        glTranslated(0,-3,0);
        glRotated(-90,1,0,0);
        glutSolidCylinder(1,3,20,20);
    glPopMatrix();
    glPushMatrix();//Cheville
        glTranslated(0,-3,0);
        glutSolidSphere(0.75,20,20);
    glPopMatrix();
}

void Queue(int longueur, int nbSegments, int nbPointCercle, double rayon){
    Point depart = Point(0,0,0);
    Point arrive = Point(longueur,0,0);
    int circonference = nbPointCercle;
    int nbPoint = nbSegments;
    double r = rayon;
    Point pointsCirconferences[nbPoint][circonference];//nbPoint = nbBezier && circonference = nombre point sur 1 cercle

    /*Initialisation Bezier*/
    Point bez[4] = {depart,Point(longueur/3,5,0),Point(2*longueur/3,-5,0),arrive};
    Point p[nbPoint+1];
    drawBezier(bez, nbPoint, p);
    p[nbPoint] = arrive;

    /*Creation des points circonference*/
    for(int j=0 ; j<nbPoint ; j++){
        for (int i = 0; i < circonference; i++){
            double theta = (double) (2.0*i*M_PI/circonference);
            pointsCirconferences[j][i] = {0, ((r-(r*j/nbPoint)) * sin(theta)), ((r-(r*j/nbPoint)) * cos(theta))};
            if(j>0){
                double u[2] = {0,1};
                double v[2] = {-(p[j].y-p[j-1].y) , p[j].x-p[j-1].x};
                double ps = u[0]*v[0] + u[1]*v[1];
                double nu = sqrt(pow(u[0],2)+pow(u[1],2));
                double nv = sqrt(pow(v[0],2)+pow(v[1],2));
                double alpha = acos(ps/(nu*nv));
                if(p[j].y<p[j-1].y)
                    alpha = -alpha;
                pointsCirconferences[j][i] = Point(pointsCirconferences[j][i].x*cos(alpha)-pointsCirconferences[j][i].y*sin(alpha),
                                                   pointsCirconferences[j][i].x*sin(alpha)+pointsCirconferences[j][i].y*cos(alpha),
                                                   pointsCirconferences[j][i].z);
            }
            pointsCirconferences[j][i] = pointsCirconferences[j][i] + p[j];
        }
    }

    for(int j = 0 ; j<nbPoint ; j++){
        glBegin(GL_LINE_LOOP);
            for(int i=0 ; i<circonference ; i++){
                glVertex3d(pointsCirconferences[j][i].x,pointsCirconferences[j][i].y,pointsCirconferences[j][i].z);
            }
        glEnd();
    }

    /*for(int j=0 ; j<nbPoint-1 ;  j++){
        glBegin(GL_QUADS);
            for (int i = 0; i < circonference; i++){
                glColor3d(0.0,0.0,1.0);
                glVertex3d(pointsCirconferences[j][i].x, pointsCirconferences[j][i].y, pointsCirconferences[j][i].z);
                glVertex3d(pointsCirconferences[j][(i+1)%circonference].x, pointsCirconferences[j][(i+1)%circonference].y, pointsCirconferences[j][(i+1)%circonference].z);
                glVertex3d(pointsCirconferences[j+1][(i+1)%circonference].x, pointsCirconferences[j+1][(i+1)%circonference].y, pointsCirconferences[j+1][(i+1)%circonference].z);
                glVertex3d(pointsCirconferences[j+1][i].x, pointsCirconferences[j+1][i].y, pointsCirconferences[j][i].z);
            }
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(p[nbPoint].x, p[nbPoint].y, p[nbPoint].z);
        for(int i=0 ; i< circonference ; i++){
            glVertex3d(pointsCirconferences[nbPoint-1][i].x, pointsCirconferences[nbPoint-1][i].y, pointsCirconferences[nbPoint-1][i].z);
        }
        glVertex3d(pointsCirconferences[nbPoint-1][0].x, pointsCirconferences[nbPoint-1][0].y, pointsCirconferences[nbPoint-1][0].z);
    glEnd();*/
}

void MainDrag(){
    int n=6;
    Point p[12] = {
        Point(0,0,1),
        Point(0,0,-1),
        Point(2,0,-1.5),
        Point(3.5,0,-1.5),
        Point(3.5,0,1.5),
        Point(2,0,1.5),
        Point(0,1,1),
        Point(0,1,-1),
        Point(2,1,-1.5),
        Point(3.5,1,-1.5),
        Point(3.5,1,1.5),
        Point(2,1,1.5),
    };

    glColor3d(0.84,0.51,0.26);
    for(int j = 1 ; j<3 ; j++){
        glBegin(GL_POLYGON);
            for(int i=(j-1)*n ; i<n*j ;i++){
                glVertex3d(p[i].x, p[i].y, p[i].z);
            }
        glEnd();
    }
    for(int i=0;i<n;i++){
        glBegin(GL_QUADS);
            glVertex3d(p[i].x,p[i].y,p[i].z);
            glVertex3d(p[(i+1)%n].x,p[(i+1)%n].y,p[(i+1)%n].z);
            glVertex3d(p[(i+1)%n+n].x,p[(i+1)%n+n].y,p[(i+1)%n+n].z);
            glVertex3d(p[i+n].x,p[i+n].y,p[i+n].z);
        glEnd();
    }

    glPushMatrix();
        glTranslated(3.5,0.5,0);
        glutSolidSphere(0.5,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3.5,0.5,-1);
        glutSolidSphere(0.5,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3.5,0.5,1);
        glutSolidSphere(0.5,20,20);
    glPopMatrix();

    glPushMatrix();
        glTranslated(3.5,0.5,0);
        glRotated(90,0,1,0);
        Doigt();
    glPopMatrix();
    glPushMatrix();
        glTranslated(3.5,0.5,1);
        glRotated(90,0,1,0);
        Doigt();
    glPopMatrix();
    glPushMatrix();
        glTranslated(3.5,0.5,-1);
        glRotated(90,0,1,0);
        Doigt();
    glPopMatrix();
}

void Doigt(){
    glPushMatrix();
        glutSolidCylinder(0.5,2,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,2);
        glutSolidSphere(0.5,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,2);
        glRotated(90,0,-1,0);
        glScaled(1,0.4,0.4);
        Griffe();
    glPopMatrix();
}

void Corps(){
    Point depart = Point(-5,0,0);
    Point arrive = Point(10,7,0);
    double rayon = 1.5;
    int nbPoint_Cercle = 20;
    int nbCercles = 50;
    Point points_Cercle[nbCercles+1][nbPoint_Cercle];

    /*Initialisation Bezier*/
    Point bez[4] = {depart,Point(15,0,0),Point(0,7,0),arrive};
    Point p[nbCercles+1];
    drawBezier(bez, nbCercles, p);
    p[nbCercles] = arrive;

    for(int j=0 ; j<nbCercles+1 ; j++){
        for (int i = 0; i < nbPoint_Cercle; i++){
            double theta = (double) (2.0*i*M_PI/nbPoint_Cercle);
            points_Cercle[j][i] = {0, (rayon * sin(theta)), (rayon * cos(theta))};
            if(j>0){
                double u[2] = {0,1};
                double v[2] = {-(p[j].y-p[j-1].y) , p[j].x-p[j-1].x};
                double ps = u[0]*v[0] + u[1]*v[1];
                double nu = sqrt(pow(u[0],2)+pow(u[1],2));
                double nv = sqrt(pow(v[0],2)+pow(v[1],2));
                double alpha = acos(ps/(nu*nv));
                if(p[j].y<p[j-1].y)
                    alpha = -alpha;
                points_Cercle[j][i] = Point(points_Cercle[j][i].x*cos(alpha)-points_Cercle[j][i].y*sin(alpha),
                                                   points_Cercle[j][i].x*sin(alpha)+points_Cercle[j][i].y*cos(alpha),
                                                   points_Cercle[j][i].z);
            }
            points_Cercle[j][i] = points_Cercle[j][i] + p[j];
            if(j<(nbCercles/2))
                rayon+=0.005;
            else
                rayon-=0.005;
        }
    }
    /*for(int j=0 ; j<nbCercles+1 ; j++){
        glBegin(GL_POLYGON);
            for(int i=0 ; i<nbPoint_Cercle ; i++){
                glVertex3d(points_Cercle[j][i].x, points_Cercle[j][i].y, points_Cercle[j][i].z);
            }
        glEnd();
    }*/

    for(int j=0 ; j<nbCercles ;  j++){
        glBegin(GL_QUADS);
            for (int i = 0; i < nbPoint_Cercle; i++){
                glColor3d(1.0,0.0,0.0);
                glVertex3d(points_Cercle[j][i].x, points_Cercle[j][i].y, points_Cercle[j][i].z);
                glVertex3d(points_Cercle[j][(i+1)%nbPoint_Cercle].x, points_Cercle[j][(i+1)%nbPoint_Cercle].y, points_Cercle[j][(i+1)%nbPoint_Cercle].z);
                glVertex3d(points_Cercle[j+1][(i+1)%nbPoint_Cercle].x, points_Cercle[j+1][(i+1)%nbPoint_Cercle].y, points_Cercle[j+1][(i+1)%nbPoint_Cercle].z);
                glVertex3d(points_Cercle[j+1][i].x, points_Cercle[j+1][i].y, points_Cercle[j][i].z);
            }
        glEnd();
    }

    glPushMatrix();
    glTranslated(0,-1,0);
        glPushMatrix();
            glScaled(0.7,0.7,0.7);
            Cuisse();
        glPopMatrix();
        glPushMatrix();
        glTranslated(0,-2,0);
        glRotated(-45,0,0,1);
            glPushMatrix();
                glScaled(0.7,0.7,0.7);
                Mollet();
            glPopMatrix();
            glPushMatrix();
                glTranslated(-1,-3,0);
                glScaled(0.7,0.7,0.7);
                Pied();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}
