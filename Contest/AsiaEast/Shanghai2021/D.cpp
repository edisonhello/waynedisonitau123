#include <bits/stdc++.h>
using namespace std;


int main() {
	int t; cin >> t;

	while (t--) {

		long long p, q; cin >> p >> q;

		long long g = __gcd( p, q);
		p /= g;
		q /= g;

		long long d = p * p - 4 * q * q;
		if (d < 0) {
			cout << "0 0" << '\n';
			continue;
		}

		long long z = round(sqrt(d));
		if (z * z != d) {
			cout << "0 0\n";
			continue;
		}

		auto solve = [&](long long x) -> bool {
			if (x & 1) {
				return false;
			}

			x /= 2;

			long long y = round(sqrt(x));
			if (y * y != x) {
				return false;
			}

			cout << y << ' ' << q / y << '\n';
			return true;

		};

		if (!( solve(p + z) || solve(p - z))) {
				cout << "0 0\n";
			}



	}
}

