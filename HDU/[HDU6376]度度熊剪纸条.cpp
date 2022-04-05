#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,k;
char s[MAXN+48];
Pair a[MAXN+48];int tot;
Pair b[MAXN+48];int t;

inline bool cmp(Pair x,Pair y)
{
	return (x.y-x.x+1)>(y.y-y.x+1);
}

int main ()
{
	int i;
	while (scanf("%d%d",&n,&k)!=EOF)
	{
		scanf("%s",s+1);tot=0;int lastpos=0;
		s[n+1]='#';
		for (i=1;i<=n;i++)
			if (s[i]!=s[i+1])
				a[++tot]=mp(s[i]-'0',i);
		if (tot==1)
		{
			if (a[1].x==1) printf("%d\n",n); else puts("0");
			continue;
		}
		if (k==0)
		{
			if (a[1].x==1) printf("%d\n",a[1].y); else puts("0");
			continue;
		}
		t=0;
		for (i=1;i<=tot;i++) if (a[i].x==1) b[++t]=mp(a[i-1].y+1,a[i].y);
		if (b[1].x!=1 && b[t].y!=n)
		{
			int nu=(k+1)/2;
			sort(b+1,b+t+1,cmp);int ans=0;
			for (i=1;i<=min(nu,t);i++) ans+=b[i].y-b[i].x+1;
			printf("%d\n",ans);
			continue;
		}
		if (b[1].x==1 && b[t].y==n)
		{
			sort(b+2,b+t,cmp);
			int ans=0;
			//0 0
			int nu=(k+1)/2,cnt=0;
			for (i=1;i<=min(nu,t-2);i++) cnt+=b[i+1].y-b[i+1].x+1;
			ans=max(ans,cnt);
			//0 1
			nu=k/2,cnt=0;
			for (i=1;i<=min(nu,t-2);i++) cnt+=(b[i+1].y-b[i+1].x+1);
			cnt+=b[t].y-b[t].x+1;
			ans=max(ans,cnt);
			//1 0
			nu=k/2,cnt=0;
			for (i=1;i<=min(nu,t-2);i++) cnt+=(b[i+1].y-b[i+1].x+1);
			cnt+=b[1].y-b[1].x+1;
			ans=max(ans,cnt);
			//1 1
			nu=(k-1)/2,cnt=0;
			for (i=1;i<=min(nu,t-2);i++) cnt+=(b[i+1].y-b[i+1].x+1);
			cnt+=b[1].y-b[1].x+1;
			cnt+=b[t].y-b[t].x+1;
			ans=max(ans,cnt);
			printf("%d\n",ans);
			continue;
		}
		if (b[1].x==1)
		{
			sort(b+2,b+t+1,cmp);int ans=0;
			//0 0
			int nu=(k+1)/2,cnt=0;
			for (i=1;i<=min(nu,t-1);i++) cnt+=b[i+1].y-b[i+1].x+1;
			ans=max(ans,cnt);
			//1 0
			nu=k/2,cnt=0;
			for (i=1;i<=min(nu,t-1);i++) cnt+=(b[i+1].y-b[i+1].x+1);
			cnt+=b[1].y-b[1].x+1;
			ans=max(ans,cnt);
			printf("%d\n",ans);
			continue;
		}
		if (b[t].y==n)
		{
			sort(b+1,b+t,cmp);int ans=0;
			//0 0
			int nu=(k+1)/2,cnt=0;
			for (i=1;i<=min(nu,t-1);i++) cnt+=b[i].y-b[i].x+1;
			ans=max(ans,cnt);
			//0 1
			nu=k/2,cnt=0;
			for (i=1;i<=min(nu,t-1);i++) cnt+=(b[i].y-b[i].x+1);
			cnt+=b[t].y-b[t].x+1;
			ans=max(ans,cnt);
			printf("%d\n",ans);
			continue;
		}
	}
	return 0;
}
/*
10 3
1101011111
*/
