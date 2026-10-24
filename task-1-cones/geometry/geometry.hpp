#pragma once

#include <iterator>
class Point {
private:
    double x;
    double y;

public:
    Point(double x, double y);

    double getX() const;
    double getY() const;

    void setX(double newx);
    void setY(double newy);
};

class Circle : public Point {
		private:
				double radius;
		public:
				Circle(double x, double y, double radius);

				double getRadius() const;

				void setRadius(double newradius);

				double getArea() const;
};

class Cone : public Circle {
		private:
				double height;
		public:
				Cone(double x, double y, double radius, double height);

				double getHeight() const;

				void setHeight(double newheight);

				double getVolume() const;
};

double distance(const Point& a, const Point& b);
				
