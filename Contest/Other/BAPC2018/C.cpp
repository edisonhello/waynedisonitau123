#include <bits/stdc++.h>
using namespace std;


int main() {
    int v; cin >> v;
    
    long long mx = LLONG_MAX;


    auto update = [&] (int a, int b, int c) {
        mx = min(mx, (long long)(a * b + b * c + a * c) * 2);
    };


    for (int fi = floor(pow(v, (double)1 / 3.0) + 0.5); fi >= 1; --fi) {
        if (v % fi) continue;
        int le = v / fi;
        for (int se = floor(pow(v, (double)1 / 2.0) + 0.5); se >= 1; --se) {
            if (le % se) continue;
            int ti = le / se;
            update(fi, se, ti);
        }
    }

    cout << mx << endl;
}

