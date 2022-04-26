#include <bits/stdc++.h>

#define IMAX 1 << 29
#define PI 3.14159265359

using namespace std;

#define rep_(i, a_, b_, a, b, ...) for (int i = (a), i##_len = (b); i < i##_len; ++i)
#define rep(i, ...) rep_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)

template <typename T>
void show(vector<T> v)
{
  for (auto _v : v)
    cout << _v << " ";
  cout << endl;
}

template <typename T>
void show(vector<T> v, int maxrow) // 適度に改行入れるver
{
  for (int ix = 0; ix != v.size(); ++ix)
  {
    if (ix != 0 && ix % maxrow == 0)
      cout << endl;
    cout << v[ix] << " ";
  }
  cout << endl;
}

template <typename T>
void show2(vector<vector<T>> v)
{
  int ix = 0;
  for (auto __v : v)
  {
    cout << "[" << ix++ << "] (";
    for (auto _v : __v)
    {
      cout << _v << ", ";
    }
    cout << ")" << endl;
  }
}

/******** end of Utility ***************/

// check if all pieces can be longer than `_min`
bool check(vector<ulong> &A, ulong _min, ulong k, ulong L)
{
  ulong current = 0;
  auto p = A.begin();
  ulong count = 0;
  while (p < A.end() && count < k)
  {
    if (*p - current >= _min)
    {
      current = *p;
      ++count;
    }

    ++p;
  }
  // cout << _min << ": " << count << " (" << current << ")" << endl;
  if (L - current < _min)
    return false;
  if (count >= k)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int main(void)
{
  // input
  ulong N, L, K;
  cin >> N >> L >> K;
  vector<ulong> A(N);
  rep(ix, N)
  {
    cin >> A[ix];
  }
  sort(A.begin(), A.end());

  // main
  size_t left = 0, right = L;
  size_t result = 0;
  while (left <= right)
  {
    // cout << "[" << left << ", " << right << "]" << endl;
    size_t l = (right + left) / 2;
    if (check(A, l, K, L))
    {
      left = l + 1;
      result = max(result, l);
    }
    else
    {
      right = l - 1;
    }
  }

  // print
  cout << result << endl;
}
