#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, c;
	cin >> n >> c;
	vector<int> a(n);
	vector<vector<int>> p(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i]--;
		p[a[i]].push_back(i);
	}

	vector<int64_t> A(n), B(n);

	auto ModifyA = [&](int ql, int qr, int v) {
		A[ql] += v;
		if (qr < n) A[qr] -= v;
	};

	auto ModifyB = [&](int ql, int qr, int v) {
		B[ql] += v;
		if (qr < n) B[qr] -= v;
	};

	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < p[i].size(); ++j) {
			if (j > 0) {
				int pv = p[i][j - 1];
				ModifyA((pv + p[i][j]) / 2, p[i][j], -1);
				ModifyB((pv + p[i][j]) / 2, p[i][j], p[i][j]);
			} else {
				ModifyA(0, p[i][j], -1);
				ModifyB(0, p[i][j], p[i][j]);
			}
			if (j + 1 < p[i].size()) {
				int pv = p[i][j + 1];
				ModifyA(p[i][j], (pv + p[i][j]) / 2, 1);
				ModifyB(p[i][j], (pv + p[i][j]) / 2, -p[i][j]);
			} else {
				ModifyA(p[i][j], n, 1);
				ModifyB(p[i][j], n, -p[i][j]);
			}
		}
	}
	int64_t pp = 1LL * n * n, qq = 1;
	for (int i = 0; i < n; ++i) {
		if (i > 0) {
			A[i] += A[i - 1];
			B[i] += B[i - 1];
		}
		int64_t a = A[i];
		int64_t b = B[i];
		int64_t sum = 1LL * a * i + b;
		int64_t dm = c;
		int64_t g = __gcd(sum, dm);
		sum /= g;
		dm /= g;
		if (sum * qq < pp * dm) {
			pp = sum;
			qq = dm;
		}
	}
	cout << pp << "/" << qq << "\n";
	return 0;
}

