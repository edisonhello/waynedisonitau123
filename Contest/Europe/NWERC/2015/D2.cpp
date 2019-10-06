#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, r, p; scanf("%d%d%d", &n, &r, &p);
	if (n == 1) {
		puts("0");
		return 0;
	}
	long long ans = 1e18;
	for (int i = 1; i < 30; ++i) {
		int j = n - 1;
		for (int d = 30; d >= 0; --d) {
			int k = j - (1 << d);
			if (k < 0) continue;
			int rd = k % i;
			long long prod = 1;
			for (int z = 0; z < rd; ++z) {
				prod *= (k / i + 2);
				if (prod > n) prod = n;
			}
			for (int z = rd; z < i; ++z) {
				prod *= (k / i + 1);
				if (prod > n) prod = n;
			}
			if (prod >= n)
				j = k;
		}
		ans = min(ans, p * 1ll * j + r * 1ll * i);
	}
	printf("%lld\n", ans);
}
