#pragma GCC optimize("O3")
// #include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
// using namespace __gnu_pbds;
using namespace std;

template <typename Key, typename Value>
using Map = unordered_map<Key, Value>;

struct Majority {
  Map<int, int> s;
  int mode, cnt;
  bool rev;
  Map<int, int> consume;
  int smode, scnt;

  Majority(int v) : mode(v), cnt(1), rev(false) { s[v] = 1; }
  size_t size() const { return s.size(); }

  void Save() {
    rev = true;
    smode = mode;
    scnt = cnt;
  }

  bool operator==(const Majority &rhs) const {
    return mode == rhs.mode && cnt == rhs.cnt && s == rhs.s;
  }

  void Undo() {
    if (!rev) return;
    rev = false;
    for (auto it : consume) {
      s[it.first] -= it.second;
      if (s[it.first] == 0) s.erase(it.first);
    }
    mode = smode;
    cnt = scnt;
    consume.clear();
  }

  void Merge(const Majority &rhs) {
    auto tmp(std::move(rhs));
    for (auto it : tmp.s) {
      if (rev) consume[it.first] += it.second;
      s[it.first] += it.second;
      int kc = s[it.first];
      if (kc > cnt) {
        cnt = kc;
        mode = it.first;
      } else if (kc == cnt) {
        mode = min(mode, it.first);
      }
    }
  }

  void Merge(Majority &&rhs) {
    auto tmp(std::move(rhs));
    assert(!rev);
    for (auto it : tmp.s) {
      s[it.first] += it.second;
      int kc = s[it.first];
      if (kc > cnt) {
        cnt = kc;
        mode = it.first;
      } else if (kc == cnt) {
        mode = min(mode, it.first);
      }
    }
  }
};

void Solve() {
  int N, M;
  cin >> N >> M;
  vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    cin >> C[i];
    C[i]--;
  }
  vector<tuple<int, int, int>> edge;
  for (int i = 0; i < M; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    x--, y--;
    edge.emplace_back(w, x, y);
  }
  sort(edge.begin(), edge.end());

  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<Majority> maj;
  for (int i = 0; i < N; ++i) maj.emplace_back(C[i]);

  int counter = 0;

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (maj[x].size() > maj[y].size()) swap(x, y);
    counter += maj[x].size();
    maj[y].Merge(std::move(maj[x]));
    uf[x] = y;
    return true;
  };

  vector<tuple<int, int, int>> nedge;
  vector<vector<int>> huf;
  vector<vector<Majority>> hmaj;
  vector<int> save;
  vector<int> iter;
  huf.push_back(uf);
  hmaj.push_back(maj);
  save.push_back(-1);
  iter.push_back(-1);
  const int kB = 2000;
  for (int i = 0; i < M; ++i) {
    auto [w, x, y] = edge[i];
    // cout << "x = " << x << " y = " << y << endl;
    if (Merge(x, y)) {
      if (counter >= kB) {
        huf.push_back(uf);
        hmaj.push_back(maj);
        save.push_back(w);
        iter.push_back(nedge.size());
        counter = 0;
      }
      nedge.push_back(edge[i]);
    }
  }

  // for (auto e : nedge) cout << get<1>(e) << " " << get<2>(e) << endl;

  int Q, last = 0;
  vector<int> buffer(N, -1);
  vector<int> ut, touch;
  cin >> Q;
  while (Q--) {
    int x, W;
    cin >> x >> W;
    x ^= last;
    W ^= last;
    x--;
    // cout << "x = " << x << " W = " << W << endl;
    auto it = upper_bound(save.begin(), save.end(), W) - save.begin() - 1;
    // cout << "it = " << it << endl;
    assert(it >= 0);

    auto &U = huf[it];
    auto &M = hmaj[it];

    // const auto Us = huf[it];
    // const auto Ms = hmaj[it];
    ut.clear();

    auto Assign = [&](int p, int v) {
      if (buffer[p] == -1) {
        buffer[p] = U[p];
        ut.push_back(p);
      }
      U[p] = v;
    };

    vector<pair<int *, int>> hist;
    function<int(int)> Find = [&](int x) {
      if (x == U[x]) return x;
      Assign(x, Find(U[x]));
      return U[x];
    };

    touch.clear();
    auto Merge = [&](int x, int y) {
      x = Find(x);
      y = Find(y);
      assert(x != y);
      assert(U[x] == x);
      assert(U[y] == y);
      if (!M[x].rev) M[x].Save();
      if (!M[y].rev) M[y].Save();
      if (M[x].size() > M[y].size()) swap(x, y);
      M[y].Merge(M[x]);
      Assign(x, y);
      touch.push_back(x);
      touch.push_back(y);
    };

    for (int j = iter[it] + 1; j < nedge.size(); ++j) {
      auto [w, x, y] = nedge[j];
      if (w > W) break;
      // cout << "w = " << w << " W = " << W << endl;
      // cout << "j = " << j << endl;
      Merge(x, y);
    }
    int g = Find(x);
    cout << (last = M[g].mode + 1) << "\n";
    last = 0;
    for (int u : touch) {
      // cout << "u = " << u << endl;
      M[u].Undo();
    }
    for (int u : ut) {
      U[u] = buffer[u];
      buffer[u] = -1;
    }
    // assert(U == Us);
    // assert(M == Ms);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": \n";
    Solve();
  }
}
