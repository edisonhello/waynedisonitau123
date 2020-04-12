#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

vector<vector<long long>> Mul(vector<vector<long long>> a, vector<vector<long long>> b) {
	vector<vector<long long>> r = {{0,0,0}, {0,0,0}, {0,0,0}};
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) for (int k = 0; k < 3; ++k) 
		r[i][j] += a[i][k] * b[k][j];
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) r[i][j] %= mod;
	return r;
}

vector<vector<long long>> mpw(vector<vector<long long>> b, long long n) {
	vector<vector<long long>> a = {{1,0,0}, {0,1,0}, {0,0,1}};
	while (n) {
		if (n & 1) a = Mul(a, b);
		b = Mul(b, b); n >>= 1;
	}
	return a;
}

long long GetA(long long n) {
	static const long long a1 = 1;
	static const long long a2 = 2;
	static const long long a3 = 4;
	vector<vector<long long>> t = {{0,1,0}, {0,0,1}, {1,1,1}};
	t = mpw(t, n - 1);
	return (t[0][0] * a1 + t[0][1] * a2 + t[0][2] * a3) % mod;
}

long long GetB(long long n) {
	static const long long b1 = 1;
	static const long long b2 = 4;
	static const long long b3 = 8;
	vector<vector<long long>> t = {{0,1,0}, {0,0,1}, {1,3,1}};
	t = mpw(t, n - 1);
	return (t[0][0] * b1 + t[0][1] * b2 + t[0][2] * b3) % mod;
}

long long GetC(long long i) {
	return 1ll * (GetB(i) - GetA(i) + mod) * ((mod + 1) >> 1) % mod;
}

long long Calc(long long i) {
	if (i == 1) return 1;
	if (i == 2) return 4;
	if (i == 3) return 10;
	return (2 * GetA(i - 1) + 2 * GetA(i - 2) + GetA(i - 3) +
		   3 * GetC(i - 1) + 3 * GetC(i - 2) + GetC(i - 3)) % mod;
}

long long a[105], b[105], c[105];

int main() {
	// a[1] = 1; a[2] = 2; a[3] = 4;
	// b[1] = 1; b[2] = 4; b[3] = 8;

	// for (int i = 4; i <= 100; ++i) a[i] = a[i - 1] + a[i - 2] + a[i - 3];
	// for (int i = 4; i <= 100; ++i) b[i] = b[i - 1] + 3 * b[i - 2] + b[i - 3];
	// for (int i = 1; i <= 100; ++i) c[i] = (b[i] - a[i]) / 2;

	// for (int i = 1; i <= 100; ++i) {
	// 	cout << "i = " << i << ' ';
	// 	if (i == 1) {
	// 		cout << 1 << ' ';
	// 	} else if (i == 2) {
	// 		cout << 4 << ' ';
	// 	} else if (i == 3) { 
	// 		cout << 10 << ' ';
	// 	} else {
	// 		cout << (2 * a[i - 1] + 2 * a[i - 2] + a[i - 3] +
	// 				3 * c[i - 1] + 3 * c[i - 2] + c[i - 3]) % mod << ' ';
	// 	}

	// 	cout << " calc " << Calc(i) << endl;
	// }

	long long n; cin >> n;
	cout << Calc(n) << endl;

}
