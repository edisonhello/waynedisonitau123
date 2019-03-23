#include <bits/stdc++.h>
using namespace std;

pair<int, int> seg[300005];

int main() {
	ios_base::sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int t, l; cin >> t >> l;
		seg[i] = make_pair(t, t + l - 1);
	}
	sort(seg, seg + n);
	priority_queue<int, vector<int>, greater<int>> pq;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> empty;
	int open = 0;
	for (int i = 0; i < n; ++i) {
		int nt = seg[i].first;
		while (empty.size() && empty.top().first < nt) {
			pq.push(empty.top().second);
			empty.pop();
		}
		while (pq.size() && pq.top() < nt) pq.pop();
		if (pq.size()) {
			pq.pop();
		} else {
			++open;
		}
		empty.emplace(seg[i].second, seg[i].second + m + 1);
	}
	cout << n - open << endl;
}
