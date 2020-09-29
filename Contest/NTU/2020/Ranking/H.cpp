#include <bits/stdc++.h>
using namespace std;

double test(double a, double b, double c) {
	if (a >= b + c || b >= a + c || c >= a + b) return 0;
	double s = (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
	int t; cin >> t; while (t--) {
		double a, b, c, d; cin >> a >> b >> c >> d;
		cout << fixed << setprecision(12);
		double mx = max(max(max(test(a, b, c), test(a, b, d)), test(c, b, d)), test(a, c, d));
		mx = max(test(a + b, c, d), mx);
		mx = max(test(a + c, b, d), mx);
		mx = max(test(a + d, b, c), mx);
		mx = max(test(b + c, a, d), mx);
		mx = max(test(b + d, a, c), mx);
		mx = max(test(c + d, a, b), mx);
		cout << mx * 3 << '\n';;
	}
}
