#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<int> g[300005];
int sz[300005], mxch[300005];

void dfs1(int now, int pa) {
	sz[now] = 1;
	for (int i : g[now]) if (i != pa) {
		dfs1(i, now);
		sz[now] += sz[i];
		if (sz[mxch[now]] < sz[i]) {
			mxch[now] = i;
		}
	}
}

pair<int, int> hdfs(int now, int pa) {
	sz[now] = 1;
	// multiset<int> hhs;
	vector<pair<int, int>> hhs;
	int esz = 1;

	for (int i : g[now]) if (i != pa) {
		auto ress = hdfs(i, now);
		sz[now] += sz[i];

		hhs.push_back(ress);
	}

	sort(hhs.begin(), hhs.end());
	int hhhh = sz[now];
	for (int i = 0, j = 0; i < (int)hhs.size(); i = j) {
		for (; j < hhs.size() && hhs[j].first == hhs[i].first; j++) {
			hhhh = (131LL * hhhh + hhs[j].first) % 1000000007;
		}
		esz += hhs[i].second;
	}
	hhhh = (123321LL * hhhh + sz[now]) % 1000000007;
	hhhh = (123321LL * hhhh + esz) % 1000000007;

	return make_pair(hhhh, esz);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs1(1, 0);

	vector<int> cen;
	for (int i = 1; i <= n; ++i) {
		if (max(sz[mxch[i]], n - sz[i]) <= n / 2) {
			cen.push_back(i);
		}
	}

	memset(sz, 0, sizeof(sz));
	memset(mxch, 0, sizeof(mxch));

	if (cen.size() == 1u) {
		cout << hdfs(cen[0], 0).second << '\n';
	} else {
		auto ans1 = hdfs(cen[0], 0);
		memset(sz, 0, sizeof(sz));
		memset(mxch, 0, sizeof(mxch));
		auto ans2 = hdfs(cen[1], 0);

		if (ans1.first == ans2.first) {
			cout << ans1.second / 2 << '\n';
		} else cout << ans1.second << '\n';
	}
}

