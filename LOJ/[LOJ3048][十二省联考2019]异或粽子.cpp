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

const int MAXN=5e5;

int n,k;
uint a[MAXN+18],xsum[MAXN+48];

int root[MAXN+48];

namespace Trie
{
	int nxt[MAXN*33+48][2],cnt[MAXN*33+48],tot;
	inline int Create() {++tot;nxt[tot][0]=nxt[tot][1]=0;cnt[tot]=0;return tot;}
	inline void init()
	{
		tot=0;root[0]=Create();int cur=root[0];cnt[cur]=1;
		for (register int i=31;i>=0;i--)
		{
			nxt[cur][0]=Create();
			cur=nxt[cur][0];cnt[cur]++;
		}
	}
	inline void insert(int &cur,int last,uint val,int layer)
	{
		if (!cur) cur=Create();
		nxt[cur][0]=nxt[last][0];nxt[cur][1]=nxt[last][1];cnt[cur]=cnt[last]+1;
		if (layer==-1) return;
		int w=(val>>layer&1);nxt[cur][w]=Create();
		insert(nxt[cur][w],nxt[last][w],val,layer-1);
	}
	inline uint query(int cur,int k,uint val,int layer)
	{
		if (layer==-1) return 0;
		int w=((val>>layer&1)^1),cmp=cnt[nxt[cur][w]];
		if (k<=cmp) return query(nxt[cur][w],k,val,layer-1)|(1ll<<layer); else return query(nxt[cur][w^1],k-cmp,val,layer-1);
	}
}

struct node
{
	uint val;int pos,rnk;
	node () {}
	inline node (uint _v,int _p,int _r) {val=_v;pos=_p;rnk=_r;}
	inline bool operator < (const node &other) const {return val<other.val;}
};priority_queue<node> q;

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,k);
	for (register int i=1;i<=n;i++) Get(a[i]);
	xsum[1]=a[1];for (register int i=2;i<=n;i++) xsum[i]=xsum[i-1]^a[i];
	Trie::init();for (register int i=1;i<=n;i++) root[i]=Trie::Create(),Trie::insert(root[i],root[i-1],xsum[i],31);
	for (register int i=1;i<=n;i++) q.push(node(Trie::query(root[i-1],1,xsum[i],31),i,1));
	LL ans=0;
	while (k--)
	{
		int pos=q.top().pos,rnk=q.top().rnk;ans+=q.top().val;q.pop();
		if (rnk==pos) continue;
		q.push(node(Trie::query(root[pos-1],rnk+1,xsum[pos],31),pos,rnk+1));
	}
	printf("%lld\n",ans);
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
