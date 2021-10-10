#include <bits/stdc++.h>
using namespace std;

#define int long long 

struct Z {
  int t, h, i;
};

struct S {
  int p, a;
};

int32_t main() {
  int n, m, V, K, D; cin >> n >> m >> V >> K >> D;
  vector<Z> zs(n);
  vector<S> spikes(m);
  for (int i = 0; i < n; ++i) {
    int t, h; cin >> t >> h;
    zs[i] = Z{t, h, i};
  }

  vector<pair<int, int>> spike_list;
  for (int i = 0; i < m; ++i) {
    int p, a;
    cin >> p >> a;
    spikes[i] = S{p, a};

    int spike_hurt_sec = (p - 1) / V + 1;
    spike_list.emplace_back(spike_hurt_sec, a);
  }

  sort(spike_list.begin(), spike_list.end());
  // cerr << "spike_list:" << endl;
  // cerr << spike_list[0].first <<  ' ' << spike_list[0].second << endl;
  for (int i = 1; i < (int)spike_list.size(); ++i) {
    spike_list[i].second += spike_list[i - 1].second;
    // cerr << spike_list[i].first << ' ' << spike_list[i].second << endl;
  }



  auto get_only_spike_damage = [&] (const int l, const int r) -> long long {
    if (l > r) return 0;
    if (r < spike_list[0].first) return 0;
    if (l > spike_list.back().first) return 0;
    int rr = prev(upper_bound(spike_list.begin(), spike_list.end(), make_pair(r + 1, (int)-1)))->second;
    auto it = lower_bound(spike_list.begin(), spike_list.end(), make_pair(l, (int)-1));
    int ll = it == spike_list.begin() ? 0 : prev(it)->second;
    // cerr << "        get _only spike daage fro " << l << " to " << r << " damage: " << ll << " " << rr << " -> " << rr - ll << endl;
    return rr - ll;
  };

  sort(zs.begin(), zs.end(), [&] (const Z a, const Z b) {
    return make_pair(a.t, a.i) < make_pair(b.t, b.i);
  });

  int peasec = 1, pealeft = K;

  vector<int> deadtime(n, 0);

  for (auto zomb : zs) {
    // cerr << "zomb i t h " << zomb.i << ' ' << zomb.t << ' ' << zomb.h << endl;
    // cerr << "peasec " << peasec << endl;
    if (zomb.t > peasec) {
      peasec = zomb.t;
      pealeft = K;
    }

    int only_spike_sec = peasec - 1 - (zomb.t - 1);

    int only_spike_damage = get_only_spike_damage(1, only_spike_sec);

    // cerr << "only_spike sec damage " << only_spike_sec << ' ' << only_spike_damage << endl;
    if (only_spike_damage >= zomb.h) {
      int L = 1, R = only_spike_sec;
      while (L < R) {
        int M = (L + R) >> 1;
        int d = get_only_spike_damage(1, M);
        if (d < zomb.h) L = M + 1;
        else R = M;
      }

      deadtime[zomb.i] = zomb.t - 1 + L;
    } else {
      zomb.h -= only_spike_damage;
      // cerr << "  h become " << zomb.h << endl;

      int L = 0, R = 1000000000 / K + 1;
      while (L < R) {
        int M = (L + R + 1) >> 1;
        int d = get_only_spike_damage(only_spike_sec + 1, only_spike_sec + M) + ((M - 1) * K + pealeft) * D;
        if (d >= zomb.h) R = M - 1;
        else L = M;
      }

      // cerr << "  can hold extra " << L << " seconds before die" << endl;
      // cerr << "  spike damage " << get_only_spike_damage(only_spike_sec + 1, only_spike_sec + L) << " pea damage " << ((L - 1) * K + pealeft) * D << endl;

      if (L) {
        zomb.h -= get_only_spike_damage(only_spike_sec + 1, only_spike_sec + L) + ((L - 1) * K + pealeft) * D;
        // cerr << "peasec " << peasec << " to " << zomb.t - 1 + only_spike_damage + L + 1 << endl;
        peasec = zomb.t - 1 + only_spike_sec + L + 1;
        pealeft = K;
      }

      // cerr << "  h become " << zomb.h << endl;
      assert(zomb.h > 0);

      // cerr << "  dead second spike damage " << get_only_spike_damage(only_spike_sec + L + 1, only_spike_sec + L + 1) << endl;
      zomb.h -= get_only_spike_damage(only_spike_sec + L + 1, only_spike_sec + L + 1);

      // cerr << "  h become " << zomb.h << endl;

      if (zomb.h > 0) {
        int peahit = (zomb.h + (D - 1)) / D;
        assert(peahit <= pealeft);
        pealeft -= peahit;
        // cerr << "  peahit = " << peahit << endl;
        // cerr << "  pealeft = " << pealeft << endl;

        if (pealeft == 0) {
          pealeft = K;
          ++peasec;
        }
      }

      deadtime[zomb.i] = zomb.t - 1 + only_spike_sec + L + 1;
    }
  }

  for (int i = 0; i < n; ++i) cout << deadtime[i] << ' ';
  cout << endl;
}
