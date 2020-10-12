#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; while (cin >> n) {
		if (!n) return 0;
		vector<pair<double, int>> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;

		sort(v.begin(), v.end());

		auto meow = [&] (int n, vector<pair<double, int>> v) {

		vector<int> pre(n,0), suf(n,0);

		for (int i = 0; i < n; ++i) {
			if (v[i].second == 1) ++pre[i];
			else ++suf[i];
		}

		for (int i = 1; i < n; ++i) pre[i] += pre[i-  1];
		for (int i = n - 2; i >=0 ;--i) suf[i] += suf[i + 1];

		int mx = max(pre.back(), suf[0]);
		for (int i = 0; i < n - 1; ++i) {
			mx = max(mx, pre[i] + suf[i + 1]);
		}

		return mx;
		};

		int mx = meow(n, v);
		for (int i = 0; i < n; ++i) v[i].second ^= 1;
		mx = max(mx, meow(n, v));
		cout << mx << '\n';
	}
}
