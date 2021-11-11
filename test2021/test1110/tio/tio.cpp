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

int mod;

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

const int N = 1e7 + 5;

int n, rt, top, a[N], sta[N], lc[N], rc[N];
int lm[N], rm[N], mu[N], ans;

void calc (int u) {
	if (! lc[u] && ! rc[u]) {
		mu[u] = a[u], lm[u] = rm[u] = add (a[u], 1);
		return pls (ans, mul (a[u], a[u])), void ();
	}
	if (! lc[u]) {
		calc (rc[u]);
		mu[u] = mul (mu[rc[u]], a[u]);
		lm[u] = add (1, mul (lm[rc[u]], a[u]));
		rm[u] = add (rm[rc[u]], mul (mu[rc[u]], a[u]));
		return pls (ans, mul (lm[rc[u]], mul (a[u], a[u])));
	}
	if (! rc[u]) {
		calc (lc[u]);
		mu[u] = mul (mu[lc[u]], a[u]);
		rm[u] = add (1, mul (rm[lc[u]], a[u]));
		lm[u] = add (lm[lc[u]], mul (mu[lc[u]], a[u]));
		return pls (ans, mul (rm[lc[u]], mul (a[u], a[u])));
	}
	calc (lc[u]), calc (rc[u]);
	mu[u] = mul (mul (mu[lc[u]], mu[rc[u]]), a[u]);
	lm[u] = add (lm[lc[u]], mul (mu[lc[u]], mul (a[u], lm[rc[u]])));
	rm[u] = add (rm[rc[u]], mul (mu[rc[u]], mul (a[u], rm[lc[u]])));
	return pls (ans, mul (mul (rm[lc[u]], lm[rc[u]]), mul (a[u], a[u])));
}

inline void build () {
	lep (i, 1, n) {
		int lst = 0;
		while (top && a[sta[top]] <= a[i]) lst = sta[top], -- top;
		if (! top) lc[i] = lst;
		else rc[sta[top]] = i, lc[i] = lst;
		sta[ ++ top] = i;
	}
	calc (sta[1]), printf ("%d\n", ans);
}

namespace PrePare {
namespace GenHelper {
	unsigned z1, z2, z3, z4, b;

	unsigned rand_() {
		b = ((z1 << 6) ^ z1) >> 13;
		z1 = ((z1 & 4294967294U) << 18) ^ b;
		b = ((z2 << 2) ^ z2) >> 27;
		z2 = ((z2 & 4294967288U) << 2) ^ b;
		b = ((z3 << 13) ^ z3) >> 21;
		z3 = ((z3 & 4294967280U) << 7) ^ b;
		b = ((z4 << 3) ^ z4) >> 12;
		z4 = ((z4 & 4294967168U) << 13) ^ b;
		return (z1 ^ z2 ^ z3 ^ z4);
	}
}
void get (int n, unsigned s, int l, int r) {
	using namespace GenHelper;

	z1 = s;
	z2 = unsigned((~s) ^ 0x233333333U);
	z3 = unsigned(s ^ 0x1234598766U);
	z4 = (~s) + 51;

	lep (i, 1, n) {
		int x = rand_() & 32767;
		int y = rand_() & 32767;
		a[i] = l + (x * 32768 + y) % (r - l + 1);
	}
}
inline void prepare () {
	IN (n);
	unsigned s; IN (s);
	int l, r; IN (l), IN (r);
	get (n, s, l, r), IN (mod);
}
}
int main () {
	freopen ("tio.in", "r", stdin);
	freopen ("tio.out", "w", stdout);
	PrePare :: prepare (), build ();
	return 0;
}