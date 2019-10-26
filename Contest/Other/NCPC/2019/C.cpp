#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> G[100005];
int d[100005], cf[100005];;

void dfs(int now, int pa) {
	cf[now] = pa;
	for (pair<int, int> i : G[now]) {
		if (i.first == pa) continue;
		d[i.first] = d[now] + i.second;
		dfs(i.first, now);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n; cin >> n;
		for (int i = 1; i < n; ++i) {
			int u, v, w; cin >> u >> v >> w;
			G[u].emplace_back(v, w);
			G[v].emplace_back(u, w);
		}
		d[0] = 0;
		dfs(0, -1);
		int far = max_element(d, d + n) - d;
		d[far] = 0;
		dfs(far, -1);
		int far2 = max_element(d, d + n) - d;
		int D = d[far2];
		int now = far2;
		int mn = D;
		while (now != -1) {
			mn = min(mn, max(d[now], D - d[now]));
			now = cf[now];
		}
		now = far2;
		set<int> ans;
		while (now != -1) {
			if (max(d[now], D - d[now]) == mn) ans.insert(now);
			now = cf[now];
		}
		for (int i : ans) cout << i << ' ';
		cout << '\n';
		for (int i = 0; i < n; ++i) cf[i] = 0, d[i] = 0, G[i].clear();
	}
}
