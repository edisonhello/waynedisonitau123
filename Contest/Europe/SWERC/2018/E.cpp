#include <bits/stdc++.h>
using namespace std;

string name[10005];
int pt[10005];
int lr[10005][2];

void NO() {
  cout << "IMPOSSIBLE" << endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> name[i] >> pt[i];
  for (int i = 1; i <= n; ++i) lr[i][0] = max(pt[i] * 100 - 50, 0), lr[i][1] = min(pt[i] * 100 + 49, 10000);
  for (int i = 1; i <= n; ++i) {
    int ls = 0, rs = 0;
    for (int j = 1; j <= n; ++j) if (j != i) {
      ls += pt[j] * 100 - 50;
      rs += pt[j] * 100 + 49;
    }
    int r = 10000 - ls;
    int l = 10000 - rs;
    lr[i][0] = max(lr[i][0], l);
    lr[i][1] = min(lr[i][1], r);
    if (lr[i][0] > lr[i][1]) NO();
  }

  for (int i = 1; i <= n; ++i) {
    printf("%s %d.%02d %d.%02d\n", name[i].c_str(), lr[i][0] / 100, lr[i][0] % 100, lr[i][1] / 100, lr[i][1] % 100);
  }

}
