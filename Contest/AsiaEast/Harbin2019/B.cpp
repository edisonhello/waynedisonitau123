#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int M, N;
		cin >> M >> N;
		vector<int> L(N), R(N), l(N), r(N);
		for (int i = 0; i < N; ++i) cin >> L[i] >> R[i];
		for (int i = 0; i < N; ++i) l[i] = L[i], r[i] = R[i];
		for (int i = 1; i < N; ++i) {
			int p = -1;
			for (int b = 0; b < M; ++b) {
				if (L[i] >> b & 1) {
					p = b;
					break;
				}
			}
			l[i - 1] = max(l[i - 1], L[i] ^ (1 << p));
			int v = L[i];
			for (int b = 0; b < p; ++b) v ^= (1 << b);
			r[i] = min(r[i], v);
		}
		constexpr int kP = 100'000'000 + 7;
		int ans = 1;
		for (int i = 0; i < N; ++i) {
			int s = 0;
			for (int j = l[i]; j <= r[i]; ++j) (s += j) %= kP;
			ans = 1LL * ans * s % kP;
		}
		cout << ans << "\n";
	}
}

