#include <bits/stdc++.h>
using namespace std;


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n, k; cin >> n >> k;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		vector<int> pt(n / 2);
		for (int i = 0; i < n / 2; ++i) {
			pt[i] = a[i * 2] > a[i * 2 + 1] ? 1 : -1;
		}
		int ans = 0;
		for (int i : pt) if (i > 0) ++ans;

		// cerr << "pt = ";
		// for (int i : pt) cerr << i << ' ';
		// cerr << endl;

		vector<int> len;
		for (int i = 0, j; i < (int)pt.size(); i = j) {
			if (pt[i] == 1) {
				j = i + 1;
				continue;
			}
			for (j = i; j < (int)pt.size(); ++j) {
				if (pt[j] != -1) break;
			}
			int d = j - i;
			len.push_back(d);
			ans -= (d + 1) / 2;
		}
		// cerr << "1z" << endl;

		k *= 2;
		for (int &i : len) {
			if (i & 1) {
				if (k) {
					--k;
					++ans; ++ ans;
					--i;
				}
			}
		}

		for (int &i : len) {
			if (!k) break;
			while (i >= 2 && k >= 2) {
				i -= 2;
				k -= 2;
				++ans; ++ ans; ++ ans;
			}
		}

		for (int &i : len) {
			if (k == 1 && i >= 1) {
				i -= 1;
				k -= 1;
				ans += 1;
			}
		}
		// cerr << "2z" << endl;

		cout << ans << '\n';
	}
}
