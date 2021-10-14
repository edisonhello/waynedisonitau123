void dfs(int x, int p) {
  dfn[x] = low[x] = tk++;
  int ch = 0;
  st.push(x); // bridge
  for (auto e : g[x]) if (e.first != p) {
    if (!ins[e.second]) { // articulation point
      st.push(e.second);
      ins[e.second] = true;
    }
    if (~dfn[e.first]) {
      low[x] = min(low[x], dfn[e.first]);
      continue;
    }
    dfs(u.first, x);
    if (low[u.first] >= low[x]) { // articulation point
      cut[x] = true;
      while (true) {
        int z = st.top(); st.pop();
        bcc[z] = sz;
        if (z == e.second) break;
      }
      sz++;
    }
  }
  if (ch == 1 && p == -1) cut[x] = false;
  if (dfn[x] == low[x]) { // bridge
    while (true) {
      int z = st.top(); st.pop();
      bcc[z] = sz;
      if (z == x) break;
    }
  }
}
