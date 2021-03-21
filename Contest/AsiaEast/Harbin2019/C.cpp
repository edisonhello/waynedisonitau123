#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Player {
	int game_played;
	int game_point;
	int match_played;
	int match_point;
	vector<int> op_list;

	Player() : game_played(0), game_point(0), match_played(0), match_point(0) {}

	void match(int op, int win, int lose, int tie) {
		if (op) op_list.push_back(op);
		game_played += win + lose + tie;
		game_point += win * 3 + tie;
		match_played++;
		match_point += win > lose ? 3 : win == lose ? 1 : 0;
	}

	void byes() {
		match(0, 2, 0, 0);
	}

	pair<int, int> GetMW() {
		int u = match_point, d = match_played * 3;
		int g = __gcd(u, d);
		u /= g, d /= g;
		if (u * 3 < d) return make_pair(1ll, 3ll);
		return make_pair(u, d);
	}

	pair<int, int> GetGW() {
		int u = game_point, d = game_played * 3;
		int g = __gcd(u, d);
		u /= g, d /= g;
		if (u * 3 < d) return make_pair(1ll, 3ll);
		return make_pair(u, d);
	}
};

void solve() {
	int n, m; cin >> n >> m;
	vector<int> games(m + 1);
	for (int i = 1; i <= m; ++i) cin >> games[i];

	vector<Player> players(n + 1);

	vector<tuple<int, int, int, int, int>> play_record;
	vector<int> played(n + 1, 0);
	auto PlayGames = [&] (const int rnd) {
		play_record.clear();
		fill(played.begin(), played.end(), 0);

		for (int i = 0; i < games[rnd]; ++i) {
			int pa, pb, wa, wb, ti; cin >> pa >> pb >> wa >> wb >> ti;
			played[pa] = played[pb] = 1;
			players[pa].match(pb, wa, wb, ti);
			players[pb].match(pa, wb, wa, ti);
		}
	};
	
	auto ReceiveByes = [&] () {
		for (int i = 1; i <= n; ++i) {
			if (!played[i]) players[i].byes();
		}
	};

	auto StringFrac = [&] (pair<int, int> p) {
		int g = __gcd(p.first, p.second);
		return to_string(p.first / g) + "/" + to_string(p.second / g);
	};

	auto GetOMW = [&] (Player &p) {
		int u = 0, d = 1;
		if (p.op_list.empty()) return make_pair(1ll, 3ll);
		for (int op : p.op_list) {
			auto r = players[op].GetMW();
			int g = __gcd(d, r.second);
			int dd = d / g * r.second;
			u = u * (dd / d) + r.first * (dd / r.second);
			d = dd;
			g = __gcd(u, d);
			u /= g, d /= g;
		}
		int sz = p.op_list.size();
		int g = __gcd(u, sz);
		u /= g, sz /= g;
		d *= sz;
		// if (3 * u < d) return make_pair(1, 3);
		return make_pair(u, d);
	};

	auto GetOGW = [&] (Player &p) {
		int u = 0, d = 1;
		if (p.op_list.empty()) return make_pair(1ll, 3ll);
		for (int op : p.op_list) {
			auto r = players[op].GetGW();
			int g = __gcd(d, r.second);
			int dd = d / g * r.second;
			u = u * (dd / d) + r.first * (dd / r.second);
			d = dd;
			g = __gcd(u, d);
			u /= g, d /= g;
		}
		int sz = p.op_list.size();
		int g = __gcd(u, sz);
		u /= g, sz /= g;
		d *= sz;
		// if (3 * u < d) return make_pair(1, 3);
		return make_pair(u, d);
	};

	auto OutputStatus = [&] (const int rnd) {
		cout << "Round " << rnd << '\n';
		for (int i = 1; i <= n; ++i) {
			Player &p = players[i];
			cout << p.match_point << ' ' << StringFrac(GetOMW(p)) << ' ' << StringFrac(p.GetGW()) << ' ' << StringFrac(GetOGW(p)) << '\n';
		}
	};

	for (int i = 1; i <= m; ++i) {
		PlayGames(i);
		ReceiveByes();
		OutputStatus(i);
	}

}

int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) solve();
}

