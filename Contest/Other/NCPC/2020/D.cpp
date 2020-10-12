#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n; cin >> n;
		vector<int> c(12, 0);
		while (n--) {
			int z; cin >> z;
			++c[z];
		}
		vector<int> v;
		while (c[9]) {
			--c[9];
			v.push_back(9);
		}

		vector<int> ans;
		auto update = [&] (vector<int> v) {
			if (v.size() > ans.size()) {
				ans = v;
			} else if (v.size() == ans.size()) {
				for (int i = 0; i < (int)v.size(); ++i) {
					if (v[i] != ans[i]) {
						if (v[i] < ans[i]) return;
						else {
							ans = v;
							return;
						}
					}
				}
			}
		};
		auto meow = [&] (vector<int> v, vector<int> c, int p) {
			while (c[6] >= 3) {
				c[6] -= 3;
				v.push_back(6);
				v.push_back(6);
				v.push_back(6);
			}

			if (p == 6) {
				if (c[3] < 1) return;
				--c[3];
				v.push_back(3);
			}
			if (p == 3) {
				if (c[3] < 2) return;
				--c[3]; --c[3];
				v.push_back(3);
				v.push_back(3);
			}

			while (c[3] >= 3) {
				c[3] -= 3;
				v.push_back(3);
				v.push_back(3);
				v.push_back(3);
			}

				while (c[0]) {
					--c[0];
					v.push_back(0);
				}

			update(v);
		};

		meow(v, c, 0);
		if (c[6]) {
			--c[6];
			v.push_back(6);
			meow(v, c, 6);
			if (c[6]) {
				--c[6];
				v.push_back(6);
				meow(v, c, 3);
				if (c[6]) {
					--c[6];
					v.push_back(6);
					meow(v, c, 0);
				}
			}
		}

		if (ans.empty()) {
			cout << -1 << '\n';
		} else {
			for (int i = 0; i < (int)ans.size(); ++i) {
				cout << ans[i] << " \n"[i == (int)ans.size() - 1];
			}
		}
	}
}
