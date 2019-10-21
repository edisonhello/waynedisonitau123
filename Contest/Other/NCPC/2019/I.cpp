#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

inline char gtx() {
	const int N = 4096;
	static char buf[N];
	static char *p = buf, *e = buf;
	if (p == e) {
		(e = buf + fread_unlocked(buf, 1, N, stdin));
		p = buf;
	}
	return *p++;
}

int rit() {
	char c;
	while (c = gtx(), c < '0' || c > '9');
	int x = c & 15;
	while (c = gtx(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
	return x;
}

bitset<10004> g[10004];

int main() {
	int t = rit(); while (t--) {
		int n = rit(), m = rit();
		for (int i = 0; i < n; ++i) g[i].reset();
		for (int i = 0; i < m; ++i) {
			int u = rit(), v = rit(); --u, --v;
			g[u][v] = g[v][u] = 1;
		}
		bool stop = false;
		for (int i = 0; i < n; ++i) {
			int it = g[i]._Find_first();
			bitset<10004> OR = g[it], XOR = g[it];
			OR[i] = 0;
			XOR[i] = 0;

			while ((it = g[i]._Find_next(it)) < 10004) {
				OR |= g[it];
				XOR ^= g[it];
				OR[i] = 0; XOR[i] = 0;
				if (OR != XOR) {
					int u = i, v = it;
					bool stop1 = false;
					for (int j = g[u]._Find_first(); j < n; j = g[u]._Find_next(j)) if (j != u && j != v) {
						bitset<10004> zz = g[v] & g[j];
						if (zz.count() > 1u) {
							stop1 = true;
							int iit = zz._Find_first();
							if (iit == u) iit = zz._Find_next(iit);
							printf("%d %d %d %d\n", u + 1, v + 1, iit + 1, j + 1);
							break;
						}
					}
					if (stop1) {
						stop = true;
						break;
					}
				}
			}
			if (stop == 1) break;
		}
		if (!stop) puts("-1");
	}
}
