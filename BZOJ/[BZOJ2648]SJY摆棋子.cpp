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
using namespace std;

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,root;
int ans;

inline int myabs(int x) {return x>=0?x:-x;}

namespace KDTree
{
	struct node
	{
		int lson,rson;
		int d[2],minn[2],maxn[2];
	}a[1000048];
	inline void update(int cur,int k)
	{
		a[cur].minn[0]=min(a[cur].minn[0],a[k].minn[0]);
		a[cur].minn[1]=min(a[cur].minn[1],a[k].minn[1]);
		a[cur].maxn[0]=max(a[cur].maxn[0],a[k].maxn[0]);
		a[cur].maxn[1]=max(a[cur].maxn[1],a[k].maxn[1]);
	}
	int cmpd;
	inline bool cmp(node x,node y)
	{
		if (x.d[cmpd]!=y.d[cmpd]) return x.d[cmpd]<y.d[cmpd];
		return x.d[cmpd^1]<y.d[cmpd^1];
	}
	inline int build(int left,int right,int D)
	{
		int mid=(left+right)>>1;cmpd=D;
		nth_element(a+left,a+mid,a+right+1,cmp);
		a[mid].minn[0]=a[mid].maxn[0]=a[mid].d[0];
		a[mid].minn[1]=a[mid].maxn[1]=a[mid].d[1];
		if (left!=mid) a[mid].lson=build(left,mid-1,D^1);
		if (right!=mid) a[mid].rson=build(mid+1,right,D^1);
		if (a[mid].lson) update(mid,a[mid].lson);
		if (a[mid].rson) update(mid,a[mid].rson);
		return mid;
	}
	inline void Insert(int pos)
	{
		int D=0,cur=root;
		while (true)
		{
			update(cur,pos);
			if (a[pos].d[D]<a[cur].d[D])
			{
				if (!a[cur].lson) {a[cur].lson=pos;return;} else {cur=a[cur].lson,D^=1;}
			}
			else
			{
				if (!a[cur].rson) {a[cur].rson=pos;return;} else {cur=a[cur].rson,D^=1;}
			}
		}
	}
	inline int getdist(int cur,int x,int y)
	{
		int res=0;
		if (x<a[cur].minn[0]) res+=a[cur].minn[0]-x;
		if (x>a[cur].maxn[0]) res+=x-a[cur].maxn[0];
		if (y<a[cur].minn[1]) res+=a[cur].minn[1]-y;
		if (y>a[cur].maxn[1]) res+=y-a[cur].maxn[1];
		return res;
	}
	inline void query(int cur,int x,int y)
	{
		ans=min(ans,myabs(x-a[cur].d[0])+myabs(y-a[cur].d[1]));
		int dl=(a[cur].lson?getdist(a[cur].lson,x,y):INF);
		int dr=(a[cur].rson?getdist(a[cur].rson,x,y):INF);
		if (dl<dr)
		{
			if (dl<ans) query(a[cur].lson,x,y);
			if (dr<ans) query(a[cur].rson,x,y);
		}
		else
		{
			if (dr<ans) query(a[cur].rson,x,y);
			if (dl<ans) query(a[cur].lson,x,y);
		}
	}
}

int main ()
{
	using namespace KDTree;
	int i,type,x,y;
	n=getint();m=getint();
	for (i=1;i<=n;i++) a[i].d[0]=getint(),a[i].d[1]=getint();
	root=KDTree::build(1,n,0);
	for (i=1;i<=m;i++)
	{
		type=getint();
		if (type==1)
		{
			++n;
			a[n].d[0]=getint();a[n].d[1]=getint();
			a[n].minn[0]=a[n].maxn[0]=a[n].d[0];
			a[n].minn[1]=a[n].maxn[1]=a[n].d[1];
			KDTree::Insert(n);
		}
		else
		{
			x=getint();y=getint();ans=INF;
			KDTree::query(root,x,y);
			printf("%d\n",ans);
		}
	}
	return 0;
}
