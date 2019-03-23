#include <bits/stdc++.h>
using namespace std;
#define PDE1(x) cerr << #x << " = " << x << endl
#define PDE2(x, y) cerr << #x << " = " << x << " , ", PDE1(y)
#define PDE3(x, y, z) cerr << #x << " = " << x << " , ", PDE2(y, z)
#define PDE4(x, y, z, q) cerr << #x << " = " << x << " , ", PDE3(y, z, q)

bool near(double x, double y, double eps) {
	return abs(x - y) < eps;
}

struct wall {
	int x1, y1, x2, y2;
	bool operator < (const wall &y) const {
		return make_tuple(x1, y1, x2, y2) < make_tuple(y.x1, y.y1, y.x2, y.y2);
	}
};

int main() {
	int n; cin >> n;
	int ans = 0;
	int tx, ty; cin >> tx >> ty;
	vector<wall> v(n);
	for (wall &x : v) cin >> x.x1 >> x.y1 >> x.x2 >> x.y2;
	for (wall &x : v) {
		// tie(x.x1, x.x2) = minmax(x.x1, x.x2);
		// tie(x.y1, x.y2) = minmax(x.y1, x.y2);
		if (x.x1 == x.x2) {
			if (x.y1 > x.y2) swap(x.y1, x.y2);
		} else {
			if (x.x1 > x.x2) swap(x.x1, x.x2);
		}
	}
	sort(v.begin(), v.end());
	int getmax = -1;
	if (tx == 0) {
		int a = 0, b = 0, c = 0;
		for (wall &x : v) {
			if (x.x1 <= 0 && x.x2 >= 0) {
				if (ty > 0) {
					if (x.y1 > ty) ++c;
					else if (x.y1 > 0 && x.y1 < ty) ++b;
					else ++a;

				} else {
					if (x.y1 > 0) ++a;
					else if(x.y1 > ty) ++b;
					else ++c;
				}
			}
		}
		if (a > b + c) getmax = 2 * (b + c) + 1;
		else if (a == b + c) getmax = a + b + c;
		else if (b <= a) getmax = 2 * a + 1;
	} else if (ty == 0) {
		int a = 0, b = 0, c = 0;
		for (wall &x : v) {
			if (x.y1 <= 0 && x.y2 >= 0) {
				if (tx > 0) {
					if (x.x1 > tx) ++c;
					if (x.x1 > 0 && x.x1 < tx) ++b;
					else ++a;
				} else {
					if (x.x1 > 0) ++a;
					else if(x.x1 > tx) ++b;
					else ++c;
				}
			}
		}
		if (a > b + c) getmax = 2 * (b + c) + 1;
		else if (a == b + c) getmax = a + b + c;
		else if (b <= a) getmax = 2 * a + 1;
	}
	for (int hit = n; hit; --hit) {	
		do {
			// cerr << "check wall: ";
			// for (int i = 0; i < hit; ++i) { cerr << v[i].x1 << " " << v[i].y1 << " " << v[i].x2 << " " << v[i].y2 << " :, "; } cerr << endl;
			int holex = tx, holey = ty;
			for (int i = hit - 1; i >= 0; --i) {
				if (v[i].x1 == v[i].x2) holex = 2 * v[i].x1 - holex;
				else holey = 2 * v[i].y1 - holey;
			}
			// PDE2(holex, holey);
			int gg = __gcd(holex, holey);
			if (gg == 0 || holex == 0 || holey == 0) continue;
			int dx = holex / gg, dy = holey / gg;
			double nowx = 0, nowy = 0;
			bool ok = true;
			vector<bool> disappear(n, false);
			// PDE2(dx, dy);
			for (int i = 0; i < hit; ++i) {
				wall hit = v[i];
				double min_hit_time = 1e9;
				vector<double> hit_times(n, 1e9);
				for (int j = 0; j < n; ++j) {
					if (disappear[j]) continue;
					wall tar = v[j];
					if (tar.x1 == tar.x2) {
						if (dx == 0) continue;
						if (nowx == tar.x1) continue;
						double x_dist = tar.x1 - nowx;
						double hit_time = double(x_dist) / dx;
						// PDE3(j, x_dist, hit_time);
						if (hit_time < 0) continue;
						double hit_y = nowy + dy * hit_time;
						// PDE3(tar.y1, hit_y, tar.y2);
						if (hit_y < tar.y1 - 1e-6 || tar.y2 + 1e-6 < hit_y) continue;
						hit_times[j] = hit_time;
						min_hit_time = min(min_hit_time, hit_time);
					} else {
						if (dy == 0) continue;
						if (nowy == tar.y1) continue;
						double y_dist = tar.y1 - nowy;
						double hit_time = double(y_dist)/ dy;
						if (hit_time < 0) continue;
						double hit_x = nowx + dx * hit_time;
						if (hit_x < tar.x1 - 1e-6 || tar.x2 + 1e-6 < hit_x) continue;
						hit_times[j] = hit_time;
						min_hit_time = min(min_hit_time, hit_time);
					}
				}
				// PDE1(i);
				// PDE4(nowx, nowy, dx, dy);
				// PDE2(hit_times[i], min_hit_time);
				if (near(hit_times[i], min_hit_time, 1e-9) && min_hit_time <= 8e8) {
					disappear[i] = true;
					if (hit.x1 == hit.x2) {
						double x_dist = hit.x1 - nowx;
						double hit_time = double(x_dist) / dx;
						double hit_y = nowy + dy * hit_time;
						// PDE3(x_dist, hit_time, hit_y);
						nowx = hit.x1;
						nowy = hit_y;
						dx *= -1;
					} else {
						double y_dist = hit.y1 - nowy;
						double hit_time = double(y_dist)/ dy;
						double hit_x = nowx + dx * hit_time;
						nowx = hit_x;
						nowy = hit.y1;
						dy *= -1;
					}
				} else {
					ok = false;
					break;
				}
			}
			if (ok) {
				double min_hit_time = 1e9;
				vector<double> hit_times(n, 1e9);
				for (int j = 0; j < n; ++j) {
					if (disappear[j]) continue;
					wall tar = v[j];
					if (tar.x1 == tar.x2) {
						if (dx == 0) continue;
						if (nowx == tar.x1) continue;
						double x_dist = tar.x1 - nowx;
						double hit_time = double(x_dist) / dx;
						if (hit_time < 0) continue;
						double hit_y = nowy + dy * hit_time;
						if (hit_y < tar.y1 - 1e-6 || tar.y2 + 1e-6 < hit_y) continue;
						hit_times[j] = hit_time;
						min_hit_time = min(min_hit_time, hit_time);
					} else {
						if (dy == 0) continue;
						if (nowy == tar.y1) continue;
						double y_dist = tar.y1 - nowy;
						double hit_time = double(y_dist)/ dy;
						if (hit_time < 0) continue;
						double hit_x = nowx + dx * hit_time;
						if (hit_x < tar.x1 - 1e-6 || tar.x2 + 1e-6 < hit_x) continue;
						hit_times[j] = hit_time;
						min_hit_time = min(min_hit_time, hit_time);
					}
				}
				double x_dist = tx - nowx;
				double hit_time = double(x_dist) / dx;
				if (hit_time < 0) continue;
				double hit_y = nowy + dy * hit_time;
				if (!near(hit_y, ty, 1e-9)) continue;
				if (hit_time > min_hit_time) continue;
				cout << max(hit, getmax) << endl;
				exit(0);
			}
		} while (next_permutation(v.begin(), v.end()));
	}

	double nowx = 0, nowy = 0;
	int dx = tx, dy = ty;

	double min_hit_time = 1e9;
	vector<double> hit_times(n, 1e9);
	for (int j = 0; j < n; ++j) {
		wall tar = v[j];
		if (tar.x1 == tar.x2) {
			if (dx == 0) continue;
			if (nowx == tar.x1) continue;
			double x_dist = tar.x1 - nowx;
			double hit_time = double(x_dist) / dx;
			if (hit_time < 0) continue;
			double hit_y = nowy + dy * hit_time;
			if (hit_y < tar.y1 - 1e-6 || tar.y2 + 1e-6 < hit_y) continue;
			hit_times[j] = hit_time;
			min_hit_time = min(min_hit_time, hit_time);
		} else {
			if (dy == 0) continue;
			if (nowy == tar.y1) continue;
			double y_dist = tar.y1 - nowy;
			double hit_time = double(y_dist)/ dy;
			if (hit_time < 0) continue;
			double hit_x = nowx + dx * hit_time;
			if (hit_x < tar.x1 - 1e-6 || tar.x2 + 1e-6 < hit_x) continue;
			hit_times[j] = hit_time;
			min_hit_time = min(min_hit_time, hit_time);
		}
	}
	if (getmax != -1) {
		cout << getmax << endl;
		exit(0);
	}
	auto imp = [&] () -> void { cout << "impossible" << endl; exit(0); };
	if (tx != nowx) {
		double x_dist = tx - nowx;
		double hit_time = double(x_dist) / dx;
		if (hit_time < 0) imp();
		double hit_y = nowy + dy * hit_time;
		if (!near(hit_y, ty, 1e-9)) imp();
		if (hit_time > min_hit_time) imp();
		cout << 0 << endl;
	} else {
		double y_dist = ty - nowy;
		double hit_time = double(y_dist) / dy;
		if (hit_time < 0) imp();
		double hit_x = nowx + dx * hit_time;
		if (!near(hit_x, tx, 1e-9)) imp();
		if (hit_time > min_hit_time) imp();
		cout << 0 << endl;
	}
}
