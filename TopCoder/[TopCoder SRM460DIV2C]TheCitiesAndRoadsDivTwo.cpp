#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define REP(i,l,r) for (register int i=int(r);i>=int(l);i--)

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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}

class TheCitiesAndRoadsDivTwo
{
	int ga[48][48],n,m;
	bool visited[48];int cnt[48],tot;
	int exp[48];
	public:
		inline int find(vector<string> Map)
		{
			n=int(Map.size());m=int(Map[0].size());
			rep(i,1,n) rep(j,1,n) ga[i][j]=(Map[i-1][j-1]=='Y'?1:0);
			rep(k,1,n) rep(i,1,n) rep(j,1,n)
				if (i!=k && i!=j && j!=k && !ga[i][j] && ga[i][k] && ga[k][j]) ga[i][j]=1;
			/*
			rep(i,1,n)
			{
				rep(j,1,n)
					cerr<<ga[i][j]<<' ';
				cerr<<endl;
			}
			*/
			memset(visited,false,sizeof(visited));
			tot=0;
			rep(i,1,n)
				if (!visited[i])
				{
					cnt[++tot]=1;
					rep(j,1,n) if (ga[i][j]) cnt[tot]++,visited[j]=true;
				}
			// cerr<<tot<<"*"<<endl;
			if (tot==1) return 1;
			int ans=1;rep(i,1,tot-2) Mul(ans,n);
			rep(i,1,tot) Mul(ans,cnt[i]);
			return ans;
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	TheCitiesAndRoadsDivTwo A;
	vector<string> aa;string s;int nn;
	while (cin>>nn)
	{
		aa.clear();
		rep(i,1,nn) cin>>s,aa.pb(s);
		cout<<A.find(aa)<<endl;
	}
	return 0;
}
*/
