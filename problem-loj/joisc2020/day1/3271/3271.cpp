#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define fi first
#define se second
#define rez resize
#define pb push_back
#define mkp make_pair
#define eb emplace_back
#define debug(...) fprintf (stderr, __VA_ARGS__)

#define Lep(i, l, r) for (int i = l; i < r; ++ i)
#define Rep(i, r, l) for (int i = r; i > l; -- i)
#define lep(i, l, r) for (int i = l; i <= r; ++ i)
#define rep(i, r, l) for (int i = r; i >= l; -- i)

char _c; bool _f; template <class T> inline void IN (T & x) {
	x = 0, _f = 0; while (_c = getchar (), ! isdigit (_c)) if (_c == '-') _f = 1;
	while (isdigit (_c)) x = x * 10 + _c - '0', _c = getchar (); if (_f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 1e6 + 5;

bool ans[N];
int n, n2, a[N], b[N], f[N][2], g[N][2];

inline bool check (int x, int y, int c) { return f[x][y] >= c && g[x][y] <= c; }
int main () {
	IN (n), n2 = n << 1;
	lep (i, 1, n2) IN (a[i]);
	lep (i, 1, n2) IN (b[i]);

	memset (f, -1, sizeof f), f[0][0] = f[0][1] = 0;
	lep (i, 1, n2) {
		if (a[i - 1] <= a[i]) chkmax (f[i][0], f[i - 1][0]);
		if (a[i - 1] <= b[i]) chkmax (f[i][1], f[i - 1][0] + 1);
		if (b[i - 1] <= a[i]) chkmax (f[i][0], f[i - 1][1]);
		if (b[i - 1] <= b[i]) chkmax (f[i][1], f[i - 1][1] + 1);
	}

	memset (g, 0x3f, sizeof g), g[0][0] = g[0][1] = 0;
	lep (i, 1, n2) {
		if (a[i - 1] <= a[i]) chkmin (g[i][0], g[i - 1][0]);
		if (a[i - 1] <= b[i]) chkmin (g[i][1], g[i - 1][0] + 1);
		if (b[i - 1] <= a[i]) chkmin (g[i][0], g[i - 1][1]);
		if (b[i - 1] <= b[i]) chkmin (g[i][1], g[i - 1][1] + 1);
	}

	int all = n, now = ! check (n2, 0, n);
	if (! check (n2, now, n)) return puts ("-1"), 0;

	rep (i, n2, 1) {
		ans[i] = now, all -= now;
		if (i > 1) now = ! (check (i - 1, 0, all) && a[i - 1] <= (now ? b[i] : a[i]));
	}
	lep (i, 1, n2) putchar ('A' + ans[i]);
	puts ("");
	return 0;
}