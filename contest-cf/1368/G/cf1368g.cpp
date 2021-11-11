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

const int N = 2e5 + 5;

int n, m, cnt, lim, tim, du[N], dfn[N], siz[N];
struct Node { int tim, opt, L, R; } q[N << 1];
char str[N], mp[N];
vector <int> to[N];

// {{{ segment tree

#define mid ((l + r) >> 1)
#define lc ((x) << 1)
#define rc ((x) << 1 | 1)

int mi[N << 2], tot[N << 2], tag[N << 2];

inline void update (int x, int y) { mi[x] += y, tag[x] += y; }
inline void pushdown (int x) { if (tag[x]) update (lc, tag[x]), update (rc, tag[x]), tag[x] = 0; }
inline void pushup (int x) {
	mi[x] = min (mi[lc], mi[rc]), tot[x] = 0;
	if (mi[lc] == mi[x]) tot[x] += tot[lc];
	if (mi[rc] == mi[x]) tot[x] += tot[rc];
}

void build (int x, int l, int r) {
	mi[x] = 0, tag[x] = 0, tot[x] = r - l + 1;
	if (l != r) build (lc, l, mid), build (rc, mid + 1, r);
}
void modify (int x, int l, int r, int L, int R, int opt) {
	if (L <= l && r <= R) return update (x, opt), void ();
	pushdown (x);
	if (L <= mid) modify (lc, l, mid, L, R, opt);
	if (R > mid) modify (rc, mid + 1, r, L, R, opt);
	pushup (x);
}
int query () { return mi[1] == 0 ? lim - tot[1] : lim; }

#undef mid
#undef lc
#undef rc

// }}}

void dfs (int u) {
	dfn[u] = ++ tim, siz[u] = 1;
	for (int v : to[u]) dfs (v), siz[u] += siz[v];
}

int id (int x, int y) { return (x - 1) * m + y; }
int main () {
	IN (n), IN (m), lim = n * m;
	lep (i, 1, n) {
		scanf ("%s", str + 1);
		lep (j, 1, m) {
			if (str[j] == 'L' && j + 2 <= m) to[id (i, j + 2)].pb (id (i, j)), ++ du[id (i, j)];
			if (str[j] == 'R' && j - 2 >= 1) to[id (i, j - 2)].pb (id (i, j)), ++ du[id (i, j)];
			if (str[j] == 'U' && i + 2 <= n) to[id (i + 2, j)].pb (id (i, j)), ++ du[id (i, j)];
			if (str[j] == 'D' && i - 2 >= 1) to[id (i - 2, j)].pb (id (i, j)), ++ du[id (i, j)];
			mp[id (i, j)] = str[j];
		}
	}
	lep (i, 1, lim) if (! du[i]) dfs (i);

	lep (i, 1, n) lep (j, 1, m) {
		if (mp[id (i, j)] == 'L') {
			int L1 = dfn[id (i, j)];
			int L2 = dfn[id (i, j + 1)];
			int R1 = L1 + siz[id (i, j)] - 1;
			int R2 = L2 + siz[id (i, j + 1)] - 1;

			q[ ++ cnt] = (Node) { L1, 1, L2, R2 };
			q[ ++ cnt] = (Node) { R1 + 1, -1, L2, R2 };
			q[ ++ cnt] = (Node) { L2, 1, L1, R1 };
			q[ ++ cnt] = (Node) { R2 + 1, -1, L1, R1 };
		}
		if (mp[id (i, j)] == 'U') {
			int L1 = dfn[id (i, j)];
			int L2 = dfn[id (i + 1, j)];
			int R1 = L1 + siz[id (i, j)] - 1;
			int R2 = L2 + siz[id (i + 1, j)] - 1;

			q[ ++ cnt] = (Node) { L1, 1, L2, R2 };
			q[ ++ cnt] = (Node) { R1 + 1, -1, L2, R2 };
			q[ ++ cnt] = (Node) { L2, 1, L1, R1 };
			q[ ++ cnt] = (Node) { R2 + 1, -1, L1, R1 };
		}
	}
	sort (q + 1, q + 1 + cnt, [](Node x, Node y) { return x.tim < y.tim; });
	build (1, 1, lim);

	ll ans = 0;
	for (int l = 1, r = 0; l <= cnt; l = r + 1) {
		while (r < cnt && q[r + 1].tim == q[l].tim) ++ r;
		lep (i, l, r) modify (1, 1, lim, q[i].L, q[i].R, q[i].opt);
		ans += 1ll * ((r == cnt ? lim + 1 : q[r + 1].tim) - q[r].tim) * query ();
	}
	printf ("%lld\n", ans >> 1ll);
	return 0;
}