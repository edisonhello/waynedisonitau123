#include <bits/stdc++.h>
using namespace std;

int ps[4003][3];
const double pi = acos(-1);

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> ps[i][0] >> ps[i][1] >> ps[i][2];
  if (n == 2) {
    cout << 0 << endl;
    exit(0);
  }

  long long mn = LLONG_MAX;
  for (int i = 0; i < n; ++i) {
    // cerr << "i = " << i << endl;
    vector<double> angle(n);
    vector<double> angle2(n);
    vector<int> o;
    for (int j = 0; j < n; ++j) if (i != j) {
      angle[j] = atan2(ps[j][1] - ps[i][1], ps[j][0] - ps[i][0]);
      angle2[j] = angle[j];
      if (angle2[j] < 0) angle2[j] += pi;

      o.push_back(j);
    }
    sort(o.begin(), o.end(), [&] (const int a, const int b) { return angle2[a] < angle2[b]; });

    set<int> up, down;
    long long ups = 0, downs = 0;
    double s1 = angle2[o[0]] - pi, s2 = angle2[o[0]];
    for (int k = 0; k < n; ++k) if (k != i) {
      if (k == o[0]) continue;
      if (s1 <= angle[k] && angle[k] <= s2) down.insert(k), downs += ps[k][2];
      else up.insert(k), ups += ps[k][2];
    }
    
    // cerr << "  order: "; for (int i : o) cerr << i << ' '; cerr << endl;
    // cerr << "  init diff " << abs(ups - downs) << " ups downs " << ups << ' ' << downs << endl;
    // cerr << "    up = "; for (int i : up) cerr << i << ' '; cerr << endl;
    // cerr << "    down = "; for (int i : down) cerr << i << ' '; cerr << endl;
    mn = min(mn, abs(ups - downs));

    for (int i = 1; i < (int)o.size(); ++i) {
      if (angle[o[i - 1]] >= 0) {
        down.insert(o[i - 1]);
        downs += ps[o[i - 1]][2];
      } else {
        up.insert(o[i - 1]);
        ups += ps[o[i - 1]][2];
      }

      if (down.count(o[i])) {
        down.erase(o[i]);
        downs -= ps[o[i]][2];
      } else {
        up.erase(o[i]);
        ups -= ps[o[i]][2];
      }

      // cerr << "   diff " << abs(ups - downs) << ", ups downs " << ups << ' ' << downs << endl;
      // cerr << "     up = "; for (int i : up) cerr << i << ' '; cerr << endl;
      // cerr << "     down = "; for (int i : down) cerr << i << ' '; cerr << endl;

      mn = min(mn, abs(ups - downs));
    }
  }
  cout << mn << endl;
}
