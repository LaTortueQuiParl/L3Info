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
        void appliTexture(char* fichier, int l, int h);
        unsigned char* getTexture();

    protected:

    private:
        Point* pCylindre;
        int nombrePoints;
        double rayon, hauteur;
        unsigned char* texture;
};

#endif // CYLINDRE_H
