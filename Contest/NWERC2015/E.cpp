#include <bits/stdc++.h>
using namespace std;

const int maxn = 11000;

struct dinic {
	struct edge {
		int to, rev, cap;
		edge(int a, int b, int c): to(a), cap(b), rev(c) {}
	};
	vector<edge> g[maxn];
	int lev[maxn], qu[maxn];
	void add_edge(int a, int b, int c) {
		g[a].emplace_back(b, c, (int)g[b].size() - 0);
		g[b].emplace_back(a, 0, (int)g[a].size() - 1);
	}
	bool bfs(int s, int t) {
		memset(lev, -1, sizeof(lev));
		int ql = 0, qr = 0;
		lev[s] = 0;
		qu[qr++] = s;
		while (ql < qr) {
			int x = qu[ql++];
			for (int i = 0; i < (int)g[x].size(); ++i) {
				if (lev[g[x][i].to] == -1 && g[x][i].cap > 0) {
					lev[g[x][i].to] = lev[x] + 1;
					qu[qr++] = g[x][i].to;
				}
			}
		}
		return lev[t] != -1;
	}
	int dfs(int x, int t, int flow) {
		if (x == t) return flow;
		int res = 0;
		for (int i = 0; i < (int)g[x].size(); ++i) {
			if (g[x][i].cap > 0 && lev[g[x][i].to] == lev[x] + 1) {
				int f = dfs(g[x][i].to, t, min(g[x][i].cap, flow - res));
				res += f;
				g[x][i].cap -= f;
				g[g[x][i].to][g[x][i].rev].cap += f;
			}
		}
		if (res == 0) lev[x] = -1;
		return res;
	}
	int operator()(int s, int t) {
		int res = 0;
		for (; bfs(s, t); res += dfs(s, t, 1e9));
		return res;
	}
} flow;

int node[maxn], sz, x[maxn], y[maxn];
map<long long, int> result;

int get(long long x) {
	if (result.find(x) != result.end())
		return result[x];
	result[x] = sz++;
	return result[x];
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) node[i] = sz++;
	for (int i = 0; i < n; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		x[i] = a, y[i] = b;
		flow.add_edge(node[i], get(a + b), 1);
		flow.add_edge(node[i], get(a - b), 1);
		flow.add_edge(node[i], get(a * 1ll * b), 1);
	}

	int s = sz++, t = sz++;
	for (int i = 0; i < n; ++i) 
		flow.add_edge(s, node[i], 1);

	for (auto it : result) 
		flow.add_edge(get(it.first), t, 1);

	int f = flow(s, t);
	if (f != n) {
		puts("impossible");
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		int type = -1;
		for (int j = 0; j < (int)flow.g[node[i]].size(); ++j) {
			int to = flow.g[node[i]][j].to, cap = flow.g[node[i]][j].cap;
			if (cap == 0) {
				if (to == get(x[i] + y[i]))
					type = 0;
				if (to == get(x[i] - y[i]))
					type = 1;
				if (to == get(x[i] * 1ll * y[i]))
					type = 2;
			}
		}
		assert(type >= 0);
		if (type == 0)
			printf("%d + %d = %d\n", x[i], y[i], x[i] + y[i]);
		if (type == 1)
			printf("%d - %d = %d\n", x[i], y[i], x[i] - y[i]);
		if (type == 2)
			printf("%d * %d = %lld\n", x[i], y[i], x[i] * 1ll * y[i]);
	}
	
}
