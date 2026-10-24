#include "gaussian.hpp"

/* генерация облака точек по гауссу */
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


