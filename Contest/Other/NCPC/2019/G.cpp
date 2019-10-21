#include <bits/stdc++.h>
using namespace std;

long long sign(long long x) {
	if (x == 0) return x;
	if (x > 0) return 1;
	return -1;
}

struct P {
	long long x, y;
	long long operator ^ (const P b) const {
		return x * b.y - y * b.x;
	}
	P operator - (const P b) const {
		return {x - b.x, y - b.y};
	}
};

bool intersect(P p1, P p2, P p3, P p4) {
	if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
	if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
	return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 && 
		   sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

bool intersect(pair<P, P> l1, pair<P, P> l2) {
	return intersect(l1.first, l1.second, l2.first, l2.second);
}

int fa[50], sz[50];

int Find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = Find(fa[x]);
}

void Merge(int x, int y) {
	if ((x = Find(x)) == (y == Find(y))) return;
	fa[x] = y;
	sz[y] += sz[x];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) {
		int n; cin >> n;

		vector<pair<P, P>> l(n);
		for (int i = 0; i < n; ++i) {
			cin >> l[i].first.x >> l[i].first.y;
			cin >> l[i].second.x >> l[i].second.y;
		}

		int ans = 0;
		for (int i = 0; i < n; ++i) fa[i] = i, sz[i] = 1;
		for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
			if (intersect(l[i], l[j])) Merge(i, j);
		}

		for (int i = 0; i < n; ++i) {
			if (Find(i) == i) ans += sz[i] * (sz[i] - 1) / 2;
		}

		cout << ans << endl;
	}
}
