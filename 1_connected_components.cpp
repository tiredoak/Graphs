/*
  Given an undirected graph with n vertices and m edges
  compute the number of connected components.
  Runs depth first search and keeps a clock, increasing it
  whenever finishing exploring a connected component.

  Input: a graph given in the standard format
         1 <= n <= 10^3, 0 <= m <= 10^3
  Output: number of connected components.
*/

#include <iostream>
#include <vector>
#include <utility> // for pair initialisation

using std::vector;
using std::pair;

// Depth first search
void explore(vector<vector<int> > &adj, vector<pair<int, bool> > &visited, int v, int cc) {
	// Mark as visited
	visited[v].second = true;
	// Set connected component
	visited[v].first = cc;
	for (int i = 0; i < adj[v].size(); i++) {
		if (visited[adj[v][i]].second == false) {
			explore(adj, visited, adj[v][i], cc);
		}
	}
}

int number_of_components(vector<vector<int> > &adj) {
  vector<pair<int, bool> > visited (adj.size(), std::make_pair(0, false));
  int cc = 0;
  for (int i = 0; i < adj.size(); i++){
  	if (visited[i].second == false) {
  		explore(adj, visited, i, cc);
  		cc++;
  	}
  }
  return cc;
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
  std::cout << number_of_components(adj);
  std::cout << std::endl;
}
