#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x) * (x))

// #define double long double

const double eps = 1e-12;
const double pi = acos(-1);
bool same(double a, double b) {
	return abs(a - b) < eps;
}

struct P {
	double x, y;
	P() : x(0), y(0) {}
	P(double x, double y) : x(x), y(y) {}
	
	double abs() const {
		return hypot(x, y);
	}
	double angle() const {
		return atan2(y, x);
	}
};

P operator + (const P &a, const P &b) {
	return P(a.x + b.x, a.y + b.y);
}
P operator - (const P &a, const P &b) {
	return P(a.x - b.x, a.y - b.y);
}
P operator * (const P &a, double b) {
	return P(a.x * b, a.y * b);
}
P operator / (const P &a, double b) {
	return P(a.x / b, a.y / b);
}
double operator * (const P &a, const P &b) {
	return a.x * b.x + a.y * b.y;
}
double operator ^ (const P &a, const P &b) {
	return a.x * b.y - a.y * b.x;
}

bool operator < (const P &a, const P &b) {
	return same(a.x, b.x) ? same(a.y, b.y) ? 0 : a.y < b.y : a.x < b.x;
}

struct C {
	P c;
	double r;
	C() : c(), r(0) {}
	C(P p, double r) : c(p), r(r) {}
};

vector<pair<double, double>> CoverSegment(C &a, C &b) {
	double d = (a.c - b.c).abs();
	vector<pair<double, double>> res;
	if (same(a.r + b.r, d)) ;
	else if (d <= abs(a.r - b.r) + eps) {
		if (a.r < b.r) res.emplace_back(0, 2 * pi);
	} else if (d < abs(a.r + b.r) - eps) {
		double o = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d)), z = (b.c - a.c).angle();
		if (z < 0) z += 2 * pi;
		double l = z - o, r = z + o;
		if (l < 0) l += 2 * pi;
		if (r > 2 * pi) r -= 2 * pi;
		if (l > r) res.emplace_back(l, 2 * pi), res.emplace_back(0, r);
		else res.emplace_back(l, r);
	}
	return res;
}

double CircleUnionArea(vector<C> c) {
	int n = c.size();
	double a = 0, w;
	for (int i = 0; w = 0, i < n; ++i) {
		vector<pair<double, double>> s = {{2 * pi, 9}}, z;
		for (int j = 0; j < n; ++j) if (i != j) {
			z = CoverSegment(c[i], c[j]);
			for (auto &e : z) s.push_back(e);
		}
		sort(s.begin(), s.end());
		auto F = [&] (double t) { return c[i].r * (c[i].r * t + c[i].c.x * sin(t) - c[i].c.y * cos(t)); };
		for (auto &e : s) {
			if (e.first > w) a += F(e.first) - F(w);
			w = max(w, e.second);
		}
	}
	return a * 0.5;
}

vector<C> CircleUnique(vector<C> cs) {
	// cerr << "union" << endl;
	// for (C c : cs) cerr << c.c.x << ' ' << c.c.y << ' ' << c.r << endl;
	map<P, double> mp;

	for (C c : cs) {
		if (!mp.count(c.c)) mp[c.c] = c.r;
		else mp[c.c] = max(mp[c.c], c.r);
	}

	
	vector<C> r;
	for (auto p : mp) r.emplace_back(p.first, p.second);
	// cerr << "to" << endl;
	// for (C c : r) cerr << c.c.x << ' ' << c.c.y << ' ' << c.r << endl;
	return r;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	double A; cin >> A;

	vector<C> cs(n);
	for (int i = 0; i < n; ++i) {
		cin >> cs[i].c.x >> cs[i].c.y >> cs[i].r;
	}

	double L = 0, R = 1000000;
	int it = 90;
	while (it--) {
		double M = (L + R) / 2;
		vector<C> ccs;
		
		for (C c : cs) {
			if (c.r > M) continue;
			ccs.emplace_back(c.c, M - c.r);
		}

		if (CircleUnionArea(CircleUnique(ccs)) >= A) {
			R = M;
		} else {
			L = M;
		}
	}

	cout << fixed << setprecision(12) << L << endl;

}

