#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct P {
	int x, y, i;
	P() : x(0), y(0), i(-1) {}
};

struct Frac {
	int u, d;
	void norm() {
		if (d == 0) {
			u = u > 0 ? 1 : u < 0 ? -1 : 0;
			return;
		}
		int g = __gcd(u, d);
		u /= g;
		d /= g;
		if (d < 0) {
			d *= -1;
			u *= -1;
		}
	}
};

bool operator > (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d > 1ll * b.u * a.d;
}
bool operator >= (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d >= 1ll * b.u * a.d;
}
bool operator < (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d < 1ll * b.u * a.d;
}
bool operator <= (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d <= 1ll * b.u * a.d;
}
ostream& operator << (ostream &o, const Frac &f) {
	o << f.u << "/" << f.d;
	return o;
}

Frac Slope(P &a, P &b) {
	Frac f;
	f.u = b.y - a.y;
	f.d = b.x - a.x;
	f.norm();
	return f;
}

int rit() {
	char c; bool flag = false;
	int x;
	while (c = getchar(), (c < '0' && c != '-') || c > '9');
	c == '-' ? (flag = true, x = 0) : (x = c & 15);
	while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
	return flag ? -x : x;
}

void solve(int n, int m) {
	vector<P> curve(n);
	for (int i = 0; i < n; ++i) {
		curve[i].x = rit();
		curve[i].y = rit();
	}

	vector<Frac> slopes;
	for (int i = 0; i < n - 1; ++i) {
		slopes.push_back(Slope(curve[i], curve[i + 1]));
	}

	for (int i = 0; i < m; ++i) {
		P query;
		query.x = rit();
		query.y = rit();

		int L = 0, R = n - 1;
		while (L < R) {
			int M = (L + R) >> 1;

			// cerr << "L M R " << L << ' ' << M << ' ' << R << endl;

			if (M == 0) {
				if (slopes[0] <= Slope(curve[0], query)) {
					L = R = 0;
				} else {
					L = M + 1;
				}
			} else {
				Frac m = Slope(query, curve[M]);
				Frac lm = slopes[M - 1];
				Frac rm = slopes[M];
				// cout << "lm m rm " << lm << ' ' << m << ' ' << rm << endl;
				if (lm > m && m >= rm) {
					L = R = M;
				} else if (m >= lm) {
					R = M - 1;
				} else {
					L = M + 1;
				}
			}
		}

		cout << L + 1 << '\n';
	}


}

int main() {
	int n, m; while (true) {
		n = rit();
		m = rit();
		if (!(n | m)) return 0;
		solve(n, m);
	}
}
