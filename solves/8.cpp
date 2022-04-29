#include<bits/stdc++.h>
#include <iterator>

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

const ulong _mod = 1000000000 + 7;
const string cmap = "-atcoder";

int main(void)
{
  // input
  ulong N; cin >> N;
  string S; cin >> S;
  vector<vector<ulong>> dp(N + 1, vector<ulong>(8, 0)); // [i][j]: 左からi文字目までで`atcoder`のj文字目まで確定した総数
  dp[0][0] = 1;

  rep(ix, N) {
    rep(c, 8) {
      if (c <= 6) dp[ix + 1][c + 1] += (c <= 6 && cmap[c+1] == S[ix]) ? dp[ix][c] : 0;
      dp[ix + 1][c] += dp[ix][c];
    }
    rep(cx, 8) {
      dp[ix+1][cx] %= _mod;
    }
  }

  // print
  cout << dp[N][7] << endl;
  return 0;
}
