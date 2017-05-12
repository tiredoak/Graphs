/*
  Given a DAG, output one of its topological orderings
*/

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

enum {white, grey, black};

void explore(vector<vector<int> > &adj, vector<int> &order, 
  vector<int> &color, int node, int &order_index) {
  color[node] = grey;
  for (int i = 0; i < adj[node].size(); i++) {
    if (color[adj[node][i]] == white) {
      explore(adj, order, color, adj[node][i], order_index);
    }
  }
  color[node] = black;
  // This node is a sink so add to last in order
  order[order_index] = node;
  order_index--;
}

vector<int> dfs(vector<vector<int> > &adj) {
  int graph_size = adj.size(), order_index = graph_size - 1;
  vector<int> order(graph_size, 0);
  vector<int> color(graph_size, white);
  for (int i = 0; i < graph_size; i++) {
    if (color[i] == white) {
      explore(adj, order, color, i, order_index);
    }
  }
  return order;
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> order = dfs(adj);
  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
