#pragma GCC optimize ("Ofast,no-stack-protector,unroll-loops,fast-math")
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
	for (; y; y >>= 1, x = mul (x, x)) if (y & 1) res = mul (x, res);
	return res;
}

char _c; bool _f; template <class T> inline void IN (T & x) {
	x = 0, _f = 0; while (_c = getchar (), ! isdigit (_c)) if (_c == '-') _f = 1;
	while (isdigit (_c)) x = x * 10 + _c - '0', _c = getchar (); if (_f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

int main () {
    
	return 0;
}