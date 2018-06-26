vector<pair<int, int>> g[maxn];
int tin[maxn], low[maxn], t;
int a[maxn], b[maxn];
int bcc[maxn], sz;
bool br[maxn];

stack<int> st;

void dfs(int x, int p) {
    tin[x] = low[x] = ++t;
    st.push(x);
    for (auto u : g[x]) if (u.first != p) {
        if (tin[u.first]) {
            low[x] = min(low[x], tin[u.first]);
            continue;
        }
        dfs(u.first, x);
        low[x] = min(low[x], low[u.first]);
        if (low[u.first] == tin[u.first]) {
            br[u.second] = true;
            ++sz;
            while (true) {
                int z = st.top(); st.pop();
                bcc[z] = sz;
                if (z == u.first) break;
            }
        }
    }
}
