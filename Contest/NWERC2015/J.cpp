#include <bits/stdc++.h>
using namespace std;

int ans[256];

int main() {
	for (int x = 0; x < 256; ++x) {
		int y = (x << 1) & 255;
		ans[x ^ y] = x;
	}
	int n; scanf("%d", &n);
	while (n--) {
		int x; scanf("%d", &x);
		printf("%d ", ans[x]);
	}
	puts("");
}
