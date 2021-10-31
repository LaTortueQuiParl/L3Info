#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(double newX, double newY, double newZ);
        virtual ~Point();

        double getX();
        double getY();
        double getZ();

        void setX(double newX);
        void setY(double newY);
        void setZ(double newZ);

    protected:

    private:

        double x,y,z;
};

#endif // POINT_H
