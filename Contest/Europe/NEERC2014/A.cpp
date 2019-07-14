#include <bits/stdc++.h>
using namespace std;
 
 
 
int main() {
#ifdef ONLINE_JUDGE
#define FILENAME "alter"
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#undef FILENAME
#endif
	int n, m; cin >> n >> m;
	cout << n / 2 + m / 2 << endl;
	for (int i = 2; i <= n; i += 2) cout << i << " 1 " << i << " " << m << endl;
	for (int i = 2; i <= m; i += 2) cout << "1 " << i << " " << n << " " << i << endl;
}
