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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m;
int Mask[100048];
char s[21][100048];
LL num[2000048],dp[2000048];

inline int Cnt(int x)
{
	int i,res=0;
	for (i=1;i<=n;i++) if (x&(1<<(i-1))) res++;
	return res;
}

void FWT(LL c[],int len,int fl)
{
	int clen,j,k;
	for (clen=2;clen<=len;clen<<=1)
		for (j=0;j<len;j+=clen)
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k],tmp2=c[k+(clen>>1)];
				if (fl==1) c[k]=tmp1+tmp2,c[k+(clen>>1)]=tmp1-tmp2; else c[k]=(tmp1+tmp2)>>1,c[k+(clen>>1)]=(tmp1-tmp2)>>1;
			}
}

void calc_FWT()
{
	FWT(num,1<<n,1);
	FWT(dp,1<<n,1);
	for (int i=0;i<=(1<<n)-1;i++) num[i]*=dp[i];
	FWT(num,1<<n,-1);
}

int main ()
{
	int i,j;
	n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",s[i]+1);
	for (j=1;j<=m;j++)
	{
		Mask[j]=0;
		for (i=1;i<=n;i++) if (s[i][j]=='1') Mask[j]|=(1<<(n-i));
		num[Mask[j]]++;
	}
	for (i=0;i<=(1<<n)-1;i++) dp[i]=min(Cnt(i),n-Cnt(i));
	//for (i=0;i<=(1<<n)-1;i++) cout<<num[i]<<' ';
	//cout<<endl;
	//for (i=0;i<=(1<<n)-1;i++) cout<<dp[i]<<' ';
	//cout<<endl;
	calc_FWT();
	LL ans=LINF;
	for (i=0;i<=(1<<n)-1;i++) ans=min(ans,num[i]);
	//printf("%d\n",ans);
	cout<<ans<<endl;
	return 0;
}
