#pragma once

#include <algorithm>
#include "../geometry/geometry.hpp"
#include "../grid/grid.hpp"

/* реализация алгоритма краскала */

#include <map>
#include <vector>

struct Edge {
		int u;
		int v;
		double dist;
};

/* disjoint set unite имеет 3 метода:
 * 1) сздание множества
 * 2) поиск корня(прародителя)
 * 3) объединение двух отельных компонент связности в одну
 * */

class DSU {
		private:
				std::vector<int> parent;
				std::vector<int> rank;
		public:
				DSU(int n) {
						parent.assign(n,-1);
						rank.assign(n,0);

						for (int i = 0; i < n; i++) {
								makeset(i);
						}
				}
				void makeset(int v) {
						if (parent[v] == -1) {
								parent[v] = v;
								rank[v] = 0;
						}
				}

				int find_(int v) {
						while (parent[v] != v) {
								parent[v] = parent[parent[v]];
								v = parent[v];
						}
						return v;
				}

				bool unite(int v, int u) {
						v = find_(v);
						u = find_(u);

						if (v == u) {
								return false; // уже в одном множестве
						}

						if (rank[v] < rank[u]) {
								int r = v;
								v = u;
								u = r;
						}

						parent[u] = v;

						if (rank[v] == rank[u]) {
								rank[v] = rank[v] + 1;
						}
						return true;
				}


};
				
/* алгоритм краскала:
 * 1) перечисляем все ребра
 * 2) сортируем по расстоянию
 * 3) используя dsu делаем минимальное дерево
 * 4) возвращаем*/
class Kruskal_1 {
		public:
				std::vector<Edge> builtMST(const std::vector<Point>& points) {
						int n = static_cast<int>(points.size()); // резервируем для скорости
						std::vector<Edge> edges; 
						edges.reserve(static_cast<std::size_t>(n) * (n - 1) / 2);

						if (n < 2) {
								return { };
						}

						/* всего n(n-1)/2 элемента */
						for (int i = 0; i < n; ++i) {
								for (int j = i + 1; j < n; ++j) {
										edges.emplace_back(i,j,distance(points[i], points[j]));
										
								}
						}
						
						/* сортируем, используя лямбда-функцию [](a,b) {return a < b; } */

						std::sort(edges.begin(),edges.end(), [](const Edge& a, const Edge& b) { return a.dist < b.dist; });

						
						DSU dsu(n);

						std::vector<Edge> mst;
						mst.reserve(n - 1); // резервируем для скорости

						for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
								if (dsu.find_(edges[i].u) != dsu.find_(edges[i].v)) {
										mst.emplace_back(edges[i]);
										dsu.unite(edges[i].v, edges[i].u);
								}

								if (static_cast<int>(mst.size()) == (n - 1)) {
										break;
								}
						}

						return mst;
				}
};

class Kruskal_2 {
		public:
				std::vector<Edge> builtMST(const std::vector<Point>& points, double cellsize) {

						int n = static_cast<int>(points.size());

						if (n < 2)
								return {};

						// 1. Строим сетку из ИНДЕКСОВ точек.
						std::map<CellCoord, std::vector<int>> indexedGrid;

						for (int i = 0; i < n; ++i) {
								CellCoord cell = getCell(points[i], cellsize);
								indexedGrid[cell].push_back(i);
						}

						// 2. Собираем локальные рёбра.
						std::vector<Edge> edges;

						for (int i = 0; i < n; ++i) {
								CellCoord cell = getCell(points[i], cellsize);

								// Обходим свою клетку и 8 соседних
								for (int di = -1; di <= 1; ++di) {
										for (int dj = -1; dj <= 1; ++dj) {

												CellCoord neighbor = {
														cell.i + di,
														cell.j + dj
												};

												auto it = indexedGrid.find(neighbor);

												if (it == indexedGrid.end())
														continue;

												// Перебираем точки соседней клетки
												for (int j : it->second) {

														// Исключаем саму точку
														// и повторяющиеся рёбра
														if (i >= j)
																continue;

														double d = distance(points[i], points[j]);

														edges.push_back({i, j, d});
												}
										}
								}
						}

						// 3. Сортируем рёбра по возрастанию длины.
						std::sort(
										edges.begin(),
										edges.end(),
										[](const Edge& a, const Edge& b) {
										return a.dist < b.dist;
										}
								 );

						// 4. Запускаем обычного Краскала.
						DSU dsu(n);

						std::vector<Edge> mst;
						mst.reserve(n - 1);

						for (const Edge& edge : edges) {

								// unite возвращает true,
								// если соединены разные компоненты
								if (dsu.unite(edge.u, edge.v)) {
										mst.push_back(edge);
								}

								if (static_cast<int>(mst.size()) == n - 1)
										break;
						}


						return mst;
				}
};







