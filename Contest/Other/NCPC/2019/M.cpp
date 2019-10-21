#include <bits/stdc++.h>
using namespace std;


array<int, 6> spin(array<int, 6> o, vector<int> v) {
	array<int, 6> x = o;
	for (int i = 0; i < 4; ++i) {
		x[v[i]] = o[v[i == 3 ? 0 : i + 1]];
	}
	return x;
}

int main() {
	int t; cin >> t; while (t--) {
		array<int, 6> giv, now;
		for (int i = 0; i < 5; ++i) cin >> giv[i];
		for (int i = 0; i < 6; ++i) cin >> now[i];
		set<array<int, 6>> st; st.insert(now);
		queue<pair<array<int, 6>, int>> q; q.emplace(now, 0);
		bool ok = false;
		while (q.size()) {
			now = q.front().first;
			int step = q.front().second;
			q.pop();

			bool diff = false;
			for (int i = 0; i < 5; ++i) {
				if (now[i] != giv[i]) diff = true;
			}
			if (!diff) {
				cout << step << '\n';
				ok = true;
				break;
			}

			auto xx = spin(now, {4, 1, 5, 3});
			if (st.count(xx) == 0) {
				st.insert(xx);
				q.emplace(xx, step + 1);
			}
			xx = spin(now, {4, 3, 5, 1});
			if (st.count(xx) == 0) {
				st.insert(xx);
				q.emplace(xx, step + 1);
			}
			xx = spin(now, {4, 2, 5, 0});
			if (st.count(xx) == 0) {
				st.insert(xx);
				q.emplace(xx, step + 1);
			}
			xx = spin(now, {4, 0, 5, 2});
			if (st.count(xx) == 0) {
				st.insert(xx);
				q.emplace(xx, step + 1);
			}
		}
		if (!ok) {
			cout << -1 << '\n';
		}
	}
}
