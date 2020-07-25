#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i] >> b[i];
	}
	int m;
	cin >> m;
	vector<int> u(m), v(m);
	for (int i = 0; i < m; ++i) {
		cin >> u[i] >> v[i];
	}
	vector<int> x(n), y(m);
	iota(x.begin(), x.end(), 0);
	iota(y.begin(), y.end(), 0);
	sort(x.begin(), x.end(), [&](int i, int j) { return a[i] > a[j]; });
	sort(y.begin(), y.end(), [&](int i, int j) { return u[i] > u[j]; });
	constexpr int kM = 100'000;
	vector<int> tree(kM * 4, n);

	auto Modify = [&](int p, int v) {
		auto _ = [&](auto self, int l, int r, int o = 0) {
			if (r - l == 1) {
				tree[o] = min(tree[o], v);
				return;
			}
			int m = (l + r) >> 1;
			if (p < m) self(self, l, m, o * 2 + 1);
			else self(self, m, r, o * 2 + 2);
			tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
		};
		_(_, 0, kM);
	};

	auto Query = [&](int ql, int qr) {
		auto _ = [&](auto self, int l, int r, int o = 0) {
			if (l >= qr || ql >= r) return n;
			if (l >= ql && r <= qr) return tree[o];
			int m = (l + r) >> 1;
			return min(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
		};
		return _(_, 0, kM);
	};

	int64_t res = 0;
	for (int i = 0, j = 0; i < m; ++i) {
		while (j < n && a[x[j]] >= u[y[i]]) {
			Modify(b[x[j]] - 1, x[j]);
			j++;
		}
		int r = Query(0, v[y[i]]);
		if (r < n) res += r + 1;
	}
	cout << res << "\n";
	return 0;
}

