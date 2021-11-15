#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>
#include "Point.h"

#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif

//Initialisation Glut
void InitGL(int argc, char** argv);
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void mouse(int button, int state, int x, int y);
void mousemotion(int x,int y);
void fleches(int key, int x, int y);
void loadJpegImage(char *fichier, unsigned char *im, const int l, const int h);

void axes();
void Lumiere();// Active une lumiere dans la scène

/*Utilisation Courbe Bézier*/
Point Bezier(Point A, Point B, Point C, Point D, double t);//Génération d'un point de la courbe de Bézier
void drawBezier(Point* tab, int nombreIteration, Point pts[]);//Génération de tous les points de la couble de bézier (Appel de la méthode <Point Bezier>)
void drawLine(Point p1, Point p2);//dessine une ligne entre 2 points.

/*Dessin Dragon*/
void Griffe();
void Pied(double r, double g, double b);
void Cuisse(double r, double g, double b);
void Mollet(double r, double g, double b);
void Queue(int longueur, int nbSegments, int nbPointCercle, double rayon);
void Dragon(double r, double g, double b);
void Aile();
void Tete(double r, double g, double b);

/*Variables globales*/
int anglex=0,angley=0,x,y,xold,yold;
char presse;
float zoom = 10, lookx = 1.0, looky = 1.0;
const int hImg = 416;//hauteur de la texture
const int lImg = 416;//largeur de la texture
unsigned char img[hImg*lImg*3];//Texture

double g_Ico = 0.0; //Couleur verte de l'icosaedre
bool isNotGreen = true; //vérifie que g_Ico atteint sa valeur max ou min
double angle_Ico = 0; //Angle de rotation de l'icosaedre

double angle_Aile = 0;//Angle de rotation des ailes
int testaile = 1;//vérifie que angle_Aile atteint sa valeur max ou min


GLfloat source[] = {4,1.25,0,1};//Source de la lumière
GLfloat direction[] = {0,0,0,0};//Direction de la lumière
GLfloat diff[] = {1,1,1,1};//composante diffuse de la lumière
GLfloat ambient[] = {1,1,1,1};//composante ambiant de la lumière
GLfloat spec[] = {1,1,1,1};//composante speculaire de la lumière


int main(int argc, char** argv) {

    /* Initialisation d'OpenGL */
    InitGL(argc, argv);

    /*Initialisation lumière*/
    Lumiere();

    /*Chargement Texture*/
    loadJpegImage("./textures/ecaille.jpg", img, lImg, hImg);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,lImg,hImg,0,
                 GL_RGB,GL_UNSIGNED_BYTE,img);
    glEnable(GL_TEXTURE_2D);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void InitGL(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(680,400);
    glutCreateWindow("Dragon Yann MOURELON & Daniel PINSON");

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,1,1.0,5.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(fleches);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutReshapeFunc(reshape);
}

void Lumiere(){
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_POSITION, source);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}

void affichage() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(lookx, looky, 1.0,
              0.0, 0.0, 0.0,
              0.0, -1.0, 0.0);
    glOrtho(zoom,-zoom, zoom, -zoom, zoom/2, -zoom/2);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    /*Affichage de notre dragon*/
    glPushMatrix();
        glScaled(0.2,0.2,0.2);
        Dragon(0,0,1);
    glPopMatrix();

    /*Affichage de la boule de feu*/
    glPushMatrix();
        glTranslated(4,1.25,0);
        glScaled(0.5,0.5,0.5);
        glRotated(angle_Ico,1,1,0);
        glColor3d(1.0,g_Ico,0.0);
        glutSolidIcosahedron();
    glPopMatrix();

    /*Vérification de la couleur verte de l'icosaèdre*/
    if(isNotGreen)
        g_Ico+=0.01;
    else
        g_Ico-=0.01;
    if(g_Ico>=1)
        isNotGreen = false;
    if(g_Ico<=0)
        isNotGreen = true;

    angle_Ico++;

    //axes();

    glutSwapBuffers();
    glutPostRedisplay();
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
    case 'd': /*Opacitée active*/
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':/*Transparence active*/
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a': /*Changement de mode de polygône à filaire*/
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_FRONT,GL_LINE);
      glutPostRedisplay();
    break;
    case 'z': /*zoom en (0,0,0)*/
        if(zoom>=0){
            zoom-=.1f;
            glutPostRedisplay();
        }
    break;  /*dezoom*/
    case 'Z':
        zoom+=.1f;
        glutPostRedisplay();
    break;
    case 'm': /*Active l'animation de battement d'aile en restant appuyé*/
        if(testaile == 1){
            angle_Aile+=1;
            if(angle_Aile == 60)
                testaile = 0;
            glutPostRedisplay();
        }
        if(testaile == 0){
            angle_Aile-=1;
            if(angle_Aile == 0)
                testaile = 1;
            glutPostRedisplay();
        }
    break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void fleches(int key, int x, int y){
    switch(key){
        /*Modifie la position de la "caméra"*/
        case GLUT_KEY_RIGHT:
            lookx-=0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_LEFT:
            lookx+=0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            looky+=0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            looky-=0.1;
            glutPostRedisplay();
        break;
    }
}

