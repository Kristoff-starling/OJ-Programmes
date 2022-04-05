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

int n;
char a[MAXN+48];

struct node
{
	int val,l,r;
	node () {}
	inline node (int vv,int ll,int rr) {val=vv;l=ll;r=rr;}
	inline bool operator < (const node &other) const {return val<other.val;}
}dp[MAXN+48],maxn[48],ans;
int t1[MAXN+48][10],t2[MAXN+48][10];
int L,R;

inline void init()
{
	int i,j;
	for (i=0;i<=9;i++) maxn[i].val=0,t1[0][i]=0;
	for (i=1;i<=n;i++)
	{
		dp[i].val=1;
		for (j=0;j<=a[i]-'0';j++)
			if (maxn[j].val+1>dp[i].val)
				dp[i].val=maxn[j].val+1;
		maxn[a[i]-'0'].val=max(maxn[a[i]-'0'].val,dp[i].val);
		for (j=0;j<=9;j++) t1[i][j]=t1[i-1][j];
		t1[i][a[i]-'0']=max(t1[i][a[i]-'0'],dp[i].val);
	}
	for (i=1;i<=n;i++)
		for (j=1;j<=9;j++)
			t1[i][j]=max(t1[i][j],t1[i][j-1]);
	for (i=0;i<=9;i++) maxn[i].val=0,t2[n+1][i]=0;
	for (i=n;i>=1;i--)
	{
		dp[i].val=1;
		for (j=a[i]-'0';j<=9;j++)
			if (maxn[j].val+1>dp[i].val)
				dp[i].val=maxn[j].val+1;
		maxn[a[i]-'0'].val=max(maxn[a[i]-'0'].val,dp[i].val);
		for (j=0;j<=9;j++) t2[i][j]=t2[i+1][j];
		t2[i][a[i]-'0']=max(t2[i][a[i]-'0'],dp[i].val);
	}
	for (i=1;i<=n;i++)
		for (j=8;j>=0;j--)
			t2[i][j]=max(t2[i][j],t2[i][j+1]);
}

inline void solve()
{
	int i,j;
	for (i=0;i<=9;i++) maxn[i].val=-1;
	for (i=1;i<=n;i++)
		if (L<=a[i]-'0' && a[i]-'0'<=R)
		{
			dp[i]=node(t1[i-1][L]+1,i,i);
			for (j=a[i]-'0';j<=R;j++)
				if (maxn[j].val+1>dp[i].val)
				{
					dp[i].val=maxn[j].val+1;
					dp[i].l=maxn[j].l;
				}
			if (maxn[a[i]-'0'].val<dp[i].val) maxn[a[i]-'0']=dp[i];
			if (dp[i].val+t2[i+1][R]>ans.val) ans=dp[i],ans.val+=t2[i+1][R];
		}
}

int main ()
{
	int i,j,ca;ca=getint();
	while (ca--)
	{
		n=getint();scanf("%s",a+1);ans.val=-1;
		init();
		ans.val=-1;
		for (i=0;i<=9;i++) if (ans.val<t1[n][i]) ans.val=t1[n][i];
		ans.l=ans.r=1;
		for (i=0;i<=8;i++)
			for (j=i+1;j<=9;j++)
			{
				L=i;R=j;
				solve();
			}
		printf("%d %d %d\n",ans.val,ans.l,ans.r);
	}
	return 0;
}
