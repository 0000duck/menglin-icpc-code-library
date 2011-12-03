//2-SAT problem

//Written by Fuch

#include <cstdio>

#include <cstdlib>

#include <cstring>

using namespace std;

const int maxn = 1100, maxm = maxn * maxn * 2;

int n, an, bn;

int a1[maxn], a2[maxn], b1[maxn], b2[maxn], d1[maxn], d2[maxn], x[maxn],
		y[maxn];

int sx1, sx2, sy1, sy2, m1, m2, dd;

struct edge {
	int v, next;
};

edge e[maxm];

int g[maxn], f[maxn];

void StrongDFS(int a, int g[], edge e[], int u[], int &b)

{
	u[a] = -1;
	for (int i = g[a]; i != -1; i = e[i].next)
		if (!u[e[i].v])
			StrongDFS(e[i].v, g, e, u, b);
	u[a] = ++b;
}

void StrongBack(int a, int f[], edge e[], int *r, int b)

{
	r[a] = b;
	for (int i = f[a]; i != -1; i = e[i].next)
		if (r[e[i].v] == -1)
			StrongBack(e[i].v, f, e, r, b);
}

//g[]=Origin graph, f[]=Reversed g[]

//Return the number of components. r[] stores IDs for each vertex.

int StrongCC(int g[], int f[], edge e[], int n, int r[])

{
	int u[maxn] = { }, v[maxn], b = 0, m = 0;
	memset(r, 255, sizeof(*r) * n);
	for (int i = 0; i < n; i++)
		if (!u[i])
			StrongDFS(i, g, e, u, b);
	for (int i = 0; i < n; i++)
		v[u[i] - 1] = i;
	for (int i = n - 1; i >= 0; i--)
		if (r[v[i]] == -1)
			StrongBack(v[i], f, e, r, m++);
	return m;
}

void init()

{
	scanf("%d%d%d", &n, &an, &bn);
	scanf("%d%d%d%d", &sx1, &sy1, &sx2, &sy2);
	dd = abs(sx1 - sx2) + abs(sy1 - sy2);
	m1 = 0;
	m2 = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &x[i], &y[i]);
		d1[i] = abs(sx1 - x[i]) + abs(sy1 - y[i]);
		d2[i] = abs(sx2 - x[i]) + abs(sy2 - y[i]);
		if (m1 < d1[i])
			m1 = d1[i];
		if (m2 < d2[i])
			m2 = d2[i];
	}
	for (int i = 0; i < an; i++) {
		scanf("%d%d", &a1[i], &a2[i]);
		a1[i]--;
		a2[i]--;
	}
	for (int i = 0; i < bn; i++) {
		scanf("%d%d", &b1[i], &b2[i]);
		b1[i]--;
		b2[i]--;
	}
}

#define add(_u,_v)\
 

{\

	e[m].v = _v;\

	e[m].next = g[_u];\

	g[_u] = m++;\

	e[m].v = _u;\

	e[m].next = f[_v];\

	f[_v] = m++;\

}

bool check(int l)

{
	int m = 0;
	memset(g, 255, sizeof(g));
	memset(f, 255, sizeof(f));
	for (int i = 0; i < an; i++) {
		add ( a1[i], a2[i] + n ); add ( a1[i] + n, a2[i] ); add ( a2[i], a1[i] + n ); add ( a2[i] + n, a1[i] );
	}
	for (int i = 0; i < bn; i++) {
		add ( b1[i], b2[i] ); add ( b1[i] + n, b2[i] + n ); add ( b2[i], b1[i] ); add ( b2[i] + n, b1[i] + n );
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (d1[i] + d1[j] > l) {
				add ( i, j + n ); add ( j, i + n );
			}
			if (d2[i] + d2[j] > l) {
				add ( i + n, j ); add ( j + n, i );
			}
			if (d1[i] + d2[j] + dd > l) {
				add ( i, j ); add ( j + n, i + n );
			}
			if (d2[i] + d1[j] + dd > l) {
				add ( i + n, j + n ); add ( j, i );
			}
		}
	}
	static int r[maxn];
	bool ret = true;
	StrongCC(g, f, e, n * 2, r);
	for (int i = 0; i < n; i++) {
		if (r[i] == r[i + n])
			ret = false;
	}
	return ret;
}

//Using Strongly Connected Component

//Vertex: 0..n-1=true, n..2n-1=false

bool sat(int g[], int f[], edge e[], int n, bool s[])

{
	static int r[maxn], q[maxn], c[maxn], l[maxn], a[maxn];
	int h = 0, d = 0, m = StrongCC(g, f, e, n * 2, r);
	for (int i = 0; i < n; i++)
		if (r[i] == r[i + n])
			return false;
	memset(c, 0, sizeof(*c) * m);
	memset(a, 255, sizeof(*a) * m);
	for (int i = 0; i < n * 2; i++) {
		l[i] = a[r[i]];
		a[r[i]] = i;
		for (int j = g[i]; j != -1; j = e[j].next)
			if (r[i] != r[e[j].v])
				c[r[e[j].v]]++;
	}
	for (int i = 0; i < m; i++)
		if (c[i] == 0)
			q[d++] = i;
	while (h < d) {
		int t = q[h++];
		for (int i = a[t]; i != -1; i = l[i])
			for (int j = g[i]; j != -1; j = e[j].next) {
				int v = r[e[j].v];
				if (t == v)
					continue;
				if (--c[v] == 0)
					q[d++] = v;
			}
	}
	static char u[maxn];
	memset(u, 255, sizeof(u));
	for (int k = m - 1; k >= 0; k--) {
		int t = q[k];
		if (u[t] != -1)
			continue;
		u[t] = 1;
		for (int i = a[t]; i != -1 && u[t]; i = l[i])
			for (int j = g[i]; j != -1; j = e[j].next)
				if (u[r[e[j].v]] == 0) {
					u[t] = 0;
					break;
				}
		for (int i = a[t]; i != -1; i = l[i])
			if (i < n)
				u[r[i + n]] = 1 - u[r[i]];
			else
				u[r[i - n]] = 1 - u[r[i]];
	}
	for (int i = 0; i < n; i++)
		s[i] = u[r[i]] ? true : false;
	return true;
}

int solve()

{
	int a = 0, b = m1 + m2 + dd;
	while (a <= b) {
		int c = (a + b) >> 1;
		if (check(c))
			b = c - 1;
		else
			a = c + 1;
	}
	if (check(a))
		return a;
	else
		return -1;
}

int main()

{
	init();
	printf("%d\n", solve());
	return 0;
}

