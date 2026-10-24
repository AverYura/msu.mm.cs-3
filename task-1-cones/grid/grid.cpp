#include "grid.hpp"
#include <iostream>

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
		for(const auto&  entry : grid){
				std::cout << "Cell (" << entry.first.i << "," << entry.first.j << "):\n";
				for (const Point& p : entry.second) {
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

/* вектор точек */
std::vector<Point> collectPoints(const std::map<CellCoord, std::vector<Point>>& grid) {
		std::vector<Point> result;

		for(const auto& entry : grid) {

				for (const Point& p : entry.second) {
						result.emplace_back(p); // push_back
				}
		}

		return result;
}


