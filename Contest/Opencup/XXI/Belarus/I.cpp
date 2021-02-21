#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    int A = 0, B = 0;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        A += x == 0;
    }
    for (int i = 0; i < M; ++i) {
        int x;
        cin >> x;
        B += x == 1;
    }
    cout << abs(A - B) << "\n";
}

