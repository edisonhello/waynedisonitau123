#include <bits/stdc++.h>
using namespace std;

const int kN = 300'000 + 5;
char s[kN];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    vector<pair<int, int>> v;
    for (int i = 0, j = 0; i < n; i = j) {
        for (j = i; j < n && s[j] == s[i]; ++j);
        v.emplace_back(s[i], j - i);
    }
    if (v.size() % 2 == 0) {
        puts("0");
        return 0;
    }
    for (int i = 0; i < v.size() / 2; ++i) {
        if (v[i].first != v[v.size() - 1 - i].first || 
            v[i].second + v[v.size() - 1 - i].second < 3) {
            puts("0");
            return 0;
        }
    }
    if (v[v.size() / 2].second + 1 < 3) {
        puts("0");
    } else {
        printf("%d\n", v[v.size() / 2].second + 1);
    }
}
