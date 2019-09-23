#include <bits/stdc++.h>
using namespace std;

int tab[10][10];

bool check(int x) {
    array<int, 5> dig{};
    for (int i = 3; i >= 0; --i) {
        dig[i] = x % 10;
        x /= 10;
    }
    int sum = 0;
    for (int i = 0; i < 4; ++i) sum = tab[sum][dig[i]];
    dig[4] = sum;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (dig[i] == j) continue;
            int tsum = 0;
            int old = dig[i];
            dig[i] = j;
            for (int k = 0; k < 5; ++k) tsum = tab[tsum][dig[k]];
            if (tsum == 0) return true;
            dig[i] = old;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (dig[i] == dig[i + 1]) continue;
        swap(dig[i], dig[i + 1]);
        int tsum = 0;
        for (int k = 0; k < 5; ++k) tsum = tab[tsum][dig[k]];
        if (tsum == 0) return true;
        swap(dig[i], dig[i + 1]);
    }
    return false;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) 
            cin >> tab[i][j];
    }
    int ans = 0;
    for (int i = 0; i < 10000; ++i) ans += check(i);
    cout << ans << endl;
    return 0;
}
