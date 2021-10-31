#ifndef CYLINDRE_H
#define CYLINDRE_H
#include <math.h>
#include <GL/freeglut.h>
#include "Point.h"


class Cylindre
{
    public:
        Cylindre();
        Cylindre(int newNombrePoint, double newRayon, double newHauteur);
        virtual ~Cylindre();

        void drawPoint();
        void appliTexture(unsigned char* text, int largim, int hautim);

    protected:

    private:
        Point* pCylindre;
        int nombrePoints;
        double rayon, hauteur;
};

#endif // CYLINDRE_H
