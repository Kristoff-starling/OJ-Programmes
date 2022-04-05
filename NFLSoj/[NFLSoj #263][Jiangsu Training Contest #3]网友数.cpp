#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int 
#define pb push_back
#define pf push_front
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
#define LOCAL true

const int INF=2e9;
const LL LINF=2e18;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

inline void Getchar(char &x)
{
	while (!isalpha(x=getchar()));
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

LL l,r,k;

LL dp[48];

int tot;int nxt[10048][48];
int id[10000048],taboo[10048];

struct node
{
	int A[7];
	inline int getind()
	{
		int res=0;
		for (register int i=0;i<=6;i++) res=res*10+(A[i]+1);
		return res;
	}
};

inline int extend(node sta)
{
	int ind=sta.getind();
	if (id[ind]) return id[ind];
	id[ind]=++tot;int cur=tot;
	if (sta.A[0]<0) taboo[cur]=1;
	int y[7];
	for (register int num=0;num<=9;num++)
	{
		memset(y,0xff,sizeof(y));
		for (register int i=0;i<=6;i++)
		{
			if (sta.A[i]<0) continue;
			for (register int num4=0;num4<=sta.A[i];num4++)
				for (register int num7=0;num7<=sta.A[i]-num4;num7++)
				{
					int now=i+num4*4+num7*7;
					if (now%10!=num) continue;
					check_max(y[now/10],num4+num7);
				}
		}
		node tmp;memcpy(tmp.A,y,sizeof(y));
		nxt[cur][num]=extend(tmp);
	}
	return cur;
}

//0: cur not larger; 1: cur larger
LL DP[48][10048][2];
inline LL calc(LL x)
{
	int bit[48],len=0;
	++len;bit[1]=x%10;x/=10;
	while (x) bit[++len]=x%10,x/=10;
	memset(DP,0,sizeof(DP));
	DP[0][1][0]=1;
	for (register int i=1;i<=len;i++)
		for (register int j=1;j<=tot;j++)
			for (register int num=0;num<=9;num++)
			{
				if (num>bit[i]) DP[i][nxt[j][num]][1]+=DP[i-1][j][0]+DP[i-1][j][1];
				if (num==bit[i]) DP[i][nxt[j][num]][0]+=DP[i-1][j][0],DP[i][nxt[j][num]][1]+=DP[i-1][j][1];
				if (num<bit[i]) DP[i][nxt[j][num]][0]+=DP[i-1][j][0]+DP[i-1][j][1];
			}
	LL res=0;
	for (register int i=1;i<=tot;i++) if (!taboo[i]) res+=DP[len][i][0];
	return res;
}

int main ()
{
	int method[]={4,7};
	for (register int i=0;i<=40;i++) dp[i]=LINF;dp[0]=0;
	for (register int i=0;i<=1;i++)
		for (register int j=method[i];j<=28;j++)
			check_min(dp[j],dp[j-method[i]]+1);
	Get(l);Get(r);Get(k);LL ans=0;
	while (l<=r && l<=28) ans+=(dp[l++]<=k);
	if (k>=9) {ans+=(r-l+1);printf("%lld\n",ans);return 0;}
	node sta;memset(sta.A,0,sizeof(sta.A));sta.A[0]=k;extend(sta);
	ans+=calc(r)-calc(l-1);
	printf("%lld\n",ans);
	return 0;
}
