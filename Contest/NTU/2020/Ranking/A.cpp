#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> y[i];
    }
    for (int it = 0; it < N; ++it) {
        for (int i = it + 1; i < N; ++i) x[i] -= x[it];
        for (int i = it + 1; i < N; ++i) y[i] -= y[it];
        for (int i = it + 1; i < N; ++i) {
            if (y[i] % x[i] != 0) {
                cout << "No\n";
                return 0;
            }
            y[i] /= x[i];
        }
    }
    cout << "Yes\n";
}
