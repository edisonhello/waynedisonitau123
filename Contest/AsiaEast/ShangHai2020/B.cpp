#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> A(N);
    vector<string> B(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    swap(A, B);
    int X = 0, Y = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            X += A[i][j] == B[i][j];
            Y += A[i][j] != B[i][j];
        }
    }
    assert(max(X, Y) >= N * M - (N * M) / 2);
    if (Y > X) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (B[i][j] == '.') B[i][j] = 'X';
                else B[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < N; ++i) cout << B[i] << "\n";
}

