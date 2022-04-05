#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

int n,d,c[48];LL k;

inline LL string_to_int(char s[])
{
	LL res=0;
	for (register int i=1;i<=d;i++) if (s[i]=='1') res|=(1ll<<(i-1));
	return res;
}

struct Linear_Base
{
	LL b[66],from[66];
	inline void clear() {memset(b,0,sizeof(b));memset(from,0,sizeof(from));}
	inline void print()
	{
		cerr<<"------------------"<<endl;
		for (register int i=d;i>=1;i--) if (b[i]) cerr<<i<<' '<<b[i]<<endl;
		cerr<<"------------------"<<endl;
	}
	inline void insert(LL x,int ind)
	{
		LL nf=0;if (ind) nf|=(1ll<<(ind-1));
		for (register int i=d;i>=1;i--)
			if (x&(1ll<<(i-1)))
				if (!b[i]) {b[i]=x;from[i]=nf;return;}
				else x^=b[i],nf^=from[i];
	}
	inline pLL find(LL x)
	{
		pLL res=mp(1,0);
		for (register int i=d;i>=1;i--)
			if (x&(1ll<<(i-1)))
				if (!b[i]) return mp(0,0); else x^=b[i],res.y^=from[i];
		return res;
	}
	inline LL query(LL x,int pos)
	{
		for (register int i=d;i>=pos;i--)
			if (x&(1ll<<(i-1)))
				if (!b[i]) return 0; else x^=b[i];
		LL res=1;
		for (register int i=pos-1;i>=1;i--) if (b[i]) res<<=1;
		return res;
	}
	inline Linear_Base merge(Linear_Base other)
	{
		Linear_Base res,A=(*this),B,r;res.clear();r.clear();B.clear();
		for (register int i=d;i>=1;i--) if (A.b[i]) B.insert(A.b[i],i);
		for (register int i=d;i>=1;i--)
			if (other.b[i])
			{
				pLL info=B.find(other.b[i]);
				if (info.x)
				{
					LL tmp=0;
					for (register int j=d;j>=1;j--) if (info.y&(1ll<<(j-1))) tmp^=A.b[j];
					r.insert(tmp,0);
				}
				B.insert(other.b[i],0);
			}
		return r;
	}
}lb[4848];

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	int t;Get(t);
	while (t--)
	{
		Get(n,d,k);char s[148];LL val;
		memset(lb,0,sizeof(lb));
		for (register int i=1;i<=n;i++) Get(c[i]);
		for (register int i=1;i<=n;i++)
			while (c[i]--)
				scanf("%s",s+1),val=string_to_int(s),lb[1<<(i-1)].insert(val,0);
		for (register int Mask=1;Mask<=(1<<n)-1;Mask++)
			if (__builtin_popcount(Mask)>1) lb[Mask]=lb[Mask^LOWBIT(Mask)].merge(lb[LOWBIT(Mask)]);
		LL ans=0;
		for (register int i=d;i>=1;i--)
		{
			LL cnt=0;ans^=(1ll<<(i-1));
			for (register int Mask=1;Mask<=(1<<n)-1;Mask++)
			{
				LL val=lb[Mask].query(ans,i);
				if (__builtin_popcount(Mask)&1) cnt+=val; else cnt-=val;
			}
			if (cnt<k) ans^=(1ll<<(i-1)),k-=cnt;
		}
		printf("%lld\n",ans<<1);
	}
	return 0;
}
