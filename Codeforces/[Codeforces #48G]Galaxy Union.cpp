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

const int MOD=1e9+7;
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

int n;
struct EDGE
{
	int to,len,ind;
};vector<EDGE> v[200048];

Pair root[200048];int rtot=0;
bool incycle[200048];
LL intree[200048],depth[200048];int bel[200048];
LL oncycle[200048];LL cnt[200048];
LL sz[200048];

namespace cycle
{
	bool inq[200048];bool found=false;
	Pair seq[200048];int stot=0;
	void getcycle(int starter)
	{
		int i,tmp=stot;
		while (seq[tmp].x!=starter) tmp--;
		for (i=tmp;i<=stot;i++) root[++rtot]=seq[i],incycle[root[rtot].x]=true;
	}
	void find_cycle(int cur,int lastind)
	{
		int i;
		seq[++stot].x=cur;inq[cur]=true;
		for (i=0;i<int(v[cur].size());i++)
			if (v[cur][i].ind!=lastind)
			{
				seq[stot].y=v[cur][i].len;
				if (inq[v[cur][i].to])
				{
					found=true;getcycle(v[cur][i].to);
					return;
				}
				find_cycle(v[cur][i].to,v[cur][i].ind);
				if (found) return;
			}
		inq[seq[stot--].x]=false;
	}
}

namespace gtree
{
	LL dpdown[200048],dpup[200048];
	void dfs(int cur,int father)
	{
		sz[cur]=1;dpdown[cur]=0;
		for (int i=0;i<int(v[cur].size());i++)
			if (v[cur][i].to!=father && !incycle[v[cur][i].to])
			{
				depth[v[cur][i].to]=depth[cur]+v[cur][i].len;
				dfs(v[cur][i].to,cur);
				sz[cur]+=sz[v[cur][i].to];
				dpdown[cur]+=dpdown[v[cur][i].to]+v[cur][i].len*sz[v[cur][i].to];
			}
	}
	queue<Pair> q;
	void getdown(int rt)
	{
		q.push(mp(rt,-1));dpup[rt]=0;
		int i,cur,fa;
		while (!q.empty())
		{
			cur=q.front().x;fa=q.front().y;q.pop();
			intree[cur]=dpdown[cur]+dpup[cur];bel[cur]=rt;
			for (i=0;i<int(v[cur].size());i++)
				if (v[cur][i].to!=fa && !incycle[v[cur][i].to])
				{
					dpup[v[cur][i].to]=dpup[cur]+dpdown[cur]-dpdown[v[cur][i].to]-v[cur][i].len*sz[v[cur][i].to]+v[cur][i].len*(sz[rt]-sz[v[cur][i].to]);
					q.push(mp(v[cur][i].to,cur));
				}
		}
	}
	void doit_intree()
	{
		int i;
		for (i=1;i<=rtot;i++)
		{
			depth[root[i].x]=0;dfs(root[i].x,-1);
			getdown(root[i].x);
		}
	}
}

namespace gcycle
{
	int csum=0;Pair tmp[600048],tmp2[600048];
	void solve(bool type)
	{
		int i,curcsum=0,curtsum=0,curcnt=0,pt=1;LL sum=0;
		for (i=1;i<=rtot;i++)
		{
			if (i!=1)
			{
				sum-=curcnt*tmp[i-1].y;
				curtsum-=intree[tmp[i].x];
				curcsum-=tmp[i-1].y;
				curcnt-=sz[tmp[i].x];
			}
			while (curcsum<=csum/2)
			{
				if (type)
				{
					if (curcsum+tmp[pt].y>csum/2) break;
				}
				else
				{
					if (csum%2==1)
						{if (curcsum+tmp[pt].y>csum/2) break;}
					else
						{if (curcsum+tmp[pt].y>=csum/2) break;}
				}
				curcsum+=tmp[pt].y;pt++;curtsum+=intree[tmp[pt].x];
				sum+=sz[tmp[pt].x]*curcsum;
				curcnt+=sz[tmp[pt].x];
			}
			oncycle[tmp[i].x]+=sum+curtsum;
			cnt[tmp[i].x]+=curcnt;
		}
	}
	void Reverse()
	{
		int i,pt=0;
		for (i=rtot*2;i>=1;i--)
		{
			tmp2[++pt].x=tmp[i].x;
			if (i!=1) tmp2[pt].y=tmp[i-1].y;
		}
		for (i=1;i<=rtot*2;i++) tmp[i]=tmp2[i];
	}
	void doit_oncycle()
	{
		int i;
		for (i=1;i<=rtot;i++) csum+=root[i].y;
		for (i=1;i<=rtot*2;i++) tmp[i]=(i<=rtot?root[i]:root[i-rtot]);
		solve(true);
		Reverse();
		solve(false);
	}
}

inline LL getans(int pt)
{
	LL res=0;int rt=bel[pt];
	res+=intree[pt];res+=oncycle[rt];res+=depth[pt]*cnt[rt];
	return res;
}

int main ()
{
	int i,x,y,c;
	n=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(EDGE{y,c,i});v[y].pb(EDGE{x,c,i});
	}
	cycle::find_cycle(1,-1);
	gtree::doit_intree();
	gcycle::doit_oncycle();
	for (i=1;i<=n;i++) printf("%lld ",getans(i));
	printf("\n");
	return 0;
}