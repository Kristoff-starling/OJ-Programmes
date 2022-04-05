#include <bits/stdc++.h>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define mp make_pair
#define pf push_front
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-5;
const int MOD=998244353;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

vector<Pair> v[48];int ga[48][48];
queue<int> q;bool inq[200048][28];
int dp[200048][28],sum[200048];
int n,m;

inline void init_sum()
{
	int Mask,i,j;
	for (Mask=0;Mask<=(1<<n)-1;Mask++)
	{
		for (i=1;i<=n;i++)
			if (Mask&(1<<(i-1)))
				for (j=0;j<int(v[i].size());j++)
					if (Mask&(1<<(v[i][j].x-1))) sum[Mask]+=v[i][j].y;
		sum[Mask]>>=1;
	}
}

int main ()
{
	int i,x,y,c,Mask,rem,sub,cur,tocur,toMask;
	n=getint();m=getint();memset(ga,0,sizeof(ga));
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
		ga[x][y]=ga[y][x]=c;
	}
	init_sum();
	memset(dp,0,sizeof(dp));memset(inq,false,sizeof(inq));
	q.push(1);q.push(1);inq[1][1]=true;
	while (!q.empty())
	{
		Mask=q.front();q.pop();cur=q.front();q.pop();
		inq[Mask][cur]=false;
		for (i=1;i<=n;i++)
			if (!(Mask&(1<<(i-1))) && ga[cur][i])
			{
				tocur=i;toMask=(Mask|(1<<(i-1)));
				if (dp[toMask][tocur]<dp[Mask][cur]+ga[cur][tocur])
				{
					dp[toMask][tocur]=dp[Mask][cur]+ga[cur][tocur];
					if (!inq[toMask][tocur]) inq[toMask][tocur]=true,q.push(toMask),q.push(tocur);
				}
			}
		rem=(1<<n)-1-Mask;
		for (sub=rem;sub;sub=rem&(sub-1))
		{
			tocur=cur;toMask=(Mask|sub);
			if (dp[toMask][tocur]<dp[Mask][cur]+sum[sub|(1<<(cur-1))])
			{
				dp[toMask][tocur]=dp[Mask][cur]+sum[sub|(1<<(cur-1))];
				if (!inq[toMask][tocur]) inq[toMask][tocur]=true,q.push(toMask),q.push(tocur);
			}
		}
	}
	printf("%d\n",dp[(1<<n)-1][n]);
	return 0;
}
