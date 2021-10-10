#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Zom {
  int t, h, i, p;
};

struct Spik {
  int p, a;
};

int spikes[20000];
vector<Zom> zof[20000];

int32_t main() {
  int n, m, V, K, D; cin >> n >> m >> V >> K >> D;
  
  vector<Zom> zombies;
  for (int i = 0; i < n; ++i) {
    int t, h; cin >> t >> h;
    zombies.push_back(Zom{t, h, i, 0});
  }

  for (int i = 0; i < m; ++i) {
    int p, a; cin >> p >> a;
    spikes[p] += a;
  }

  sort(zombies.begin(), zombies.end(), [&] (const auto a, const auto b) { return make_pair(a.t, a.i) < make_pair(b.t, b.i); });
  reverse(zombies.begin(), zombies.end());

  vector<int> deadtime(n, 0);
  int deadcount = 0;

  for (int second = 1; deadcount < n; ++second) {
    // cerr << "second " << second << endl;
    while (zombies.size() && zombies.back().t == second) {
      zof[0].push_back(zombies.back());
      zombies.pop_back();
    }

    for (int i = 10000; i >= 0; --i) {
      for (auto z : zof[i]) {
        // cerr << "check pos " << i << endl;
        for (int j = i + 1; j <= i + V; ++j) z.h -= spikes[j];
        if (z.h <= 0) {
          deadtime[z.i] = second;
          ++deadcount;
        } else {
          zof[i + V].push_back(z);
        }
      }
      zof[i].clear();
    }

    for (int i = 0; i < K; ++i) {
      // cerr << "shoot " << i << endl;
      for (int j = 10000; j >= 1; --j) {
        if (zof[j].size()) {
          zof[j][0].h -= D;
          if (zof[j][0].h <= 0) {
            deadtime[zof[j][0].i] = second;
            ++deadcount;
            zof[j].erase(zof[j].begin());
          }
          break;
        }
      }
    }
  }

  for (int i : deadtime) cout << i << ' ';
  cout << endl;


}
