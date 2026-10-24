#pragma once
#include "../grid/grid.hpp"
#include <random>
#include <list>

/* генерация облака точек по Гауссу */

/* n>0*/
std::vector<Point> generateGaussian(const Cone& cone, int n, std::mt19937& gen);

void fillGrid(const std::list<Cone>& cones, std::map<CellCoord, std::vector<Point>>& grid, int n, double cellsize, std::mt19937& gen);
