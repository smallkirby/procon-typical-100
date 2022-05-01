#include<bits/stdc++.h>
#include <climits>
#include <queue>

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

class Edge {
  public:

  size_t to;
  ulong weight;

  Edge(size_t to, ulong weight) {
    this->to = to;
    this->weight = weight;
  }
};

class Node {
  public:

  vector<Edge> tos;
  ulong current_min_weight = ULONG_MAX;
};

// O(MlogN) <= O(10**6)

void dijkstra(vector<Node> &nodes, size_t start) {
  class Waiter {
    public:
    size_t ix;
    ulong min_weight;
    Waiter(size_t ix, ulong min_weight) {
      this->ix = ix;
      this->min_weight = min_weight;
    }
  };
  const auto compare = [](const Waiter &n1, const Waiter &n2) {
    return n1.min_weight > n2.min_weight;
  };
  priority_queue<Waiter, vector<Waiter>, decltype(compare)> waiting { compare };

  waiting.emplace(Waiter { start, 0 });
  nodes[start].current_min_weight = 0;
  while (!waiting.empty()) {
    const auto waiter = waiting.top();
    waiting.pop();
    //cout << waiter.ix << ": (size)" << waiting.size() << ": (min_weight)" << waiter.min_weight << ": (current_min_weight)" << nodes[waiter.ix].current_min_weight << endl;

    if (waiter.min_weight > nodes[waiter.ix].current_min_weight) continue;
    for (auto &to_edge : nodes[waiter.ix].tos) {
      auto to_node = &nodes[to_edge.to];
      if (to_node->current_min_weight > nodes[waiter.ix].current_min_weight + to_edge.weight) {
        to_node->current_min_weight = nodes[waiter.ix].current_min_weight + to_edge.weight;
        waiting.emplace(Waiter { to_edge.to, to_node->current_min_weight });
      }
    }
  }
}

int main(void)
{
  // input
  ulong N, M; cin >> N >> M;
  vector<Node> nodes(N);
  rep(m, M) {
    ulong a,b,c; cin >> a >> b >> c; --a;--b;
    nodes[a].tos.push_back(Edge { b, c });
    nodes[b].tos.push_back(Edge { a, c });
  }

  vector<Node> nodes_zero_start = nodes;
  vector<Node> nodes_last_start = nodes;

  // main
  dijkstra(nodes_zero_start, 0);
  dijkstra(nodes_last_start, N-1);

  // print
  rep(ix, N) {
    cout << nodes_zero_start[ix].current_min_weight + nodes_last_start[ix].current_min_weight << endl;
  }
  //rep(ix, N) {
  //  cout << ix + 1 << ": " << nodes_zero_start[ix].current_min_weight << endl;
  //}
  //rep(ix, N) {
  //  cout << N - ix << ": " << nodes_last_start[N-ix-1].current_min_weight << endl;
  //}
}
