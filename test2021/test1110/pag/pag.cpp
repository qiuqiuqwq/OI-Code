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

const int N = 1e6 + 5;

int n, L[N], R[N];
long double f[N];

int main () {
	freopen ("pag.in", "r", stdin);
	freopen ("pag.out", "w", stdout);

	IN (n);
	lep (i, 1, n) IN (L[i]), IN (R[i]);

	f[n] = L[n] + 1.0 * (R[n] - L[n]) / 2;
	rep (i, n - 1, 1) {
		if (f[i + 1] <= L[i]) { f[i] = L[i] + 1.0 * (R[i] - L[i]) / 2; continue ; }
		if (f[i + 1] >= R[i]) { f[i] = f[i + 1]; continue ; }

		long double p = (R[i] - f[i + 1]) / (R[i] - L[i]);
		f[i] = f[i + 1] + p * (R[i] - f[i + 1]) / 2;
	}
	printf ("%.5Lf\n", f[1]);
	return 0;
}