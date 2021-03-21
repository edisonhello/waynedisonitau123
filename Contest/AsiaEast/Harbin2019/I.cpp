#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		if (v[0] != 0 || v.back() != n - 1) {
			cout << 0 << '\n';
			continue;
		}
		bool bad = 0;
		for (int i = 1; i < n; ++i) {
			if (v[i] < v[i - 1]) {
				bad = 1;
				break;
			}
		}
		if (bad) {
			cout << 0 << '\n';
			continue;
		}

		int fn = 0;
		int ans = 1;

		for (int i = 1; i < n; ++i) {
			if (v[i] == v[i - 1]) {
				ans = 1ll * ans * fn % mod;
				--fn;
			} else {
				fn += abs(v[i] - v[i - 1]) - 1;
				ans = ans * 2ll % mod;
			}
		}

		cout << ans << '\n';
	}
}

