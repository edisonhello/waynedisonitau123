#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<int>> g(N);
	assert(M == 3 * N / 2);
	vector<vector<int>> adj(N, vector<int>(N));
	for (int i = 0; i < M; ++i) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		adj[u][v]++;
		adj[v][u]++;
	}

	vector<int> match(N + 1, N), pre(N + 1, N), v(N + 1);
	vector<int> fa(N + 1), s(N + 1);
	queue<int> que;
	int tk = 0;

	function<int(int)> Find = [&](int x) {
		return x == fa[x] ? x : fa[x] = Find(fa[x]);
	};

	auto LCA = [&](int x, int y) {
		tk++;
		x = Find(x);
		y = Find(y);
		for (; ; swap(x, y)) {
			if (x != N) {
				if (v[x] == tk) {
					return x;
				}
				v[x] = tk;
				x = Find(pre[match[x]]);
			}
		}
	};

	auto Blossom = [&](int x, int y, int l) {
		while (Find(x) != l) {
			pre[x] = y;
			y = match[x];
			if (s[y] == 1) {
				que.push(y);
				s[y] = 0;
			}
			if (fa[x] == x) {
				fa[x] = l;
			}
			if (fa[y] == y) {
				fa[y] = l;
			}
			x = pre[y];
		}
	};

	auto Bfs = [&](int r) {
		iota(fa.begin(), fa.end(), 0);
		fill(s.begin(), s.end(), -1);
		while (!que.empty()) que.pop();
		que.push(r);
		s[r] = 0;
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			for (int u : g[x]) {
				if (s[u] == -1) {
					pre[u] = x;
					s[u] = 1;
					if (match[u] == N) {
						for (int a = u, b = x, last; b != N; a = last, b = pre[a]) {
							last = match[b];
							match[b] = a;
							match[a] = b;
						}
						return;
					}
					que.push(match[u]);
					s[match[u]] = 0;
				} else if (!s[u] && Find(u) != Find(x)) {
					int l = LCA(u, x);
					Blossom(x, u, l);
					Blossom(u, x, l);
				}
			}
		}
	};

	for (int x = 0; x < N; ++x) {
		if (match[x] == N) Bfs(x);
	}

	for (int x = 0; x < N; ++x) {
		if (match[x] == N) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
		assert(adj[x][match[x]] > 0);
		adj[x][match[x]]--;
	}

	vector<bool> vis(N);
	vector<int> nxt(N, -1), prv(N, -1);

	vector<int> cycle;

	auto Dfs = [&](auto dfs, int x) {
		vis[x] = true;
		vector<int> to;
		for (int y = 0; y < N; ++y) {
			for (int i = 0; i < adj[x][y]; ++i) {
				to.push_back(y);
			}
		}
		cycle.push_back(x);
		assert(to.size() == 2);
		if (to[0] == x) {
			assert(to[1] == x);
			return;
		}
		for (int u : to) {
			if (!vis[u]) {
				dfs(dfs, u);
			}
		}
	};

	for (int x = 0; x < N; ++x) {
		if (!vis[x]) {
			cycle.clear();
			Dfs(Dfs, x);
			for (int i = 0; i < cycle.size(); ++i) {
				nxt[cycle[i]] = cycle[(i + 1) % cycle.size()];
				prv[cycle[i]] = cycle[(i + cycle.size() - 1) % cycle.size()];
			}
		}
	}
	for (int x = 0; x < N; ++x) {
		if (x < match[x]) {
			cout << prv[x] + 1 << " " << x + 1 << " " << match[x] + 1 << " " << prv[match[x]] + 1 << "\n";
		}
	}
	return 0;
}

