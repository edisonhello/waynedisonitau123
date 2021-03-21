#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int q; cin >> q;
		vector<vector<int>> seq(q);
		vector<pair<int, long long>> info(q);
		vector<long long> len(q, 0);
		for (int i = 0; i < q; ++i) {
			auto &v = seq[i];
			auto &p = info[i];
			int t; cin >> t;
			if (t == 1) {
				v.push_back(t);
				int z; cin >> z;
				len[i] = z;
				v.push_back(z);
				for (int i = 0; i < z; ++i) {
					int y; cin >> y;
					v.push_back(y);
					if (y == p.first) {
						++p.second;
					} else if (p.second == 0) {
						p.first = y;
						p.second = 1;
					} else {
						--p.second;
					}
				}
			} else {
				int x, y; cin >> x >> y;
				--x, --y;
				v.push_back(t);
				v.push_back(x);
				v.push_back(y);
				len[i] = len[x] + len[y];
				if (info[x].first == info[y].first) {
					p = info[x];
					p.second += info[y].second;
				} else if (info[x].second > info[y].second) {
					p = info[x];
					p.second -= info[y].second;
				} else {
					p = info[y];
					p.second -= info[x].second;
				}
			}
		}

		int count_tar = info.back().first;
		vector<long long> cnt(q, 0);

		for (int i = 0; i < q; ++i) {
			auto &v = seq[i];
			if (v[0] == 1) {
				int n = v[1];
				for (int j = 2; j < 2 + n; ++j) {
					cnt[i] += v[j] == count_tar;
				}
			} else {
				cnt[i] = cnt[v[1]] + cnt[v[2]];
			}
		}


		long long fc = cnt.back();
		long long fl = len.back();
		if (fc * 2 < fl) cout << fl << '\n';
		else cout << (fl - fc) * 2 << '\n';
	}
}

