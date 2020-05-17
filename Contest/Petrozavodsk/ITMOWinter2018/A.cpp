#include <bits/stdc++.h>
#define double long double
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(15);
	int t; cin >> t; while (t--) {
		int n;
		double l, r; 
		cin >> n >> l >> r;

		auto f2 = [&](double x) {
			return r * x - x * x / 2 + x * x * log(x) / 4 - x * x / 8 - x * x * log(r) / 4;
		};

		auto xlnx = [&](double x) {
			return x * x * log(x) / 2 - x * x / 4;
		};

		auto x2lnx = [&](double x) {
			return x * x * x * log(x) / 3 - x * x * x / 9;
		};

		auto x3lnx = [&](double x) {
			return x * x * x * x * log(x) / 4 - x * x * x * x / 16;
		};

		auto x3ln3x = [&](double x) {
			return x * x * x * x * log(x) * log(x) * log(x) / 4 - 3 * x * x * x * x * log(x) * log(x) / 16 + 6 * x * x * x * x * log(x) / 64 - 6 * x * x * x * x / 256;
		};

		auto x2ln2x = [&](double x) {
			return x * x * x * log(x) * log(x) / 3 - 2 * x * x * x * log(x) / 9 + 2 * x * x * x / 27;
		};

		auto x3ln2x = [&](double x) {
			return x * x * x * x * log(x) * log(x) / 4 - x * x * x * x * log(x) / 8 + x * x * x * x / 32;
		};

		auto f3 = [&] (double x) {
			return r * r * x + x * x * x / 9 * pow(log(r), 2) + x * x * x / 3 + x * x * x * log(x) * log(x) / 9 - 2 * x * x * x * log(x) / 27 + 2 * x * x * x / 81
				- r * x * x * log(r) / 2 - r * x * x + r * x * x * log(x) / 2 - r * x * x / 4 
				+ x * x * x / 3 * log(r) - 2 * x * x * x * log(x) * log(r) / 9 + 2 * x * x * x * log(r) / 27 - x * x * x * log(x) / 3 + x * x * x / 9;
		};

		auto fx = [&](double x) {
			return r * r * x * x / 2 + x * x *x *x / 12 * log(r) * log(r) + x * x * x * x / 4 + x3ln2x(x) / 3 - r * log(r) * x * x * x / 3 - 2 * r * x * x * x / 3 + r * x2lnx(x) + x * x * x * x / 4 * log(r) - 2 * x3lnx(x) * log(r) / 3 - x3lnx(x);
		};

		auto fylnr = [&] (double x) {
			double lnr = log(r), lnx = log(x);
			return - x * x / 4 * r * r * lnr - x * x * x * x * lnr * lnr * lnr / 16 - x * x * x * x * lnr / 8 - x3ln2x(x) * lnr / 4
				+ 2 * r * x * x * x * lnr * lnr / 9 + r * x * x * x * lnr / 3 - 2 * r * x2lnx(x) * lnr / 3
				- 2 * x * x * x * x * lnr * lnr / 12 + x3lnx(x) * lnr * lnr / 2 + 2 * x3lnx(x) * lnr / 3;
		};

		auto fylnx = [&] (double x) {
			double lnr = log(r), lnx = log(x);
			return r * r / 2 * xlnx(x) + lnr * lnr / 4 * x3lnx(x) + x3lnx(x) / 2 + x3ln3x(x) / 4
				- 2 * r / 3 * lnr * x2lnx(x) - r * x2lnx(x) + 2 * r * x2ln2x(x) / 3 
				+ 2 * lnr * x3lnx(x) / 3 - lnr * x3ln2x(x) / 2 - 2 * x3ln2x(x) / 3;
		};

		auto f4 = [&](double x) {
			return r * f3(x) - fx(x) + fylnr(x) + fylnx(x);
		};

		if (n == 2) {
			double a = pow((double)1 / (r - l), 2);
			cout << 2 * a * (f2(r) - f2(l)) << endl;
		} else if (n == 3) {
			double a = pow((double)1 / (r - l), 3);
			cout << 3 * a * (f3(r) - f3(l)) << endl;
		} else {
			double a = pow((double)1 / (r - l), 4);
			cout << 4 * a * (f4(r) - f4(l)) << endl;
		}

	}
}