void reshape(int l,int h) {
  if (l<h)
    glViewport(0,(h-l)/2,l,l);
  else
    glViewport((l-h)/2,0,h,h);
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
        //drawLine(POld, P);
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

void Pied(double r, double g, double b){
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
    glColor3d(r,g,b);
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

void Cuisse(double r, double g, double b){
    glColor3d(r,g,b);
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

void Mollet(double r, double g, double b){
    glColor3d(r,g,b);
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

void Queue(int longueur, int nbSegments, int nbPointCercle, double rayon, double r, double g, double b){
    Point depart = Point(0,0,0);
    Point arrive = Point(longueur,-5,-5);
    Point points_Cercle[nbSegments][nbPointCercle];//nbPoint = nbBezier && circonference = nombre point sur 1 cercle

    /*Initialisation Bezier*/
    Point bez[4] = {depart,Point(longueur/3,-5,0),Point(2*longueur/3,-5,0),arrive};
    Point p[nbSegments+1];
    drawBezier(bez, nbSegments, p);
    p[nbSegments] = arrive;

    /*Creation des points circonference*/
    for(int j=0 ; j<nbSegments ; j++){
        for (int i = 0; i < nbPointCercle; i++){
            double theta = (double) (2.0*i*M_PI/nbPointCercle);
            points_Cercle[j][i] = {0, ((rayon-(rayon*j/nbSegments)) * sin(theta)), ((rayon-(rayon*j/nbSegments)) * cos(theta))};
            /*Calcul des angles des points qui formes la queue*/
            if(j>0){
                double u[2] = {0,1};
                double v[2] = {-(p[j].y-p[j-1].y) , p[j].x-p[j-1].x};
                double ps = u[0]*v[0] + u[1]*v[1];
                double nu = sqrt(pow(u[0],2)+pow(u[1],2));
                double nv = sqrt(pow(v[0],2)+pow(v[1],2));
                double alpha = acos(ps/(nu*nv));
                if(p[j].y<p[j-1].y)
                    alpha = -alpha;
                //rotation des points par rapport à son origine d'angle alpha
                points_Cercle[j][i] = Point(points_Cercle[j][i].x*cos(alpha)-points_Cercle[j][i].y*sin(alpha),
                                                   points_Cercle[j][i].x*sin(alpha)+points_Cercle[j][i].y*cos(alpha),
                                                   points_Cercle[j][i].z);
            }
            points_Cercle[j][i] = points_Cercle[j][i] + p[j];
        }
    }

    /*Traçage la queue de dragon*/
    for(int j=0 ; j<nbSegments-1 ;  j++){
            for (int i = 0; i < nbPointCercle; i++){
                glBegin(GL_POLYGON);
                glColor3d(r,g,b);
                glVertex3d(points_Cercle[j][i].x, points_Cercle[j][i].y, points_Cercle[j][i].z);
                glVertex3d(points_Cercle[j][(i+1)%nbPointCercle].x, points_Cercle[j][(i+1)%nbPointCercle].y, points_Cercle[j][(i+1)%nbPointCercle].z);
                glVertex3d(points_Cercle[j+1][(i+1)%nbPointCercle].x, points_Cercle[j+1][(i+1)%nbPointCercle].y, points_Cercle[j+1][(i+1)%nbPointCercle].z);
                glVertex3d(points_Cercle[j+1][i].x, points_Cercle[j+1][i].y, points_Cercle[j][i].z);
                glEnd();
            }
    }
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(p[nbSegments].x, p[nbSegments].y, p[nbSegments].z);
        for(int i=0 ; i< nbPointCercle ; i++){
            glVertex3d(points_Cercle[nbSegments-1][i].x, points_Cercle[nbSegments-1][i].y, points_Cercle[nbSegments-1][i].z);
        }
        glVertex3d(points_Cercle[nbSegments-1][0].x, points_Cercle[nbSegments-1][0].y, points_Cercle[nbSegments-1][0].z);
    glEnd();
}

void Dragon(double r, double g, double b){
    Point depart = Point(-5,0,0);
    Point arrive = Point(10,7,0);
    double rayon = 1.5;
    int nbPoint_Cercle = 20;
    int nbCercles = 50;
    Point points_Cercle[nbCercles+1][nbPoint_Cercle];

    /*Initialisation Bezier*/
    Point bez[4] = {depart,Point(15,1,0),Point(0,7,0),arrive};
    Point p[nbCercles+1];
    drawBezier(bez, nbCercles, p);
    p[nbCercles] = arrive;

    //Très simillaire à la queue
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
                rayon+=0.003;
            else
                rayon-=0.003;
        }
    }

    /*Application de la texture au corps de notre dragon*/
    for(int j=0 ; j<nbCercles ;  j++){
            for (int i = 0; i < nbPoint_Cercle; i++){
                glBegin(GL_POLYGON);
                    glColor3d(1,1,1);
                    glTexCoord2d(0,0);
                    glVertex3d(points_Cercle[j][i].x, points_Cercle[j][i].y, points_Cercle[j][i].z);
                    glTexCoord2d(1,0);
                    glVertex3d(points_Cercle[j][(i+1)%nbPoint_Cercle].x, points_Cercle[j][(i+1)%nbPoint_Cercle].y, points_Cercle[j][(i+1)%nbPoint_Cercle].z);
                    glTexCoord2d(1,1);
                    glVertex3d(points_Cercle[j+1][(i+1)%nbPoint_Cercle].x, points_Cercle[j+1][(i+1)%nbPoint_Cercle].y, points_Cercle[j+1][(i+1)%nbPoint_Cercle].z);
                    glTexCoord2d(0,1);
                    glVertex3d(points_Cercle[j+1][i].x, points_Cercle[j+1][i].y, points_Cercle[j+1][i].z);
                glEnd();
            }
    }

    //Pied arriere droit
    glPushMatrix();
        glTranslated(-3,-1,1.5);
        glScaled(0.8,0.8,0.8);
        glRotated(20,0,0,1);
        glPushMatrix();
            Cuisse(r,g,b);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,-3.5,0);
            glRotated(-45,0,0,1);
            glPushMatrix();
                Mollet(r,g,b);
            glPopMatrix();
            glPushMatrix();
                glTranslated(-1,-4.25,0);
                glRotated(25,0,0,1);
                Pied(r,g,b);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Pied arriere gauche
    glPushMatrix();
        glTranslated(-3,-1,-1.5);
        glScaled(0.8,0.8,0.8);
        glRotated(20,0,0,1);
        glPushMatrix();
            Cuisse(r,g,b);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,-3.5,0);
            glRotated(-45,0,0,1);
            glPushMatrix();
                Mollet(r,g,b);
            glPopMatrix();
            glPushMatrix();
                glTranslated(-1,-4.25,0);
                glRotated(25,0,0,1);
                Pied(r,g,b);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Pied avant droit
    glPushMatrix();
        glTranslated(5,1,2);
        glScaled(1,1.25,1);
        glRotated(20,0,0,1);
        glPushMatrix();
            Cuisse(r,g,b);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,-3.5,0);
            glRotated(-45,0,0,1);
            glPushMatrix();
                Mollet(r,g,b);
            glPopMatrix();
            glPushMatrix();
                glTranslated(-1,-4.25,0);
                glRotated(25,0,0,1);
                Pied(r,g,b);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Pied avant gauche
    glPushMatrix();
        glTranslated(5,1,-2);
        glScaled(1,1.25,1);
        glRotated(20,0,0,1);
        glPushMatrix();
            Cuisse(r,g,b);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,-3.5,0);
            glRotated(-45,0,0,1);
            glPushMatrix();
                Mollet(r,g,b);
            glPopMatrix();
            glPushMatrix();
                glTranslated(-1,-4.25,0);
                glRotated(25,0,0,1);
                Pied(r,g,b);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();



    //Queue
    glPushMatrix();
        glTranslated(-5,0,0);
        glRotated(180,0,1,0);
        Queue(10,30,30,1.5,r,g,b);
    glPopMatrix();

    //aile gauche
    glPushMatrix();
        glTranslated(3,2.25,-9);
        glScaled(1.5,1.5,1.5);
        glRotated(90,0,0,1);
        glTranslated(0,0,5);
        glRotated(-angle_Aile,0,1,0);
        glTranslated(0,0,-5);
        Aile();
    glPopMatrix();

    //aile droite
    glPushMatrix();
        glTranslated(3,2.25,9);
        glScaled(1.5,1.5,1.5);
        glRotated(180,0,0,1);
        glRotated(180,0,1,0);
        glRotated(90,0,0,1);
        glTranslated(0,0,5);
        glRotated(angle_Aile,0,1,0);
        glTranslated(0,0,-5);
        Aile();
    glPopMatrix();

    glPushMatrix();//Tête
        glTranslated(10,5.5,0);
        glScaled(2.5,2.5,2.5);
        Tete(r,g,b);
    glPopMatrix();
}

