#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) {
        if (A[i] > 0) {
            if (A[i] != 1) {
                cout << "NO\n";
                return 0;
            }
            break;
        }
    }
    for (int i = N - 1; i >= 0; --i) {
        if (A[i] > 0) {
            if (A[i] != 1) {
                cout << "NO\n";
                return 0;
            }
            break;
        }
    }
    vector<int> Next(N, -1), Prev(N, -1);
    for (int i = N - 1, p = -1; i >= 0; --i) {
        Next[i] = p;
        if (A[i] > 0) p = i;
    }
    for (int i = 0, p = -1; i < N; ++i) {
        Prev[i] = p;
        if (A[i] > 0) p = i;
    }
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += A[i];
        if (sum % 2 == 0) {
            if (Next[i] != -1 && A[Next[i]] != 1) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    sum = 0;
    for (int i = N - 1; i >= 0; --i) {
        sum += A[i];
        if (sum % 2 == 0) {
            if (Prev[i] != -1 && A[Prev[i]] != 1) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    if (accumulate(A.begin(), A.end(), 0) % 2 != 0) cout << "NO\n";
    else cout << "YES\n";
}

