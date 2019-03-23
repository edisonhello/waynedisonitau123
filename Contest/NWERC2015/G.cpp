#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y, z;
} p[200005];

int a[200005], b[200005], c[200005];
int pa[200005], pb[200005], pc[200005];
unordered_map<int, unordered_map<int, int>> mp;
int bit[200005];

void add(int x, int v) {
	for (; x; x -= x & -x) bit[x] += v;
}
int query(int x, int v = 0) {
	for (; x < 200005; x += x & -x) v += bit[x];
	return v;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	long long ans = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 1; i <= n; ++i) pa[a[i]] = i;
	for (int i = 1; i <= n; ++i) pb[b[i]] = i;
	for (int i = 1; i <= n; ++i) pc[c[i]] = i;
	for (int i = 1; i <= n; ++i) p[i] = {pa[i], pb[i], pc[i]};
	sort(p + 1, p + 1 + n, [&] (const point &x, const point &y) -> bool {
		return x.x < y.x;
	});
	for (int i = 1; i <= n; ++i) {
		int y = p[i].y, z = p[i].z;
		for (int yy = y - 1; yy; yy -= yy & -yy) {
			auto vit = mp.find(yy);
			if (vit == mp.end()) continue;
			for (int zz = z - 1; zz; zz -= zz & -zz) {
				auto it = vit->second.find(zz);
				if (it == vit->second.end()) continue;
				ans += it->second;
			}
		}
		for (int yy = y; yy < 200005; yy += yy & -yy) {
			auto &vv = mp[yy];
			for (int zz = z; zz < 200005; zz += zz & -zz) {
				vv[zz] += 1;
			}
		}
	}
	cout << ans << endl;

	// for (int i = 1; i <= n; ++i) apos[a[i]] = i;
	// for (int i = 1; i <= n; ++i) b[i] = apos[b[i]];
	// for (int i = 1; i <= n; ++i) c[i] = apos[c[i]];
	// for (int i = 1; i <= n; ++i) cpos[c[i]] = i;
	// for (int i = 1; i <= n; ++i) add(i, 1);
	// long long ans = 0;
	// for (int i = 1; i <= n; ++i) {
	// 	int x = b[i];
	// 	int pos = cpos[x];
	// 	add(pos, -1);
	// 	ans += query(pos);
	// }
	// cout << ans << endl;
}
