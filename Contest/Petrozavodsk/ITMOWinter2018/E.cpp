#include <bits/stdc++.h>
using namespace std;

int main() {
	int64_t n;
	cin >> n;

	auto fpow = [&](uint64_t a, int64_t n) -> uint64_t {
		uint64_t res = 1;
		while (n > 0) {
			if (n & 1) res *= a;
			a *= a;
			n >>= 1;
		}
		return res;
	};

	// constexpr int kN = (1 << 22);

	// vector<uint64_t> fc(kN, 1);
	// for (int i = 1; i < kN; ++i) {
	// 	fc[i] = fc[i - 1] * i;
	// }

	uint64_t cyc = 1;
	for (int i = 1; i < (1 << 22); i += 2) cyc *= i;

	auto g = [&](int64_t n) {
		assert(n % 2 == 0);
		if (n < (1 << 22)) {
			uint64_t res = 1;
			for (int i = 1; i < n; i += 2) res *= i;
			return res;
		}
		int64_t k = n / (1 << 22);	
		uint64_t res = fpow(cyc, k);
		for (int64_t i = k * (1 << 22) + 1; i < n; i += 2) res *= i;
		return res;
	};

	function<uint64_t(int64_t)> f = [&](int64_t n) -> uint64_t {
		if (n < 2) return 1;
		if (n % 2 == 1) return f(n + 1);
		return f(n / 2) * g(n);
	};

	cout << f(n) << "\n";
}

