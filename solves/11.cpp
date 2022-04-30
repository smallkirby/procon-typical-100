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

struct Task {
  ulong deadline;
  ulong consume;
  ulong score;
};

/*
  O(N * max_deadline) <= O(10**7)
*/

int main(void)
{
  // input
  ulong N; cin >> N;
  vector<Task> tasks(N);
  rep (ix, N) cin >>  tasks[ix].deadline >> tasks[ix].consume >> tasks[ix].score;
  sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
    return a.deadline < b.deadline;
  });
  const ulong max_deadline = tasks[N-1].deadline;

  // main
  vector<vector<ulong>> dp(N+1, vector<ulong>(max_deadline+1, 0)); // dp[i][j]: i個目のtaskまで見たときにj日使った場合の最大スコア
  for (ulong ix = 0; ix != N; ++ix) {
    for (ulong day = 0; day != max_deadline+1; ++day) {
      if (day < tasks[ix].consume || day > tasks[ix].deadline) {
        // discard the job
        dp[ix+1][day] = dp[ix][day];
      } else {
        // work on the job if the score is large enough
        dp[ix+1][day] = max(dp[ix][day - tasks[ix].consume] + tasks[ix].score, dp[ix][day]);
      }
    }
  }

  // print
  ulong _max = 0;
  rep(day, max_deadline+1) _max = max(_max, dp[N][day]);
  cout << _max << endl;
}
