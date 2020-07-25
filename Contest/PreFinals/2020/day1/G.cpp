#include <bits/stdc++.h>
using namespace std;

vector<int> pos[100005];


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, n; cin >> m >> n;
	vector<int> v(n);
	// v[0] = 1;
	for (int i = 0; i < n; ++i) cin >> v[i];

	for (int i = 0; i < (int)v.size(); ++i) 
		pos[v[i]].push_back(i);

	// cerr << "v: ";
	// for (int i : v) cerr << i << ' ';
	// cerr << endl;

	vector<pair<int, int>> ccc;
	for (int i = 1; i <= m; ++i) {
		if (i == v[0]) continue;
		// cerr << "first put " << i << endl;
		int le = 0;
		int now = i;
		int at = -1;
		while (true) {
			auto it = upper_bound(pos[now].begin(), pos[now].end(), at);
			if (it == pos[now].end()) break;
			at = *it - 1;
			now = v[at];
			// cerr << "next at = " << at << endl;
			// cerr << "become " << now << endl;
			++le;
		}
		ccc.emplace_back(le, i);
	}

	sort(ccc.begin(), ccc.end());
	reverse(ccc.begin(), ccc.end());
	long long tot = 0;
	for (int i = 1; i <= (int)ccc.size(); ++i) {
		tot += 1ll * i * ccc[i - 1].first;
	}
	cout << tot << endl;
	for (auto p : ccc) cout << p.second << ' ';
	cout << endl;
}

