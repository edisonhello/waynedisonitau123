#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int to, cap, rev, cost;
	Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), cost(d) {}
};

int64_t Flow(vector<vector<Edge>> g, int s, int t) {
	int n = g.size();
	constexpr int64_t kInf = 1'000'000'000'000'000;
	int64_t res = 0;
	while (true) {
		vector<int64_t> dist(n, -kInf);
		vector<bool> inque(n);
		vector<int> pv(n, -1);
		vector<int> ed(n, -1);
		vector<int> que(1, s);
		dist[s] = 0;
		for (int it = 0; it < que.size(); ++it) {
			int x = que[it];
			inque[x] = false;
			for (int i = 0; i < g[x].size(); ++i) {
				Edge &e = g[x][i];
				if (e.cap == 0) continue;
				if (dist[e.to] < dist[x] + e.cost) {
					dist[e.to] = dist[x] + e.cost;
					pv[e.to] = x;
					ed[e.to] = i;
					if (!inque[e.to]) {
						inque[e.to] = true;
						que.push_back(e.to);
					}
				}
			}
		}	
		if (dist[t] == -kInf) break;
		int f = 1e9;
		for (int x = t; x != s; x = pv[x]) f = min(f, g[pv[x]][ed[x]].cap);
		for (int x = t; x != s; x = pv[x]) {
			Edge &e = g[pv[x]][ed[x]];
			e.cap -= f;
			g[e.to][e.rev].cap += f;
		}
		res += 1LL * f * dist[t];
	}
	return res;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> k(n);
	vector<vector<Edge>> g(n + n + 2);

	auto AddEdge = [&](int a, int b, int c, int d) {
		g[a].emplace_back(b, c, (int)g[b].size() - 0, d);
		g[b].emplace_back(a, 0, (int)g[a].size() - 1, -d);
	};

	int s = n + n, t = n + n + 1;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		AddEdge(u, v + n, 1, w);
	}
	for (int i = 0; i < n; ++i) {
		AddEdge(s, i, 1, 0);
		AddEdge(i + n, t, 1, 0);
		AddEdge(i, i + n, 1, 0);
	}
	cout << fixed << setprecision(12) << Flow(g, s, t) / 20.0 << endl;
}

