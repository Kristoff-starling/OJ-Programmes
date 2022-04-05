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
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
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

int n,L,R,k;
int a[500048],sum[500048];

namespace ST
{
	int ST[500048][21],pos[500048][21],tolen[500048],maxlen;
	inline void init()
	{
		int i,j;
		maxlen=0;
		for (i=1;i<=n;i++)
		{
			if ((1<<(maxlen+1))<=i) maxlen++;
			tolen[i]=maxlen;
		}
		for (i=1;i<=n;i++) ST[i][0]=sum[i],pos[i][0]=i;
		for (j=1;j<=maxlen;j++)
			for (i=1;i<=n;i++)
			{
				ST[i][j]=ST[i][j-1];pos[i][j]=pos[i][j-1];
				if (i+(1<<(j-1))<=n)
					if (ST[i][j]<ST[i+(1<<(j-1))][j-1])
					{
						ST[i][j]=ST[i+(1<<(j-1))][j-1];
						pos[i][j]=pos[i+(1<<(j-1))][j-1];
					}
			}
	}
	inline Pair query(int starter,int left,int right)
	{
		int curlen=tolen[right-left+1];Pair res;
		if (ST[left][curlen]>ST[right-(1<<curlen)+1][curlen])
			res=mp(ST[left][curlen],pos[left][curlen]);
		else
			res=mp(ST[right-(1<<curlen)+1][curlen],pos[right-(1<<curlen)+1][curlen]);
		res.x-=sum[starter-1];return res;
	}
}

struct node
{
	int val;
	int starter,left,right,pos;
	inline bool operator < (const node &x) const {return val<x.val;}
};
priority_queue<node> q;

int main ()
{
	int i,l,r;
	n=getint();k=getint();L=getint();R=getint();
	for (i=1;i<=n;i++) a[i]=getint(),sum[i]=sum[i-1]+a[i];
	ST::init();node ins;
	for (i=1;i<=n;i++)
	{
		if (i+L-1>n) continue;
		l=i+L-1;r=min(n,i+R-1);
		Pair res=ST::query(i,l,r);
		ins=node{res.x,i,l,r,res.y};q.push(ins);
	}
	LL ans=0;
	for (register int cnt=1;cnt<=k;cnt++)
	{
		node res=q.top();q.pop();
		ans+=res.val;
		if (res.pos>res.left)
		{
			ins=res;ins.right=res.pos-1;
			Pair rr=ST::query(ins.starter,ins.left,ins.right);
			ins.val=rr.x;ins.pos=rr.y;
			q.push(ins);
		}
		if (res.pos<res.right)
		{
			ins=res;ins.left=res.pos+1;
			Pair rr=ST::query(ins.starter,ins.left,ins.right);
			ins.val=rr.x;ins.pos=rr.y;
			q.push(ins);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
