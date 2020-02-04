#include <bits/stdc++.h>
using namespace std;

set<long long> s;

void Dfs(long long n) {
    if (s.count(n)) return;
    int a = 1'000'000'000;
    for (int d = 30; d >= 0; --d) {
        int k = a - (1 << d);
        if (k < 0) continue;
        if (1LL * k * k >= n) a = k;
    }
    int b = 1LL * a * a - n;
    Dfs(a);
    Dfs(b);
    s.insert(n);
    printf("%d %d\n", a, b);
}

int main() {
    s.insert(0);
    s.insert(1);
    s.insert(2);
    long long n;
    scanf("%lld", &n);
    Dfs(n);    
}

