#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  vector<int> distance(adj.size(), -1);
  int s = 0;
  distance[s] = 0;
  queue<int> to_explore;
  to_explore.push(s);
  while (!to_explore.empty()) {
    int v = to_explore.front();
    to_explore.pop();
    for (int i = 0; i < adj[v].size(); i++) {
      if (distance[adj[v][i]] == -1) {
        to_explore.push(adj[v][i]);
        distance[adj[v][i]] = distance[v] + 1;
      } else if (distance[adj[v][i]] == distance[v]) {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
  std::cout << std::endl;
}
