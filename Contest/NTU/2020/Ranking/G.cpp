#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int to, cap, rev;

	Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

int64_t Flow(vector<vector<Edge>> g, int s, int t) {
	int N = g.size();
	vector<int> iter(N), lev(N);
	int64_t res = 0;
	while (true) {
		fill(lev.begin(), lev.end(), -1);
		fill(iter.begin(), iter.end(), 0);

		vector<int> que(1, s);
		lev[s] = 0;
		for (int it = 0; it < que.size(); ++it) {
			int x = que[it];
			for (Edge &e : g[x]) {
				if (e.cap > 0 && lev[e.to] == -1) {
					lev[e.to] = lev[x] + 1;
					que.push_back(e.to);
				}
			}
		}

		if (lev[t] == -1) break;

		auto Dfs = [&](auto dfs, int x, int f = 1'000'000'000) -> int {
			if (x == t) return f;
			int res = 0;
			for (int &it = iter[x]; it < g[x].size(); ++it) {
				Edge &e = g[x][it];
				if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
					int p = dfs(dfs, e.to, min(f - res, e.cap));
					e.cap -= p;
					g[e.to][e.rev].cap += p;
					res += p;
				}
			}
			if (res == 0) lev[x] = -1;
			return res;
		};

		res += Dfs(Dfs, s);
	}
	return res;
}

void bye() {
	cout << "Meow!" << endl;
	exit(0);
}

int main () {
	vector<vector<Edge>> g;

	auto AddEdge = [&](int a, int b, int c) {
		g[a].emplace_back(b, c, (int)g[b].size() - 0);
		g[b].emplace_back(a, 0, (int)g[a].size() - 1);
	};

	int n, m, k; cin >> n >> m >> k;
	vector<int> r(n), c(m);
	vector<vector<int>> cant(n, vector<int>(m, 0));
	g.resize(n + m + 2);

	while (k--) {
		int x, y; cin >> x >> y; --x; --y;
		cant[x][y] = 1;
	}

	for (int i = 0; i < n; ++i) cin >> r[i];
	for (int i = 0; i < m; ++i) cin >> c[i];

	auto Id = [&] (int x, int y) {
		return x * m + y;
	};

	for (int i = 0; i < n; ++i) {
		int put = 0;
		for (int j = 0; j < m; ++j) if (!cant[i][j]) put++;

		if (put < r[i]) bye();

		AddEdge(n + m, i, put - r[i]);
	}
	for (int j = 0; j < m; ++j) {
		int put = 0;
		for (int i = 0; i < n; ++j) if (!cant[i][j]) ++put;

		if (put < c[j]) bye();

		AddEdge(n + j, n + m + 1, put - c[j]);
	}

	int all = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (!cant[i][j]) {
		AddEdge(i, j + n, 1);
		++all;
	}

	int res = Flow(g, n + m, n + m + 1);

	cout << all - res << endl;
}
