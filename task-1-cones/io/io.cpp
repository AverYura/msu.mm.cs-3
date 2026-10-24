#include "io.hpp"

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


/* вывод в файл */
void writeGrid(
    const std::map<CellCoord, std::vector<Point>>& grid,
    double cellsize,
    std::ofstream& gaussP,
    std::ofstream& cellP
) {
    for (const auto& entry : grid) {
		const CellCoord& cell = entry.first;
		const std::vector<Point>& points= entry.second;        // Координаты левого нижнего угла квадрата
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

void WriteClusters(const std::vector<Point>& points,
				const std::vector<int>& labels, 
				std::ofstream& fout) {
		if (static_cast<int>(points.size()) != static_cast<int>(labels.size())) {
				std::cerr << "Error: points and labels size are diff\n";
				return;
		}

		for (int i = 0; i < static_cast<int>(points.size()); ++i) {
				fout << points[i].getX()  << " "
						<< points[i].getY() << " "
						<< labels[i] << '\n';
		}
}

