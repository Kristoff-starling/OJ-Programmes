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

const int MAXN=3000;

int n,m;
vector<int> v[MAXN+48];
vector<LL> sum[MAXN+48];int cnt[MAXN+48];
priority_queue<int> q;

int main ()
{
	n=getint();m=getint();int i,j,x,c;
	for (i=1;i<=n;i++)
	{
		x=getint();c=getint();
		v[x].pb(c);
	}
	for (i=2;i<=m;i++) sort(v[i].begin(),v[i].end());
	for (i=2;i<=m;i++)
	{
		cnt[i]=int(v[i].size());LL cursum=0;
		for (j=0;j<=cnt[i]-1;j++)
		{
			sum[i].pb(cursum+v[i][j]);
			cursum+=v[i][j];
		}
	}
	cnt[1]=int(v[1].size());
	LL ans=LINF;
	for (i=0;i<=n;i++)
	{
		LL ss=0,ccc=0;
		while (!q.empty()) q.pop();
		for (j=2;j<=m;j++)
		{
			int k=0;
			if (cnt[j]>i)
				for (k=0;k<=(cnt[j]-i-1);k++) ccc++,ss+=v[j][k];
			for (;k<int(v[j].size());k++) q.push(-v[j][k]);
		}
		while (!q.empty() && cnt[1]+ccc<=i) ss+=(-q.top()),ccc++,q.pop();
		if (cnt[1]+ccc<=i) continue;
		ans=min(ans,ss);
	}
	printf("%I64d\n",ans);
	return 0;
}
