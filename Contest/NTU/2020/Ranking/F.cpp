#include <bits/stdc++.h>
using namespace std;

int a[405], b[405];
int anx[405][105], bnx[405][105];
int apv[405][105], bpv[405][105];
int n, m;

map<tuple<int, int, int, int>, int> dp;

int Dfs(int a, int b, int c, int d) {
	// cerr << "Dfs " << a << ' ' << b << ' ' << c << ' ' << d << endl;
	auto it = dp.find(make_tuple(a, b, c, d));
	if (it != dp.end()) return it->second;

	int v = 0;
	
	for (int j = 1; j <= 100; ++j) {
		int aa = anx[a][j];
		int bb = apv[b][j];
		int cc = bnx[c][j];
		int dd = bpv[d][j];
		if (aa > bb || cc > dd) continue;
		v = max(v, Dfs(aa, bb, cc, dd));
	}

	if (::a[a] == ::a[b] && ::a[a] == ::b[c] && ::a[a] == ::b[d]) {
		if (a == b || c == d) v += 1;
		else v += 2;
	}

	// cerr << "Find " << a << ' ' << b << ' ' << c << ' ' << d << " val = " << v << endl;
	
	return dp[make_tuple(a, b, c, d)] = v;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];
	a[0] = 199;
	a[n + 1] = 200;
	b[0] = 201;
	b[m + 1] = 202;

	for (int j = 1; j <= 100; ++j) anx[n][j] = n + 1;
	for (int i = n - 1; i >= 0; --i) {
		for (int j = 1; j <= 100; ++j) anx[i][j] = anx[i + 1][j];
		anx[i][a[i + 1]] = i + 1;
	}
	for (int j = 1; j <= 100; ++j) bnx[n][j] = n + 1;
	for (int i = m - 1; i >= 0; --i) {
		for (int j = 1; j <= 100; ++j) bnx[i][j] = bnx[i + 1][j];
		bnx[i][b[i + 1]] = i + 1;
	}
	for (int j = 1; j <= 100; ++j) apv[1][j] = 0;
	for (int j = 1; j <= 100; ++j) bpv[1][j] = 0;
	for (int i = 2; i <= n + 1; ++i) {
		for (int j = 1; j <= 100; ++j) apv[i][j] = apv[i - 1][j];
		apv[i][a[i - 1]] = i - 1;
	}
	for (int i = 2; i <= m + 1; ++i) {
		for (int j = 1; j <= 100; ++j) bpv[i][j] = bpv[i - 1][j];
		bpv[i][b[i - 1]] = i - 1;
	}

	cout << Dfs(0, n + 1, 0, m + 1) << endl;
}
