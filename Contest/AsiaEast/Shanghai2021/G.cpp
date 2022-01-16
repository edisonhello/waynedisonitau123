#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int fac[200005];
int ifac[200005];

int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int pw(int b, int n) {
	int a = 1;
	while (n) {
		if (n & 1) a = 1ll * a * b % mod;
		b = 1ll * b * b % mod;
		n >>= 1;
	}
	return a;
}

int inv(int x) {
	return pw(x, mod - 2);
}

vector<int> g[200005];

pair<int, int> dfs(int now, int pa) {
	int mul = 1;
	int cntfre = 0;
	for (int i : g[now]) if (i != pa) {
		auto [res, fre] = dfs(i, now);
		mul = 1ll * mul * res % mod;
		cntfre += fre;
	}

	int add = 1;
	int grp = 0;
	while (cntfre >= 2) {
		add = 1ll * C(cntfre, 2) * add % mod;
		cntfre -= 2;
		++grp;
	}

	add = 1ll * add * ifac[grp] % mod;
	return pair{(int)(1ll * mul * add % mod), 1 - cntfre};

}

int main() {
	fac[0] = 1;
	for (int i = 1; i <= 200000; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[200000] = inv(fac[200000]);
	for (int i = 199999; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;

	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	auto [dp, fre] = dfs(1, 0);

	assert(fre);
	cout << dp << endl;

}

