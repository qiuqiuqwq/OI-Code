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

const int mod = 998244353;

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

int n, a[N], f[N];

signed main () {
	freopen ("qwq.in", "r", stdin);
	freopen ("qwq.out", "w", stdout);

	IN (n);
	lep (i, 1, n) IN (a[i]), f[i] = a[i];

	int tag = 0, inv = modpow (n - 1, -1);
	lep (i, 1, n) pls (tag, mul (add (f[i], tag), inv)), f[i] = mod - tag;
	lep (i, 1, n) printf ("%d ", add (f[i], tag));
	puts ("");
	return 0;
}
