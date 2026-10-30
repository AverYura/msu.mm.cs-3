#pragma once
#include "../grid/grid.hpp"
#include <cmath>
#include <queue>
#include <iostream>

class Wave {
		private:
				// матрица смежности
				std::vector<std::vector<unsigned char>> adjacency;

				// номера кластеров
				std::vector<int> labels;

				// порог
				//const double EPS = 0.5;
		public:
				/* строим матрицу смежности */
				void buildAdjacency(const std::vector<Point>& points, double eps);
				void clusterize();
				const std::vector<int>& getLabel() const;
};
