#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

struct point {
	double x, y, z;
	point() {}
	point(double x, double y, double z): x(x), y(y), z(z) {}
	point(int phi, int lambda) {
		double p = pi * phi / 180, l = pi * lambda / 180;
		x = cos(p) * cos(l);
		y = cos(p) * sin(l);
		z = sin(p);
	}
	double operator*(const point &p) const {
		return x * p.x + y * p.y + z * p.z;
	}
	point operator^(const point &p) const {
		return point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}
	double abs() {
		return sqrt(x * x + y * y + z * z);
	}
};

double dist(point a, point b) {
	return acos((a * b) / a.abs() / b.abs());
}

point mid(point a, point b) {
	double x = 0.5 * (a.x + b.x);
	double y = 0.5 * (a.y + b.y);
	double z = 0.5 * (a.z + b.z);
	double len = sqrt(x * x + y * y + z * z);
	x *= 1. / len;
	y *= 1. / len;
	z *= 1. / len;
	return point(x, y, z);
}

const int maxn = 100;
vector<point> cont[maxn];

int plane(point p, point l) {
	double res = p * l;
	return res > 0;
}

bool equal(point a, point b) {
	return fabs(a.x - b.x) < 1e-9 && fabs(a.y - b.y) < 1e-9 && fabs(a.z - b.z) < 1e-9;
}

point inter(point a, point b, point c, point d) {
	point ab = (a ^ b), cd = (c ^ d);
	// printf("a = (%.5lf, %.5lf, %.5lf)\n", a.x, a.y, a.z);
	// printf("b = (%.5lf, %.5lf, %.5lf)\n", b.x, b.y, b.z);
	// printf("c = (%.5lf, %.5lf, %.5lf)\n", c.x, c.y, c.z);
	// printf("d = (%.5lf, %.5lf, %.5lf)\n", d.x, d.y, d.z);
	if (plane(a, cd) == plane(b, cd) || plane(c, ab) == plane(d, ab))
		return point(1e9, 1e9, 1e9);
	point z1, z2;
	{
		point l = a, r = b;
		int sgn = plane(l, cd);
		for (int it = 0; it < 50; ++it) {
			point m = mid(l, r);
			if (plane(m, cd) == sgn)
				l = m;
			else
				r = m;
		}
		assert(plane(l, cd) == plane(a, cd));
		if (equal(l, a) || equal(l, b))
			return point(1e9, 1e9, 1e9);
		z1 = l;
	}
	{
		point l = c, r = d;
		int sgn = plane(l, ab);
		for (int it = 0; it < 50; ++it) {
			point m = mid(l, r);
			if (plane(m, ab) == sgn)
				l = m;
			else
				r = m;
		}
		assert(plane(l, ab) == plane(c, ab));
		if (equal(l, c) || equal(l, d))
			return point(1e9, 1e9, 1e9);
		z2 = l;
	}
	if (equal(z1, z2))
		return z1;
	
	return point(1e9, 1e9, 1e9);
	printf("z1 = (%.5lf, %.5lf, %.5lf)\n", z1.x, z1.y, z1.z);
	printf("z2 = (%.5lf, %.5lf, %.5lf)\n", z2.x, z2.y, z2.z);
	assert(equal(z1, z2));
	return z1;
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int m; scanf("%d", &m);
		for (int j = 0; j < m; ++j) {
			int p, l; scanf("%d%d", &p, &l);
			cont[i].emplace_back(p, l);
			// printf("%.5lf %.5lf %.5lf\n", cont[i].back().x, cont[i].back().y, cont[i].back().z);
		}
	}
	int m; scanf("%d", &m);
	vector<point> path;
	for (int i = 0; i < m; ++i) {
		int p, l; scanf("%d%d", &p, &l);
		path.emplace_back(p, l);
	}
	int lnd = 1;
	double land = 0.0;
	double all = 0.0;
	double check = 0.0;
	for (int i = 0; i < m - 1; ++i) check += dist(path[i], path[(i + 1) % m]);
	for (int i = 0; i < m - 1; ++i) {
		vector<point> s;
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < (int)cont[j].size(); ++k) {
				point a = path[i], b = path[(i + 1) % m];
				point c = cont[j][k], d = cont[j][(k + 1) % (int)cont[j].size()];
				point e = inter(a, b, c, d);
				if (e.x > 7122) continue;
				s.push_back(e);	
			}
		}
		sort(s.begin(), s.end(), [&](point a, point b) {
			return a * path[i] > b * path[i];
		});
		// cout << "s.size() = " << s.size() << endl;
		s.push_back(path[(i + 1) % m]);
		point p = path[i];
		for (int j = 0; j < (int)s.size(); ++j) {
			if (lnd) land += dist(s[j], p);
			// printf("s[j] = (%.5lf, %.5lf, %.5lf)\n", s[j].x, s[j].y, s[j].z);
			// printf("p = (%.5lf, %.5lf, %.5lf)\n", p.x, p.y, p.z);
			// printf("distance = %.20lf\n", dist(s[j], p));
			all += dist(s[j], p);
			if (j != (int)s.size() - 1) lnd ^= 1;
			p = s[j];
		}
	}
	check *= 6370;
	printf("%.20lf %.20lf\n", all * 6370, 100 - 100 * land / all);
}
