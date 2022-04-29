#include <algorithm>
#include<bits/stdc++.h>
#include <iomanip>
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

class Point {
  public:

  long long x, y;

  Point() {
    this->x = 0.0;
    this->y = 0.0;
  }
  Point(long long x, long long y) {
    this->x = x;
    this->y = y;
  }

  Point operator-(const Point &ohr) const noexcept {
    return Point{this->x - ohr.x, this->y - ohr.y};
  }
  Point operator+(const Point &ohr) const noexcept {
    return Point{this->x + ohr.x, this->y + ohr.y};
  }
  bool operator==(const Point &ohr) const noexcept {
    return this->x == ohr.x && this->y == ohr.y;
  }
  friend ostream& operator<<(ostream &out, const Point& it) {
    return out << "(" << it.x << "," << it.y << ")";
  }

  double angle() const {
    const auto tmp = (atan2((double)this->y, (double)this->x) * 360.0) / (2.0 * PI);
    return tmp >= 0 ? tmp : 360.0 + tmp;
  }
};

vector<Point> get_vecs(const Point &center, const vector<Point> &points) {
  vector<Point> vecs;
  rep(ix, points.size()) {
    if (points[ix] == center) continue;
    vecs.push_back(points[ix] - center);
  }
  return vecs;
}

double maxangle(size_t center, const vector<Point> &points) {
  auto vecs = get_vecs(points[center], points);
  vector<double> angles;
  transform(vecs.begin(), vecs.end(), back_inserter(angles), [](const Point &v) { return v.angle(); });
  //show(vecs);
  //show(angles);
  sort(angles.begin(), angles.end());

  double _max = 0;
  rep(ix, angles.size()) {
    auto base = angles[ix] + 180.0;
    base = base >= 360.0 ? base - 360.0 : base;
    auto bound = lower_bound(angles.begin(), angles.end(), base);

    double p1 = abs((bound == angles.begin() ? angles[ix] : *(bound-1)) - angles[ix]);
    double p2 = abs((bound == angles.end() ? angles[ix] : *bound) - angles[ix]);
    p1 = p1 >= 180.0 ? 360.0 - p1 : p1;
    p2 = p2 >= 180.0 ? 360.0 - p2 : p2;
    _max = max(_max, max(p1, p2));
  }

  return _max;
}

int main(void)
{
  // input
  long long N; cin >> N;
  vector<Point> points(N);
  rep(ix, N) cin >> points[ix].x >> points[ix].y;

  // main
  double _max = 0.0;
  rep(ix, N) {
    _max = max(_max, maxangle(ix, points));
  }

  // print
  cout << fixed << setprecision(10) << _max << endl;
}
