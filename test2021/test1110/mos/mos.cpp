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

const int mod = 998244353;

inline int mul (int x, int y) { return 1ll * x * y % mod; }
inline void sub (int &x, int y) { x -= y; if (x < 0) x += mod; }
inline void pls (int &x, int y) { x += y; if (x >= mod) x -= mod; }
inline int dec (int x, int y) { x -= y; if (x < 0) x += mod; return x; }
inline int add (int x, int y) { x += y; if (x >= mod) x -= mod; return x; }
inline int modpow (int x, ll y, int res = 1) {
	for (y = (y + mod - 1) % (mod - 1); y; y >>= 1, x = mul (x, x)) if (y & 1) res = mul (x, res);
	return res;
}

char _c; bool _f; template <class T> inline void IN (T & x) {
	x = 0, _f = 0; while (_c = getchar (), ! isdigit (_c)) if (_c == '-') _f = 1;
	while (isdigit (_c)) x = x * 10 + _c - '0', _c = getchar (); if (_f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 1e5 + 5;
const int M = 2e7 + 5;

int n, m, a[N], inv[M], fac[M];

int main () {
	freopen ("mos.in", "r", stdin);
	freopen ("mos.out", "w", stdout);

	IN (n), IN (m);
	lep (i, 1, n) IN (a[i]);
	int res = 0, sum = 0, lim = n * m + 1;

	fac[0] = 1;
	lep (i, 1, lim) fac[i] = mul (fac[i - 1], i);
	inv[lim] = modpow (fac[lim], -1);
	rep (i, lim, 1) inv[i - 1] = mul (inv[i], i);

	Lep (i, 1, lim) pls (res, mul (i, mul (fac[i], inv[i + 1])));
	lep (i, 1, n) pls (sum, mul (m, a[i]));
	printf ("%d\n", mul (mul (sum, res), modpow (lim - 1, -1)));
	return 0;
}