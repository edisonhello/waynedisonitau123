#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		string A, B;
		cin >> A >> B;
		vector<int> s(N + 1);
		for (int i = 0; i < N; ++i) {
			s[i + 1] = s[i] + (A[i] == '1');
		}
		for (int i = 0; i <= N; ++i) {
			s[i] <<= 1;
			s[i] -= i;
		}

		using Bs = bitset<100001>;
		vector<int> order(N + 1);
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [&](int i, int j) {
			return s[i] < s[j];
		});

		Bs lt{}, gt{};
		Bs ans{};
		for (int i = 0; i < N; ++i) {
			gt.set(-i + N);
		}
		for (int i = 0, j = 0; i < order.size(); ++i) {
			while (j < order.size() && s[order[j]] < s[order[i]]) {
				if (order[j] < N) {
					lt.set(-order[j] + N);
					gt.reset(-order[j] + N);
				}
				j++;
			}
			// cout << "cur = " << order[i] << endl;
			// cout << "lt = "; for (int i = 0; i < N; ++i) cout << lt[-i + N]; cout << "\n";
			// cout << "gt = "; for (int i = 0; i < N; ++i) cout << gt[-i + N]; cout << "\n";

			if (order[i] > 0) {
				if (B[order[i] - 1] == '0') {
					ans |= lt << order[i];	
				} else {
					ans |= gt << order[i];
				}
			}
		}
		int mx = -1'000'000'000, mn = 1'000'000'000;
		for (int k = 1; k <= N; ++k) {
			if (B[k - 1] == '0') mx = max(mx, s[k]);
			if (B[k - 1] == '1') mn = min(mn, s[k]);
			int res = (int(ans[k + N]) ^ 1);
			if (mn <= 0 || mx > 0) res = 0;
			cout << res;
		}
		cout << "\n";
	}
	return 0;
}

