/* Averyanoff Juriy-212 */ 

#include <iostream> //стандартный ввод выпод
#include <fstream>  // для работы с файлами
#include <list> // stl
#include <cmath> // для библиотеки с синусами и косинусами
				

/* Написать C++-программу, которая читает из файла описание нескольких конусов,
 * хранит их в двусвязном списке STL
 * и подготавливает данные для визуализации этих конусов в gnuplot.
 * При этом геометрические объекты должны быть реализованы через наследование классов. */


class Point { 

		// координаты точки (центра)
private:
		double x;
		double y;
public:
		// конструктор
		Point(double x, double y)
				: x(x), y(y) {}
		// вернуть x,y / задать x,y
		double getX() const { return x; }
		double getY() const { return y; }

		void setX(double newx) { x = newx; }
		void setY(double newy) { y = newy; }
};

class Circle : public Point {
		// радиус круга (не Михаила)
private:
		double radius;
public:
		// конструктор
		Circle(double x, double y, double radius)
				: Point(x,y), radius(radius) {}
		// вернуть / задать
		double getRadius() const { return radius; }
		void setRadius(double newradius) { radius = newradius; }

		double getArea() const { return radius*radius*3.141593; } // площадь круга
};

class Cone : public Circle { 
		// высота конуса
private:
		double height;
public:
		// конструктор
		Cone(double x, double y, double radius, double height)
				: Circle(x,y,radius), height(height) {}
		// получить / задать
		double getHeight() const { return height; }
		void setHeight(double newheight) { height = newheight; }
		double getVolume() const { return getArea() * height / 3.0; } // объем
};

// прочитать данные из файла в двусвязный список
std::list<Cone> Read(const std::string& filename) {
		// двусвязный список
		std::list<Cone> cones;
		// входной файл
		std::ifstream finput(filename);
		
		// ошибка открытия
		if (!finput.is_open()) {
				std::cerr << "Cannot open file \n";
				return cones;
		}
		
		// параметры, которые читаем из файла построчно
		double x,y,R,h;
		while(finput >> x >> y >> R >> h) {
				cones.emplace_back(x,y,R,h); // чтобы контейнер сам вызывал конструктор в отлчие от пуш_бэка()
		}
		return cones;
}

// войд-функуия для вовращения файла со списком точек конуса
void writeConePoints(const Cone& cone, std::ofstream& fout) {
		double x0, y0, x, y, z, r, phi, R, H, dz, dphi;

		x0 = cone.getX();
		y0 = cone.getY();
		R = cone.getRadius();
		H = cone.getHeight();
		dz = 0.1;
		dphi = 0.1;

		// задаем конус уравнением
		
		for (z = 0; z <= H; z += dz) {
				r = R * (1.0 - z / H);

				for (phi = 0; phi <= 2 * 3.141593; phi += dphi) {
						x = x0 + r * cos(phi);
						y = y0 + r * sin(phi);

						fout 	<< x << " "
								<< y << " "
								<< z << "\n";
				}
				fout << "\n";
		}
}



int main() {
		// входник
		std::list<Cone> cones = Read("data.txt");
		// выходник
		std::ofstream fout("cone-points.txt");

		if(!fout.is_open()) {
				std::cerr << "Cannot open the file \n";
				return -1;
		}
		for (const Cone& cone : cones) {
				writeConePoints(cone, fout);
				fout << "\n";
		}
		return 0;
}
