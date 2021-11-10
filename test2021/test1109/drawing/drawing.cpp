// qiuly
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

char _c; bool _f; template <class T> inline void IN (T & x) {
	x = 0, _f = 0; while (_c = getchar (), ! isdigit (_c)) if (_c == '-') _f = 1;
	while (isdigit (_c)) x = x * 10 + _c - '0', _c = getchar (); if (_f) x = -x;
}

template <class T> inline void chkmin (T & x, T y) { if (x > y) x = y; }
template <class T> inline void chkmax (T & x, T y) { if (x < y) x = y; }

const int N = 1e6 + 5;

int n, m, q, b[N], sta[2], sum[3], lpt[N], rpt[N];
set <int> S;

struct segment_tree { // {{{ segment tree
	#define mid ((l + r) >> 1)
	#define lc ((x) << 1)
	#define rc ((x) << 1 | 1)

	ll sum[N << 2];
	int cnt[N << 2];

	void Insert (int x, int l, int r, const int &pos) {
		sum[x] += pos, ++ cnt[x];
		if (l != r) pos <= mid ? Insert (lc, l, mid, pos) : Insert (rc, mid + 1, r, pos);
	}
	void Delete (int x, int l, int r, const int &pos) {
		sum[x] -= pos, -- cnt[x];
		if (l != r) pos <= mid ? Delete (lc, l, mid, pos) : Delete (rc, mid + 1, r, pos);
	}
	int Find (int x, int l, int r, int &k) {
		if (l == r) {
			if (l) {
				int now = min (k / l, cnt[x]);
				return k -= now * l, now;
			}
			return cnt[x];
		}
		if (k <= sum[lc]) return Find (lc, l, mid, k);
		return k -= sum[lc], cnt[lc] + Find (rc, mid + 1, r, k);
	}

	#undef mid
	#undef lc
	#undef rc
} s[2]; // }}}

void ins (int l, int r) {
	if (b[l] != b[r]) ++ sum[2];
	else ++ sum[b[l]], s[b[l]].Insert (1, 0, n, r - l - 1);
}
void del (int l, int r) {
	if (b[l] != b[r]) -- sum[2];
	else -- sum[b[l]], s[b[l]].Delete (1, 0, n, r - l - 1);
}

int main () {
	freopen ("drawing.in", "r", stdin);
	freopen ("drawing.out", "w", stdout);

	IN (n), IN (m), IN (q);
	for (int a, i = 1; i <= n; ++ i) IN (a), ++ sta[a & 1];

	memset (b, -1, sizeof b), S.insert (0), S.insert (n + 1);
	for (int p, i = 1; i <= m; ++ i) {
		IN (p), S.insert (p);
		IN (b[p]), b[p] &= 1, -- sta[b[p]];
	}
	for (int x = 0, i = 1; i <= n; ++ i) if (~ b[i]) lpt[i] = x, x = i;
	for (int x = n + 1, i = n; i >= 1; -- i) if (~ b[i]) rpt[i] = x, x = i;

	lep (i, 1, n) if (~ b[i] && lpt[i] != 0) ins (lpt[i], i);

	for (int opt, p; q; -- q) {
		IN (opt), IN (p);

		if (opt == 1) {
			if (lpt[p] != 0) del (lpt[p], p);
			if (rpt[p] != n + 1) del (p, rpt[p]);
			rpt[lpt[p]] = rpt[p], lpt[rpt[p]] = lpt[p];
			if (lpt[p] != 0 && rpt[p] != n + 1) ins (lpt[p], rpt[p]);
			++ sta[b[p]], b[p] = -1, S.erase (p);
		}
		if (opt == 2) {
			IN (b[p]), b[p] &= 1, -- sta[b[p]];
			auto it = S.upper_bound (p); -- it;
			lpt[p] = *it, it = S.lower_bound (p), rpt[p] = *it, S.insert (p);
			if (lpt[p] != 0 && rpt[p] != n + 1) del (lpt[p], rpt[p]);
			rpt[lpt[p]] = lpt[rpt[p]] = p;
			if (lpt[p] != 0) ins (lpt[p], p);
			if (rpt[p] != n + 1) ins (p, rpt[p]);
		}

		if (S.size () == 2) printf ("%d\n", (sta[0] > 0) + (sta[1] > 0) - 1);
		else {
			int ans = sum[2], lst0 = sta[0], lst1 = sta[1];
			ans += 2 * (sum[0] - s[0].Find (1, 0, n, sta[0]));
			ans += 2 * (sum[1] - s[1].Find (1, 0, n, sta[1]));

			auto it = S.begin (); ++ it; int bg = *it; it = S.end (), -- it, -- it; int ed = *it;
			if (sta[b[bg]] >= bg - 1) sta[b[bg]] -= bg - 1; else ++ ans;
			if (sta[b[ed]] >= n - ed) sta[b[ed]] -= n - ed; else ++ ans;
			printf ("%d\n", ans), sta[0] = lst0, sta[1] = lst1;
		}
	}
	return 0;
}