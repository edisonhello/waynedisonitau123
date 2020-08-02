#include <bits/stdc++.h>
using namespace std;

struct Group {
  int since, nowrank;
  long long sum;
};

int pre[300005];
long long sumrank[300005];
int bel[300005];
Group group[300005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, w; cin >> n >> w;

  for (int i = 0; i <= 300000; ++i) pre[i] = 1;
  group[0].since = 1;
  group[0].nowrank = 1;

  auto UpdateGroup = [&] (int g, int i) {
    if (group[g].since == i) return;
    // cerr << "update group " << g << " on time " << i << endl;
    group[g].sum += (i - group[g].since) * 1ll * group[g].nowrank;
    group[g].since = i;
    // cerr << "sum => " << group[g].sum << endl;
  };
  for (int i = 1; i <= w; ++i) {
    // cerr << "week " << i << endl;
    auto AddPoint = [&] (int x) {
      int g = bel[x];
      UpdateGroup(g, i);
      UpdateGroup(g + 1, i);
      sumrank[x] += group[g].sum;
      sumrank[x] -= group[g + 1].sum;
      ++group[g].nowrank;
      ++pre[g];
      // Add(g, -1);

      ++g;
      // Add(g, 1);
      bel[x] = g;
      // group[g].nowrank = Query(g + 1) + 1;
      group[g].nowrank = pre[g];
    };

    int c; cin >> c;
    while (c--) {
      int x; cin >> x;
      AddPoint(x);
    }
  }

  for (int i = 1; i <= n; ++i) {
    int g = bel[i];
    UpdateGroup(g, w + 1);
    sumrank[i] += group[g].sum;
    cout << fixed << setprecision(12) << (double)(sumrank[i]) / w << '\n';
  }

}
