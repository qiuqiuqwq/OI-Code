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

const int mod = 1e9 + 7;

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

const int N = 5e2 + 5;
const int M = 1e5 + 5;

int n, fac[M], inv[M], dp[2][N][N][2];
char str[N];

inline void init (const int L = M - 5) {
	fac[0] = 1;
	lep (i, 1, L) fac[i] = mul (fac[i - 1], i);
	inv[L] = modpow (fac[L], -1);
	rep (i, L, 1) inv[i - 1] = mul (inv[i], i);
}
inline int binom (int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	return mul (fac[n], mul (inv[m], inv[n - m]));
}

int main () {
	freopen ("checkers.in", "r", stdin);
	freopen ("checkers.out", "w", stdout);
	init (), IN (n), scanf ("%s", str + 1);

	int now = 0, lst = 1;
	dp[0][0][0][0] = 1;
	lep (i, 1, n) {
		swap (now, lst), memset (dp[now], 0, sizeof dp[now]);
		Lep (j, 0, i) lep (k, 0, j) {
			if (str[i] != '0') {
				if (dp[lst][j][k][1]) pls (dp[now][j + 1][k - 1][0], dp[lst][j][k][1]);
				if (dp[lst][j][k][0]) pls (dp[now][j + 1][k + 1][1], dp[lst][j][k][0]);
			}
			if (str[i] != '1') {
				pls (dp[now][j][k][0], dp[lst][j][k][0]);
				pls (dp[now][j][k][0], dp[lst][j][k][1]);
			}
		}
	}

	int ans = 0;
	lep (j, 0, n) lep (k, 0, j) {
		int res = add (dp[now][j][k][0], dp[now][j][k][1]);
		if (! res) continue ;
		pls (ans, mul (res, binom (n - j + (j - k) / 2, n - j)));
	}
	printf ("%d\n", ans);
	return 0;
}