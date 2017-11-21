int tin[maxn], low[maxn], t, bccsz;
stack<int> st;
vector<int> bcc[maxn];

void dfs(int now, int fa) {
    tin[now] = ++t; low[now] = tin[now];
    st.push(now);
    for (int u : G[now]) if (u != fa) {
        if (!tin[u]) {
            dfs(u, now);
            low[now] = min(low[now], low[u]);
            if (low[u] >= tin[now]) {
                int v;
                ++bccsz;
                do {
                    v = st.top(); st.pop();
                    bcc[bccsz].push_back(v);
                } while (v != u);
                bcc[bccsz].push_back(now);
            }
        } else {
            low[now] = min(low[now], tin[u]);
        }
    }
}
