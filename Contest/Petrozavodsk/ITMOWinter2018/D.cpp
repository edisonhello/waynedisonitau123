#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	double res = 0.0;
	double pv = 0.0;
	for (int t = n; t >= 1; t--) {
		double p = 1;
		for (int i = 0; i < (1 << t) - 1; ++i) {
			p *= 1.0 * ((1 << n) - k - i) / ((1 << n) - 1 - i);
		}
		res += (p - pv) * t;
		pv = p;
	}
	if (k > 1) res++;
	cout << fixed << setprecision(20) << res << "\n";
}

