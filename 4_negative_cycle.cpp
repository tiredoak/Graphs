#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  int size = adj.size();
  // Constraint limits input to 10^5
  vector<int> dist(size, 10001);
  dist[0] = 0;
  for (int v = 0; v <= size; v++) {
    int change = 0;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < adj[i].size(); j++) {
        if (dist[adj[i][j]] > dist[i] + cost[i][j]) {
          change = 1;
          dist[adj[i][j]] = dist[i] + cost[i][j];
        }
      }
    }
    if (change == 1 && v == size) return 1;
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
  std::cout << std::endl;
}
