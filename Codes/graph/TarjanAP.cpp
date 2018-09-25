
vector<pair<int, int>> g[maxn];
int low[maxn], tin[maxn], t;
int bcc[maxn], sz;
int a[maxn], b[maxn], deg[maxn];
bool cut[maxn], ins[maxn];

vector<int> ed[maxn];

stack<int> st;

void dfs(int x, int p) {
    tin[x] = low[x] = ++t;
    int ch = 0;
    for (auto u : g[x]) if (u.first != p) {
        if (!ins[u.second]) st.push(u.second), ins[u.second] = true;
        if (tin[u.first]) {
            low[x] = min(low[x], tin[u.first]);
            continue;
        }
        ++ch;
        dfs(u.first, x);
        low[x] = min(low[x], low[u.first]);
        if (low[u.first] >= tin[x]) {
            cut[x] = true;
            ++sz;
            while (true) {
                int e = st.top(); st.pop();
                bcc[e] = sz;
                if (e == u.second) break;
            }
        }
    }
    if (ch == 1 && p == -1) cut[x] = false;
}
