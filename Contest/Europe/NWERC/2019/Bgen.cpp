#include <bits/stdc++.h>
using namespace std;

int p[1000], l[1000], r[1000];
int dep[1000];
vector<int> id;

bool dfs(int now) {
  int lc = l[now], rc = r[now];

  if (!lc && !rc) {
    dep[now] = 0;
    id.push_back(now);
    return 1;
  }

  if (lc && !dfs(lc)) return 0;
  id.push_back(now);
  if (rc && !dfs(rc)) return 0;

  if (!lc && dep[rc] > 0) return 0;
  if (!rc && dep[lc] > 0) return 0;
  if (abs(dep[lc] - dep[rc]) > 1) return 0;

  // cerr << "now = " << now << " lc rc " << lc << ' ' << rc << " deps " << dep[lc] << ' ' << dep[rc] << endl;
  dep[now] = max(dep[lc], dep[rc]) + 1;
  return 1;
}

int main() {
  srand(clock() * time(0) * clock());

  int n = 16;
  int k = rand() % (n - 1) + 1;
  cout << n << ' ' << k << endl;

  while (true) {
    memset(p, 0, sizeof(p));
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    memset(dep, 0, sizeof(dep));

    bool ok = 1;

    vector<int> per(n);
    iota(per.begin(), per.end(), 1);
    random_shuffle(per.begin(), per.end());

    p[per[0]] = -1;
    for (int i = 1; i < n; ++i) p[per[i]] = per[rand() % i];

    int root = -1;
    for (int i = 1; i <= n; ++i) {
      if (p[i] != -1) {
        if (p[i] < i) {
          if (r[p[i]]) { ok = 0; break; }
          r[p[i]] = i;
        } else {
          if (l[p[i]]) { ok = 0; break; }
          l[p[i]] = i;
        }
      } else root = i;
    }

    id.clear();
    if (!dfs(root)) ok = 0;

    if (ok) {
      // for (int i = 1; i <= n; ++i) cerr << "i p[i] " << i << ' ' << p[i] << endl;
      // cerr << "id: ";
      // for (int i : id) cerr << i << ' ';
      // cerr << endl;
      vector<int> pos(n + 1);
      for (int i = 0; i < n; ++i) pos[id[i]] = i + 1;

      for (int i = 0; i < n; ++i) {
        if (p[id[i]] == -1) cout << -1 << endl;
        else cout << pos[p[id[i]]] << endl;
      }
      break;
    }
  }
}
