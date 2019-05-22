#include <bits/stdc++.h>
using namespace std;

pair<int, int> p[1005];
tuple<int, int, int> ext[1005];
vector<int> G[1005];
int c[1005];

pair<int, int> operator - (const pair<int, int> a, const pair<int, int> b) {
	return make_pair(a.first - b.first, a.second - b.second);
}
long long operator ^ (const pair<int, int> a, const pair<int, int> b) {
	return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

bool in(pair<int, int> p, pair<int, int> p1, pair<int, int> p2) {
	if (((p - p1) ^ (p2 - p1)) == 0) return 1;
	return 0;
}

bool cross(pair<int, int> s1, pair<int, int> s2, pair<int, int> t1, pair<int, int> t2) {
	if (((t2 - t1) ^ (s1 - t1)) * 1ll * ((t2 - t1) ^ (s2 - t1)) > 0) return false;
	if (((s2 - s1) ^ (t1 - s1)) * 1ll * ((s2 - s1) ^ (t2 - s1)) > 0) return false;
	return true;
}

bool dfs(int now, int nc) {
	c[now] = nc;
	for (int i : G[now]) {
		if (c[i]) {
			if (c[i] == nc) return 0;
		} else {
			if (!dfs(i, 3 - nc)) return 0;
		}
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> p[i].first >> p[i].second;
	for (int i = 1; i <= m; ++i) {
		int x, dx, dy; cin >> x >> dx >> dy;
		ext[i] = make_tuple(x, dx, dy);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {
			int i1, dx1, dy1; tie(i1, dx1, dy1) = ext[i];
			int i2, dx2, dy2; tie(i2, dx2, dy2) = ext[j];
			int x1, y1; tie(x1, y1) = p[i1];
			int x2, y2; tie(x2, y2) = p[i2];
			int x1to = dx1, y1to = dy1;
			int x2to = dx2, y2to = dy2;
			// cerr << "condition " << i << " and " << j << endl;
			// cerr << "x1 y1 x1to y1to " << x1 << " " << y1 << " " << x1to << " " << y1to << endl;
			// cerr << "x2 y2 x2to y2to " << x2 << " " << y2 << " " << x2to << " " << y2to << endl;
			if (x1to == x2to && y1to == y2to) {
				G[i].push_back(j); 
				G[j].push_back(i);
				// cerr << "make edge: " << i << " " << j << endl;
			} else if (in(make_pair(x1, y1), make_pair(x2, y2), make_pair(x2to, y2to)));
			else if (in(make_pair(x2, y2), make_pair(x1, y1), make_pair(x1to, y1to)));
			else if (cross(make_pair(x1, y1), make_pair(x1to, y1to), make_pair(x2, y2), make_pair(x2to, y2to))) {
				G[i].push_back(j); 
				G[j].push_back(i);
				// cerr << "make edge: " << i << " " << j << endl;
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		if (!c[i]) if (!dfs(i, 1)) {
			cout << "impossible" << endl;
			exit(0);
		}
	}
	cout << "possible" << endl;
}
