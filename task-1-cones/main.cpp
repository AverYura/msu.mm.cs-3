/* Averyanoff Juriy-212 */ 

#include "grid/grid.hpp"
#include "geometry/geometry.hpp"
#include "gaussian/gaussian.hpp"
#include "io/io.hpp"
#include "wave/wave.hpp"
#include "MST-realisations/mst.hpp"
#include <chrono>
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
		int n = 200;

		//размер клетки
		double cellsize = 1.0;

		fillGrid(cones, grid, n, cellsize, gen);

		if(!fout.is_open() || !gaussP.is_open() || !cellP.is_open()) {
				std::cerr << "Cannot open the file \n";
				return -1;
		
		}
		/* собираем точки из сетки в один вектор */
		std::vector<Point> points = collectPoints(grid);
		
		/* == измеряем время == */
		Kruskal_1 kruskal1;
		Kruskal_2 kruskal2;

		// Первый Краскал
		auto start1 = std::chrono::steady_clock::now();

		std::vector<Edge> mst1 = kruskal1.builtMST(points);

		auto end1 = std::chrono::steady_clock::now();

		// Второй Краскал
		auto start2 = std::chrono::steady_clock::now();

		std::vector<Edge> mst2 = kruskal2.builtMST(points, cellsize);

		auto end2 = std::chrono::steady_clock::now();

		// Время в миллисекундах
		double time1 =
				std::chrono::duration<double, std::milli>(end1 - start1).count();

		double time2 =
				std::chrono::duration<double, std::milli>(end2 - start2).count();

		double length1 = 0.0;
		double length2 = 0.0;

		for (const Edge& e : mst1) {
				length1 += e.dist;
		}

		for (const Edge& e : mst2) {
				length2 += e.dist;
		}

		std::cout << "Kruskal 1:\n";
		std::cout << "  Edges: " << mst1.size() << '\n';
		std::cout << "  Length: " << length1 << '\n';
		std::cout << "  Time: " << time1 << " ms\n";

		std::cout << "Kruskal 2:\n";
		std::cout << "  Edges: " << mst2.size() << '\n';
		std::cout << "  Length: " << length2 << '\n';
		std::cout << "  Time: " << time2 << " ms\n";

		/* == конец измерения == */
		
		/*
		std::ofstream fout1("txt/mst-full.txt");
		writeMST(points, mst1, fout1);
		*/

		std::ofstream fout2("txt/mst-grid.txt");
		writeMST(points, mst2, fout2);
		
		/* для построения гитсограмм */
		std::ofstream lengths1("txt/lengths-full.txt");
		writeEdgeLengths(mst1, lengths1);

		std::ofstream lengths2("txt/lengths-grid.txt");
		writeEdgeLengths(mst2, lengths2);

		/* ======================= */

		/* объект волнового алгоритма */

		double eps = 0.3;
		Wave wave;

		/* строим матрицу смежности */

		wave.buildAdjacency(points,eps);

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
