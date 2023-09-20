#include <bits/stdc++.h>
#define x first
#define y second
#define LL long long
#define LD long double
#define pb push_back
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const LL LINF=2e16;

int n,V;
int c[41],v[41];
vector<pLL> vv[2];

template<typename T> void check_max(T &x,T y) {x=max(x,y);}

bool cmp(pLL x,pLL y) {return x.x>y.x;}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&V);
	rep(i,1,n) scanf("%d%d",c+i,v+i);
	for (int Mask=0;Mask<=(1<<min(20,n))-1;Mask++)
	{
		pLL cur=mp(0,0);
		for (int i=1;i<=min(20,n);i++)
			if (Mask&(1<<(i-1)))
			{
				cur.x+=c[i];
				cur.y+=v[i];
			}
		vv[0].pb(cur);
	}
	if (n<=20)
	{
		LL ans=0;
		for (auto item : vv[0])
			if (item.x<=V) check_max(ans,item.y);
		printf("%lld\n",ans);
		return 0;
	}
	int N=n-20;
	for (int Mask=0;Mask<=(1<<N)-1;Mask++)
	{
		pLL cur=mp(0ll,0ll);
		for (int i=1;i<=N;i++)
			if (Mask&(1<<(i-1)))
			{
				cur.x+=c[i+20];
				cur.y+=v[i+20];
			}
		vv[1].pb(cur);
	}
	sort(vv[0].begin(),vv[0].end(),cmp);
	sort(vv[1].begin(),vv[1].end());
	LL maxn=0,ans=0,pt=0;
	for (auto item : vv[0])
	{
		if (item.x>V) continue;
		int lim=V-item.x;
		while (pt<int(vv[1].size()) && vv[1][pt].x<=lim) check_max(maxn,vv[1][pt].y),pt++;
		check_max(ans,item.y+maxn);
	}
	printf("%lld\n",ans);
	return 0;
}
