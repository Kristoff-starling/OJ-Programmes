#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
#define DEBUG(...)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

struct node
{
    int left,right;
    int lson,rson;
    int cnt;
}tree[4000048];int tot=0;
int root[100048];

int itot=0;
struct element
{
    int val,nv;
    int pos;
};
inline bool cmp_val(element x,element y) {return x.val<y.val;}
inline bool cmp_pos(element x,element y) {return x.pos<y.pos;}

int n,q;
element a[100048];int table[100048];

inline void build(int cur,int left,int right)
{
    tree[cur].left=left;tree[cur].right=right;tree[cur].cnt=0;
    if (left!=right)
    {
        int mid=(left+right)>>1;
        tree[cur].lson=++tot;
        build(tree[cur].lson,left,mid);
        tree[cur].rson=++tot;
        build(tree[cur].rson,mid+1,right);
    }
    else
    {
        tree[cur].lson=tree[cur].rson=-1;
    }
}

inline void pushup(int cur)
{
    tree[cur].cnt=tree[tree[cur].lson].cnt+tree[tree[cur].rson].cnt;
}

inline void Insert(int last,int cur,int val)
{
    tree[cur]=tree[last];
    if (tree[cur].left==tree[cur].right)
    {
        tree[cur].cnt++;
        return;
    }
    int mid=(tree[cur].left+tree[cur].right)>>1;
    if (val<=mid)
        tree[cur].lson=++tot,Insert(tree[last].lson,tree[cur].lson,val);
    else
        tree[cur].rson=++tot,Insert(tree[last].rson,tree[cur].rson,val);
    pushup(cur);
}

inline int query(int left,int right,int k)
{
    if (tree[left].left==tree[left].right) return tree[left].left;
    int cmp=tree[tree[right].lson].cnt-tree[tree[left].lson].cnt;
    if (cmp>=k)
        return query(tree[left].lson,tree[right].lson,k);
    else
        return query(tree[left].rson,tree[right].rson,k-cmp);
}

int main ()
{
    int i,l,r,k;
    n=getint();q=getint();
    for (i=1;i<=n;i++) a[i].pos=i,a[i].val=getint();
    sort(a+1,a+n+1,cmp_val);
    for (i=1;i<=n;i++)
        if (i!=1 && a[i].val==a[i-1].val)
            a[i].nv=itot;
        else
            a[i].nv=++itot,table[itot]=a[i].val;
    sort(a+1,a+n+1,cmp_pos);
    root[0]=++tot;build(root[0],1,itot);
    for (i=1;i<=n;i++) root[i]=++tot,Insert(root[i-1],root[i],a[i].nv);
    while (q--)
    {
        l=getint();r=getint();k=getint();
        printf("%d\n",table[query(root[l-1],root[r],k)]);
    }
    //system("pause");
    return 0;
}
    
