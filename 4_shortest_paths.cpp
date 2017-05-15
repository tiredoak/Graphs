/*
  Given a directed with possibly negative edge weights and with
  n vertices and m edges, compute the length of the shortest paths
  from s to all other vertices of the graph.
  Use Bellman-Ford and if after V - 1 iteration there are still
  edges to relax, there is a negative cycle. Find these vertices
  and run breadth first search from them to find the vertices
  for which infinite arbitrage is possible.

  Input: graph given in the standard format
         1 <= n <= 10^3, 0 <= m <= 10^4
         edge weights are integers of absolute value at most 10^9
  Output: For all vertices i from 1 to n output the following
          on a separate line:
            "*" if there is no path s to u
            "-" if there is a path s to u, but there is no shortest
            path from s to u (that is, the distance from s to u is 
            -infinity)
            length of the shortest path otherwise
*/

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void bfs(vector<vector<int> > &adj, queue<int> q, vector<bool> &shortest) {
  int size = adj.size();
  vector<bool> visited(size, false);
  while (!q.empty()) {
    int v = q.front();
    if (visited[v]) {
      q.pop();
    } else {
      q.pop();
      for (int i = 0; i < adj[v].size(); i++) {
        shortest[adj[v][i]] = true;
        q.push(adj[v][i]);
      }
    }
    visited[v] = true;
  }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<long long> > &cost, int s, 
  vector<long long> &distance, vector<bool> &reachable, vector<bool> &shortest) {
  int size = adj.size();
  distance[s] = 0;
  reachable[s] = true;
  queue<int> negative_cycle;
  // Set initial distances and get negative cycles
  for (int i = 0; i <= size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        // Edge relaxation
        if (distance[adj[j][k]] > distance[j] + cost[j][k]) {
          reachable[adj[j][k]] = true;
          if (i == size) {
            // Store negative cycles
            negative_cycle.push(adj[j][k]);
            shortest[adj[j][k]] = true;
          }
          distance[adj[j][k]] = distance[j] + cost[j][k];
        }
      }
    }
  }
  bfs(adj, negative_cycle, shortest);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<long long> > cost(n, vector<long long>());
  for (int i = 0; i < m; i++) {
    long long x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, 100000000000000);
  vector<bool> reachable(n, false);
  vector<bool> shortest(n, false);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
