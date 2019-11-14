#include <bits/stdc++.h>
using namespace std;
#define isinf ghjfsije
#define double long double

double eps = 1e-12;
double pi = acos(-1);
bool same(double a, double b) { return abs(a - b) < eps; }

struct P;
struct L;

bool operator < (const P &a, const P &b) {
	return same(a.x, b.x) ? same(a.y, b.y) ? 0 : a.y < b.y : a.x < b.x;
}

P Intersect(L x, L y);

#define sq(x) ((x) * (x))

const double inf = 1e12;
// double eps = 1e-6; // 0 when integer
bool in_cc(P& p1, P& p2, P& p3, P& p4);
double side(P& a, P& b, P& p);
struct Tri;
struct Edge;
struct Tri {} pool[N * 10], *tris;
void edge( Edge a, Edge b );
struct Trig;
vector<Tri *> triang;
set<Tri *> vst;
void go(Tri *now);
void build(int n, P *ps);

bool jizz(L l1,L l2,L l3);
bool cmp(const L &a,const L &b);
vector<P> HPI(vector<L> &ls);

#define crx(a, b, c) ((b - a) ^ (c - a))
vector<P> convex(vector<P> ps);

P ps[N], ops[N];
map<P, int> ptoid;
vector<L> ls[N];
bool isinf[N];
double ans[N];

int gid(P &p) {
	auto it = ptoid.find(p);
	if (it == ptoid.end()) return -1;
	return it->second;
}

L make_line(P p, L l) {
	P d = l.pb - l.pa; d = d.spin(pi / 2);
	P m = (l.pa + l.pb) / 2;
	l = L(m, m + d);
	if (((l.pb - l.pa) ^ (p - l.pa)) < 0) l = L(m + d, m);
	return l;
}

double calc_ans(int i) {
	vector<P> ps = HPI(ls[i]);
	double rt = 0;
	for (int i = 0; i < (int)ps.size(); ++i) {
		rt += (ps[i] ^ ps[(i + 1) % ps.size()]);
	}
	return abs(rt) / 2;
}

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
	for (int i = 0; i < n; ++i) ops[i] = ps[i], ptoid[ops[i]] = i;

	random_shuffle(ps, ps + n);

	build(n, ps);

	for (auto *t : triang) {
		int z[3] = {gid(t->p[0]), gid(t->p[1]), gid(t->p[2])};
		for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (i != j && z[i] != -1 && z[j] != -1) {
			L l(t->p[i], t->p[j]);
			ls[z[i]].push_back(make_line(t->p[i], l));
		}
	}

	vector<P> tb = convex(vector<P>(ps, ps + n));
	for (auto &p : tb) isinf[gid(p)] = true;

	for (int i = 0; i < n; ++i) {
		if (isinf[i]) cout << -1 << '\n';
		else cout << fixed << setprecision(12) << calc_ans(i) << '\n';
	}
}
