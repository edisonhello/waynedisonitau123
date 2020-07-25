#include <bits/stdc++.h>
using namespace std;


int main() {
	int n, h; cin >> n >> h;
	
	map<int, int> cnt;
	while (n--) {
		int t; cin >> t; 
		cnt[t]++;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;
	for (auto &p : cnt) {
		pq.emplace(p.second, p.first);
	}
	
	vector<set<int>> ans;
	while (pq.size()) {
		vector<pair<int, int>> tmp;
		set<int> t;

		while (pq.size() && (int)t.size() < h) {
			pair<int, int> p = pq.top(); pq.pop();
			assert(!t.count(p.second));
			t.insert(p.second);
			if (p.first > 1) {
				tmp.emplace_back(p.first - 1, p.second);
			}
		}

		if ((int)t.size() < h) break;

		for (auto p : tmp) pq.push(p);

		ans.push_back(t);
	}

	if (ans.empty()) {
		cout << "impossible" << endl;
	} else {
		for (auto s : ans) {
			for (int i : s) cout << i << ' ';
			cout << endl;
		}
	}
}

