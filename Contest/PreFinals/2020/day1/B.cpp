#include <bits/stdc++.h>
using namespace std;

struct Line {
	mutable int64_t a, b, p;
	bool operator<(const Line &rhs) const { return a < rhs.a; }
	bool operator<(const int64_t x) const { return p < x; }
};

struct DynamicHull : multiset<Line, less<>> {
	static const int64_t kInf = 1'000'000'000'000'000'000;
	static int64_t Div(int64_t a, int64_t b) {
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool Isect(iterator x, iterator y) {
		if (y == end()) {
			x->p = kInf;
			return false;
		}
		if (x->a == y->a) {
			x->p = x->b > y->b ? kInf : -kInf;
		} else {
			x->p = Div(y->b - x->b, x->a - y->a);
		}
		return x->p >= y->p;
	}
	void Insert(int64_t a, int64_t b) {
		auto z = insert({-a, -b, 0}), y = z++, x = y;
		while (Isect(y, z)) z = erase(z);
		if (x != begin() && Isect(--x, y)) Isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) Isect(x, erase(y));
	}
	int64_t Query(int64_t x) {
		auto l = *lower_bound(x);
		return -(l.a * x + l.b);
	}
};

int main() {
	int r;
	cin >> r;
	int n = (1 << r);
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];

	constexpr int64_t kInf = 1'000'000'000'000'000'000;

	auto Square = [&](int x) { return 1LL * x * x; };

	auto Solve = [&](auto self, int l, int r) -> vector<int64_t> {
		if (r - l == 1) {
			return {0};
		}
		int m = (l + r) >> 1;
		auto x = self(self, l, m);
		auto y = self(self, m, r);
		int k = m - l;
		vector<int64_t> res(r - l, kInf);
		vector<int> u(k), v(k);
		iota(u.begin(), u.end(), 0);
		iota(v.begin(), v.end(), 0);
		sort(u.begin(), u.end(), [&](int c, int d) { return a[l + c] < a[l + d]; });
		sort(v.begin(), v.end(), [&](int c, int d) { return a[m + c] < a[m + d]; });
		DynamicHull hull;
		multiset<int64_t> s;
		for (int i = 0; i < k; ++i) s.insert(y[i]);
		for (int i = k - 1, j = k - 1; i >= 0; --i) {
			while (j >= 0 && a[m + v[j]] > a[l + u[i]]) {
				hull.Insert(-2 * a[m + v[j]], 1LL * a[m + v[j]] * a[m + v[j]] + y[v[j]]);
				s.erase(s.find(y[v[j]]));
				j--;
			}
			if (!hull.empty()) {
				res[u[i]] = min(res[u[i]], hull.Query(a[l + u[i]]) + (int64_t)a[l + u[i]] * a[l + u[i]] + x[u[i]]);
			}
			if (!s.empty()) {
				res[u[i]] = min(res[u[i]], x[u[i]] + *s.begin());
			}
		}
		s.clear();
		hull.clear();
		for (int i = 0; i < k; ++i) s.insert(x[i]);
		for (int i = k - 1, j = k - 1; i >= 0; --i) {
			while (j >= 0 && a[l + u[j]] > a[m + v[i]]) {
				hull.Insert(-2 * a[l + u[j]], 1LL * a[l + u[j]] * a[l + u[j]] + x[u[j]]);
				s.erase(s.find(x[u[j]]));
				j--;
			}
			if (!hull.empty()) {
				res[k + v[i]] = min(res[k + v[i]], hull.Query(a[m + v[i]]) + (int64_t)a[m + v[i]] * a[m + v[i]] + y[v[i]]);
			}
			if (!s.empty()) {
				res[k + v[i]] = min(res[k + v[i]], y[v[i]] + *s.begin());
			}
		}
		// for (int i = 0; i < k; ++i) {
		// 	for (int j = 0; j < k; ++j) {
		// 		int64_t g = a[i + l] >= a[m + j] ? 0 : Square(a[i + l] - a[m + j]);
		// 		res[i] = min(res[i], x[i] + y[j] + g);
		// 		int64_t h = a[i + l] <= a[m + j] ? 0 : Square(a[i + l] - a[m + j]);
		// 		res[j + k] = min(res[j + k], x[i] + y[j] + h);
		// 	}
		// }
		return res;
	};

	cout << Solve(Solve, 0, n)[0] << endl;
	return 0;
}

