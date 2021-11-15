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

inline short Query (const vector <int> &A, const vector <int> &B) {
	printf ("? %d\n", (int) A.size ()), fflush (stdout);
	for (int ele : A) printf ("%d ", ele + 1), fflush (stdout); puts (""), fflush (stdout);
	for (int ele : B) printf ("%d ", ele + 1), fflush (stdout); puts (""), fflush (stdout);
	short x; fflush (stdout); return IN (x), x;
}
inline vector <int> Merge (const vector <int> &A, const vector <int> &B) {
	vector <int> C(0);
	for (int ele : A) C.pb (ele);
	for (int ele : B) C.pb (ele);
	return C;
}

int SolvePow3 (int N, vector <int> S, const short &LstResult) {
	if (N == 1) return S[0];
	int PartSize = N / 3;

	vector <int> Tmp0(PartSize), Tmp1(PartSize), Tmp2(PartSize);
	Lep (i, 0, PartSize) Tmp0[i] = S[i], Tmp1[i] = S[PartSize + i], Tmp2[i] = S[(PartSize << 1) + i];
	short Result = Query (Tmp0, Tmp1);

	if (Result == 1) return SolvePow3 (PartSize, Tmp2, LstResult);
	if (Result == LstResult) return SolvePow3 (PartSize, Tmp0, LstResult);
	return SolvePow3 (PartSize, Tmp1, LstResult);
}
int Solve (int N, vector <int> S, vector <int> Known) {
	if (N == 1) return S[0];

	int Now = 1;
	while (Now * 3 < N + 1) Now *= 3;

	vector <int> Tmp0(Now), Tmp1(Now), Tmp2;
	Lep (i, 0, Now) Tmp0[i] = Known[i], Tmp1[i] = S[i];
	short Result = Query (Tmp1, Tmp0);

	if (Result == 1) {
		Tmp2.clear ();
		Lep (i, Now, N) Tmp2.pb (S[i]);
		return Solve (N - Now, Tmp2, Merge (Known, Tmp1));
	}
	return SolvePow3 (Now, Tmp1, Result);
}
int Rescursion (int N, vector <int> S, short LstResult) {
	int PartSize = (N - 1) / 3;
	short Result = -1;
	vector <int> Tmp0 (PartSize), Tmp1 (PartSize), Tmp2;

	if (Result = LstResult, Result == -1) {
		Lep (i, 0, PartSize) Tmp0[i] = S[i], Tmp1[i] = S[PartSize + i];
		Result = Query (Tmp0, Tmp1), LstResult = Result;
	}
	if (Result == 1) {
		Tmp2.clear ();
		Lep (i, PartSize << 1, N) Tmp2.pb (S[i]);
		return Solve (PartSize + 1, Tmp2, Merge (Tmp0, Tmp1));
	}
	if (PartSize == 1) {
		Tmp0.clear (), Tmp0.pb (S[0]);
		Tmp1.clear (), Tmp1.pb (S[2]);
		Result = Query (Tmp0, Tmp1);
		return S[Result == 1];
	}

	int Now = 1;
	while (Now * 3 < PartSize) Now *= 3;
	if (LstResult == 2) Lep (i, 0, PartSize) swap (S[i], S[PartSize + i]);

	Tmp0.clear ();
	Lep (i, 0, Now / 3 * 2) Tmp0.pb (S[i]);
	Lep (i, 0, Now / 3 * 2) Tmp0.pb (S[PartSize + i]);

	Tmp1.clear ();
	Lep (i, 0, Now / 3) Tmp1.pb (S[Now / 3 * 2 + i]);
	Lep (i, 0, Now / 3) Tmp1.pb (S[PartSize + Now / 3 * 2 + i]);
	Lep (i, 0, Now / 3 * 2) Tmp1.pb (S[N - i - 1]);

	Tmp2.clear ();
	Lep (i, 0, PartSize - Now) Tmp2.pb (S[Now + i]);
	Lep (i, 0, PartSize - Now) Tmp2.pb (S[PartSize + Now + i]);
	Lep (i, 0, PartSize - Now + 1) Tmp2.pb (S[(PartSize << 1) + Now + i]);

	Result = Query (Tmp0, Tmp1);
	if (Result == 1) return Rescursion ((int) Tmp2.size (), Tmp2, 0);
	if (Result == 0) {
		Tmp0.clear (), Tmp1.clear (), Tmp2.clear ();
		Lep (i, 0, Now / 3) Tmp0.pb (S[i]);
		Lep (i, 0, Now / 3) Tmp1.pb (S[Now / 3 + i]);
		Lep (i, 0, Now / 3) Tmp2.pb (S[PartSize + Now / 3 * 2 + i]);

		Result = Query (Tmp0, Tmp1);
		if (Result == 1) return SolvePow3 (Now / 3, Tmp2, 2);
		if (Result == 0) return SolvePow3 (Now / 3, Tmp0, 0);
		if (Result == 2) return SolvePow3 (Now / 3, Tmp1, 0);
	} else {
		Tmp0.clear (), Tmp1.clear (), Tmp2.clear ();
		Lep (i, 0, Now / 3) Tmp0.pb (S[PartSize + i]);
		Lep (i, 0, Now / 3) Tmp1.pb (S[PartSize + Now / 3 + i]);
		Lep (i, 0, Now / 3) Tmp2.pb (S[Now / 3 * 2 + i]);

		Result = Query (Tmp0, Tmp1);
		if (Result == 1) return SolvePow3 (Now / 3, Tmp2, 0);
		if (Result == 0) return SolvePow3 (Now / 3, Tmp1, 2);
		if (Result == 2) return SolvePow3 (Now / 3, Tmp0, 2);
	}
}

int n, lim;
vector <int> S;

int main () {
	puts ("Qiuls AK IOI!"), fflush (stdout);
	IN (n), IN (lim);
	Lep (i, 0, n) S.pb (i);
	printf ("! %d\n", Rescursion (n, S, -1) + 1), fflush (stdout);
	return 0;
}