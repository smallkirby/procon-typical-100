#include<bits/stdc++.h>

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

bool check(unsigned n, unsigned N) {
  unsigned open = 0;
  const unsigned limit = N/2;
  for (unsigned ix = 0; ix != N; ++ix) {
    if ((n & (1 << ix)) != 0) { // open
      ++open;
      if (open > limit) return false;
    } else { // close
      if (open == 0) return false;
      --open;
    }
  }
  return open == 0;
}

string print(unsigned n, unsigned N) {
  string s;
  for (unsigned ix = 0; ix != N; ++ix) {
    if ((n &(1 << ix)) != 0) {
      s += '(';
    } else {
      s += ')';
    }
  }
  return s;
}

// O(2^N * N) <= O(10^7)

int main(void)
{
  // input
  unsigned N; cin >> N;

  if (N % 2 != 0) {
    return 0;
  }

  // main
  vector<string> results;
  for (unsigned n = 0; n != (1 << N); ++n) {
    if (check(n, N)) results.push_back(print(n, N));
  }

  sort(results.begin(), results.end());
  rep(ix, results.size()) {
    cout << results[ix] << endl;
  }
}
