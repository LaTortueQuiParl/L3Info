#ifndef POINT_H
#define POINT_H
class Point
{
    public:
        double x,y,z;
        Point();
        Point(double newX, double newY, double newZ);

        double getX();
        double getY();
        double getZ();

        void setX(double newX);
        void setY(double newY);
        void setZ(double newZ);

        const Point &operator=(const Point &p){
            x = p.x;
            y = p.y;
            z = p.z;
            return *this;
        }
        const Point &operator+(const Point &p){
            x = x+p.x;
            y = y+p.y;
            z = z+p.z;
            return *this;
        }
};

#endif //POINT_H
