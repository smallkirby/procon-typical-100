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

struct Person {
  unsigned cls;
  ulong score;
};

int main(void)
{
  // input
  ulong N; cin >> N;
  vector<Person> persons(N);
  rep(ix, N) cin >> persons[ix].cls >> persons[ix].score;

  vector<ulong> sums1(N+1), sums2(N+1);
  rep(ix, N) {
    if (persons[ix].cls == 1) {
      sums1[ix+1] = sums1[ix] + persons[ix].score;
      sums2[ix+1] = sums2[ix];
    } else {
      sums2[ix+1] = sums2[ix] + persons[ix].score;
      sums1[ix+1] = sums1[ix];
    }
  }
  //show(sums1);
  //show(sums2);

  // main
  ulong Q; cin >> Q;
  rep(q, Q) {
    ulong l, r; cin >> l >> r;

    cout << (sums1[r] - sums1[l-1]) << " ";
    cout << (sums2[r] - sums2[l-1]) << endl;
  }

  // print
}
