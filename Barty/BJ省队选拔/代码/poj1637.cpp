#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
using namespace std;
typedef struct
{
    int v, next, val;
}edge;
const int MAXN = 1024;
const int MAXM = 4096;
edge e[MAXM];
int p[MAXN], eid;
inline void sapinit()
{
    memset(p, -1, sizeof(p));
    eid = 0;
}
inline void insert1(int from, int to, int val)
{
    e[eid].v = to;
    e[eid].val = val;
    e[eid].next = p[from];
    p[from] = eid++;
    swap(from, to);
    e[eid].v = to;
    e[eid].val = 0;
    e[eid].next = p[from];
    p[from] = eid++;
}
int n, m;
int h[MAXN], gap[MAXN];
int source, sink;
inline int dfs(int pos, int cost)
{
    if (pos == sink)
    {
        return cost;
    }
    int j, minh = n - 1, lv = cost, d;
    for (j = p[pos]; j != -1; j = e[j].next)
    {
        int v = e[j].v, val = e[j].val;
        if (val > 0)
        {
            if (h[v] + 1 == h[pos])
            {
                if (lv < e[j].val) d = lv;
                else d = e[j].val;
                d = dfs(v, d);
                e[j].val -= d;
                e[j ^ 1].val += d;
                lv -= d;
                if (h[source] >= n) return cost - lv;
                if (lv == 0) break;
            }
            if (h[v] < minh) minh = h[v];
        }
    }
    if (lv == cost)
    {
        --gap[h[pos]];
        if (gap[h[pos]] == 0) h[source] = n;
        h[pos] = minh + 1;
        ++gap[h[pos]];
    }
    return cost - lv;
}
int sap(int st, int ed)
{
    source = st;
    sink = ed;
    int ret = 0;
    memset(gap, 0, sizeof(gap));
    memset(h, 0, sizeof(h));
    gap[st] = n;
    while (h[st] < n)
    {
        ret += dfs(st, INT_MAX);
    }
    return ret;
}

int rd[MAXN], cd[MAXN];

int main()
{
    int t, x, y, k;
    scanf("%d", &t);
    while (t--)
    {
        sapinit();
        memset(rd, 0, sizeof(rd));
        memset(cd, 0, sizeof(cd));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d%d", &x, &y, &k);
            if (!k) insert1(x, y, 1);
            rd[y]++, cd[x]++;
        }
        bool flag = true;
        source = n + 1, sink = n + 2;
        for (int i = 1; i <= n; ++i)
            if ((rd[i] - cd[i]) % 2) flag = false;
        if (!flag) printf("impossible\n");
        else{
            int s = 0;
            for (int i = 1; i <= n; ++i)
                if (cd[i] > rd[i]) {insert1(source, i, (cd[i] - rd[i]) / 2); s += (cd[i] - rd[i]) / 2;}
                else if (rd[i] > cd[i]) {insert1(i, sink, (rd[i] - cd[i]) / 2);}
            n += 2;
            if (sap(source, sink) == s) printf("possible\n");
            else printf("impossible\n");
        }
    }
    return 0;
}
