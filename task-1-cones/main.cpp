/* Averyanoff Juriy-212 */ 

#include <iostream> //стандартный ввод выпод
#include <fstream>  // для работы с файлами
#include <iterator>
#include <list> // stl
#include <cmath> // для библиотеки с синусами и косинусами
#include <map>
#include <vector>
#include <random>
				

/* Написать C++-программу, которая читает из файла описание нескольких конусов,
 * хранит их в двусвязном списке STL
 * и подготавливает данные для визуализации этих конусов в gnuplot.
 * При этом геометрические объекты должны быть реализованы через наследование классов. */

/* работаем в плоскости с положительными координатами для удобства */

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
		// может ограничить кол-во прохождений дляизбежания повтора на вершинах	
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

struct CellCoord { //структура с координатами квадратов
		int i;
		int j;
		/* лексикографический порядок */
		bool operator<(const CellCoord& other) const { // как упорядочить квадраты
				if (i != other.i)
						return i < other.i;
				return j < other.j;
		}
};

/* координаты точки, и пространство квадратов,
 * нижняя левая координата и размер клетки */

/* для каждой точки получаем координату(левую нижнюю) квадрата,
 * в котором она содержится
 * xmin = ymin = 0.0*/

CellCoord getCell(const Point& point, /*double xmin, double ymin, */ double cellsize) {
		CellCoord cell;

		//cell.i = (int)(point.getX()/cellsize);
		//cell.j = (int)(point.getY()/cellsize);
		
		cell.i = static_cast<int>(std::floor(point.getX() / cellsize));
		cell.j = static_cast<int>(std::floor(point.getY() / cellsize));

		return cell;
}
/* координата квадрата 1: список точек к нему 
 * координата квадрата 2: список точек к нему
 * и тд*/
void addPoint(std::map<CellCoord, std::vector<Point>>& grid,
				const Point& point,
				double cellsize)
{
		CellCoord cell = getCell(point, cellsize);
		grid[cell].push_back(point);
}

/* печать клетки и точек в ней (или относящихся к ней) */
void printGrid(const std::map<CellCoord, std::vector<Point>>& grid)
{
		for(const auto&  [struct_,vector_] : grid){
				std::cout << "Cell (" << struct_.i << "," << struct_.j << "):\n";
				for (const Point& p : vector_) {
						std::cout << "(" << p.getX() << "," << p.getY() << "); ";
				}
				std::cout << '\n';
		}

}

/* печать точек в соотв клетке */
void PrintCell(const std::map<CellCoord, std::vector<Point>>& grid, int i, int j){
		CellCoord cell{i,j};
		auto it = grid.find(cell);

		if (it != grid.end()){
				for (const Point& p : it->second) {
						std::cout << "(" << p.getX() << "," << p.getY() << ");\n";
				std::cout << "\n";
		}
		}
}

/* вывод в файл */
void writeGrid(
    const std::map<CellCoord, std::vector<Point>>& grid,
    double cellsize,
    std::ofstream& gaussP,
    std::ofstream& cellP
) {
    for (const auto& [cell, points] : grid) {

        // Координаты левого нижнего угла квадрата
        double x = cell.i * cellsize;
        double y = cell.j * cellsize;

        // Записываем границы квадрата
        cellP << x << " " << y << '\n';
        cellP << x + cellsize << " " << y << '\n';
        cellP << x + cellsize << " " << y + cellsize << '\n';
        cellP << x << " " << y + cellsize << '\n';
        cellP << x << " " << y << "\n\n\n";

        // Записываем точки внутри квадрата
        for (const Point& p : points) {
            gaussP << p.getX() << " "
                   << p.getY() << '\n';
        }
    }
}

/* работа с соседями точки */
void printNeighbors(const std::map<CellCoord, std::vector<Point>>& grid, int i, int j){
		int di, dj;
		for (di = -1; di<=1; ++di) {
				for (dj = -1; dj<=1; ++dj) {
						CellCoord neighbor{i + di, j + dj};
						auto it = grid.find(neighbor);

						if (it != grid.end()) {
								for (const Point& p : it->second) {
										std::cout << "(" << p.getX() << "," << p.getY() << ")\n";
								}
								std::cout << "\n";
						}
				}
		}
}

/* расстояние между точками */
double distance(const Point& a, const Point& b) {
		return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY()-b.getY(),2));
}

/* генерация облака точек по Гауссу */

/* n>0*/
std::vector<Point> generateGaussian(const Cone& cone, int n, std::mt19937& gen) {
		double x, y;
		int i;
		std::vector<Point> points;
		double sigma = cone.getRadius() / (1.0 + cone.getHeight());
		
		std::normal_distribution<double> distx(cone.getX(), sigma);
		std::normal_distribution<double> disty(cone.getY(), sigma);
		
		for(i = 0; i < n; ++i){
				x = distx(gen);
				y = disty(gen);
				points.emplace_back(x,y);
		}


		return points;
}

void fillGrid(const std::list<Cone>& cones, std::map<CellCoord, std::vector<Point>>& grid, int n, double cellsize, std::mt19937& gen){
		for (const Cone& cone : cones) {
				auto points = generateGaussian(cone, n, gen);
				for (const Point& p : points) {
						addPoint(grid, p, cellsize);
				
				}
		}
}

int main() {
		// входник
		std::list<Cone> cones = Read("data.txt");
		// выходник
		std::ofstream fout("cone-points.txt");
		
		// сюда заносим точки гауссового распределения
		std::ofstream gaussP("gauss-points.txt");
		
		//сюда заносим координаты клеток
		std::ofstream cellP("cell-points.txt");

		// каждой паре (i,j) сопоставляем динамический массив точек
		std::map<CellCoord, std::vector<Point>> grid;
		
		// сид
		std::mt19937 gen(std::random_device{}());
		
		// число точек под конусом
		int n = 500;

		//размер клетки
		double cellsize = 1.0;

		fillGrid(cones, grid, n, cellsize, gen);

		if(!fout.is_open() || !gaussP.is_open() || !cellP.is_open()) {
				std::cerr << "Cannot open the file \n";
				return -1;
		
		}

		writeGrid(grid, cellsize, gaussP, cellP);

		for (const Cone& cone : cones) {
				writeConePoints(cone, fout);
				fout << "\n";
		}


		return 0;
}
