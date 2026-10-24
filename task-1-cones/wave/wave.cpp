#include "wave.hpp"



void Wave::buildAdjacency(const std::vector<Point>& points) {
		int n = static_cast<int>(points.size());
		adjacency.assign(n, std::vector<unsigned char>(n,0));

		for (int i = 0; i < n; i++) {
				for (int j = i + 1; j< n; j++) {
						if (distance(points[i], points[j]) <= EPS) {
								adjacency[i][j] = 1;
								adjacency[j][i] = 1;
						}
				}
		}
}
				/* кластеризуем */
void Wave::clusterize() {
		std::queue<int> q;
						
		int row;
		int n = static_cast<int>(adjacency.size());
		int clusterId = 0;

		labels.assign(n, -1); // (-1,...-1)

		for (int i = 0; i < n; ++i) {
				if (labels[i] != -1)
						continue; //вершина уже посещена

				labels[i] = clusterId;
				q.push(i);

				while (!q.empty()) {
						row = q.front(); // первый элемент очереди
						q.pop();
												
						// обработка соседей
						for (int j = 0; j < n; ++j) {
								/* во избежание филлерных проверок */
								if (adjacency[row][j] == 1 && labels[j] == -1) {
										q.push(j);
										labels[j] = clusterId;
								}
						}
				}

				++clusterId;
						
		}
}
				
const std::vector<int>& Wave::getLabel() const {
		return labels;
}

