/*
  Given an undirected graph with n vertices and m edges, and 
  two vertices u and v, compute the length of the shortest path
  between u and v.
  The idea is simply to traverse graph using breadth first
  search (bfs) starting at u and record its distance to other
  vertices in the graph.

  Input: graph given in the standard format.
         next line contains vertices u and v.
         2 <= n <= 10^5, 0 <= m <= 10^5, u != v, 1 <= u, v <= n
  Output: minimum number of edges between u and v or -1 if there
          is no path.
*/

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  vector<int> distance(adj.size(), -1);
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
      }
    }
  }
  return distance[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
  std::cout << std::endl;
}
