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
const LL LINF=2e16;
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

const int MAXN=5e5;
const int i2=499122177;

int n;
LL a[MAXN+48];

int ans;
int sta[MAXN+48],stot;

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

inline double calc_k(int id1,int id2) {return double(a[id1]-a[id2])/(id1-id2);}

inline int calc_val(int id1,int id2)
{
	if (!id1) return a[id2]%MOD;
	int res=add(a[id1]%MOD+a[id2]%MOD);
	res=1ll*res*(id2-id1+1)%MOD*i2%MOD;
	Sub(res,a[id1]%MOD);return res;
}

int main ()
{
	Get(n);for (register int i=1;i<=n;i++) Get(a[i]);
	for (register int i=1;i<=n;i++)
	{
		while (stot>=2 && calc_k(sta[stot-1],sta[stot])<=calc_k(sta[stot],i)) Sub(ans,calc_val(sta[stot-1],sta[stot])),stot--;
		sta[++stot]=i;Add(ans,calc_val(sta[stot-1],sta[stot]));
		printf("%d ",1ll*ans*quick_pow(i,MOD-2)%MOD);
	}
	printf("\n");return 0;
}
