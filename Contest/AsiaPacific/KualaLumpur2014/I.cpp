#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];
    vector<vector<bitset<500>>> bs(N, vector<bitset<500>>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = j; k < M; ++k) {
                if (grid[i][k] == 'G') {
                    bs[i][j].set(k - j);
                }
            }
        }
    }
    int Q;
    cin >> Q;
    for (int q = 1; q <= Q; ++q) {
        int X, Y;
        cin >> X >> Y;
        vector<bitset<500>> BB(X);
        vector<string> board(X);
        for (int i = 0; i < X; ++i) {
            cin >> board[i];
            for (int j = 0; j < Y; ++j) {
                if (board[i][j] == 'L') BB[i].set(j);
            }
        }
        int A = -1, B = -1, ans = -1;
        for (int c = 0; c + Y <= M; ++c) {
            bitset<500> mask;
            for (int i = 0; i < Y; ++i) mask.set(i);
            for (int r = 0; r + X <= N; ++r) {
                int match = 0;
                for (int k = 0; k < X; ++k) {
                    match += ((bs[r + k][c] ^ BB[k]) & mask).count();
                }
                if (match > ans) {
                    ans = match;
                    A = r;
                    B = c;
                } else if (match == ans) {
                    if (r < A) {
                        A = r;
                        B = c;
                    } else if (r == A) {
                        B = min(B, c);
                    }
                }
            }
        }
        int G = 0, L = 0;
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                if (board[i][j] == grid[i + A][j + B]) {
                    if (board[i][j] == 'G') G++;
                    if (board[i][j] == 'L') L++;
                }
            }
        }
        cout << "Case #" << q << ": " << A + 1 << " " << B + 1 << " " << G << " " << L << "\n";
    }
}
