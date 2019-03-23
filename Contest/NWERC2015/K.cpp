#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const long long inf = 1000000000000000000 + 1;
int b[maxn];
vector<int> v[maxn];

int main() {
	int r, s, m, d, n; scanf("%d%d%d%d%d", &r, &s, &m, &d, &n);
	for (int i = 0; i < r; ++i) scanf("%d", &b[i]);
	for (int i = 0; i < s + m + d; ++i) {
		int k; scanf("%d", &k);
		for (int j = 0; j < k; ++j) {
			int y; scanf("%d", &y);
			--y;
			v[i].push_back(y);
		}
	}
	set<pair<int, int>> ed;
	for (int i = 0; i < n; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		--x, --y;
		ed.insert(minmax(x, y));
	}
	long long ans = 0;
	for (int i = 0; i < s; ++i) {
		for (int j = s; j < s + m; ++j) {
			for (int k = s + m; k < s + m + d; ++k) {
				if (ed.count(minmax(i, j)) || ed.count(minmax(j, k)) || ed.count(minmax(i, k))) continue;
				map<int, int> cnt;
				for (int p : v[i]) cnt[p]++;
				for (int p : v[j]) cnt[p]++;
				for (int p : v[k]) cnt[p]++;
				long long add = 1;
				for (auto p : cnt) {
					if (add * 1.0 * b[p.first] > inf) add = inf;
					else add *= b[p.first];
				}
				ans += add;
				if (ans > inf) ans = inf;
			}
		}
	}
	if (ans >= inf) puts("too many");
	else printf("%lld\n", ans);
}
