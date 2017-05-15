/*
  Given a directed with possibly negative edge weights and with
  n vertices and m edges, check whether it contains a cycle of
  negative weight. 
  Use Bellman-Ford and if after V - 1 iteration there are still
  edges to relax, there is a negative cycle.

  Input: graph given in the standard format
         1 <= n <= 10^3, 0 <= m <= 10^4
         edge weights are integers of absolute value at most 10^3
  Output: 1 if the graph has a negative cycle and 0 otherwise.
*/

#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  int size = adj.size();
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
