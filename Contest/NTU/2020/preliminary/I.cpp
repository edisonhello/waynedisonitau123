#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

pair<int, int> ps[2505]; 

int32_t main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> ps[i].first >> ps[i].second;

	if (n == 1) {
		cout << 1 << endl;
		exit(0);
	}

	int mx = 2;
	vector<pair<int, int>> po;
	vector<pair<int, int>> d;
	for (int i = 0; i < n; ++i) {
		po.clear();
		d.clear();

		for (int j = 0; j < n; ++j) if (j != i) po.push_back(ps[j]);

		auto [x, y] = ps[i];
		for (auto [nx, ny] : po) {
			int dx = nx - x;
			int dy = ny - y;
			if (dy < 0) {
				dy = -dy;
				dx = -dx;
			} else if (dy == 0 && dx < 0) {
				dx = -dx;
			}

			int g = __gcd(dx, dy);
			dx /= g;
			dy /= g;
			d.emplace_back(dx, dy);
		}

		sort(d.begin(), d.end());
		for (int i = 0, j; i < (int)d.size(); i = j) {
			for (j = i; j < (int)d.size(); ++j) {
				if (d[i] != d[j]) break;
			}
			mx = max(mx, j - i + 1);
		}
	}

	cout << mx << endl;
}
