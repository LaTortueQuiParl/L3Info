#include "Point.h"

Point::Point(){
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double newX, double newY, double newZ){
    x = newX;
    y = newY;
    z = newZ;
}

double Point::getX(){return x;}
double Point::getY(){return y;}
double Point::getZ(){return z;}

void Point::setX(double newX){x = newX;}
void Point::setY(double newY){y = newY;}
void Point::setZ(double newZ){z = newZ;}
