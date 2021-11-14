#ifndef CYLINDRE_H
#define CYLINDRE_H
#include "Point.h"
#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <math.h>
#include <iostream>
#include <jerror.h>
#include <vector>


class Cylindre
{
    public:
        Cylindre();
        Cylindre(int newNombrePoint, double newRayon, double newHauteur);
        virtual ~Cylindre();

        void drawPoint();
        void ColorCylindre(float red, float green, float blue);
        void appliTexture();
        void setTexture(char* fichier, int l, int h);
        unsigned char* getTexture();

        Point* pCylindre;
        int nombrePoints;
        double rayon, hauteur;
        unsigned char* texture;
        int HTexture, LTexture;
    protected:

    private:

};

#endif // CYLINDRE_H
