#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    if (accumulate(A.begin(), A.end(), 0) % 2 == 1) {
        cout << "no quotation\n";
        return 0;
    }
    for (int k = 100; k >= 2; --k) {
        int left = 0;
        bool ok = true;
        vector<int> B = A;
        for (int j = k; j >= 2; --j) {
            if (left >= N) {
                ok = false;
                break;
            }
            if (B[left] < j) {
                ok = false;
                break;
            }
            B[left] -= j;
            if (B[left] == 0) left++;
        }
        if (!ok) continue;
        int right = N - 1;
        for (int j = k; j >= 2; --j) {
            if (right < 0) {
                ok = false;
                break;
            }
            if (B[right] < j) {
                ok = false;
                break;
            }
            B[right] -= j;
            if (B[right] == 0) right--;
        }
        if (!ok) continue;
        if (right < left) continue;
        if (right == left && B[right] == 0) continue;
        cout << k << "\n";
        return 0;
    }
    if (N == 1 && A[0] == 2) {
        cout << "1\n";
        return 0;
    }
    if (N == 2 && A[0] == 1 && A[1] == 1) {
        cout << "1\n";
        return 0;
    }
    cout << "no quotation\n";
    return 0;
}