void Aile(){
    Point pointAile[13] = {
        Point(0,0,1*5),
        Point(0,0.25*5,0.85*5),
        Point(0,0.5*5,sqrt(2)/2*5),
        Point(0,sqrt(2)/2*5,sqrt(2)/2*5),
        Point(0,sqrt(2)/2*5,0.5*5),
        Point(0,0.85*5,0.25*5),
        Point(0,1*5,0),
        Point(0,0.85*5,-0.25*5),
        Point(0,sqrt(2)/2*5,-0.5*5),
        Point(0,sqrt(2)/2*5,-sqrt(2)/2*5),
        Point(0,0.5*5,-sqrt(2)/2*5),
        Point(0,0.25*5,-0.85*5),
        Point(0,0,-1*5),
    };

    glBegin(GL_POLYGON);
        glColor3d(1.0,0.0,0.0);
        for(int i=0; i< 13; i++){
            glVertex3d(pointAile[i].x,pointAile[i].y,pointAile[i].z);
        }
    glEnd();

    /*Arêtes de l'aile*/
    glColor3d(0.0,0.0,1.0);
    glPushMatrix();
            glRotated(-45,1,0,0);
            glutSolidCylinder(0.25,5,20,20);
    glPopMatrix();
    glPushMatrix();
            glRotated(-90,1,0,0);
            glutSolidCylinder(0.25,5,20,20);
    glPopMatrix();
    glPushMatrix();
            glRotated(-135,1,0,0);
            glutSolidCylinder(0.25,5,20,20);
    glPopMatrix();

    /*Bras de l'aile*/
    glutSolidSphere(0.4,20,20);
    glutSolidCylinder(0.25,5,20,20);
    glPushMatrix();
        glTranslated(0,0,5);
        glutSolidSphere(0.4,20,20);
    glPopMatrix();
    glPushMatrix();
            glRotated(180,1,0,0);
            glutSolidCylinder(0.25,5,20,20);
    glPopMatrix();

}

