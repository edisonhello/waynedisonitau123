#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

const int kITR2 = 40;
const int kITR3 = 50;

const double eps = 1e-9;
const double pi = acos(-1);

bool same(double a, double b) { return abs(a - b) < eps; }

struct P {
	double x, y; 
	P() : x(0), y(0) {}
	P(double x, double y) : x(x), y(y) {}
	P operator + (P b){ return P(x + b.x, y + b.y); }
	P operator - (P b){ return P(x - b.x, y - b.y); }
	P operator * (double b){ return P(x * b, y * b); }
	P operator / (double b){ return P(x / b, y / b); }
	double operator * (P b) { return x * b.x + y * b.y; }
	double operator ^ (P b) { return x * b.y - y * b.x; }
	double abs() { return hypot(x, y); }
	P unit() { return *this / abs(); }
	P spin(double o) {
		double c = cos(o), s = sin(o);
		return P(c * x - s * y, s * x + c * y);
	}
};

struct L {
	double a, b, c, o;
	P pa, pb;
	L() : a(0), b(0), c(0), pa(), pb() {}
	L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
	P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
	double area() { return pa ^ pb; }
};

P ps[5005];
L ls[5005];

double segarea[5005][5005];

int nxt[5005], prv[5005];
int cnt[5005];

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> ps[i].x >> ps[i].y;
		nxt[i] = (i + 1) % n;
		prv[i] = (i - 1 + n) % n;
	}
	double area = 0;
	for (int i = 0; i < n; ++i) {
		ls[i] = L(ps[i], ps[nxt[i]]);
		area += ls[i].area();
	}

	for (int i = 0; i < n; ++i) {
		bool no = true;
		for (int j = i; j != i || no; j = nxt[j]) {
			no = false;
			segarea[i][j] = segarea[i][prv[j]] + ls[j].area();
			// cerr << "segarea " << i << " " << j << " = " << segarea[i][j] << endl;
		}
	}


	double AMIN = 1e9, AMAX = 0;
	auto update = [&] (double x) {
		// cerr << "Update with " << x << endl;
		AMIN = min(AMIN, x);
		AMAX = max(AMAX, x);
	};

	auto solve = [&] (int i, int j) {
		// cerr << "solve " << i << " " << j << endl;
		double s1 = 0, s2 = 0;
		// cerr << "ls[j].pa = " << ls[j].pa.x << " " << ls[j].pa.y << " ls[i].pb = " << ls[i].pb.x << " " << ls[i].pb.y << endl;
		s1 = segarea[nxt[i]][prv[j]] + (ls[j].pa ^ ls[i].pb);
		s2 = segarea[nxt[j]][prv[i]] + (ls[i].pa ^ ls[j].pb);
		if (nxt[i] == j) s1 = 0;
		if (nxt[j] == i) s2 = 0;

		// cerr << "s1 = " << s1 << ", s2 = " << s2 << endl;

		if (s1 >= area / 2 - eps || s2 >= area / 2 - eps) return;
		double tarea = ls[i].area() + (ls[i].pb ^ ls[j].pa) + ls[j].area() + (ls[j].pb ^ ls[i].pa);

		// cerr << "tarea = " << tarea << endl;

		if (s1 + tarea <= area / 2 + eps || s2 + tarea <= area / 2 + eps) return;

		auto gcl = [&] (P mp) -> double {
			bool can_update = true;
			// cerr << "gcl mp = " << mp.x << ", " << mp.y << endl;
			double L = 0, R = 1;
			int itr = kITR2;
			P mmp;
			while (itr--) {
				double M = (L + R) / 2;
				mmp = ls[j].pa * M + ls[j].pb * (1 - M);
				double as1 = (mp ^ ls[i].pb) + (ls[i].pb ^ ls[j].pa) + (ls[j].pa ^ mmp) + (mmp ^ mp);
				double as2 = tarea - as1;
				// assert(abs(as2 - ((mmp ^ ls[j].pb) + (ls[j].pb ^ ls[i].pa) + (ls[i].pa ^ mp) + (mp ^ mmp))) < 1e-5);

				if (s1 + as1 < s2 + as2) R = M;
				else L = M;

				// cerr << "inner BS M = " << M << ", mmp = " << mmp.x << " " << mmp.y << endl;
				// cerr << "as1 = " << as1 << " as2 = " << as2 << endl;
				// cerr << "difference between two area = " << abs(s1 + as1 - s2 - as2) << endl;

				if (abs(s1 + as1 - s2 - as2) > area / 1e10) can_update = false;
				else can_update = true;
			}

			// cerr << "gcl ans = " << (mp - mmp).abs() << ", update = " << can_update << endl;
			double len = (mp - mmp).abs();
			if (can_update) update(len);

			return len;
		};

		double L = 0, R = 1;
		int itr = kITR3;
		while (itr--) {
			double ML = (L * 2 + R * 1) / 3;
			double MR = (L * 1 + R * 2) / 3;
			// cerr << "outer TS1 " << ML << " " << MR << endl;
			P mlp = ls[i].pa * ML + ls[i].pb * (1 - ML);
			P mrp = ls[i].pa * MR + ls[i].pb * (1 - MR);
			double al = gcl(mlp);
			double ar = gcl(mrp);

			// cerr << "outer TS1 answer = " << al << " " << ar << endl;

			if (al < ar) R = MR;
			else L = ML;
		}

		L = 0, R = 1;
		itr = kITR3;
		while (itr--) {
			double ML = (L * 2 + R * 1) / 3;
			double MR = (L * 1 + R * 2) / 3;
			// cerr << "outer TS2 " << ML << " " << MR << endl;
			P mlp = ls[i].pa * ML + ls[i].pb * (1 - ML);
			P mrp = ls[i].pa * MR + ls[i].pb * (1 - MR);
			double al = gcl(mlp);
			double ar = gcl(mrp);

			// cerr << "outer TS2 answer = " << al << " " << ar << endl;

			if (al > ar) R = MR;
			else L = ML;
		}

		if (nxt[j] != i) gcl(ls[i].pa); 
		if (nxt[i] != i) gcl(ls[i].pb);
	};

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j != i; j = nxt[j]) {
			solve(i, j);
		}
	}

	cout << fixed << setprecision(12) << AMIN << endl << AMAX << endl;
}
