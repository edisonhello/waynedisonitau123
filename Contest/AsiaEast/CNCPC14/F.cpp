#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int CalcTake(vector<int> cnt) {
    // cerr << "cnt: ";
    // for (int i : cnt) cerr << i << ' ';
    // cerr << endl;

    sort(cnt.begin(), cnt.end(), greater<int>());


    int a = cnt[0];
    int b = cnt[1];
    int c = cnt[2];
    int d = cnt[3];
    int e = cnt[4];

    int bcde2 = (b + c + d + e + 1) / 2;

    int r;
    if (a >= bcde2 && b <= c + d + e) {
        r = bcde2 + (a - bcde2 + 1) / 2;
    } else if (a >= bcde2) {
        r = b + (a - b + 1) / 2;
    } else {
        r = (a + b + c + d + e + 2) / 3;
    }
    // cerr << "r = " << r << endl;
    return r;
}

int solve() {
    int n, m, goal; cin >> n >> m >> goal;
    vector<tuple<int, int, vector<pair<int, int>>>> cards;
    for (int i = 0; i < n; ++i) {
        int score, type, need;
        cin >> score >> type >> need;
        --type;
        vector<pair<int, int>> ne;
        while (need--) {
            int typ, nee;
            cin >> typ >> nee;
            --typ;
            ne.emplace_back(typ, nee);
        }
        cards.emplace_back(score, type, ne);
    }

    vector<int> piratescore;
    vector<vector<vector<int>>> gemgetpirate(5, vector<vector<int>>(10));

    for (int i = 0; i < m; ++i) {
        int score, need; cin >> score >> need;
        vector<int> needs(5, 0);

        while (need--) {
            int typ, nee;
            cin >> typ >> nee;
            --typ;
            needs[typ] = nee;
        }

        piratescore.push_back(score);
        for (int j = 0; j < 5; ++j) gemgetpirate[j][needs[j]].push_back(i);
    }

    int mnround = INT_MAX;

    int curscore = 0;
    vector<int> gemcard(5, 0);
    vector<int> gemneed(5, 0);
    vector<int> piratesatisfy(m, 0);
    int cardcount = 0;

    auto CalcAnswer = [&] () {
        if (curscore >= goal) {
            int rt = cardcount + CalcTake(gemneed);
            // cerr << "curscore " << curscore << endl;
            // cerr << "cardcount = " << cardcount << " rt = " << rt << endl;
            mnround = min(mnround, rt);
            return rt;
        }
        return -1;
    };

    auto Dfs = [&] (auto self, int cur) {
        if (cur == n) {
            CalcAnswer();
            return;
        }

        // cerr << "not take " << cur << endl;

        self(self, cur + 1);
        // cerr << "take " << cur << endl;

        auto &[cardscore, cardtype, cardneed] = cards[cur];

        ++cardcount;
        curscore += cardscore;
        gemcard[cardtype]++;
        for (auto &[t, c] : cardneed) gemneed[t] += c;
        for (int pi : gemgetpirate[cardtype][gemcard[cardtype]]) {
            // cerr << "cardtype " << cardtype << " gemcard count " << gemcard[cardtype]
            ++piratesatisfy[pi];
            // cerr << "pi " << pi << " now satisfy " << piratesatisfy[pi] << endl;
            if (piratesatisfy[pi] == 5) {
                // cerr << "pi get good " << pi << endl;
                curscore += piratescore[pi];
            }
        }

        self(self, cur + 1);

        for (int pi : gemgetpirate[cardtype][gemcard[cardtype]]) {
            if (piratesatisfy[pi] == 5) {
                // cerr << "pi bad " << pi << endl;
                curscore -= piratescore[pi];
            }
            --piratesatisfy[pi];
        }
        for (auto &[t, c] : cardneed) gemneed[t] -= c;
        gemcard[cardtype]--;
        curscore -= cardscore;
        --cardcount;
    };

    for (int i = 0; i < 5; ++i) {
        for (int pi : gemgetpirate[i][0]) ++piratesatisfy[pi];
    }

    Dfs(Dfs, 0);

    if (mnround >= 1e9) return -1;
    return mnround;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        cout << solve() << '\n';
    }
}

