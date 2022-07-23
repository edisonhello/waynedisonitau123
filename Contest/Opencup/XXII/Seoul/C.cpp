#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 512;

namespace std {

bool operator<(const bitset<kN>& a, const bitset<kN>& b) {
  int t = (a ^ b)._Find_first();
  return t < kN && !a.test(t);
}

}  // namespace std

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<pair<int, int>> p(N);
  for (int i = 0; i < N; ++i) {
    cin >> p[i].first >> p[i].second;
    p[i].first *= 2;
    p[i].second *= 2;
  }

  auto Dist = [&](pair<int, int> a, pair<int, int> b) {
    return 1LL * (a.first - b.first) * (a.first - b.first) +
           1LL * (a.second - b.second) * (a.second - b.second);
  };

  bitset<kN> all{};
  for (int i = 0; i < N; ++i) {
    all.set(i);
  }

  map<tuple<bitset<kN>, pair<int, int>, pair<int, int>>,
      pair<pair<int, int>, pair<int, int>>>
      term;
  map<tuple<bitset<kN>, pair<int, int>, pair<int, int>>, int> depth;
  map<pair<pair<int, int>, pair<int, int>>, int> exps;
  map<pair<pair<int, int>, pair<int, int>>, int> cnt;

  auto Med = [&](vector<int>& v) {
    if (v.size() & 1) {
      nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
      return v[v.size() / 2];
    } else {
      nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
      return (*max_element(v.begin(), v.begin() + v.size() / 2) +
              v[v.size() / 2]) /
             2;
    }
  };

  vector<int> x, y;

  auto Debug = [&](bitset<kN> bs) {
    cerr << "debug: ";
    for (int i = 0; i < N; ++i) {
      cerr << bs.test(i);
    }
    cerr << endl;
  };

  auto Dfs = [&](auto self, bitset<kN> s, pair<int, int> q1, pair<int, int> q2)
      -> tuple<pair<pair<int, int>, pair<int, int>>, int> {
    if (term.find(make_tuple(s, q1, q2)) != term.end()) {
      return make_tuple(term[make_tuple(s, q1, q2)],
                        depth[make_tuple(s, q1, q2)]);
    }
    pair<int, int> p1{}, p2{};
    {
      x.clear();
      y.clear();
      for (int i = 0; i < N; ++i) {
        if (s.test(i)) {
          x.push_back(p[i].first);
          y.push_back(p[i].second);
        }
      }
      p1.first = Med(x);
      p1.second = Med(y);
    }
    {
      x.clear();
      y.clear();
      for (int i = 0; i < N; ++i) {
        if (!s.test(i)) {
          x.push_back(p[i].first);
          y.push_back(p[i].second);
        }
      }
      p2.first = Med(x);
      p2.second = Med(y);
    }
    if (p1 == q1 && p2 == q2) {
      return make_tuple(make_pair(p1, p2), 0);
    }
    bitset<kN> ns{};
    for (int k = 0; k < N; ++k) {
      if (Dist(p1, p[k]) < Dist(p2, p[k]) ||
          Dist(p1, p[k]) == Dist(p2, p[k]) && p1 < p2) {
        ns.set(k);
      }
    }
    auto [t, d] = self(self, ns, p1, p2);
    term[make_tuple(s, q1, q2)] = t;
    depth[make_tuple(s, q1, q2)] = d + 1;
    return make_tuple(t, d + 1);
  };

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      bitset<kN> s{};
      for (int k = 0; k < N; ++k) {
        if (Dist(p[i], p[k]) < Dist(p[j], p[k]) ||
            Dist(p[i], p[k]) == Dist(p[j], p[k]) && p[i] < p[j]) {
          s.set(k);
        }
      }
      auto p1 = p[i], p2 = p[j];
      // Debug(s);
      auto [t, d] = Dfs(Dfs, s, p1, p2);
      // cerr << "t = " << t.first.first << " " << t.first.second << " "
      //      << t.second.first << " " << t.second.second << " d = " << d <<
      //      endl;
      exps[t] += d + 1;
      cnt[t]++;
    }
  }

  auto Print = [&](int x) {
    if (x < 0) {
      cout << "-";
      x = -x;
    }
    cout << x / 2;
    if (x & 1) {
      cout << ".5";
    } else {
      cout << ".0";
    }
  };

  map<pair<pair<int, int>, pair<int, int>>, int> nexps;
  map<pair<pair<int, int>, pair<int, int>>, int> ncnt;

  for (auto [t, d] : exps) {
    auto tt = t;
    if (tt.first > tt.second) {
      swap(tt.first, tt.second);
    }
    nexps[tt] += d;
  }
  for (auto [t, d] : cnt) {
    auto tt = t;
    if (tt.first > tt.second) {
      swap(tt.first, tt.second);
    }
    ncnt[tt] += d;
  }

  for (auto [t, d] : nexps) {
    Print(t.first.first);
    cout << " ";
    Print(t.first.second);
    cout << " ";
    Print(t.second.first);
    cout << " ";
    Print(t.second.second);
    cout << " ";
    cout << fixed << setprecision(20) << static_cast<double>(d) / ncnt[t]
         << "\n";
  }
}
