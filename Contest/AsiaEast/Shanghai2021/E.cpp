#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, K;
	cin >> N >> K;
	vector<int> A(N);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());
	vector<int> dp(N + 1);
	for (int i = 0, j = 0; i < N; ++i) {
		while (j <= i && A[i] >= A[j] + K) j++;
		dp[i + 1] = dp[j] + 1;
		dp[i + 1] = max(dp[i + 1], dp[i]);
	}
	cout << dp[N] << "\n";
}

