// BEGIN CUT HERE

// END CUT HERE
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE

const int N = 300 + 9;

struct Tree {
    struct edge {
        int v, next;
    } e[N * 2];
    int p[N], eid;
    double cnt[N];
    int dist[N];
    void init() {
        eid = 0;
        memset(p, -1, sizeof(p));
    }
    void insert(int x, int y) {
        e[eid].v = y;
        e[eid].next = p[x];
        p[x] = eid++;
    }
    void insert2(int x, int y) {
        insert(x, y);
        insert(y, x);
    }
    void dfs(int v) {
        ++cnt[dist[v]];
        for (int i = p[v];  i != -1; i = e[i].next)
            if (!dist[e[i].v]) {
                dist[e[i].v] = dist[v] + 1;
                dfs(e[i].v);
            }
    }
    void gaog(int n) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            memset(dist, 0, sizeof(dist));
            dist[i] = 1;
            dfs(i);
        }
    }
} a, b;

class TreeUnion {
public:
    Tree a, b;
    double expectedCycles(vector <string> tree1, vector <string> tree2, int K) {
        a.init();
        b.init();
        string t1 = "", t2 = "";
        for (int i = 0; i < tree1.size(); ++i)
            t1 += tree1[i];
        for (int i = 0; i < tree2.size(); ++i)
            t2 += tree2[i];
        vector<int> x = splitInt(t1), y = splitInt(t2);
        int n = x.size(), m = y.size();
        for (int i = 0; i < n; ++i)
            a.insert2(i + 1, x[i]);
        for (int i = 0; i < n; ++i)
            b.insert2(i + 1, y[i]);
        ++n;
        a.gaog(n), b.gaog(n);
        double ans = 0;
        for (int i = 2; i <= K - 2; ++i)
            ans += a.cnt[i] * b.cnt[K-i];
        double fm = n;
        fm = fm * (n-1) * 2.0;
        return ans / fm;
    }

};
// BEGIN CUT HERE
int main() {
    {
        string tree1ARRAY[] = {"0"};
        vector <string> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
        string tree2ARRAY[] = {"0"};
        vector <string> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
        TreeUnion theObject;
        eq(0, theObject.expectedCycles(tree1, tree2, 4),1.0);
    }
    {
        string tree1ARRAY[] = {"0 1"};
        vector <string> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
        string tree2ARRAY[] = {"0 1"};
        vector <string> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
        TreeUnion theObject;
        eq(1, theObject.expectedCycles(tree1, tree2, 4),1.3333333333333333);
    }
    {
        string tree1ARRAY[] = {"0 1"};
        vector <string> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
        string tree2ARRAY[] = {"0 1"};
        vector <string> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
        TreeUnion theObject;
        eq(2, theObject.expectedCycles(tree1, tree2, 6),0.3333333333333333);
    }
    {
        string tree1ARRAY[] = {"0 ", "1 1 1"};
        vector <string> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
        string tree2ARRAY[] = {"0 1 0 ", "1"};
        vector <string> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
        TreeUnion theObject;
        eq(3, theObject.expectedCycles(tree1, tree2, 5),4.0);
    }
    {
        string tree1ARRAY[] = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"};
        vector <string> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
        string tree2ARRAY[] = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"};
        vector <string> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
        TreeUnion theObject;
        eq(4, theObject.expectedCycles(tree1, tree2, 7),13.314285714285713);
    }
    return 0;
}
// END CUT HERE
