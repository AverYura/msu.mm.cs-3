#pragma once

#include <map>
#include <vector>
#include <cmath>
#include "../geometry/geometry.hpp"

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

CellCoord getCell(const Point& point, /*double xmin, double ymin, */ double cellsize);

/* координата квадрата 1: список точек к нему 
 * координата квадрата 2: список точек к нему
 * и тд*/

void addPoint(std::map<CellCoord, std::vector<Point>>& grid,
				const Point& point,
				double cellsize);

/* печать клетки и точек в ней (или относящихся к ней) */
void printGrid(const std::map<CellCoord, std::vector<Point>>& grid);

/* печать точек в соотв клетке */

void PrintCell(const std::map<CellCoord, std::vector<Point>>& grid, int i, int j);

/* работа с соседями точки */
void printNeighbors(const std::map<CellCoord, std::vector<Point>>& grid, int i, int j);

/* вектор точек */
std::vector<Point> collectPoints(const std::map<CellCoord, std::vector<Point>>& grid);
