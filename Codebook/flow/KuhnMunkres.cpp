int64_t KuhnMunkres(vector<vector<int>> W) {
  int N = W.size();
  vector<int> fl(N, -1), fr(N, -1), hr(N), hl(N);
  for (int i = 0; i < N; ++i) {
    hl[i] = *max_element(W[i].begin(), W[i].end());
  }
  auto Bfs = [&](int s) {
    vector<int> slk(N, kInf), pre(N);
    vector<bool> vl(N, false), vr(N, false);
    queue<int> que;
    que.push(s);
    vr[s] = true;
    auto Check = [&](int x) -> bool {
      if (vl[x] = true, fl[x] != -1) {
        que.push(fl[x]);
        return vr[fl[x]] = true;
      }
      while (x != -1) swap(x, fr[fl[x] = pre[x]]);
      return false;
    };
    while (true) {
      while (!que.empty()) {
        int y = que.front(); que.pop();
        for (int x = 0, d = 0; x < N; ++x) {
          if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - W[x][y])) {
            if (pre[x] = y, d) slk[x] = d;
            else if (!Check(x)) return;
          }
        }
      }
      int d = kInf;
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && d > slk[x]) d = slk[x];
      }
      for (int x = 0; x < N; ++x) {
        if (vl[x]) hl[x] += d;
        else slk[x] -= d;
        if (vr[x]) hr[x] -= d;
      }
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && !slk[x] && !Check(x)) return;
      }
    }
  };
  for (int i = 0; i < N; ++i) Bfs(i);
  int64_t res = 0;
  for (int i = 0; i < N; ++i) res += W[i][fl[i]];
  return res;
}
