#include <bits/stdc++.h>
using namespace std;

int main() {
    int L, R;
    cin >> L >> R;

    auto Get = [&](int x) {
        int res = 0;
        for (int i = 1; i < x; ++i) {
            if (x % i == 0) res += i;
        }
        return res;
    };

    int a = 0, b = 0, c = 0;
    for (int i = L; i <= R; ++i) {
        int t = Get(i);
        if (t < i) a++;
        else if (t == i) b++;
        else c++;
    }
    cout << a << " " << b << " " << c << "\n";
}
