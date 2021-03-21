#include <bits/stdc++.h>
using namespace std;

int cnt[6][256];

int main() {
	int t; cin >> t; while (t--) {
		vector<string> ss(6);
		for (int i = 0; i < 6; ++i) cin >> ss[i];
		memset(cnt, 0, sizeof(cnt));

		for (int i = 0; i < 6; ++i) {
			for (char j : ss[i]) {
				cnt[i][j]++;
			}
		}

		string tar = "harbin";
		sort(tar.begin(), tar.end());
		bool yes = 0;
		do {
			bool ok = 1;
			for (int i = 0; i < 6; ++i) {
				if (!cnt[i][tar[i]]) { ok = 0; break; }
			}
			if (ok) { yes = 1; break; }
		} while (next_permutation(tar.begin(), tar.end()));

		cout << (yes ? "Yes" : "No") << '\n';
	}
}

