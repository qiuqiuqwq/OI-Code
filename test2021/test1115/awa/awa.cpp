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

char __c; bool __f; template <class T> inline void IN (T & x) {
	__f = 0, x = 0; while (__c = getchar (), ! isdigit (__c)) if (__c == '-') __f = 1;
	while (isdigit (__c)) x = x * 10 + __c - '0', __c = getchar (); if (__f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 2e5 + 5;
const int LogN = 19;

int n, m, n2, col[N], val[N];

// {{{ tree

int tim, dep[N], dfn[N], jump[N][LogN];
vector <int> to[N], csta[N];

void dfs1 (int u, int pre) {
	dep[u] = dep[pre] + 1, dfn[u] = ++ tim, jump[u][0] = pre;
	lep (i, 1, 18) jump[u][i] = jump[jump[u][i - 1]][i - 1];
	for (int v : to[u]) if (v != pre) dfs1 (v, u);
}
inline int lca (int u, int v) {
	if (u == v) return u;
	if (dep[u] < dep[v]) swap (u, v);
	rep (i, 18, 0) if (dep[jump[u][i]] >= dep[v]) u = jump[u][i];
	if (u == v) return u;
	rep (i, 18, 0) if (jump[u][i] != jump[v][i]) u = jump[u][i], v = jump[v][i];
	return jump[u][0];
}

// }}}

// {{{ virtree

int nowcol, vtop, god[N], vsta[N];
vector <int> vto[N];

void dfs3 (int u) {
	god[u] = (col[u] == nowcol) ? dep[u] : n2 + 1;
	for (int v : vto[u]) dfs3 (v), chkmin (god[u], god[v]);
}
void dfs2 (int u, int lst) {
	if (col[u] == nowcol) chkmax (val[u], lst), chkmax (lst, dep[u]);
	if (! vto[u].size ()) return ;
	sort (vto[u].begin (), vto[u].end (), [&](int x, int y) { return god[x] < god[y]; });

	const int lim = vto[u].size (), buf = max (1, (dep[u] << 1) - god[vto[u][0]]);
	dfs2 (vto[u][0], lst);
	Lep (i, 1, lim) dfs2 (vto[u][i], max (buf, lst));
	vto[u].clear ();
}

inline void build (vector <int> &p) {
	sort (p.begin (), p.end (), [&](int x, int y) { return dfn[x] < dfn[y]; });
	vsta[vtop = 1] = n2;

	for (int u : p) if (u != n2) {
		int _lca = lca (u, vsta[vtop]);
		while (vtop > 1 && dep[vsta[vtop - 1]] >= dep[_lca]) vto[vsta[vtop - 1]].pb (vsta[vtop]), -- vtop;
		if (_lca != vsta[vtop]) vto[_lca].pb (vsta[vtop]), vsta[vtop] = _lca;
		vsta[ ++ vtop] = u;
	}
	rep (i, vtop, 2) vto[vsta[i - 1]].pb (vsta[i]);
}

// }}}

// {{{ divide

bool vis[N];
int rt, mxp, all, dtop, ans[N], dis[N], siz[N];
vector <pii> qsta[N];
struct Node { int typ, nid, qid, val, pos; } dsta[N << 1];

// {{ tree array

int tr, tc[N];
inline int lowbit (int x) { return x & (- x); }
inline void modify (int x, int y) { while (x <= n2) tc[x] += y, x += lowbit (x); }
inline int query (int x) { tr = 0; while (x) tr += tc[x], x -= lowbit (x); return tr; }

// }}}

inline void insque (int u, const int &typ) {
	if (u > n) return ;
	dsta[ ++ dtop] = (Node) { typ, u, 0, dis[u], val[u] };
	for (pii ele : qsta[u]) {
		int now = ele.fi - dis[u];
		if (now >= 0) dsta[ ++ dtop] = (Node) { 0, u, ele.se, now, dep[u] - ele.fi };
	}
}
inline void calc () {
	sort (dsta + 1, dsta + 1 + dtop, [](Node x, Node y) {
		return x.val == y.val ? x.typ > y.typ : x.val < y.val;
	});
	Node now;
	lep (i, 1, dtop) {
		if (now = dsta[i], now.typ == 0) ans[now.qid] += query (max (0, now.pos));
		else modify (now.pos + 1, now.typ == 1 ? 1 : -1);
	}
	lep (i, 1, dtop) if (now = dsta[i], now.typ) modify (now.pos + 1, now.typ == 1 ? -1 : 1);
}

void getsiz (int u, int pre) {
	siz[u] = 1;
	for (int v : to[u]) if (v != pre && ! vis[v]) getsiz (v, u), siz[u] += siz[v];
}
void getnod (int u, int pre, const int &typ) {
	dis[u] = dis[pre] + 1, insque (u, typ);
	for (int v : to[u]) if (v != pre && ! vis[v]) getnod (v, u, typ);
}
void findrt (int u, int pre) {
	int now = all - siz[u];
	for (int v : to[u]) if (v != pre && ! vis[v]) findrt (v, u), chkmax (now, siz[v]);
	if (now < mxp) mxp = now, rt = u;
}

void solve (int u) {
	vis[u] = true, dis[u] = 0;

	dtop = 0, insque (u, 1);
	for (int v : to[u]) if (! vis[v]) getnod (v, u, 1);
	calc ();
	for (int v : to[u]) if (! vis[v]) dtop = 0, getnod (v, u, 2), calc ();

	for (int v : to[u]) if (! vis[v])
		getsiz (v, 0), all = siz[v], mxp = all + 1, findrt (v, 0), solve (rt);
}

// }}}

inline void clear () {
	tim = 0, n2 = n << 1;
	lep (i, 1, n) qsta[i].clear ();
	lep (i, 0, n) csta[i].clear ();
	lep (i, 1, n2) to[i].clear ();
	memset (col, 0, sizeof col);
	memset (val, 0, sizeof val);
	memset (vis, 0, sizeof vis);
	memset (ans, 0, sizeof ans);
}
inline void solve () {
	IN (n), clear ();
	lep (i, 1, n) IN (col[i]);
	for (int u, v, i = 1; i < n; ++ i) IN (u), IN (v), to[u].pb (v), to[v].pb (u);
	lep (i, n + 1, n2) to[i].pb (i - 1), to[i - 1].pb (i);

	dfs1 (n2, 0);
	lep (i, 1, n) csta[col[i]].pb (i);
	lep (i, 1, n) if (csta[i].size ()) nowcol = i, build (csta[i]), dfs3 (n2), dfs2 (n2, 0);

	IN (m);
	for (int x, d, i = 1; i <= m; ++ i) IN (x), IN (d), qsta[x].pb (mkp (d, i));
	getsiz (n2, 0), all = siz[n2], mxp = all + 1, findrt (n2, 0), solve (rt);
	lep (i, 1, m) printf ("%d\n", ans[i]);
}

signed main () {
	freopen ("awa.in", "r", stdin);
	freopen ("awa.out", "w", stdout);

	int CASEID, T;
	IN (CASEID), IN (T);
	while (T -- ) solve ();
	return 0;
}