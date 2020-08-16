#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

static const int maxn = 155;

struct edge {
	int to, cap, rev, ocap;
	edge(int d, int c, int r) : to(d), cap(c), rev(r), ocap(c) {}
};

struct dinic {
	static const int inf = 1e9;
	vector<edge> g[maxn];
	int qu[maxn], ql, qr;
	int lev[maxn];
	bool walked[maxn];
	void init() {
		for (int i = 0; i < maxn; ++i) g[i].clear();
	}
	void add_edge(int a, int b, int c)  {
		g[a].emplace_back(b, c, g[b].size() - 0);
		g[b].emplace_back(a, c, g[a].size() - 1);
	}
	bool bfs(int s, int t) {
		memset(lev, -1, sizeof(lev));
		lev[s] = 0;
		ql = qr = 0;
		qu[qr++] = s;
		while (ql < qr) {
			int x = qu[ql++];
			for (edge &e : g[x]) if (lev[e.to] == -1 && e.cap > 0) {
				lev[e.to] = lev[x] + 1;
				qu[qr++] = e.to;
			}
		}
		return lev[t] != -1;
	}
	int dfs(int x, int t, int flow) {
		if (x == t) return flow;
		int res = 0;
		for (auto &e : g[x]) if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
			int f = dfs(e.to, t, min(e.cap, flow -res));
			res += f;
			e.cap -= f;
			g[e.to][e.rev].cap += f;
		}
		if (res == 0) lev[x] = -1;
		return res;
	}
	void walk(int now) {
		if (walked[now]) return;
		walked[now] = 1;
		for (auto &e : g[now]) if (e.cap) {
			if (walked[e.to]) continue;
			walk(e.to);
		}
	}
	void reset() {
		for (int i = 0; i < maxn; ++i) {
			for (auto &e : g[i]) {
				e.cap = e.ocap;
			}
		}
		memset(walked, 0, sizeof(walked));
	}
	int operator()(int s, int t) {
		int flow = 0;
		for (; bfs(s, t); flow += dfs(s, t, inf));
		return flow;
	}
} flow;

int go[maxn];
vector<edge> gmrh(int n) {
	vector<edge> rt;
	for (int i = 1; i <= n; ++i) go[i] = 1;
	for (int i = 2; i <= n; ++i) {
		int t = go[i];
		flow.reset();
		rt.push_back({i, t, flow(i, t)});
		flow.walk(i);
		for (int j = i + 1; j <= n; ++j) {
			if (go[j] == t && flow.walked[j]) go[j] = i;
		}
	}
	return rt;
}

int anss[155][155];

bool vis[155];
vector<pair<int, int>> gg[155];

int Dfs(int now, int to, int mn) {
	if (now == to) return mn;
	vis[now] = 1;
	for (auto e : gg[now]) {
		if (vis[e.first]) continue;
		int rt = Dfs(e.first, to, min(mn, e.second));
		if (rt != -1) return rt;
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	while (m--) {
		int u, v, w; cin >> u >> v >> w;
		flow.add_edge(u, v, w);
	}

	auto ansg = gmrh(n);

	for (auto &e : ansg) {
		gg[e.to].emplace_back(e.cap, e.rev);
		gg[e.cap].emplace_back(e.to, e.rev);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j) {
				cout << 0 << ' ';
				continue;
			}
			memset(vis, 0, sizeof(vis));
			cout << Dfs(i, j, INT_MAX) << ' ';
		}
		cout << '\n';
	}
}
