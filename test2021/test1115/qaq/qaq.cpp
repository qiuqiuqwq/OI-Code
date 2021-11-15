// #pragma GCC optimize ("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
#define debug(...) fprintf (stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

#define fi first
#define se second
#define mkp make_pair
typedef pair <int, int> pii;

#define rez resize
#define pb push_back
#define ep emplace_back
typedef vector <int> poly;

#define lep(i, l, r) for (int i = (l), i##_end = (r); i <= i##_end; ++ i)
#define rep(i, r, l) for (int i = (r), i##_end = (l); i >= i##_end; -- i)
#define Lep(i, l, r) for (int i = (l), i##_end = (r); i < i##_end; ++ i)
#define Rep(i, r, l) for (int i = (r), i##_end = (l); i > i##_end; -- i)

const int mod = 1e9 + 7;

inline int mul (int x, int y) { return 1ll * x * y % mod; }
inline int add (int x, int y) { return (x + y) % mod; }
inline int dec (int x, int y) { return (x - y + mod) % mod; }
inline void pls (int &x, int y) { (x += y) %= mod; }
inline void sub (int &x, int y) { (x += mod - y) %= mod; }

inline int modpow (int x, ll y, int res = 1) {
	for (y = (y + mod - 1) % (mod - 1); y; y >>= 1, x = mul (x, x)) if (y & 1) res = mul (res, x);
	return res;
}

char __c; bool __f; template <class T> inline void IN (T & x) {
	__f = 0, x = 0; while (__c = getchar (), ! isdigit (__c)) if (__c == '-') __f = 1;
	while (isdigit (__c)) x = x * 10 + __c - '0', __c = getchar (); if (__f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 1e6 + 5;
const int M = 1e7 + 5;

int n, m, len[N], fac[M], inv[M], pwm0[M], pwm1[M];

inline void init (const int L = M - 5) {
	fac[0] = 1;
	lep (i, 1, L) fac[i] = mul (fac[i - 1], i);
	inv[L] = modpow (fac[L], -1);
	rep (i, L, 1) inv[i - 1] = mul (inv[i], i);
	pwm0[0] = pwm1[0] = 1;
	lep (i, 1, L) pwm0[i] = mul (pwm0[i - 1], m), pwm1[i] = mul (pwm1[i - 1], m - 1);
}
inline int binom (int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	return mul (fac[n], mul (inv[m], inv[n - m]));
}

signed main () {
	freopen ("qaq.in", "r", stdin);
	freopen ("qaq.out", "w", stdout);

	IN (n), IN (m), init ();
	lep (i, 1, n) IN (len[i]);
	
	int ans = pwm0[len[n]];
	rep (i, n - 1, 1) {
		int res = 0, lst = len[i + 1], now = len[i];
		lep (j, lst, now) pls (res, mul (binom (j - 1, lst - 1), mul (pwm1[j - lst], pwm0[now - j])));
		ans = mul (ans, res);
	}
	printf ("%d\n", ans);
	return 0;
}
