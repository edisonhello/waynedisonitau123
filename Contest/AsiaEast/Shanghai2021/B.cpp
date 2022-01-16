#include <bits/stdc++.h>
using namespace std;

namespace fft {

constexpr int kN = 262144;
constexpr int kR = 3;
constexpr int kP = 998244353;
int omega[kN + 1];

int fpow(int a, int n) {
	int res = 1;
	while (n > 0) {
		if (n & 1) res = 1LL * res * a % kP;
		a = 1LL * a * a % kP;
		n >>= 1;
	}
	return res;
}

void Init() {
	int x = fpow(kR, (kP - 1) / kN);
	omega[0] = 1;
	for (int i = 1; i <= kN; ++i) {
		omega[i] = 1LL * omega[i - 1] * x % kP;
	}
}

void BitReverse(vector<int>& v, int n) {
	int z = __builtin_ctz(n) - 1;
	for (int i = 0; i < n; ++i) {
		int x = 0;
		for (int j = 0; j <= z; ++j) {
			x ^= (i >> j & 1) << (z - j);
		}
		if (x > i) swap(v[x], v[i]);
	}
}

void Transform(vector<int>& v, int n) {
	BitReverse(v, n);
	for (int s = 2; s <= n; s <<= 1) {
		int z = s >> 1;
		for (int i = 0; i < n; i += s) {
			for (int k = 0; k < z; ++k) {
				int x = 1LL * v[i + k + z] * omega[kN / s * k] % kP;
				v[i + k + z] = (v[i + k] + kP - x) % kP;
				(v[i + k] += x) %= kP;
			}
		}
	}
}

void InvTransform(vector<int>& v, int n) {
	Transform(v, n);
	for (int i = 1; i < n / 2; ++i) {
		swap(v[i], v[n - i]);
	}
	const int kI = fpow(n, kP - 2);
	for (int i = 0; i < n; ++i) {
		v[i] = 1LL * v[i] * kI % kP;
	}
}

}  // namespace fft

using fft::kP;
using fft::fpow;

vector<int> Multiply(vector<int> a, vector<int> b) {
	int n = a.size(), m = b.size(), s = 1;
	while (s < n + m - 1) s <<= 1;
	a.resize(s);
	b.resize(s);
	fft::Transform(a, s);
	fft::Transform(b, s);
	for (int i = 0; i < s; ++i) {
		a[i] = 1LL * a[i] * b[i] % kP;
	}
	fft::InvTransform(a, s);
	a.resize(n + m - 1);
	return a;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	fft::Init();

	int N;
	cin >> N;
	int k = 0;
	vector<int> A(N);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		A[i]--;
		k += (A[i] == i);
	}
	vector<bool> vis(N);
	priority_queue<pair<int, vector<int>>> poly;


	vector<int> fc(N + 1, 1), iv(N + 1, 1);

	for (int i = 1; i <= N; ++i) {
		fc[i] = 1LL * fc[i - 1] * i % kP;
		iv[i] = fpow(fc[i], kP - 2);
	}

	for (int i = 0; i < N; ++i) {
		if (vis[i]) continue;
		int x = i, cnt = 0;
		while (!vis[x]) {
			vis[x] = true;
			cnt++;
			x = A[x];
		}
		vector<int> vec(cnt);
		for (int j = 0; j < cnt; ++j) {
			vec[j] = 1LL * fc[cnt] * iv[j] % kP * iv[cnt - j] % kP;
		}
		poly.emplace(-cnt, vec);
	}
	while (poly.size() > 1) {
		auto a = poly.top().second;
		poly.pop();
		auto b = poly.top().second;
		poly.pop();
		auto c = Multiply(a, b);
		poly.emplace(-c.size(), c);
	}


	auto fin = poly.top().second;
	// cout << "poly = ";
	// for (int u : fin) cout << u << " ";
	// cout << "\n";

	int ans = 0;
	for (int i = 0; i < fin.size(); ++i) {
		int comb = 1LL * fin[i] * fc[N - i] % kP;
		if ((i & 1) == 0) {
			ans += comb;
		} else {
			ans += kP - comb;
		}
		ans %= kP;
	}
	cout << ans << "\n";
}

