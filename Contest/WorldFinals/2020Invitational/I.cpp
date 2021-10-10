#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-11;

bool same(double x, double y) { return abs(x - y) < eps; }

struct iP {
  int x, y;
};

double Ask(int x, int y) {
  cout << "? " << x << ' ' << y << endl;
  double x;
  cin >> x;
  return x;
}

int main() {
  double dpx = Ask(1, 0);
  double dnx = Ask(-1, 0);
  double dpy = Ask(0, 1);
  double dny = Ask(0, -1);

  double mx = max({dpx, dpy, dnx, dny});
  int cntmx = int(same(dpx, mx)) + int(same(dnx, mx)) +
              int(same(dpy, mx)) + int(same(dny, mx));
  int cnt0 = int(same(dpx, 0)) + int(same(dnx, 0)) + int(same(dpy, 0)) +
             int(same(dny, 0));

  iP s;
  vector<iP> fp;
  if (same(dpx, mx)) fp.push_back(iP{1, 0});
  if (same(dnx, mx)) fp.push_back(iP{-1, 0});
  if (same(dpy, mx)) fp.push_back(iP{0, 1});
  if (same(dny, mx)) fp.push_back(iP{0, -1});
  assert(fp.size() >= 2u);
  fp.resize(2);

  if (same(dnx, 0) && same(dny, 0)) 
    s = iP{(int)dpy, (int)dpx};
  else if (same(dnx, 0) && same(dpy, 0))
    s = iP{(int)dny, -(int)dpx};
  else if (same(dpx, 0) && same(dpy, 0))
    s = iP{-(int)dny, -(int)dnx};
  else 
    s = iP{-(int)dny, (int)dnx};


}
