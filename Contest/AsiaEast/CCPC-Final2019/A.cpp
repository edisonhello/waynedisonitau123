#include <bits/stdc++.h>
using namespace std;


pair<int, int> parse(pair<string, string> a) {
    pair<int, int> rt;
    if (a.first == "Jan") rt.first = 1;
    else if (a.first == "Feb") rt.first = 2;
    else if (a.first == "Mar") rt.first = 3;
    else if (a.first == "Apr") rt.first = 4;
    else if (a.first == "May") rt.first = 5;
    else if (a.first == "Jun") rt.first = 6;
    else if (a.first == "Jul") rt.first = 7;
    else if (a.first == "Aug") rt.first = 8;
    else if (a.first == "Sept") rt.first = 9;
    else if (a.first == "Oct") rt.first = 10;
    else if (a.first == "Nov") rt.first = 11;
    else if (a.first == "Dec") rt.first = 12;

    rt.second = atoi(a.second.substr(0, a.second.size() - 2).c_str());
    
    return rt;
}

bool cmp(pair<string, string> a, pair<string, string> b) {
    pair<int, int> aa = parse(a), bb = parse(b);
    return aa < bb;
}

int main() {
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        int n; cin >> n;
        vector<pair<string, string>> days(n);
        for (int i = 0; i < n; ++i) cin >> days[i].first >> days[i].second;
        pair<string, string> now; cin >> now.first >> now.second;

        sort(days.begin(), days.end(), cmp);
        auto it = upper_bound(days.begin(), days.end(), now, cmp);
        if (it == days.end()) cout << "Case #" << T << ": See you next year" << endl;
        else cout << "Case #" << T << ": " << it->first << ' ' << it->second << endl;
    }
}

