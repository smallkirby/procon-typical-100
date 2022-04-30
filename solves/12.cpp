#include<bits/stdc++.h>

#define ULMAX (ulong)(-1L)
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

class UnionFindTree {
  private:

  vector<size_t> pnodes; // parent of each nodes
  size_t H, W;

  public:

  UnionFindTree (size_t H, size_t W) {
    pnodes = vector<size_t>(H * W, ULMAX);
    this->H = H;
    this->W = W;
  }

  //void show_parents(bool do_transform = true) {
  //  cout << "**************" << endl;
  //  rep(h, H) {
  //    rep(w, W) {
  //      if (do_transform) cout << (pnodes[h * W + w] == ULLONG_MAX ? "X": to_string(root(pnodes[h * W + w]))) << " ";
  //      else cout << pnodes[h * W + w] << " ";
  //    }
  //    cout << endl;
  //  }
  //}

  size_t root(size_t ix) {
    if (pnodes[ix] == ix) return ix;
    else {
      return pnodes[ix] = root(pnodes[ix]); // ついでに経路圧縮
    }
  }

  void paint(size_t h, size_t w) {
    h--; w--;
    ulong ix = h*W+w, tmp;
    pnodes[ix] = ix;
    //cout << this->H << ", " << this->W << endl;
    //cout << h << ", " << w << endl;
    //cout << "***" << h * this->W + w << endl;;

    tmp = (h-1) * W + w;
    if (h != 0 && pnodes[tmp] != ULMAX) {
      //cout << "top" << endl;
      pnodes[root(pnodes[tmp])] = ix;
    }
    tmp = h * W + (w-1);
    if (w != 0 && pnodes[tmp] != ULMAX) {
      //cout << "left" << endl;
      pnodes[root(pnodes[tmp])] = ix;
    }
    tmp = (h+1) * W + w;
    if (h != H - 1 && pnodes[tmp] != ULMAX) {
      //cout << "bottom" << endl;
      pnodes[root(pnodes[tmp])] = ix;
    }
    tmp = h * W + (w+1);
    if (w != W - 1 && pnodes[tmp] != ULMAX) {
      //cout << "right" << endl;
      pnodes[root(pnodes[tmp])] = ix;
    }
  }

  bool is_connectable(size_t r1, size_t c1, size_t r2, size_t c2) {
    --r1;--c1;--r2;--c2;
    size_t ix = r1 * W + c1;
    size_t jx = r2 * W + c2;
    if (pnodes[ix] == ULMAX || pnodes[jx] == ULMAX) return false;
    size_t iroot = root(ix), jroot = root(jx);
    return iroot != ULMAX && iroot == jroot;
  }
};

int main(void)
{
  // input
  ulong H,W; cin >> H >> W;
  UnionFindTree tree(H, W);
  ulong Q; cin >> Q;

  // main
  rep(q, Q) {
    unsigned typ;
    cin >> typ;
    switch(typ) {
      case 1:
        unsigned r,c; cin >> r >> c;
        tree.paint(r, c);
        //tree.show_parents();
        break;
      case 2:
        unsigned r1,r2,c1,c2; cin >> r1 >> c1 >> r2 >> c2;
        if (tree.is_connectable(r1, c1, r2, c2)) cout << "Yes" << endl;
        else cout << "No" << endl;
        break;
      default:
        throw runtime_error("unexpected typ");
    }
  }

  // print
}
