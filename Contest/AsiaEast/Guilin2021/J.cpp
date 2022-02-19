#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  string s;
  cin >> s;

  auto Build = [&](const string& s) {
    int N = s.size();

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
      return s[i] < s[j];
    });

    vector<int> new_order(N);
    iota(new_order.begin(), new_order.end(), 0);

    vector<int> rnk(N);
    vector<int> new_rnk(N);

    for (int i = 0, r = 0; i < N; ++i) {
      if (i > 0 && s[order[i - 1]] != s[order[i]]) {
        r++;
      }
      rnk[order[i]] = r;
    }

    vector<int> old_rank(N);
    for (int k = 1; k <= N; k <<= 1) {

      auto Get = [&](int p) {
        int x = rnk[p];
        int y = p + k >= N ? -1 : rnk[p + k];
        return make_pair(x, y);
      };


      sort(new_order.begin(), new_order.end(), [&](int i, int j) {
        return Get(i) < Get(j);
      });

      int r = 0;
      for (int i = 0; i < N; ++i) {
        if (i > 0 && Get(new_order[i - 1]) != Get(new_order[i])) {
          r++;
        }
        new_rnk[new_order[i]] = r;
      } 
      order.swap(new_order);
      rnk.swap(new_rnk);
      if (r == N) {
        break;
      }
    }
    return make_pair(order, rnk);
  };

  auto [sa, rnk] = Build(s);
  int N = s.size();
  for (int i = 0; i < N; ++i) {
    rnk[sa[i]] = i;
  }
  vector<int> lcp(N);
  for (int i = 0, ptr = 0; i < N; ++i) {
    if (!rnk[i]) {
      ptr = 0;
      continue;
    }
    while (i + ptr < N && s[i + ptr] == s[sa[rnk[i] - 1] + ptr]) {
      ptr++;
    }
    lcp[rnk[i]] = ptr ? ptr-- : 0;
  }

  vector<vector<int>> sp(1, vector<int>(lcp.begin(), lcp.end()));
  for (int i = 1; (1 << i) <= N; ++i) {
    sp.emplace_back(N);
    for (int j = 0; j + (1 << i) <= N; ++j) {
      sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
    }
  }

  auto Query = [&](int l, int r) {
    l++;
    r++;
    int p = 31 - __builtin_clz(r - l + 1);
    return min(sp[p][l], sp[p][r - (1 << p) + 1]);
  };

  int sz = 1;
  while (sz < N + 2) {
    sz <<= 1;
  }
  vector<int> fw(sz);

  auto Update = [&](int p, int v) {
    for (int i = p + 1; i < sz; i += i & -i) {
      fw[i] += v;
    } 
  };

  auto FindKth = [&](int k) {
    int res = 0;
    for (int bit = sz / 2; bit > 0; bit >>= 1) {
      if (fw[res + bit] <= k) {
        res += bit;
        k -= fw[res];
      }
    }
    return res;
  };

  auto QueryFw = [&](int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i) {
      res += fw[i];
    }
    return res;
  };

  vector<vector<int>> die(N + 1);
  vector<bool> dead(N);
  vector<int64_t> cl(N + 1);

  for (int L = N; L >= 1; --L) {
    int p = rnk[N - L];  
    int v = QueryFw(p);
    bool alive = true;
    if (v > 0) {
      int q = FindKth(v - 1);
      int t = Query(q, p - 1);
      if (N - L < sa[q]) {
        die[min(t, L)].push_back(q);
      } else {
        if (t < L) {
          die[t].push_back(p);
        } else {
          alive = false;
        }
      }
    }
    if (v < QueryFw(N - 1)) {
      int q = FindKth(v);
      int t = Query(p, q - 1);
      if (N - L < sa[q]) {
        die[min(t, L)].push_back(q);
      } else {
        if (t < L) {
          die[t].push_back(p);
        } else {
          alive = false;
        }
      }
    }
    if (alive) {
      Update(p, 1);
    } else {
      dead[p] = true;
    }
    for (int u : die[L]) {
      if (!dead[u]) {
        dead[u] = true;
        Update(u, -1);
      }
    }
    int cnt = QueryFw(N - 1);
    cl[L] = cnt;
  }

  int Q;
  cin >> Q;

  vector<pair<int, int>> ans(Q);
  vector<vector<pair<int, int>>> qr(N + 1);

  for (int i = 2; i <= N; ++i) {
    cl[i] += cl[i - 1];
  }

  for (int i = 0; i < Q; ++i) {
    int64_t k;
    cin >> k;
    int L = 0;
    for (int d = 20; d >= 0; --d) {
      if (L + (1 << d) <= N && cl[L + (1 << d)] < k) {
        L += (1 << d);
      }
    }
    if (L == N) {
      ans[i] = make_pair(-1, -1);
      continue;
    }

    k -= cl[L];
    k--;
    L++;
    assert(k >= 0 && k < cl[L] - cl[L - 1]);
    qr[L].emplace_back(i, k);
  }

  fill(fw.begin(), fw.end(), 0);
  fill(dead.begin(), dead.end(), false);
  for (int i = 0; i <= N; ++i) {
    die[i].clear();
  }
  for (int L = N; L > 0; --L) {
    int p = rnk[N - L];  
    int v = QueryFw(p);
    bool alive = true;
    if (v > 0) {
      int q = FindKth(v - 1);
      int t = Query(q, p - 1);
      if (N - L < sa[q]) {
        die[min(t, L)].push_back(q);
      } else {
        if (t < L) {
          die[t].push_back(p);
        } else {
          alive = false;
        }
      }
    }
    if (v < QueryFw(N - 1)) {
      int q = FindKth(v);
      int t = Query(p, q - 1);
      if (N - L < sa[q]) {
        die[min(t, L)].push_back(q);
      } else {
        if (t < L) {
          die[t].push_back(p);
        } else {
          alive = false;
        }
      }
    }
    if (alive) {
      Update(p, 1);
    } else {
      dead[p] = true;
    }
    for (int u : die[L]) {
      if (!dead[u]) {
        dead[u] = true;
        Update(u, -1);
      }
    }
    for (auto [q, k] : qr[L]) {
      int x = FindKth(k);
      ans[q] = make_pair(sa[x] + 1, sa[x] + L);
    }
  }
  for (int i = 0; i < Q; ++i) {
    cout << ans[i].first << " " << ans[i].second << "\n";
  }
  return 0;
}

