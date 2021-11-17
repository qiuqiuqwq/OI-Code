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

const int N = 3e3 + 5;

ll dis[N];
bool vis[N];
int n, m, k, sta[N];
vector <pii> to[N];
priority_queue <pair <ll, int>, vector <pair <ll, int> >, greater <pair <ll, int> > > q;

inline ll dijkstra (const int &exw) {
	memset (dis, 0x3f, sizeof dis), memset (vis, 0, sizeof vis);
	dis[1] = 0, q.push (mkp (dis[1], 1));

	while (! q.empty ()) {
		int u = q.top ().se; q.pop ();
		if (vis[u]) continue ; vis[u] = true;
		for (auto now : to[u]) {
			int v = now.fi, w = (now.se >= exw) ? now.se - exw : 0;
			if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, q.push (mkp (dis[v], v));
		}
	}
	return dis[n] + 1ll * k * exw;
}

int main () {
	IN (n), IN (m), IN (k);
	for (int u, v, w, i = 1; i <= m; ++ i) {
		IN (u), IN (v), IN (w), sta[i] = w;
		to[u].pb (mkp (v, w));
		to[v].pb (mkp (u, w));
	}

	ll ans = dijkstra (0);
	lep (i, 1, m) chkmin (ans, dijkstra (sta[i]));
	printf ("%lld\n", ans);
	return 0;
}
