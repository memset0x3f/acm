#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 1024
#define MAXM 1024*1024
using namespace std;

//���ݽṹ
typedef struct{
    int s, v, next, opp;
    bool used;
}EDGE;
EDGE e[MAXM];//�߱�
int n, m, eid, res;//eid��ʾ�߱�������, n-resΪ���ս��
int  p[MAXN];//�߱�����������
bool map[MAXN][MAXN];//��ʼ�ڽӾ���ȡ��ͼ��
bool resb[MAXN];//��ĳ�����Ƿ�����һ����Ȧ
int mem[MAXN];//�ж϶���ͼʱ��ǽڵ����ɫ
bool mark[MAXN];//����ڵ�˫��ͨ�����еĳ������
int dfn[MAXN], low[MAXN], stack[MAXM];//tarjan�㷨�Ļ������ݽṹ
int dindex = 0, top;//dindex��ʾtarjan�㷨�еı�ţ�top��ʾջ����
int temp1, temp2;


//�߱��Ļ�������
void insert(int x, int y)
{
    e[eid].s = x;
    e[eid].v = y;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert2(int x, int y)
{
    temp1 = eid, temp2 = eid + 1;
    e[eid].s = x;
    e[eid].v = y;
    e[eid].next = p[x];
    e[eid].opp = temp2;
    p[x] = eid++;
    e[eid].s = y;
    e[eid].v = x;
    e[eid].opp = temp1;
    e[eid].next = p[y];
    p[y] = eid++;

}
void printmap()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%d:", i);
        for (int j = p[i]; j != -1; j = e[j].next)
            printf("%d ", e[j].v);
        printf("\n");
    }
}

//�������ݣ�ȡ��ͼ
bool init()
{
    memset(e, 0, sizeof(e));
    memset(p, -1, sizeof(p));
    eid = 0;
    scanf("%d%d", &n, &m);
    int x, y;
    if (n + m == 0) return false;
    memset(map, true, sizeof(map));
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x, &y);
        map[x][y] = false;
        map[y][x] = false;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (map[i][j]) insert2(i, j);
    return true;
}

//�ж�ͼ�Ƿ�Ϊ����ͼ��ֻ��mark��ǵĽڵ�
bool bigraph(int v, int now)
{
    mem[v] = now;
    for (int i = p[v]; i != -1; i = e[i].next)
        if (mark[e[i].v])
        {
            int u = e[i].v;
            if (mem[u] == mem[v]) return false;
            if ((mem[u] == -1) && !bigraph(u, 1 - now)) return false;
        }
    return true;
}

//���ҵ��ĵ�˫��ͨ���������жϣ�������Ƕ���ͼ����������е㶼���Գ�������Ȧ�С�
void color_solve(int node)
{
    //��ջ�����б߳�ջ����������бߵĶ���
    memset(mark, false, sizeof(mark));
    int k;
    do{
        k = stack[top];
        mark[e[k].v] = true;
        mark[e[k].s] = true;
        top--;
    }while (e[k].s != node);
    memset(mem, -1, sizeof(mem));
    if (!bigraph(node, 0))
    {
        //������Ƕ���ͼ��������е㶼���
        for (int i = 1; i <= n; ++i)
            resb[i] |= mark[i];
    }
}

//Tarjan�㷨���˫��ͨ����
void tarjan(int v)
{
    dfn[v] = low[v] = ++dindex;
    int u;
    for (int i = p[v]; i != -1; i = e[i].next)
    {
        u = e[i].v;
        if (e[i].used) continue;
        e[i].used = true;
        e[e[i].opp].used = true;
        stack[++top] = i;
        if (!dfn[u])
        {
            tarjan(u);
            low[v] = min(low[v], low[u]);
            if (dfn[v] <= low[u])
            {
                //��ʱ���ҵ�˫��ͨ���������ಿ�ֿ�����ģ��
                color_solve(v);
            }
        }
        else low[v] = min(low[v], dfn[u]);
    }
}

//Tarjan�㷨����Χ���֣��Լ������ս����ͳ��
void solve()
{
    memset(dfn, 0, sizeof(dfn));
    memset(stack, 0, sizeof(stack));
    memset(resb, false, sizeof(resb));
    top = 0;
    dindex = 0;
    for (int i = 1;i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    res = 0;
    for (int i = 1; i <= n; ++i)
        if (resb[i]) ++res;//resb����Ƿ�����Ȧ�г��ֹ�
}

//������
int main()
{
    while (init())
    {
        solve();
        printf("%d\n", n - res);
    }
    return 0;
}