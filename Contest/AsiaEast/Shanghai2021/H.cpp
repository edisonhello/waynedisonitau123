#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<int> A(N);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	vector<tuple<int, int, int>> edges(M);
	for (auto &[w, u, v] : edges) {
		cin >> u >> v >> w;
		u--;
		v--;
	}
	sort(edges.begin(), edges.end());

	vector<int> uf(N + N);
	vector<int> par(N + N, -1);
	vector<int> fe(N + N);
	vector<int> sum(N + N);
	copy(A.begin(), A.end(), sum.begin());
	iota(uf.begin(), uf.end(), 0);

	function<int(int)> Find = [&](int x) {
		if (x == uf[x]) return x;
		return uf[x] = Find(uf[x]);
	};

	int aux = N;

	for (auto &[w, u, v] : edges) {
		if (Find(u) == Find(v)) {
			continue;
		}	
		int fu = Find(u);
		int fv = Find(v);
		uf[fu] = uf[fv] = aux;
		par[fu] = par[fv] = aux;
		sum[aux] = sum[fu] + sum[fv];
		aux++;
		fe[fu] = fe[fv] = w;
	}

	vector<vector<int>> jump(aux, vector<int>(20, -1));
	vector<vector<int>> gap(aux, vector<int>(20, -1));
	for (int i = 0; i < aux; ++i) {
		jump[i][0] = par[i];
		gap[i][0] = fe[i] - sum[i];
	}
	for (int i = 1; i < 20; ++i) {
		for (int j = 0; j < aux; ++j) {
			if (jump[j][i - 1] == -1) continue;
			jump[j][i] = jump[jump[j][i - 1]][i - 1];
			gap[j][i] = max(gap[j][i - 1], gap[jump[j][i - 1]][i - 1]);
		}
	}

	while (Q--) {
		int x, k;
		cin >> x >> k;
		x--;
		for (int bit = 19; bit >= 0; --bit) {
			if (jump[x][bit] == -1) continue;
			if (k >= gap[x][bit]) {
				x = jump[x][bit];
			}	
		}
		cout << sum[x] + k << "\n";
	}
	return 0;
}

