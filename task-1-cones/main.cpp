/* Averyanoff Juriy-212 */ 

#include <iostream> //стандартный ввод выпод
#include <fstream>  // для работы с файлами
#include <list> // stl
				

/* Написать C++-программу, которая читает из файла описание нескольких конусов,
 * хранит их в двусвязном списке STL
 * и подготавливает данные для визуализации этих конусов в gnuplot.
 * При этом геометрические объекты должны быть реализованы через наследование классов. */


class Point { 

private:
		double x;
		double y;
public:
		Point(double x, double y)
				: x(x), y(y) {}

		double getX() const { return x; }
		double getY() const { return y; }

		void setX(double newx) { x = newx; }
		void setY(double newy) { y = newy; }
};

class Circle : public Point {
private:
		double radius;
public:
		Circle(double x, double y, double radius)
				: Point(x,y), radius(radius) {}
		double getRadius() const { return radius; }
		void setRadius(double newradius) { radius = newradius; }

		double getArea() const { return radius*radius*3.141593; }
};

class Cone : public Circle { 
private:
		double height;
public:
		Cone(double x, double y, double radius, double height)
				: Circle(x,y,radius), height(height) {}
		double getHeight() const { return height; }
		void setHeight(double newheight) { height = newheight; }
		double getVolume() const { return getArea() * height / 3.0; }
};

int main() {

}
