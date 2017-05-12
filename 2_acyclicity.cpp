/*
  Detecting cycles in a graph. Using DFS to traverse the graph
  and assigning colors as nodes are visited. If it's ever the 
  case that a grey node wants to visit another grey node, that
  implies a cycle in the graph.
*/

#include <iostream>
#include <vector>

using std::vector;
using std::pair;

enum {white, grey, black};

int explore(vector<vector<int> > &adj, vector<int> &color, int node, int &acyclic) {
  color[node] = grey;
  for (int i = 0; i < adj[node].size(); i++) {
    if (color[adj[node][i]] == grey) {
      color[node] = black;
      acyclic = 1;
      return acyclic;
    } else {
      acyclic = (acyclic == 1) ? acyclic : explore(adj, color, adj[node][i], acyclic);
    }
  }
  // Set color to black
  color[node] = black;
  return acyclic;
}


int dfs(vector<vector<int> > &adj) {
  int size = adj.size(), acyclic = 0;
  vector<int> color(size, white);
  for (int i = 0; i < size; i++) {
    if (color[i] == 0) {
      acyclic = explore(adj, color, i, acyclic);
      if (acyclic) return 1;
    }
  }
  return 0;
}

int acyclic(vector<vector<int> > &adj) {
  return dfs(adj);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
  std::cout << std::endl;
}
