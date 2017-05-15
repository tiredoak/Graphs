/* 
  Given a directed graph with positive edge weights and with n
  vertices and m edges as well two vertices u and v, compute the 
  weight of the shortest path between u and v.
  Implementation of Dijkstra's algorithm.
  Input: graph given in the standard format.
         next line contains two vertices u and v
         1 <= n <= 10^3, 0 <= m <= 10^5, u != v 
         1 <= u, v <= n
  Output: minimum weight of a path from u to v or -1 if there
          is no path.
*/

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

// Used to sort the priority queue in reverse order
class compare_pair {
public: 
  bool operator()(pair<int, int> a, pair<int, int> b) {
    return b.first < a.first;
  }
};

int dijkstra(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  int size = adj.size();
  // Constraint says max value is 10^5
  int infinity = 100001;
  vector<int> dist(size, infinity);
  // Not changing priority of items in queue, instead adding them again
  // visited is used to check to keep track of these "fake" node pairs
  vector<bool> visited(size, false);
  dist[s] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, compare_pair> min_queue;
  min_queue.push(std::make_pair(0, s));
  while (!min_queue.empty()) {
    int u = min_queue.top().second;
    // Check if it's a "fake" pair of nodes
    if (visited[u] == true) {
      min_queue.pop();  
      continue; 
    }
    min_queue.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      // Edge relaxation procedure
      if (dist[adj[u][i]] > dist[u] + cost[u][i]) {
        dist[adj[u][i]] = dist[u] + cost[u][i];
        // Using "lazy deletion" by simply adding the node again with
        // updated distance
        min_queue.push(std::make_pair(dist[adj[u][i]], adj[u][i]));
      }
    }
    visited[u] = true;
  }
  return (dist[t] == infinity) ? -1 : dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << dijkstra(adj, cost, s, t);
  std::cout << std::endl;
}
