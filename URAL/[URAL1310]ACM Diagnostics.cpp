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
const int INF=1e9;
const int magic=348;
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

struct Bigint
{
	const int lim=1e9;
	int b[2048],len;
	inline void clear() {memset(b,0,sizeof(b));len=0;}
	inline void Set(string num)
	{
		clear();int i,j;
		for (i=int(num.size())-1;i>=8;i-=9)
		{
			++len;
			for (j=i-8;j<=i;j++)
				b[len]=b[len]*10+num[j]-'0';
		}
		if (i>=0)
		{
			len++;
			for (j=0;j<=i;j++) b[len]=b[len]*10+num[j]-'0';
		}
	}
	inline Bigint operator = (Bigint other)
	{
		len=other.len;
		for (register int i=1;i<=len;i++) b[i]=other.b[i];
		return (*this);
	}
	inline Bigint operator + (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=max(len,other.len);i++)
		{
			res.b[i]+=b[i]+other.b[i];
			res.b[i+1]+=res.b[i]/lim;
			res.b[i]%=lim;
		}
		res.len=max(len,other.len);
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline Bigint operator - (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=max(len,other.len);i++)
		{
			res.b[i]+=b[i]-other.b[i];
			while (res.b[i]<0) res.b[i+1]--,res.b[i]+=lim;
		}
		res.len=max(len,other.len);
		while (!res.b[res.len] && res.len>=1) res.len--;
		if (!res.len) res.len=1;
		return res;
	}
	inline bool operator < (const Bigint &other) const
	{
		if (len<other.len) return true;
		if (len>other.len) return false;
		for (register int i=len;i>=1;i--)
		{
			if (b[i]<other.b[i]) return true;
			if (b[i]>other.b[i]) return false;
		}
		return false;
	}
	inline bool operator == (const Bigint &other) const
	{
		if (len!=other.len) return false;
		for (register int i=len;i>=1;i--) if (b[i]!=other.b[i]) return false;
		return true;
	}
	inline bool operator > (const Bigint &other) const
	{
		if ((*this)<other || (*this)==other) return false;
		return true;
	}
	inline bool operator <= (const Bigint &other) const {return (*this)<other || (*this)==other;}
	inline bool operator >= (const Bigint &other) const {return (*this)>other || (*this)==other;}
}n;

int L,m,K;string num;
Bigint dp[101][51];

inline void init()
{
	int i,j,k;
	for (i=0;i<=L;i++)
		for (j=0;j<=K-1;j++)
			dp[i][j].Set("0");
	dp[0][0].Set("1");
	for (i=0;i<=L-1;i++)
		for (j=0;j<=K-1;j++)
			if (dp[i][j].len>1 || dp[i][j].b[1])
			{
				for (k=1;k<=m;k++)
				{
					int nxt=(j+k)%K;
					dp[i+1][nxt]=dp[i+1][nxt]+dp[i][j];
				}
			}
}

int ans[148];
inline int calc(int sum)
{
	sum%=K;
	while (sum<0) sum+=K;
	while (sum>=K) sum-=K;
	return sum;
}

int main ()
{
	L=getint();m=getint();K=getint();cin>>num;n.Set(num);
	Bigint tmp,tmp2;tmp.Set("1");n=n+tmp;
	init();int i,j,sum=0;
	for (i=1;i<=L-1;i++)
	{
		tmp.Set("0");
		for (j=1;j<=m;j++)
		{
			tmp2=tmp+dp[L-i][calc(-(sum+j))];
			if (tmp2>=n) break;
			tmp=tmp2;
		}
		ans[i]=j;n=n-tmp;sum+=j;
	}
	int need=calc(-sum),cnt=0;
	for (i=1;i<=m;i++)
	{
		if (i%K==need) cnt++;
		if (cnt==n.b[1]) {ans[L]=i;break;}
	}
	for (i=1;i<=L;i++) printf("%d ",ans[i]);
	puts("");return 0;
}
