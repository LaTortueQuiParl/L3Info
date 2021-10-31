#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::~Point()
{
    //dtor
}

Point::Point(double newX, double newY, double newZ)
{
    this->x = newX;
    this->y = newY;
    this->z = newZ;
}

double Point::getX(){
    return this->x;
}
double Point::getY(){
    return this->y;
}
double Point::getZ(){
    return this->z;
}
void Point::setX(double newX){
    this->x = newX;
}
void Point::setY(double newY){
    this->y = newY;
}
void Point::setZ(double newZ){
    this->z = newZ;
}
