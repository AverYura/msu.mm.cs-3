/* Averyanoff Juriy-212 */ 

#include "grid/grid.hpp"
#include "geometry/geometry.hpp"
#include "gaussian/gaussian.hpp"
#include "io/io.hpp"
#include "wave/wave.hpp"
#include <fstream>

/* Написать C++-программу, которая читает из файла описание нескольких конусов,
 * хранит их в двусвязном списке STL
 * и подготавливает данные для визуализации этих конусов в gnuplot.
 * При этом геометрические объекты должны быть реализованы через наследование классов. */

/* работаем в плоскости с положительными координатами для удобства */

int main() {
		// входник
		std::list<Cone> cones = Read("data.txt");
		// выходник
		std::ofstream fout("txt/cone-points.txt");
		
		// сюда заносим точки гауссового распределения
		std::ofstream gaussP("txt/gauss-points.txt");
		
		//сюда заносим координаты клеток
		std::ofstream cellP("txt/cell-points.txt");

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
		/* собираем точки из сетки в один вектор */
		std::vector<Point> points = collectPoints(grid);
		/* объект волнового алгоритма */
		Wave wave;

		/* строим матрицу смежности */

		wave.buildAdjacency(points);

		/* кластеризуем */

		wave.clusterize();

		/* записываем результат */

		std::ofstream clusterFile("txt/clusters.txt");
		WriteClusters(points, wave.getLabel(), clusterFile);
		

		writeGrid(grid, cellsize, gaussP, cellP);

		for (const Cone& cone : cones) {
				writeConePoints(cone, fout);
				fout << "\n";
		}


		return 0;
}
