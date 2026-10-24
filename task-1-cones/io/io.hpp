#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include "../grid/grid.hpp"

/* прочитать данные из файла в двусвязный список */
std::list<Cone> Read(const std::string& filename); 

/* возвращает файл со списком точек конуса */
void writeConePoints(const Cone& cone, std::ofstream& fout); 

/* вывод в файл */
void writeGrid(
    const std::map<CellCoord, std::vector<Point>>& grid,
    double cellsize,
    std::ofstream& gaussP,
    std::ofstream& cellP
);
void WriteClusters(const std::vector<Point>& points,
				const std::vector<int>& labels, 
				std::ofstream& fout); 

