#include <bits/stdc++.h>
using namespace std;

int main() {
    int ai, aj, bi, bj, r; 
    scanf("%d%d%d%d%d", &ai, &aj, &bi, &bj, &r);
    if (bi < ai) swap(bi, ai), swap(bj, aj);
    if (bi + ai <= r) {
        puts("Yes");
        return 0;
    }
    if (ai <= bj && bi <= r) {
        puts("Yes");
        return 0;
    }
    puts("No");
}