void Tete(double r, double g, double b){
    glColor3d(r, g, b);

    /*Bouche*/
    glPushMatrix();
        glTranslated(1.85,0.1,0);
        glScaled(0.9,0.2,1);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslated(1.85,0.5,0);
        glScaled(0.9,0.2,1);
        glutSolidCube(1);
    glPopMatrix();

    /*Base de la tête*/
    glPushMatrix();
        glTranslated(0.5,0.7,0);
        glScaled(1.8,1.4,1.4);
        glutSolidCube(1);
    glPopMatrix();

    /*Dents*/
    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(2.0,0.2,0.4);
        glRotated(-90,1,0,0);
        glutSolidCone(0.1,0.2,5,5);
    glPopMatrix();
    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(2.0,0.2,-0.4);
        glRotated(-90,1,0,0);
        glutSolidCone(0.1,0.2,5,5);
    glPopMatrix();

    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(2.0,0.4,0.2);
        glRotated(90,1,0,0);
        glutSolidCone(0.1,0.2,5,5);
    glPopMatrix();
    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(2.0,0.4,-0.2);
        glRotated(90,1,0,0);
        glutSolidCone(0.1,0.2,5,5);
    glPopMatrix();

    /*Yeux*/
    glPushMatrix();
        glColor3d(1.0,1.0,1.0);
        glTranslated(1.3,1.0,0.5);
        glutSolidSphere(0.2,6,6);
    glPopMatrix();
    glPushMatrix();
        glColor3d(1.0,1.0,1.0);
        glTranslated(1.3,1.0,-0.5);
        glutSolidSphere(0.2,6,6);
    glPopMatrix();
}



void loadJpegImage(char *fichier, unsigned char *im, const int l, const int h)
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
