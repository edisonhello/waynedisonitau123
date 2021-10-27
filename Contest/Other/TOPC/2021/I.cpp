#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<int> st(M), ed(M), w(M);
  for (int i = 0; i < M; ++i) {
    cin >> st[i] >> ed[i];
    st[i]--;
    ed[i]--;
    w[i] = sqrt(A[st[i]] + A[ed[i]]);
    while (1LL * w[i] * w[i] > A[st[i]] + A[ed[i]]) w[i]--;
    while (1LL * (w[i] + 1) * (w[i] + 1) <= A[st[i]] + A[ed[i]]) w[i]++;
  }

  int W;
  cin >> W;
  vector<vector<int>> B(W);
  vector<int> cnt(W);
  vector<pair<int, int>> vec;
  for (int i = 0; i < W; ++i) {
    int x;
    cin >> x;
    B[i].resize(x);
    for (int j = 0; j < x; ++j) {
      int b;
      cin >> b;
      b--;
      B[i][j] = vec.size();
      vec.emplace_back(i, b);
    }
  }

  vector<int> uf(N);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    uf[x] = y;
  };

  int K = vec.size();
  vector<bool> start(K);
  vector<bool> end(K);
  vector<bool> inque(K);
  vector<int> from(K);
  constexpr int kInf = 1'000'000'000;
  vector<pair<int, int>> dist(K);
  vector<int> ans(N - 1, -1);
  vector<int> which(W, -1);
  vector<bool> chosen(K);

  
  int sum = 0;
  vector<vector<pair<int, int>>> g(N);

  for (int k = 0; k < N - 1; ++k) {
    // cout << "k = " << k << endl;
    // cout << "list: ";
    // for (int i = 0; i < K; ++i) {
    //   if (chosen[i]) cout << i << " ";
    // }
    // cout << endl;
    fill(start.begin(), start.end(), false);
    fill(end.begin(), end.end(), false);
    fill(dist.begin(), dist.end(), make_pair(kInf, -1));
    fill(inque.begin(), inque.end(), false);
    fill(from.begin(), from.end(), -1);
    for (int i = 0; i < N; ++i) {
      g[i].clear();
    }
    iota(uf.begin(), uf.end(), 0);
    vector<int> lst;
    for (int i = 0; i < K; ++i) {
      if (chosen[i]) {
        int e = vec[i].second;
        lst.push_back(i);
        // cout << "e = " << e << endl;
        // cout << "Merge " << st[e] << " " << ed[e] << endl;
        Merge(st[e], ed[e]);
        g[st[e]].emplace_back(ed[e], i);
        g[ed[e]].emplace_back(st[e], i);
      }
    }
    // int _;
    // cin >> _;
    vector<bool> vis(N);
    vector<int> fa(N), fe(N);
    vector<int> dep(N);

    auto Dfs = [&](auto dfs, int x, int p = -1, int f = -1) -> void {
      vis[x] = true;
      fa[x] = p;
      fe[x] = f;
      dep[x] = ~p ? dep[p] + 1 : 0;
      for (auto [u, e] : g[x]) {
        if (u == p) continue;
        dfs(dfs, u, x, e);
      }
    };

    for (int i = 0; i < N; ++i) {
      if (!vis[i]) {
        Dfs(Dfs, i);
      }
    }
    queue<int> que;
    for (int i = 0; i < K; ++i) {
      auto [c, e] = vec[i];
      if (!chosen[i]) {
        if (cnt[c] == 0) {
          start[i] = true;
          dist[i].first = -w[e];
          dist[i].second = 0;
          que.push(i);
          inque[i] = true;
        }
        if (Find(st[e]) != Find(ed[e])) {
          end[i] = true;
        }
      }
    }
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      // cout << "x = " << x << endl;
      // int _;
      // cin >> _;
      inque[x] = false;
      if (!chosen[x]) {
        int e = vec[x].second;
        int a = st[e], b = ed[e];
        if (Find(a) == Find(b)) {
          while (a != b) {
            // cout << "a = " << a << " b = " << b << endl;
            if (dep[a] > dep[b]) swap(a, b);
            int u = fe[b];
            int f = vec[u].second;
            assert(chosen[u]);
            // cout << "type1: " << x << " -> " << u << endl;
            if (dist[u].first > dist[x].first + w[f] ||
                dist[u].first == dist[x].first + w[f] && dist[u].second > dist[x].second + 1) {
              dist[u].first = dist[x].first + w[f];
              dist[u].second = dist[x].second + 1;
              from[u] = x;
              if (!inque[u]) {
                inque[u] = true;
                que.push(u);
              }
            }
            b = fa[b];
          }
        } else {
          for (int u : lst) {
            int f = vec[u].second;
            if (dist[u].first > dist[x].first + w[f] ||
                dist[u].first == dist[x].first + w[f] && dist[u].second > dist[x].second + 1) {
              dist[u].first = dist[x].first + w[f];
              dist[u].second = dist[x].second + 1;
              from[u] = x;
              if (!inque[u]) {
                inque[u] = true;
                que.push(u);
              }
            }
          }
        }
      } else {
        int c = vec[x].first;
        // int u = which[c];
        // assert(c != -1);
        for (int u : B[c]) {
          if (u != x && !chosen[u]) {
            // cout << "type2: " << x << " -> " << u << endl;
            int e = vec[u].second;
            if (dist[x].first - w[e] < dist[u].first || 
                dist[x].first - w[e] == dist[u].first && dist[x].second + 1 < dist[u].second) {
              from[u] = x;
              dist[u].first = dist[x].first - w[e];
              dist[u].second = dist[x].second + 1;
              if (!inque[u]) {
                inque[u] = true;
                que.push(u);
              }
            }
          }
        }
      }
    }
    int x = -1;
    for (int i = 0; i < K; ++i) {
      if (!chosen[i] && end[i]) {
        if (x == -1 || dist[i] < dist[x]) {
          x = i;
        }
      }
    }
    if (x == -1) {
      break;
    }
    if (dist[x].first == kInf) {
      break;
    }
    // cout << "end x = " << x << endl;
    sum -= dist[x].first;
    while (x != -1) {
      // cout << "path x = " << x << endl;
      if (chosen[x]) {
        int c = vec[x].first;
        cnt[c]--;
        chosen[x] = false;
        which[c] = -1;
      } else {
        int c = vec[x].first;
        cnt[c]++;
        chosen[x] = true;
        which[c] = x;
      }
      x = from[x];
    }
    ans[k] = sum;
  }
  for (int i = 0; i < N - 1; ++i) cout << ans[i] << " ";
  cout << "\n";
  return 0;
}
