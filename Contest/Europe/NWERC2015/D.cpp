#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
long long dp[maxn];

int main() {
	int n, r, p; scanf("%d%d%d", &n, &r, &p);
	for (int i = 2; i <= n; ++i) {
		dp[i] = 1e18;
		for (int j = 1; j < i; ) {
			// printf("i = %d j = %d\n", i, j);
			int k = (i + j - 1) / j;
			long long d = dp[j] + (k - 1) * 1ll * p + r;
			if (d < dp[i])
				dp[i] = d;
			int x = n / (j + 1);
			j = (n + x - 1) / x;
		}
	}
	printf("%lld\n", dp[n]);
}
