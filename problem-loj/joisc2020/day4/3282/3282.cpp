#pragma GCC optimize ("Ofast,no-stack-protector,unroll-loops,fast-math")
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

const int N = 1e5 + 5;
const int INF = 2e9 + 7;
typedef pair <ll, int> Node;

ll dis[N];
int m, n, rk[2][N];
struct Plan { int t, l, r, c, id; } a[N];
priority_queue <Node, vector <Node>, greater <Node> > q;

// {{{ segment tree

#define mid ((l + r) >> 1)
#define lc ((x) << 1)
#define rc ((x) << 1 | 1)

struct segment_tree {
	int pos[N];
	pii nod[N << 2];

	void build (int x, int l, int r, bool typ) {
		if (l == r) {
			nod[x] = mkp ((typ ? a[l].t : - a[l].t), a[l].id);
			pos[l] = typ ? a[l].l - a[l].t : a[l].l + a[l].t;
			return ;
		}
		build (lc, l, mid, typ), build (rc, mid + 1, r, typ);
		nod[x] = min (nod[lc], nod[rc]);
	}
	void modify (int x, int l, int r, int pos) {
		if (l == r) return nod[x] = mkp (INF, INF), void ();
		(pos <= mid ? modify (lc, l, mid, pos) : modify (rc, mid + 1, r, pos));
		nod[x] = min (nod[lc], nod[rc]);
	}
	pii query (int x, int l, int r, int val) {
		if (pos[l] > val) return mkp (INF, INF);
		if (pos[r] <= val) return nod[x];
		if (pos[mid] > val) return query (lc, l, mid, val);
		return min (nod[lc], query (rc, mid + 1, r, val));
	}
} sgt[2];

#undef mid
#undef lc
#undef rc

// }}}

signed main () {
	IN (m), IN (n);
	lep (i, 1, n) IN (a[i].t), IN (a[i].l), IN (a[i].r), IN (a[i].c), a[i].id = i;

	sort (a + 1, a + 1 + n, [](Plan x, Plan y) { return x.l + x.t < y.l + y.t; });
	lep (i, 1, n) rk[0][a[i].id] = i;
	sgt[0].build (1, 1, n, 0);
	sort (a + 1, a + 1 + n, [](Plan x, Plan y) { return x.l - x.t < y.l - y.t; });
	lep (i, 1, n) rk[1][a[i].id] = i;
	sgt[1].build (1, 1, n, 1);
	sort (a + 1, a + 1 + n, [](Plan x, Plan y) { return x.id < y.id; });

	memset (dis, 0x3f, sizeof dis);
	lep (i, 1, n) if (a[i].l == 1) {
		dis[i] = a[i].c, q.push (mkp (dis[i], i));
		lep (o, 0, 1) sgt[o].modify (1, 1, n, rk[o][i]);
	}

	while (! q.empty ()) {
		int v, u = q.top ().se; q.pop ();

		while ("Qiuls AK IOI") {
			pii now = sgt[0].query (1, 1, n, a[u].r + a[u].t + 1);
			if (v = now.se, - now.fi > a[u].t) {
				dis[v] = dis[u] + a[v].c, q.push (mkp (dis[v], v));
				lep (o, 0, 1) sgt[o].modify (1, 1, n, rk[o][v]);
			} else break ;
		}
		while ("Qiuls AK IOI") {
			pii now = sgt[1].query (1, 1, n, a[u].r - a[u].t + 1);
			if (v = now.se, now.fi <= a[u].t) {
				dis[v] = dis[u] + a[v].c, q.push (mkp (dis[v], v));
				lep (o, 0, 1) sgt[o].modify (1, 1, n, rk[o][v]);
			} else break ;
		}
	}

	ll ans = 4557430888798830399ll;
	lep (i, 1, n) if (a[i].r == m) chkmin (ans, dis[i]);
	printf ("%lld\n", ans == 4557430888798830399ll ? -1 : ans);
	return 0;
}