#include <algorithm>
#include<bits/stdc++.h>
#include <functional>

#define IMAX 1<<29
#define PI 3.14159265359

using namespace std;

#define rep_(i, a_, b_, a, b, ...) for (int i = (a), i##_len = (b); i < i##_len; ++i)
#define rep(i, ...) rep_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)

/******** Utility ***************/

template<typename T>
void show(vector<T> v)
{
  for(auto _v: v)
    cout << _v << " ";
  cout << endl;
}

template<typename T>
void show(vector<T> v, int maxrow)    // 適度に改行入れるver
{
  for(int ix=0; ix!=v.size(); ++ix){
    if(ix!=0 && ix%maxrow==0)
      cout << endl;
    cout << v[ix] << " ";
  }
  cout << endl;
}

template<typename T>
void show2(vector<vector<T>> v)
{
  int ix = 0;
  for(auto __v: v){
    cout << "[" << ix++ << "] (";
    for(auto _v: __v){
      cout << _v << ", ";
    }
    cout << ")" << endl;
  }
}

/******** end of Utility ***************/

/*
N頂点に対して(N-1)辺 && 全て到達可能 だから、閉路なし?
*/

struct Node {
  bool is_visited;
  vector<size_t> tos;
  size_t depth;
};

void clear(vector<struct Node> &graph) {
  for (auto &node : graph) {
    node.depth = 0;
    node.is_visited = false;
  }
}

void dfs(vector<struct Node> &graph, size_t current, ulong depth) {
  graph[current].is_visited = true;
  graph[current].depth = depth;

  vector<ulong> lengthes;
  for (auto to : graph[current].tos) {
    if (!graph[to].is_visited) {
      dfs(graph, to, depth + 1);
    }
  }
}

void show_depth(vector<struct Node> &graph) {
  for (auto &node : graph) {
    cout << node.depth << endl;
  }
}

int main(void)
{
  // input
  ulong N; cin >> N;
  vector<struct Node> nodes(N);
  rep(_, N - 1) {
    size_t a,b;
    cin >> a >> b;
    nodes[a-1].tos.push_back(b-1);
    nodes[b-1].tos.push_back(a-1);
  }

  // main
  clear(nodes);
  dfs(nodes, 0, 0);
  ulong _max = 0;
  size_t start;
  for (int ix = 0; ix != nodes.size(); ++ix) {
    _max = max(nodes[ix].depth, _max);
    if (_max == nodes[ix].depth) start = ix;
  }

  clear(nodes);
  dfs(nodes, start, 0);
  for (int ix = 0; ix != nodes.size(); ++ix) {
    _max = max(nodes[ix].depth, _max);
  }
  cout << _max + 1 << endl;
}
