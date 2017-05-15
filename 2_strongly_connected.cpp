/*
  Computes the number of strongly connected components in a 
  directed graph with n vertices and m edges.
  The key idea is that source components of the reverse graph
  (Gr) are sink components of the original graph (G). To find
  sink components of G, we run DFS on Gr.

  Input: a graph in the standard format
         1 <= n <= 10^4, 0 <= m <= 10^4
  Output: number of strongly connected components
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

enum {white, grey, black};

bool pair_compare(const pair<int, int> &a, const pair<int, int> &b) {
  return b.second < a.second;
}

void get_post(vector<vector<int> > &adj, vector<int> &color, 
  vector<pair<int, int> > &post, int node, int &clock) {
  post[node].first = node;
  clock++;
  color[node] = grey;
  for (int i = 0; i < adj[node].size(); i++) {
    if (color[adj[node][i]] == white) {
      get_post(adj, color,post, adj[node][i], clock);
    }
  }
  color[node] = black;
  post[node].second = clock;
  clock++;
}

vector<pair<int, int> > get_reverse_post(vector<vector<int> > &reverse) {
  int size = reverse.size(), clock = 0;
  vector<pair<int, int> > post(size, std::make_pair(0, 0));
  vector<int> color(size, white);
  for (int i = 0; i < size; i++) {
    if (color[i] == white) {
      get_post(reverse, color, post, i, clock);
    }
  }
  std::sort(post.begin(), post.end(), pair_compare);
  return post;
}

void get_scc(vector<vector<int> > &adj, vector<int> &color, 
  int node, vector<int> &scc_list, int &scc) {
  color[node] = grey;
  for (int i = 0; i < adj[node].size(); i++) {
    if (color[adj[node][i]] == white) {
      get_scc(adj, color, adj[node][i], scc_list, scc);
    }
  }
  color[node] = black;
  scc_list[node] = (scc_list[node] != 0) ? scc : scc_list[node];
}

int number_of_strongly_connected_components(vector<vector<int> > &adj, 
  vector<vector<int> > &reverse) {
  int scc = 0, size = adj.size();
  // Gets order in which to traverse graph
  vector<pair<int, int> > order = get_reverse_post(reverse);  
  
  vector<int> color(size, white);
  vector<int> scc_list(size, 0);
  for (int i = 0; i < size; i++) {
    if (color[order[i].first] == white) {
      get_scc(adj, color, order[i].first, scc_list, scc);
      scc++;
    }
  }
  return scc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > reverse(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    reverse[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, reverse);
  std::cout << std::endl;
}
