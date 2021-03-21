#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int N, M1, M2;
		cin >> N >> M1 >> M2;
		vector<tuple<int, int, int>> C1(M1);
		vector<tuple<int, int, int>> C2(M2);

		for (int i = 0; i < M1; ++i) {
			int l, r, w;
			cin >> l >> r >> w;
			l--;
			C1[i] = make_tuple(l, r, w);
		}
		int V = 0;
		for (int i = 0; i < M2; ++i) {
			int l, r, w;
			cin >> l >> r >> w;
			l--;
			C2[i] = make_tuple(l, r, w);
			V = max(V, w);
		}
		constexpr int kInf = 1'000'000'000;
		vector<int> dist(N + 1, kInf);
		int W = N;
		queue<int> que;
		vector<tuple<int, int, int>> Edge;
		for (auto [l, r, w] : C1) Edge.emplace_back(r, l, -w);
		for (int i = 0; i < N; ++i) Edge.emplace_back(i, i + 1, 1);
		for (int i = 0; i < N; ++i) Edge.emplace_back(i + 1, i, 0);

		auto Check = [&](int S) {
			for (auto [l, r, w] : C2) Edge.emplace_back(l, r, S - w);
			Edge.emplace_back(0, N, S);
			Edge.emplace_back(N, 0, -S);
			fill(dist.begin(), dist.end(), kInf);
			dist[0] = 0;
			bool neg = false;
			for (int iter = 0; iter < N + 2; ++iter) {
				bool upd = false;
				for (auto [l, r, w] : Edge) {
					if (dist[r] > dist[l] + w) {
						dist[r] = dist[l] + w;
						upd = true;
					}
				}
				if (iter == N + 1 && upd) neg = true;
			}
			Edge.pop_back();
			Edge.pop_back();
			for (auto [l, r, w] : C2) Edge.pop_back();
			return !neg;
		};

		// cout << "Check(1) = " << Check(1) << endl;
		// cout << "Check(0) = " << Check(0) << endl;
		for (int d = 20; d >= 0; --d) {
			int S = W - (1 << d);
			if (S < V) continue;
			if (Check(S)) W = S;
		}
		cout << W << "\n";
	}
}

