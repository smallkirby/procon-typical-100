#include <algorithm>
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

int main(void)
{
  // input
  ulong N; cin >> N;
  vector<ulong> A(N); rep(ix, N) cin >> A[ix]; // house
  vector<ulong> B(N); rep(ix, N) cin >> B[ix]; // school
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // main
  ulong result = 0;
  rep(ix, N) result += A[ix] > B[ix] ? A[ix] - B[ix] : B[ix] - A[ix];

  // print
  cout << result << endl;
}
