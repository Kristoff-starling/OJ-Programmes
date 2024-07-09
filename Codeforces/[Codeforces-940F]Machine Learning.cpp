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
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=3048;
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

int n,q;
int a[300048];
vector<int> na[300048];

struct UPDATE
{
	int ind;
	int pos;int x,nx;
}upd[300048];int utot;

struct QUERY
{
	int ind,left,right,num;
	inline bool operator < (QUERY x)
	{
		if (left/magic!=x.left/magic) return left/magic<x.left/magic;
		if (right/magic!=x.right/magic) return right/magic<x.right/magic;
		return num<x.num;
	}
}que[300048];int qtot;
int ans[300048];

struct SORT
{
	int val;bool from;int pos;
	inline bool operator < (SORT x)
	{
		return val<x.val;
	}
}b[300048];int ntot,itot;

int cnt[300048],num_cnt[300048];
namespace BIT
{
	#define LOWBIT(x) x & (-x)
	LL c[300048];
	inline void update(int x,int delta) {while (x<=itot) {c[x]+=delta;x+=LOWBIT(x);}}
	inline int query()
	{
		int i,res=0,ss=0;
		for (i=18;i>=0;i--)
			if ((res|(1<<i))<=itot && ss+c[res|(1<<i)]==(res|(1<<i))) res|=(1<<i),ss+=c[res];
		return res;
	}
}

inline int calc()
{
	int res=1;
	while (num_cnt[res]) res++;
	return res;
}

inline void doit_plus(int j)
{
	num_cnt[cnt[na[j].back()]]++;
}

inline void doit_minus(int j)
{
	num_cnt[cnt[na[j].back()]]--;
}

int main ()
{
	int i,type,x,y,pt=1;
	n=getint();q=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=q;i++)
	{
		type=getint();x=getint();y=getint();
		if (type==1) que[++qtot]=QUERY{i,x,y,0}; else upd[++utot]=UPDATE{i,x,y,0};
	}
	for (i=1;i<=n;i++) b[++ntot]=SORT{a[i],false,i};
	for (i=1;i<=utot;i++) b[++ntot]=SORT{upd[i].x,true,i};
	sort(b+1,b+ntot+1);
	for (i=1;i<=ntot;i++)
		if (i==1 || b[i].val!=b[i-1].val)
		{
			if (!b[i].from)
				na[b[i].pos].pb(++itot);
			else
				upd[b[i].pos].nx=++itot;
		}
		else
		{
			if (!b[i].from)
				na[b[i].pos].pb(itot);
			else
				upd[b[i].pos].nx=itot;
		}
	for (i=1;i<=qtot;i++)
	{
		while (pt<=utot && upd[pt].ind<que[i].ind) pt++;
		que[i].num=pt-1;
	}
	sort(que+1,que+qtot+1);
	int cur_left=1,cur_right=0,cur_upd=0;
	for (i=1;i<=qtot;i++)
	{
		while (cur_right<que[i].right)
		{
			cur_right++;
			doit_minus(cur_right);
			cnt[na[cur_right].back()]++;
			doit_plus(cur_right);
		}
		while (cur_right>que[i].right)
		{
			doit_minus(cur_right);
			cnt[na[cur_right].back()]--;
			doit_plus(cur_right);
			cur_right--;
		}
		while (cur_left<que[i].left)
		{
			doit_minus(cur_left);
			cnt[na[cur_left].back()]--;
			doit_plus(cur_left);
			cur_left++;
		}
		while (cur_left>que[i].left)
		{
			cur_left--;
			doit_minus(cur_left);
			cnt[na[cur_left].back()]++;
			doit_plus(cur_left);
		}
		while (cur_upd<que[i].num)
		{
			cur_upd++;
			if (que[i].left<=upd[cur_upd].pos && upd[cur_upd].pos<=que[i].right)
			{
				doit_minus(upd[cur_upd].pos);
				cnt[na[upd[cur_upd].pos].back()]--;
				doit_plus(upd[cur_upd].pos);
				na[upd[cur_upd].pos].pb(upd[cur_upd].nx);	
				doit_minus(upd[cur_upd].pos);
				cnt[na[upd[cur_upd].pos].back()]++;
				doit_plus(upd[cur_upd].pos);
			}
			else
				na[upd[cur_upd].pos].pb(upd[cur_upd].nx);
		}
		while (cur_upd>que[i].num)
		{
			if (que[i].left<=upd[cur_upd].pos && upd[cur_upd].pos<=que[i].right)
			{
				doit_minus(upd[cur_upd].pos);
				cnt[na[upd[cur_upd].pos].back()]--;
				doit_plus(upd[cur_upd].pos);
				na[upd[cur_upd].pos].pop_back();
				doit_minus(upd[cur_upd].pos);
				cnt[na[upd[cur_upd].pos].back()]++;
				doit_plus(upd[cur_upd].pos);
			}
			else
				na[upd[cur_upd].pos].pop_back();
			cur_upd--;
		}
		ans[que[i].ind]=calc();
	}
	for (i=1;i<=q;i++)
		if (ans[i]) printf("%d\n",ans[i]);
	return 0;
}