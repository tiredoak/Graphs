/*
  Given an undirected graph and two distinct vertices u and v, 
  check if there is a path between u and v.
  Use Depth First Seach to determine vertices reachable from
  a given vertex.

  Input: undirected graph with n vertices and m edges.
         next line contains two vertices u and v of the graph
         2 <= n <= 10^3 and 2 <= m <= 10^3 and 1 <= u, v <= n
         and u != v
  Output: 1 if there is a path between u and v and 0 otherwise
*/

#include <iostream>
#include <vector>

using std::vector;
using std::pair;

// Depth first search starting at vertex x
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
  // Do x - 1 and y - 1 to match indices in vector
  std::cout << reach(adj, visited, x - 1, y - 1);
  std::cout << std::endl;
}
