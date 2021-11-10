#include "grader.h"
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

const int N = 8e2 + 5;

bool used[N];
int n, p[N], vp[N], mod2[N], res[9][N];
vector <int> vec, plan[9];

inline void _Reply () {
    if (p[1] > n / 2)
        lep (i, 1, n / 2) swap (p[vp[i]], p[vp[n - i + 1]]);
    debug ("Fixed! Now : ["); lep (i, 1, n) debug ("%d, ", p[i]); debug ("]\n");
    
    vec.clear ();
    lep (i, 1, n) vec.pb (p[i]);
    debug ("Replied\n");
    Reply (vec);
}

void Recusion (int depth) {
    pii now = mkp (-1, -1);
    lep (i, 1, n) if (! p[i]) {
        vec.clear ();
        lep (j, 1, n) if (! p[j] && j != i) vec.pb (j);
        bool vec_res = Query (vec);
        if (vec_res) ((~ now.fi) ? now.se = i : now.fi = i), debug ("  -> FindPos[%d]\n", i);
        if (~ now.se) break ;
    }
    if (now.fi == -1 || now.se == -1) _Reply ();

    if (depth == 1) {
        mod2[now.fi] = 1;
        Rep (i, now.fi, 1) mod2[i - 1] = mod2[i] ^ (! res[2][i - 1]);
        Lep (i, now.fi, n) mod2[i + 1] = mod2[i] ^ (! res[2][i]);
        lep (i, 1, n) res[2][i] = mod2[i], debug ("  -> Mod2[%d] : %d\n", i, mod2[i]);
    } else if (mod2[now.fi] != (depth & 1)) swap (now.fi, now.se);

    debug (" -> Find[%d] : [%d, %d]\n", depth, now.fi, now.se);
    p[vp[depth] = now.fi] = depth;
    p[vp[n - depth + 1] = now.se] = n - depth + 1;
    if (depth < 4) Recusion (depth + 1);
}
inline void PrePare () {
    Lep (i, 1, n) {
        vec.clear (), vec.pb (i), vec.pb (i + 1);
        res[2][i] = Query (vec);
    }
    Recusion (1), debug ("ok PrePare\n");
}

void GetPlan (int step, int lim, int sum) {
    if (step == lim) {
        if (sum = (lim - (sum % lim)) % lim, plan[sum].size ()) return ;
        lep (i, 1, 4) if (used[i]) plan[sum].pb (vp[i]);
        rep (i, n, n - 3) if (used[i]) plan[sum].pb (vp[i]);
        return ;
    }
    lep (i, 1, 4) if (! used[i]) used[i] = true, GetPlan (step + 1, lim, sum + i), used[i] = false;
    rep (i, n, n - 3) if (! used[i]) used[i] = true, GetPlan (step + 1, lim, sum + i), used[i] = false;
}
inline bool _Query (int i, int x) {
    plan[x].pb (i);
    debug (" -> Query[%d, %d] : ", i, x);
    for (int ele : plan[x]) debug ("%d, ", ele);
    debug ("\n");
    bool tmp_res = Query (plan[x]);
    return plan[x].pop_back (), tmp_res;
}
inline void GetMod0 (int x) {
    GetPlan (1, x, 0);
    debug ("ok GetPlan[%d] : \n", x);
    Lep (o, 0, x) {
        debug (" -> Plan[%d] : ", o);
        for (int ele : plan[o]) debug ("%d(%d), ", p[ele], ele);
        debug ("\n");
    }
    lep (i, 1, n) if (! p[i]) {
        Lep (o, 0, x) if (_Query (i, o)) { res[x][i] = o, debug ("   -> [%d] is ok\n", o); break ; }
        debug (" -> res[%d, %d] = %d\n", x, i, res[x][i]);
    }
    Lep (o, 0, x) plan[o].clear ();
    debug ("ok GetMod[%d]\n", x);
}
inline void GetMod248 () {
    GetPlan (1, 4, 0);
    debug ("ok GetPlan[%d]\n", 4);
    lep (i, 1, n) if (! p[i])
        Lep (o, 0, 2) if (res[2][i] == o)
            res[4][i] = o + 2 * _Query (i, o + 2);
    Lep (o, 0, 4) plan[o].clear ();
    debug ("ok GetMod[%d]\n", 4);

    GetPlan (1, 8, 0);
    debug ("ok GetPlan[%d]\n", 8);
    lep (i, 1, n) if (! p[i])
        Lep (o, 0, 4) if (res[4][i] == o)
            res[8][i] = o + 4 * _Query (i, o + 4);
    Lep (o, 0, 8) plan[o].clear ();
    debug ("ok GetMod[%d]\n", 8);
}

void Find_Sequence (int tmp_n) {
    n = tmp_n;
    PrePare (), GetMod0 (3), GetMod0 (5), GetMod0 (7), GetMod248 ();

    lep (i, 1, n) if (! p[i]) {
        debug (" -> [%d, %d, %d, %d, %d]\n", res[2][i], res[3][i], res[5][i], res[7][i], res[8][i]);
        lep (j, 1, n) {
            if (res[3][i] != j % 3) continue ;
            if (res[5][i] != j % 5) continue ;
            if (res[7][i] != j % 7) continue ;
            if (res[8][i] != j % 8) continue ;
            p[i] = j, vp[j] = i; break ;
        }
    }
    debug ("ok GetAnswer\n"), _Reply ();
    return ;
}