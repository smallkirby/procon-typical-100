#include<bits/stdc++.h>
#include <numeric>

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

int main(void)
{
  // input
  ulong H,W; cin >> H >> W;
  vector<vector<ulong>> A(H, vector<ulong>(W));
  rep(h, H) rep(w, W) cin >> A[h][w];

  // main
  vector<ulong> row_sums(H), col_sums(W);
  rep(h, H) {
    row_sums[h] = accumulate(A[h].begin(), A[h].end(), 0);
  }
  rep(w, W) {
    ulong col_sum = 0;
    rep(h, H) {
      col_sum += A[h][w];
    }
    col_sums[w] = col_sum;
  }

  // print
  rep(h, H) {
    rep(w, W) {
      cout << row_sums[h] + col_sums[w] - A[h][w];
      if (w != W - 1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}
