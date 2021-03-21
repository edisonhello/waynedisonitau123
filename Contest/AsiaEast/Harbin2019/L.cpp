#include <bits/stdc++.h>
using namespace std;

void Solve() {
	int N, Q;
	cin >> N >> Q;
	vector<int> A(N);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		A[i]--;
	}
	int K = unique(A.begin(), A.end()) - A.begin();
	constexpr int kP = 1'000'000'000 + 123;
	constexpr int kQ = 7122;

	vector<int> pw(K + 1, 1);
	for (int i = 1; i <= K; ++i) {
		pw[i] = 1LL * pw[i - 1] * kQ % kP;
	}

	vector<vector<int>> Hash(K);
	auto Get = [&](int l, int r, int p) -> int {
		if (l == 0) return Hash[p][r];
		return (Hash[p][r] + kP - 1LL * pw[r - l + 1] * Hash[p][l - 1] % kP) % kP;
	};

	vector<int> s;
	for (int i = 0; i < K; ++i) {
		auto it = find(s.begin(), s.end(), A[i]);
		if (it != s.end()) s.erase(it);
		s.push_back(A[i]);	
		Hash[i].resize(s.size());
		Hash[i][0] = s[0];
		for (int j = 1; j < s.size(); ++j) {
			Hash[i][j] = (1LL * Hash[i][j - 1] * kQ + s[j]) % kP;
		}
	}

	vector<int> first(N, -1);
	for (int i = 0; i < N; ++i) {
		if (first[A[i]] == -1) first[A[i]] = i;
	}
	vector<bool> vis(N);
	while (Q--) {
		int M;
		cin >> M;
		vector<int> B(M);
		bool dup = false;
		for (int i = 0; i < M; ++i) {
			cin >> B[i];
			B[i]--;
			if (B[i] >= 0) {
				if (vis[B[i]]) dup = true;
				vis[B[i]] = true;
			}
		}
		if (dup) {
			cout << "No\n";
			for (int u : B) if (u >= 0) vis[u] = false;
			continue;
		}
		bool zero = find(B.begin(), B.end(), -1) != B.end();
		while (!B.empty() && B.back() == -1) B.pop_back();
		if (find(B.begin(), B.end(), -1) != B.end()) {
			cout << "No\n";
			for (int u : B) if (u >= 0) vis[u] = false;
			continue;
		}
		reverse(B.begin(), B.end());
		int V = 0;
		for (int u : B) V = (1LL * V * kQ + u) % kP;
		M = B.size();
		if (M == 0) {
			cout << "Yes\n";
			continue;
		}
		bool found = false;
		for (int i = M - 1; i < K; ++i) {
			if (M > Hash[i].size()) continue;
			if (Get(Hash[i].size() - M, Hash[i].size() - 1, i) == V) {
				bool ok = true;
				if (zero) {
					for (int j = 0; ok && j < N; ++j) {
						if (!vis[j] && first[j] != -1 && first[j] <= i) ok = false;
					}
				}
				cout << (ok ? "Yes" : "No") << "\n";
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "No\n";
		}
		for (int u : B) vis[u] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) Solve();
}

