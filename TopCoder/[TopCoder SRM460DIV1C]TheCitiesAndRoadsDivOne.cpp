// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define REP(i,l,r) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1234567891;
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

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template<typename T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

class TheCitiesAndRoadsDivOne
{
	int n;
	bool cycleexist;int ga[48][48];
	int visited[48];
	map<pair<vector<int>,int>,uint> Mp;
	inline int dfs(int cur,int father)
	{
		if (visited[cur]==2) cycleexist=true;
		if (visited[cur]) return 0;
		visited[cur]=2;int res=1;
		rep(i,1,n)
			if (i!=father && ga[cur][i]) res+=dfs(i,cur);
		visited[cur]=1;return res;
	}
	inline uint solve(vector<int> comp,int addExtra)
	{
		if (int(comp.size())==1)
		{
			if (!addExtra) return 1;
			int sz=comp[0];
			return sz*(sz-1)/2-(sz-1);
		}
		if (Mp.find(mp(comp,addExtra))!=Mp.end()) return Mp[mp(comp,addExtra)];
		uint &res=Mp[mp(comp,addExtra)];res=0;
		int N=int(comp.size());vector<int> A,B;uint szA,szB,wA,wB;
		rep(Mask,0,(1<<(N-2))-1)
		{
			A.clear();B.clear();szA=comp[N-2];szB=comp[N-1];
			rep(i,1,N-2) if (!(Mask&(1<<(i-1)))) A.pb(comp[i-1]),szA+=comp[i-1]; else B.pb(comp[i-1]);
			A.pb(comp[N-2]);B.pb(comp[N-1]);
			if (addExtra)
			{
				wA=solve(A,1);wB=solve(B,0);
				Add(res,mul(mul(wA,wB),mul(szA,szB)));
				wA=solve(A,0);wB=solve(B,1);
				Add(res,mul(mul(wA,wB),mul(szA,szB)));
				wA=solve(A,0);wB=solve(B,0);
				uint tot=szA*szB;
				Add(res,mul(mul(wA,wB),tot*(tot-1)/2));
			}
			else
			{
				wA=solve(A,0);wB=solve(B,0);
				Add(res,mul(mul(wA,wB),mul(szA,szB)));
			}
		}
		return res;
	}
	public:
		inline int find(vector<string> Map)
		{
			cycleexist=false;
			n=int(Map.size());
			rep(i,1,n) rep(j,1,n) ga[i][j]=(Map[i-1][j-1]=='Y'?1:0);
			memset(visited,0,sizeof(visited));
			vector<int> comp;comp.clear();
			rep(i,1,n) if (!visited[i]) comp.pb(dfs(i,-1));
			sort(comp.begin(),comp.end());Mp.clear();
			cerr<<solve(comp,0)<<"*"<<' '<<comp.size()<<endl;
			if (cycleexist) return solve(comp,0); else return add(solve(comp,0)+solve(comp,1));
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	vector<string> aa;string s;int nn;
	TheCitiesAndRoadsDivOne A;
	while (cin>>nn)
	{
		aa.clear();
		rep(i,1,nn) cin>>s,aa.pb(s);
		cout<<A.find(aa)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
