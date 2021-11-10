#include <bits/stdc++.h>
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

void write (__int128 x) {
	if (x > 9) write (x / 10);
	putchar ((x % 10) + '0');
}

const int N = 2e6 + 5;

int n, top, h[N], L[N], R[N], sta[N], ans[N], head[N];
struct Edge { int nxt, to, val; } G[N];

inline void init_pre () {
	sta[top = 0] = 0;
	lep (i, 1, n) {
		while (top && h[sta[top]] >= h[i]) -- top;
		L[i] = sta[top] + 1, sta[ ++ top] = i;
	}
}
inline void init_suf () {
	sta[top = 0] = n + 1;
	rep (i, n, 1) {
		while (top && h[sta[top]] >= h[i]) -- top;
		R[i] = sta[top] - 1, sta[ ++ top] = i;
	}
}

inline int find (int pos) {
	int l = 1, r = top, res = -1, mid;
	while (l <= r) mid = (l + r >> 1), pos <= sta[mid] ? res = mid, r = mid - 1 : l = mid + 1;
	return sta[res];
}

int main () {
	freopen ("sitcom.in", "r", stdin);
	freopen ("sitcom.out", "w", stdout);

	IN (n);
	lep (i, 1, n) IN (h[i]);
	init_pre ();
	init_suf ();
	lep (i, 1, n) G[i] = (Edge) { head[R[i]], L[i], i }, head[R[i]] = i;

	sta[top = 0] = 0;
	lep (r, 1, n) {
		while (top && h[sta[top]] <= h[r]) -- top;
		sta[ ++ top] = r;
		for (int i = head[r]; i; i = G[i].nxt) ans[G[i].val] = find (G[i].to);
	}

	__int128 res = 0, tp;
	lep (i, 1, n) tp = h[i], chkmax (res, tp * (R[i] - L[i] + 1) * h[ans[i]]);
	write (res), puts ("");
	return 0;
}