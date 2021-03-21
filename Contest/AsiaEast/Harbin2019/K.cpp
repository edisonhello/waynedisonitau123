#include <bits/stdc++.h>
using namespace std;


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n, k; cin >> n >> k;
		vector<int> w(n);
		long long totw = 0;
		for (int i = 0; i < n; ++i) {
			cin >> w[i];
			totw += w[i];
		}

		double u = (double)k / totw;
		for (int i = 0; i < n; ++i) {
			cout << fixed << setprecision(8) << w[i] + u * w[i] << ' ';
			w[i] += u * w[i];
		}
		cout << '\n';
	}
}

