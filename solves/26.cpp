#include<bits/stdc++.h>
#include <iterator>

#define PI 3.14159265359

using namespace std;

#define rep_(i, a_, b_, a, b, ...) for (int i = (a), i##_len = (b); i < i##_len; ++i)
#define rep(i, ...) rep_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)

using llong = long long;

/******** Utility ***************/

// Calculate (a ^ b) % mod
// O(log`mod`)
llong modpow(llong a, llong b, llong mod) {
  llong p = 1, q = a;
  for (int ix = 0; ix != 30; ++ix) {
    if ((b & (1LL << ix)) != 0) {
      p *= q;
      p %= mod;
    }
    q *= q;
    q %= mod;
  }

  return p;
}

// Calculate inv of a/b under mod, based on Fermat's little theorem
// O(log`mod`)
llong moddiv(llong a, llong b, llong mod) {
  return (a * modpow(b, mod - 2, mod)) % mod;
}

vector<llong> _factorial_memo, _factorial_inv_memo;
void init_factorial_memo(size_t N, llong mod) {
  if (_factorial_memo.empty()) {
    _factorial_memo.resize(N+1, 0);
    _factorial_inv_memo.resize(N+1, 0);
    _factorial_memo[0] = 1;
    for (size_t ix = 1; ix <= N; ++ix)
      _factorial_memo[ix] = (1LL * ix * _factorial_memo[ix - 1]) % mod;
    for (size_t ix = 0; ix <= N; ++ix)
      _factorial_inv_memo[ix] = moddiv(1LL, _factorial_memo[ix], mod);
  }
}

// O(log`mod`)
llong nCr(int n, int r, llong mod) {
  if (n < r || r < 0) return 0;
  if (_factorial_memo.empty()) init_factorial_memo(n, mod);
  return (_factorial_memo[n] * _factorial_inv_memo[r] % mod) * _factorial_inv_memo[n - r] % mod;
}

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

class Node {
  public:
  bool color = false;
  bool visited = false;
  size_t ix = 0;
  vector<size_t> tos;
};

void dfs(vector<Node> &nodes, size_t start, bool color = false) {
  if (nodes[start].visited) return;
  nodes[start].visited = true;
  nodes[start].color = color;
  for (auto to_ix : nodes[start].tos) {
    dfs(nodes, to_ix, !color);
  }
}

ulong count_color(vector<Node> &nodes, bool color) {
  return accumulate(nodes.begin(), nodes.end(), 0UL, [color](ulong cur, const Node &node) {
    return cur + (node.color == color);
  });
}

int main(void)
{
  // input
  ulong N; cin >> N;
  vector<Node> nodes(N); rep(ix, N) nodes[ix].ix = ix;
  rep(ix, N-1) {
    ulong a_ix, b_ix; cin >> a_ix >> b_ix; --a_ix; --b_ix;
    nodes[a_ix].tos.push_back(b_ix);
    nodes[b_ix].tos.push_back(a_ix);
  }

  // main
  dfs(nodes, 0);
  bool color = count_color(nodes, false) >= count_color(nodes, true) ? false : true;
  vector<Node> answer;
  copy_if(nodes.begin(), nodes.end(), back_inserter(answer), [color](const Node &node) {
    return node.color == color;
  });

  // print
  rep(ix, N / 2) {
    cout << answer[ix].ix + 1;
    if (ix == N/2-1) cout << endl;
    else cout << " ";
  }
}
