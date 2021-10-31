#include "Cylindre.h"

Cylindre::Cylindre()
{
    this->nombrePoints = 30;
    this->hauteur = 0.5;
    this->rayon = 0.5;
    this->pCylindre = new Point[2*nombrePoints];
}

Cylindre::~Cylindre()
{
   delete[] pCylindre;
}

Cylindre::Cylindre(int newNombrePoint, double newRayon, double newHauteur){
    this->nombrePoints = newNombrePoint;
    this->hauteur = newHauteur;
    this->rayon = newRayon;
    this->pCylindre = new Point[2*nombrePoints];
}

void Cylindre::drawPoint(){
    for (int i = 0; i < this->nombrePoints; i++){
        double theta = (double) (2.0*i*M_PI/this->nombrePoints);
        this->pCylindre[i] = {this->rayon * cos(theta), this->rayon * sin(theta), this->hauteur/2.0};
        this->pCylindre[i+this->nombrePoints] = {this->rayon * cos(theta), this->rayon * sin(theta), -this->hauteur/2.0};
    }
}

void Cylindre::appliTexture(unsigned char* text, int largim, int hautim){

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largim, hautim, 0, GL_RGB, GL_UNSIGNED_BYTE, text);
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < this->nombrePoints; i++){
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0,0.0);   glVertex3f(this->pCylindre[i].getX(), this->pCylindre[i].getY(), this->pCylindre[i].getZ());
        glTexCoord2f(0.0,1.0);   glVertex3f(this->pCylindre[(i+1)%this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints].getZ());
        glTexCoord2f(1.0,1.0);   glVertex3f(this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getZ());
        glTexCoord2f(1.0,0.0);   glVertex3f(this->pCylindre[i+this->nombrePoints].getX(), this->pCylindre[i+this->nombrePoints].getY(), this->pCylindre[i+this->nombrePoints].getZ());
        glEnd();
    }
}
