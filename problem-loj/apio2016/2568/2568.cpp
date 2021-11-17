#pragma GCC optimize ("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
#define debug(...) fprintf (stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

#define pc putchar
#define gc getchar

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

char __c; bool __f; template <class T> inline void IN (T & x) {
	__f = 0, x = 0; while (__c = gc (), ! isdigit (__c)) if (__c == '-') __f = 1;
	while (isdigit (__c)) x = x * 10 + __c - '0', __c = gc (); if (__f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 3e5 + 5;
const int M = N << 1;

int n, m, son[N];
struct Node {
	int fa, val, u;
	Node (int _fa = 0, int _val = 0, int _u = 0) { fa = _fa, val = _val, u = _u; }
}; vector <Node> sta;

// {{{ heap

ll pos[M];
int tot, rt[N], lc[M], rc[M], len[M];

inline int newnode (ll x) {
	return ++ tot, pos[tot] = x, tot;
}
int merge (int x, int y) {
	if (! x || ! y) return x | y;
	if (pos[x] < pos[y]) swap (x, y);
	lc[x] = merge (lc[x], y);
	if (len[lc[x]] > len[rc[x]]) swap (lc[x], rc[x]);
	return len[x] = len[lc[x]] + 1, x;
}
inline void pop (int &x) { x = merge (lc[x], rc[x]); }

// }}}

signed main () {
	IN (n), IN (m);
	for (int fa, val, i = 2; i <= n + m; ++ i)
		IN (fa), IN (val), sta.ep (fa, val, i), ++ son[fa];
	reverse (sta.begin (), sta.end ());

	for (auto [fa, val, u] : sta) {
		while (son[u] > 1) pop (rt[u]), -- son[u];
		ll R = pos[rt[u]]; pop (rt[u]);
		ll L = pos[rt[u]]; pop (rt[u]);
		rt[u] = merge (rt[u], merge (newnode (L + val), newnode (R + val)));
		rt[fa] = merge (rt[fa], rt[u]);
	}

	ll ans = 0;
	for (auto [fa, val, u] : sta) ans += val;
	while (son[1] > 0) pop (rt[1]), -- son[1];
	while (rt[1]) ans -= pos[rt[1]], pop (rt[1]);
	printf ("%lld\n", ans);
	return 0;
}