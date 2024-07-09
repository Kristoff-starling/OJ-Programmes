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

const int INF=1e9;
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

const int MAXN=1e6;

int n;
char s[MAXN+48];
int sum[MAXN+48];
int cnt;
int pos[MAXN+48],tot; 
int L[MAXN+48],r[MAXN+48],dir[MAXN+48],maxright[MAXN+48];

int main ()
{
	int i;
	n=getint();scanf("%s",s+1);
	for (i=1;i<=n;i++) if (s[i]=='P') cnt++;
	if (cnt==1)
	{
		int cc[2],cur=0,p1,p2,pp;memset(cc,0,sizeof(cc));
		for (i=1;i<=n;i++)
		{
			if (s[i]=='.') continue;
			if (s[i]=='*') cc[cur]++;
			if (s[i]=='P') cur^=1,pp=i;
		}
		for (p1=1;s[p1]!='*';p1++) {}
		for (p2=n;s[p2]!='*';p2--) {}
		if (cc[0]>cc[1]) printf("%d %d\n",cc[0],pp-p1); else printf("%d %d\n",cc[1],p2-pp);
		return 0;
	}
	tot=0;for (i=1;i<=n;i++) if (s[i]=='P') pos[++tot]=i;
	sum[0]=0;for (i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='*');
	int l=1,r=n-1,mid,ans=0;
	while (l<=r)
	{
		mid=(l+r)>>1;maxright[0]=0;
		bool f=true;
		for (i=1;i<=tot;i++)
		{
			if (maxright[i-1]>=pos[i])
			{
				dir[i]=1;
				maxright[i]=pos[i]+mid;
				continue;
			}
			int num=sum[pos[i]]-sum[maxright[i-1]];
			if (!num)
			{
				dir[i]=1;
				maxright[i]=pos[i]+mid;
				continue;
			}
			dir[i]=0;maxright[i]=pos[i];
			if (pos[i]-maxright[i-1]-1>mid && (sum[pos[i]-mid-1]-sum[maxright[i-1]])) {f=false;break;}
			if (i>=2 && !dir[i-1] && (pos[i]-maxright[i-2]-1<=mid || !(sum[pos[i]-mid-1]-sum[maxright[i-2]])))
			{
				dir[i-1]=1;
				maxright[i]=pos[i-1]+mid;
			}
			if (i>=3 && !dir[i-1] && dir[i-2] && (pos[i]-pos[i-2]-1<=mid || !(sum[pos[i]-mid-1]-sum[pos[i-2]])))
			{
				dir[i-2]=0;dir[i-1]=1;
				maxright[i]=pos[i-1]+mid;
			}
		}
		if (f && (maxright[tot]>=n || !(sum[n]-sum[maxright[tot]]))) ans=mid,r=mid-1; else l=mid+1;
	}
	int ans1=0;
	for (i=1;i<=n;i++) if (s[i]=='*') ans1++;
	printf("%d %d\n",ans1,ans);
	return 0;
}
