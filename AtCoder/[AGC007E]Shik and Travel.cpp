// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
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
    template <class T> inline void Print(T x,char ch)
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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=2e5;

int n;
vector<Pair> v[MAXN+48];

int mid;
vector<Pair> dp[MAXN+48];

inline bool cmpx(Pair x,Pair y) {return x.x<y.x;}
inline bool cmpy(Pair x,Pair y) {return x.y<y.y;}

int minn[MAXN+48];

inline void merge(vector<Pair> lson,vector<Pair> rson,vector<Pair> &cur)
{
	if (!int(lson.size()) && !int(rson.size())) return;
	if (int(lson.size())>int(rson.size())) swap(lson,rson);
	sort(lson.begin(),lson.end(),cmpy);
	sort(rson.begin(),rson.end(),cmpx);
	minn[0]=rson[0].y;for (register int i=1;i<int(rson.size());i++) minn[i]=min(minn[i-1],rson[i].y);
	int pt=int(rson.size())-1;
	for (register int i=0;i<int(lson.size());i++)
	{
		while (pt>=0 && lson[i].y+rson[pt].x>mid) pt--;
		if (pt<0) continue;
		cur.pb(mp(lson[i].x,minn[pt]));
	}
	sort(lson.begin(),lson.end(),cmpx);
	sort(rson.begin(),rson.end(),cmpy);
	minn[0]=rson[0].x;for (register int i=1;i<int(rson.size());i++) minn[i]=min(minn[i-1],rson[i].x);
	pt=int(rson.size())-1;
	for (register int i=0;i<int(lson.size());i++)
	{
		while (pt>=0 && lson[i].x+rson[pt].y>mid) pt--;
		if (pt<0) continue;
		cur.pb(mp(minn[pt],lson[i].y));
	}
}

inline void dfs(int cur)
{
	dp[cur].clear();
	if (!int(v[cur].size())) {dp[cur].pb(mp(0,0));return;}
	for (register int i=0;i<int(v[cur].size());i++) dfs(v[cur][i].x);
	vector<Pair> lson=dp[v[cur][0].x],rson=dp[v[cur][1].x];
	for (register int i=0;i<int(lson.size());i++) lson[i].x+=v[cur][0].y,lson[i].y+=v[cur][0].y;
	for (register int i=0;i<int(rson.size());i++) rson[i].x+=v[cur][1].y,rson[i].y+=v[cur][1].y;
	merge(lson,rson,dp[cur]);
}

int main ()
{
/*
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
*/
	Get(n);int x,c;
	for (register int i=1;i<=n-1;i++) Get(x,c),v[x].pb(mp(i+1,c));
	int l=0,r=1e7,ans;
	while (l<=r)
	{
		mid=(l+r)>>1;
		dfs(1);
		if (int(dp[1].size())) ans=mid,r=mid-1; else l=mid+1;
	}
	printf("%d\n",ans);
	io.flush();
/*
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
*/
	return 0;
}
