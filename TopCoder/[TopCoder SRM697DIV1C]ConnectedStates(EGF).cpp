#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=2000;

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

class ConnectedStates
{
	int n,a[MAXN+48],exp[MAXN+48];
	public:
		inline int getSum(vector<int> sz)
		{
			n=int(sz.size());
			int tot=0;for (register int i=1;i<=n;i++) a[i]=sz[i-1],Add(tot,a[i]);
			exp[0]=1;for (register int i=1;i<=n-2;i++) exp[i]=1ll*exp[i-1]*i%MOD;
			exp[n-2]=quick_pow(exp[n-2],MOD-2);
			for (register int i=n-3;i>=0;i--) exp[i]=1ll*exp[i+1]*(i+1)%MOD;
			int pw=1;for (register int i=0;i<=n-2;i++,pw=1ll*pw*tot%MOD) exp[i]=1ll*exp[i]*pw%MOD;
			for (register int i=1;i<=n;i++)
				for (register int j=n-2;j>=1;j--)
					Add(exp[j],1ll*exp[j-1]*a[i]%MOD);
			int ans=exp[n-2];
			for (register int i=1;i<=n;i++) ans=1ll*ans*a[i]%MOD;
			for (register int i=1;i<=n-2;i++) ans=1ll*ans*i%MOD;
			return ans;
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	vector<int> vv;int nn,x;ConnectedStates A;
	while (cin>>nn)
	{
		vv.clear();
		for (register int i=1;i<=nn;i++) cin>>x,vv.pb(x);
		cout<<A.getSum(vv)<<endl;
	}
	return 0;
}
*/
