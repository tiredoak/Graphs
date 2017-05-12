#include <iostream>
#include <vector>

using std::vector;
using std::pair;


int reach(vector<vector<int> > &adj, vector<bool> &visited, int x, int y) {
  visited[x] = true;
  for (int i = 0; i < adj[x].size(); i++) {
    if (visited[adj[x][i]] == false) {
      reach(adj, visited, adj[x][i], y);
    }
    if (visited[y] == true) return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::vector<bool> visited(n, 0);
  std::cout << reach(adj, visited, x - 1, y - 1);
  std::cout << std::endl;
}
