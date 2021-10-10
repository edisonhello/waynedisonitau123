#include <bits/stdc++.h>
using namespace std;

vector<int> rod[1005];

int did[1005];
vector<pair<int, int>> place[1005];
int weight[1005];

int main() {
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) rod[i].resize(3, 0);
  for (int i = 2; i >= 0; --i) {
    for (int j = 1; j <= n; ++j) {
      cin >> rod[j][i];
    }
  }
  rod[n + 1] = vector<int>{};

  vector<pair<int, int>> answer;

  auto Move = [&] (const int a, const int b) {
    // cerr << "Move " << a << ' ' << b << endl;
    answer.emplace_back(a, b);
    rod[b].push_back(rod[a].back());
    rod[a].pop_back();
  };


  for (int _ = 0; _ < n; ++_) {
    for (int i = 1; i <= n; ++i) place[i].clear();
    for (int i = 1; i <= n + 1; ++i) {
      for (int j = 0; j < rod[i].size(); ++j) {
        place[rod[i][j]].emplace_back(i, j);
      }
    }

    for (int i = 1; i <= n; ++i) {
      assert(place[i].size() == 3u);
      if (place[i][0].first == place[i][1].first && place[i][1].first == place[i][2].first) weight[i] = -1000;
      else weight[i] = place[i][0].second + place[i][1].second + place[i][2].second;
    }

    int i = max_element(weight + 1, weight + 1 + n) - weight;

    if (weight[i] == -1000) break;

    int empty = -1;
    for (int i = 1; i <= n + 1; ++i) if (rod[i].empty()) empty = i;
    assert(empty != -1);

    sort(place[i].begin(), place[i].end(), [&] (const auto a, const auto b) { return a.second > b.second; });
    assert(place[i][0].second == 2);
    assert(place[i][1].second >= 1);

    if (place[i][1].second == 2) {
      if (place[i][2].second == 2) {
        Move(place[i][0].first, empty);
        Move(place[i][1].first, empty);
        Move(place[i][2].first, empty);
        Move(place[i][2].first, place[i][0].first);
        Move(place[i][2].first, place[i][1].first);
      } else if (place[i][2].second == 1) {
        Move(place[i][0].first, empty);
        Move(place[i][1].first, empty);
        if (rod[place[i][2].first].size() == 3u) {
          Move(place[i][2].first, place[i][0].first);
          Move(place[i][2].first, empty);
          Move(place[i][2].first, place[i][1].first);
        } else if (rod[place[i][2].first].size() == 2u) {
          Move(place[i][2].first, empty);
          if (place[i][2].first == place[i][0].first) {
            Move(place[i][2].first, place[i][1].first);
          } else if (place[i][2].first == place[i][1].first) {
            Move(place[i][2].first, place[i][0].first);
          } else assert(0);
        }
      } else if (place[i][2].second == 0) {
        Move(place[i][0].first, empty);
        Move(place[i][1].first, empty);
        if (rod[place[i][2].first].size() == 3u) {
          Move(place[i][2].first, place[i][0].first);
          Move(place[i][2].first, place[i][1].first);
          Move(place[i][2].first, empty);
        } else if (rod[place[i][2].first].size() == 2u) {
          if (place[i][2].first == place[i][0].first) {
            Move(place[i][2].first, place[i][1].first);
          } else if (place[i][2].first == place[i][1].first) {
            Move(place[i][2].first, place[i][0].first);
          } else assert(0);
          Move(place[i][2].first, empty);
        } else assert(0);
      } else assert(0);
    } else if (place[i][1].second == 1) {
      if (place[i][2].second == 1) {
        Move(place[i][0].first, empty);
        if (rod[place[i][1].first].size() == 2u) {
          Move(place[i][1].first, empty);
          Move(place[i][2].first, place[i][1].first);
          Move(place[i][2].first, empty);
          Move(place[i][2].first, place[i][1].first);
        } else if (rod[place[i][2].first].size() == 2u) {
          Move(place[i][2].first, empty);
          Move(place[i][1].first, place[i][2].first);
          Move(place[i][1].first, empty);
          Move(place[i][1].first, place[i][2].first);
        } else {
          Move(place[i][1].first, place[i][0].first);
          Move(place[i][1].first, empty);
          Move(place[i][2].first, place[i][1].first);
          Move(place[i][2].first, empty);
          Move(place[i][2].first, place[i][1].first);
        }
      } else if (place[i][2].second == 0) {
        Move(place[i][0].first, empty);
        if (rod[place[i][1].first].size() == 2u) {
          Move(place[i][1].first, empty);
          if (rod[place[i][2].first].size() == 1u) assert(0);
          else {
            Move(place[i][2].first, place[i][1].first);
            Move(place[i][2].first, place[i][1].first);
            Move(place[i][2].first, empty);
          }
        } else if (rod[place[i][1].first].size() == 3u) {
          Move(place[i][1].first, place[i][0].first);
          Move(place[i][1].first, empty);
          if (rod[place[i][2].first].size() == 1u) {
            Move(place[i][2].first, empty);
          } else if (rod[place[i][2].first].size() == 3u) {
            Move(place[i][2].first, place[i][1].first);
            Move(place[i][2].first, place[i][1].first);
            Move(place[i][2].first, empty);
          } else assert(0);
        } else assert(0);
      } else assert(0);
    } else assert(0);

    // for (int j = 2; j >= 0; --j) {
    //   for (int i = 1; i <= n + 1; ++i) {
    //     if (j < rod[i].size()) cerr << rod[i][j] << ' ';
    //     else cerr << "0 ";
    //   }
    //   cerr << endl;
    // }
  }

  // empty last
  int empty = -1;
  for (int i = 1; i <= n + 1; ++i) if (rod[i].empty()) {
    empty = i;
    if (i != n + 1) {
      Move(n + 1, i);
      Move(n + 1, i);
      Move(n + 1, i);
    }
  }

  assert(empty != -1);

  cout << answer.size() << endl;
  for (auto [x, y] : answer) cout << x << ' ' << y << '\n';
}
