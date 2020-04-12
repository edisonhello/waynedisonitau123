#include <bits/stdc++.h>
using namespace std;


int main() {
	int n, a; cin >> n >> a;
	if (n == 1) cout << 1ll * a * a % 8 << endl;
	else cout << a % 2 << endl;
}
