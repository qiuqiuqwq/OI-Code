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

const int mod = 19260817;

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

int n, lima, a[N], fac[M], inv[M];

inline void init (const int L = M - 5) {
	fac[0] = 1;
	lep (i, 1, L) fac[i] = mul (fac[i - 1], i);
	inv[L] = modpow (fac[L], -1);
	rep (i, L, 1) inv[i - 1] = mul (inv[i], i);
}

signed main () {
	freopen ("quq.in", "r", stdin);
	freopen ("quq.out", "w", stdout);

	init (), IN (n);
	lep (i, 1, n) IN (a[i]);
	sort (a + 1, a + 1 + n), n = unique (a + 1, a + 1 + n) - a - 1, lima = a[n];
	
	int ans = 0;
	lep (i, 1, n) lep (j, a[i - 1] + 1, a[i]) pls (ans, mul (a[i], mul (inv[lima - j + 1], fac[lima - j])));
	printf ("%d\n", ans);
	return 0;
}
