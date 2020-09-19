#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    int res = 0;
    int64_t sum = 0;
    for (int i = 0; i < N; ++i) {
        if (sum >= A[i]) continue;
        sum += A[i];
        res++;
    }
    cout << res << "\n";
}

