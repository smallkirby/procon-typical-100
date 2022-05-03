#include<bits/stdc++.h>
#include <climits>

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

int main(void)
{
  // input
  llong N; cin >> N;
  vector<llong> A(2*N); rep(ix, 2*N) cin >> A[ix];
  vector<vector<llong>> dp(2*N, vector<llong>(2*N, LLONG_MAX)); // dp[left][right]: [left, right]まで取り除いたときの最小コスト
  rep(ix, 2*N-1) dp[ix][ix+1] = abs(A[ix] - A[ix+1]);

  // main
  for (llong size = 3; size <= 2 * N - 1; size += 2) {
    for (llong left = 0; left < 2 * N - 1 && left + size <= 2*N - 1; ++left) {
      llong right = left + size;
      dp[left][right] = min(dp[left][right], dp[left+1][right-1] + abs(A[left] - A[right]));
      for (llong med = left; med != right; ++med) {
        dp[left][right] = min(dp[left][right],
                              dp[left][med] != LLONG_MAX && dp[med+1][right] != LLONG_MAX ? dp[left][med] + dp[med+1][right] : LLONG_MAX);
      }
    }
  }

  // print
  cout << dp[0][2*N-1] << endl;
}
