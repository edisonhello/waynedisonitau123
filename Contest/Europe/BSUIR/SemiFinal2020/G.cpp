#include <bits/stdc++.h>
using namespace std;

void no() {
	cout << "NO" << '\n';
}

void print(vector<vector<int>> ans) {
	cout << "YES" << '\n';
	for (int i = 1; i < (int)ans.size(); ++i) {
		for (int j = 1; j < (int)ans[i].size(); ++j) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}
}

void solve() {
	int n, m, r, c; cin >> n >> m >> r >> c;
	int R = r, C = c;
	if ((n * m - 1) % 4) { no(); return; }
	vector<vector<int>> ans(n + 1, vector<int>(m + 1, 0));
	int id = 0;
	if (n == 1) {
		if (c % 4 != 1) { no(); return; }
		for (int i = 1; i <= m; i += 4) {
			if (i == c) ++i;
			if (i > m) break;
			++id;
			ans[1][i] = ans[1][i + 1] = ans[1][i + 2] = ans[1][i + 3] = id;
		}
		print(ans);
		return;
	}
	if (m == 1) {
		if (r % 4 != 1) { no(); return; }
		for (int i = 1; i <= n; i += 4) {
			if (i == r) ++i;
			if (i > n) break;
			++id;
			ans[i][1] = ans[i + 1][1] = ans[i + 2][1] = ans[i + 3][1] = id;
		}
		print(ans);
		return;
	}

	for (int i = max(r - 2, 1); i <= min(r, n - 2); ++i) {
		for (int j = max(c - 2, 1); j <= min(c, m - 2); ++j) { // [i, j] == left up 
			auto do_middle = [&] () -> void {
				vector<vector<int>> tans;
				if (r == i && c == j) tans = vector<vector<int>> {
					{0, 1, 1},
					{2, 1, 1},
					{2, 2, 2}
				}; else if (r == i && c == j + 1) tans = vector<vector<int>> {
					{1, 0, 2},
					{1, 1, 2},
					{1, 2, 2}
				}; else if (r == i && c == j + 2) tans = vector<vector<int>> {
					{1, 1, 0},
					{1, 2, 2},
					{1, 2, 2}
				}; else if (r == i + 1 && c == j) tans = vector<vector<int>> {
					{1, 1, 1},
					{0, 2, 1},
					{2, 2, 2}
				}; else if (r == i + 1 && c == j + 1) tans = vector<vector<int>> {
					{1, 1, 1},
					{1, 0, 2},
					{2, 2, 2}
				}; else if (r == i + 1 && c == j + 2) tans = vector<vector<int>> {
					{1, 1, 1},
					{1, 2, 0},
					{2, 2, 2}
				}; else if (r == i + 2 && c == j) tans = vector<vector<int>> {
					{1, 1, 1},
					{1, 2, 2},
					{0, 2, 2}
				}; else if (r == i + 2 && c == j + 1) tans = vector<vector<int>> {
					{1, 1, 2},
					{1, 2, 2},
					{1, 0, 2}
				}; else if (r == i + 2 && c == j + 2) tans = vector<vector<int>> {
					{1, 1, 2},
					{1, 2, 2},
					{1, 2, 0}
				};
				for (int x = 0; x < 3; ++x) for (int y = 0; y < 3; ++y) ans[i + x][j + y] = tans[x][y];
			};
			if (i % 2 && j % 2) {
				int u = i - 1, d = n - i - 2, l = j - 1, r = m - j - 2;
				int cnt_4 = int(u % 4 == 0) + int(d % 4 == 0) + int(l % 4 == 0) + int(r % 4 == 0);
				cerr << i << ' ' << j << ' ' << u << ' ' << d << ' ' << l << ' ' << r << ' ' << cnt_4 << endl;
				if (cnt_4 == 4) {
					id = 2;
					for (int jj = j; jj <= j + 2; ++jj) {
						for (int ii = i - 1; ii >= 1; ii -= 4) {
							++id;
							ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
						}
						for (int ii = i + 3; ii <= n; ii += 4) {
							++id;
							ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
						}
					}
					for (int ii = i; ii <= i + 2; ++ii) {
						for (int jj = j - 1; jj >= 1; jj -= 4) {
							++id;
							ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
						}
						for (int jj = j + 3; jj <= m; jj += 4) {
							++id;
							ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
						}
					}
					do_middle();
				} else if (cnt_4 == 2) {
					if (r % 4 && d % 4) {
						id = 2;
						ans[i][j + 3] = ans[i][j + 4] = ans[i + 1][j + 3] = ans[i + 1][j + 4] = ++id;
						ans[i + 2][j + 3] = ans[i + 2][j + 4] = ans[i + 3][j + 3] = ans[i + 3][j + 4] = ++id;
						ans[i + 3][j + 2] = ans[i + 4][j + 2] = ans[i + 4][j + 3] = ans[i + 4][j + 4] = ++id;
						ans[i + 3][j] = ans[i + 3][j + 1] = ans[i + 4][j] = ans[i + 4][j + 1] = ++id;
						for (int jj = j; jj <= j + 4; ++jj) {
							for (int ii = i - 1; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 5; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i; ii <= i + 4; ++ii) {
							for (int jj = j - 1; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 5; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
						do_middle();
					} else if (d % 4 && l % 4) {
						id = 2;
						ans[i][j - 2] = ans[i][j - 1] = ans[i + 1][j - 2] = ans[i + 1][j - 1] = ++id;
						ans[i + 2][j - 2] = ans[i + 2][j - 1] = ans[i + 3][j - 2] = ans[i + 3][j - 1] = ++id;
						ans[i + 4][j - 2] = ans[i + 4][j - 1] = ans[i + 4][j] = ans[i + 3][j] = ++id;
						ans[i + 3][j + 1] = ans[i + 3][j + 2] = ans[i + 4][j + 1] = ans[i + 4][j + 2] = ++id;
						for (int jj = j - 2; jj <= j + 2; ++jj) {
							for (int ii = i - 1; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 5; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i; ii <= i + 4; ++ii) {
							for (int jj = j - 3; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 3; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
						do_middle();
					} else if (l % 4 && u % 4) {
						id = 2;
						ans[i + 1][j - 2] = ans[i + 1][j - 1] = ans[i + 2][j - 2] = ans[i + 2][j - 1] = ++id;
						ans[i - 1][j - 2] = ans[i - 1][j - 1] = ans[i][j - 2] = ans[i][j - 1] = ++id;
						ans[i - 2][j - 2] = ans[i - 2][j - 1] = ans[i - 2][j] = ans[i - 1][j] = ++id;
						ans[i - 2][j + 1] = ans[i - 2][j + 2] = ans[i - 1][j + 1] = ans[i - 1][j + 2] = ++id;
						for (int jj = j - 2; jj <= j + 2; ++jj) {
							for (int ii = i - 3; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 3; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i - 2; ii <= i + 2; ++ii) {
							for (int jj = j - 3; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 3; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
						do_middle();
					} else if (u % 4 && r % 4) {
						id = 2;
						ans[i - 2][j] = ans[i - 2][j + 1] = ans[i - 1][j] = ans[i - 1][j + 1] = ++id;
						ans[i - 2][j + 2] = ans[i - 2][j + 3] = ans[i - 1][j + 2] = ans[i - 1][j + 3] = ++id;
						ans[i - 2][j + 4] = ans[i - 1][j + 4] = ans[i][j + 4] = ans[i][j + 3] = ++id;
						ans[i + 1][j + 3] = ans[i + 1][j + 4] = ans[i + 2][j + 3] = ans[i + 2][j + 4] = ++id;
						for (int jj = j; jj <= j + 4; ++jj) {
							for (int ii = i - 3; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 3; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i - 2; ii <= i + 2; ++ii) {
							for (int jj = j - 1; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 5; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
						do_middle();
					} else if (u % 4 && d % 4) {
						vector<vector<int>> tans;
						if (R == i && c == j) tans = vector<vector<int>> {
							{1, 1, 2},
							{1, 1, 2},
							{0, 2, 2},
							{3, 3, 4},
							{3, 3, 4},
							{5, 4, 4},
							{5, 5, 5}
						}; else if (R == i && c == j + 1) tans = vector<vector<int>> {
							{1, 1, 2},
							{1, 1, 2},
							{3, 0, 2},
							{3, 3, 2},
							{3, 4, 5},
							{4, 4, 5},
							{4, 5, 5}
						}; else if (R == i && c == j + 2) tans = vector<vector<int>> {
							{2, 1, 1},
							{2, 1, 1},
							{2, 2, 0},
							{3, 3, 3},
							{3, 5, 5},
							{4, 4, 5},
							{4, 4, 5}
						}; else if (R == i + 1 && c == j) tans = vector<vector<int>> {
							{1, 1, 2},
							{1, 2, 2},
							{1, 2, 3},
							{0, 3, 3},
							{4, 4, 3},
							{4, 4, 5},
							{5, 5, 5}
						}; else if (R == i + 1 && c == j + 1) tans = vector<vector<int>> {
							{1, 1, 2},
							{1, 1, 2},
							{3, 3, 2},
							{3, 0, 2},
							{3, 5, 5},
							{4, 4, 5},
							{4, 4, 5}
						}; else if (R == i + 1 && c == j + 2) tans = vector<vector<int>> {
							{2, 2, 1},
							{2, 2, 1},
							{3, 1, 1},
							{3, 3, 0},
							{3, 4, 4},
							{5, 4, 4},
							{5, 5, 5}
						}; else if (R == i + 2 && c == j) tans = vector<vector<int>> {
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{0, 4, 5},
							{4, 4, 5},
							{4, 5, 5}
						}; else if (R == i + 2 && c == j + 1) tans = vector<vector<int>> {
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{4, 0, 5},
							{4, 4, 5},
							{4, 5, 5}
						}; else if (R == i + 2 && c == j + 2) tans = vector<vector<int>> {
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{1, 2, 3},
							{5, 4, 0},
							{5, 4, 4},
							{5, 5, 4}
						};
						id = 5;
						for (int x = 0; x < 7; ++x) for (int y = 0; y < 3; ++y) ans[i - 2 + x][j + y] = tans[x][y];
						for (int jj = j; jj <= j + 2; ++jj) {
							for (int ii = i - 3; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 5; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i - 2; ii <= i + 4; ++ii) {
							for (int jj = j - 1; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 3; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
					} else if (l % 4 && r % 4) {
						vector<vector<int>> tans;
						if (R == i && c == j) tans = vector<vector<int>> {
							{1, 2, 0, 3, 4, 5, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 2, 3, 3, 4, 5}
						}; else if (R == i && c == j + 1) tans = vector<vector<int>> {
							{1, 2, 2, 0, 4, 4, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 3, 3, 3, 5, 5}
						}; else if (R == i && c == j + 2) tans = vector<vector<int>> {
							{1, 2, 2, 3, 0, 5, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 3, 3, 4, 4, 5}
						}; else if (R == i + 1 && c == j) tans = vector<vector<int>> {
							{1, 2, 2, 2, 4, 4, 5},
							{1, 2, 0, 3, 4, 4, 5},
							{1, 1, 3, 3, 3, 5, 5}
						}; else if (R == i + 1 && c == j + 1) tans = vector<vector<int>> {
							{1, 2, 2, 4, 4, 5, 5},
							{1, 2, 2, 0, 4, 4, 5},
							{1, 1, 3, 3, 3, 3, 5}
						}; else if (R == i + 1 && c == j + 2) tans = vector<vector<int>> {
							{1, 2, 2, 3, 4, 4, 4},
							{1, 2, 2, 3, 0, 5, 4},
							{1, 1, 3, 3, 5, 5, 5}
						}; else if (R == i + 2 && c == j) tans = vector<vector<int>> {
							{1, 2, 2, 3, 3, 5, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 0, 3, 4, 4, 5}
						}; else if (R == i + 2 && c == j + 1) tans = vector<vector<int>> {
							{1, 2, 3, 3, 3, 5, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 2, 0, 4, 4, 5}
						}; else if (R == i + 2 && c == j + 2) tans = vector<vector<int>> {
							{1, 2, 2, 3, 4, 4, 5},
							{1, 2, 2, 3, 4, 4, 5},
							{1, 1, 3, 3, 0, 5, 5}
						};
						id = 5;
						for (int x = 0; x < 3; ++x) for (int y = 0; y < 7; ++y) ans[i + x][j - 2 + y] = tans[x][y];
						for (int jj = j - 2; jj <= j + 4; ++jj) {
							for (int ii = i - 1; ii >= 1; ii -= 4) {
								++id;
								ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
							}
							for (int ii = i + 3; ii <= n; ii += 4) {
								++id;
								ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
							}
						}
						for (int ii = i; ii <= i + 2; ++ii) {
							for (int jj = j - 3; jj >= 1; jj -= 4) {
								++id;
								ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
							}
							for (int jj = j + 5; jj <= m; jj += 4) {
								++id;
								ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
							}
						}
					}
				} else {
					do_middle();
					id = 2;
					ans[i - 2][j - 2] = ans[i - 2][j - 1] = ans[i - 1][j - 2] = ans[i - 1][j - 1] = ++id;
					ans[i - 2][j] = ans[i - 2][j + 1] = ans[i - 1][j] = ans[i - 1][j + 1] = ++id;
					ans[i - 2][j + 2] = ans[i - 2][j + 3] = ans[i - 1][j + 2] = ans[i - 1][j + 3] = ++id;
					ans[i - 2][j + 4] = ans[i - 1][j + 4] = ans[i][j + 4] = ans[i][j + 3] = ++id;
					ans[i + 1][j + 3] = ans[i + 1][j + 4] = ans[i + 2][j + 4] = ans[i + 2][j + 3] = ++id;
					ans[i][j - 2] = ans[i][j - 1] = ans[i + 1][j - 2] = ans[i + 1][j - 1] = ++id;
					ans[i + 2][j - 2] = ans[i + 2][j - 1] = ans[i + 3][j - 2] = ans[i + 3][j - 1] = ++id;
					ans[i + 4][j - 2] = ans[i + 4][j - 1] = ans[i + 4][j] = ans[i + 3][j] = ++id;
					ans[i + 3][j + 1] = ans[i + 3][j + 2] = ans[i + 4][j + 1] = ans[i + 4][j + 2] = ++id;
					ans[i + 3][j + 3] = ans[i + 3][j + 4] = ans[i + 4][j + 3] = ans[i + 4][j + 4] = ++id;
					for (int jj = j - 2; jj <= j + 4; ++jj) {
						for (int ii = i - 3; ii >= 1; ii -= 4) {
							++id;
							ans[ii][jj] = ans[ii - 1][jj] = ans[ii - 2][jj] = ans[ii - 3][jj] = id;
						}
						for (int ii = i + 5; ii <= n; ii += 4) {
							++id;
							ans[ii][jj] = ans[ii + 1][jj] = ans[ii + 2][jj] = ans[ii + 3][jj] = id;
						}
					}
					for (int ii = i - 2; ii <= i + 4; ++ii) {
						for (int jj = j - 3; jj >= 1; jj -= 4) {
							++id;
							ans[ii][jj] = ans[ii][jj - 1] = ans[ii][jj - 2] = ans[ii][jj - 3] = id;
						}
						for (int jj = j + 5; jj <= m; jj += 4) {
							++id;
							ans[ii][jj] = ans[ii][jj + 1] = ans[ii][jj + 2] = ans[ii][jj + 3] = id;
						}
					}
				}
				for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
					if (ans[i][j]) continue;
					if (i == R && j == c) continue;
					ans[i][j] = ans[i + 1][j] = ans[i][j + 1] = ans[i + 1][j + 1] = ++id;
				}
				print(ans);
				return;
			}
		}
	}
}

int main() {
	int t; cin >> t; while (t--) {
		solve();
	}
}
