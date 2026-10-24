#include "geometry.hpp"
#include <cmath>
// realisation
//
// for Point

Point::Point(double x, double y)
		: x(x), y(y) {}

double Point::getX() const {
		return x;
}

double Point::getY() const {
		return y;
}

void Point::setX(double newx) {
		x = newx;
}

void Point::setY(double newy) {
		y = newy;
}

// fot Circle

Circle::Circle(double x, double y, double radius)
		: Point(x, y), radius(radius) {}

double Circle::getRadius() const {
		return radius;
}

void Circle::setRadius(double newradius) {
		radius = newradius;
}

double Circle::getArea() const {
		return radius*radius*3.141593;
}

Cone::Cone(double x, double y, double radius, double height)
		: Circle(x,y,radius), height(height) {}
double Cone::getHeight() const {
		return height;
}
void Cone::setHeight(double newheight) {
		height = newheight;
}

double Cone::getVolume() const {
		return getArea() * height / 3.0; 
}

/* расстояние между точками */
double distance(const Point& a, const Point& b) {
		return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY()-b.getY(),2));
}
