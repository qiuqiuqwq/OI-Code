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

const int NQ = 1e7 + 5;
typedef __int128 i128;
void write (i128 x) {
	if (x < 0) putchar ('-'), x = -x;
	if (x > 9) write (x / 10);
	putchar ((x % 10) + '0');
}

ll n;
int cnt, pri[NQ], mui[NQ];
bitset <NQ> vis;
i128 sum[NQ];

inline void sieve (const int L = NQ - 5) {
	mui[1] = 1;
	lep (i, 2, L) {
		if (! vis[i]) pri[ ++ cnt] = i, mui[i] = -1;
		for (int j = 1; j <= cnt && i * pri[j] <= L; ++ j) {
			vis[i * pri[j]] = true;
			if (! (i % pri[j])) { mui[i * pri[j]] = 0; break ; }
			mui[i * pri[j]] = - mui[i];
		}
	}
	lep (i, 1, L) sum[i] = sum[i - 1] + 1ll * i * i * mui[i];
}

inline i128 calc (i128 n) { return n * (n + 1) / 2; }
inline void solve () {
	IN (n);
	int sqrtn = sqrt (n);
	i128 ans = 0;

	for (int l = 1, r; l <= sqrtn; l = r + 1) {
		r = sqrt (n / (n / (1ll * l * l)));
		ans += (sum[r] - sum[l - 1]) * calc (n / (1ll * l * l));
	}
	write (ans), puts ("");
}

int main () {
	freopen ("kfc.in", "r", stdin);
	freopen ("kfc.out", "w", stdout);

	sieve ();
	int T; IN (T); while (T -- ) solve ();
	return 0;
}