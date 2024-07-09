#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define x first
#define y second
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

const int MAXN=1e6;

int n;
int son[MAXN+48],depth[MAXN+48],level[MAXN+48],fa[MAXN+48];
int pos[MAXN+48],ind;

int cnt[MAXN+48],ans[MAXN+48];

int head[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],tot;
inline void addedge(int s,int t) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;}

inline void dfs1(int cur,int father)
{
	son[cur]=0;level[cur]=depth[cur];fa[cur]=father;
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;dfs1(y,cur);
			if (level[y]>level[cur]) son[cur]=y,level[cur]=level[y];
		}
	}
}

inline void dfs2(int cur)
{
	pos[cur]=++ind;
	if (son[cur]) dfs2(son[cur]);
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=fa[cur] && y!=son[cur]) dfs2(y);
	}
}

inline void solve(int cur)
{
	if (!son[cur]) {ans[cur]=0;cnt[pos[cur]]=1;return;}
	solve(son[cur]);ans[cur]=ans[son[cur]]+1;
	cnt[pos[cur]]=1;if (cnt[pos[cur]+ans[cur]]==1) ans[cur]=0;
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=fa[cur] && y!=son[cur])
		{
			solve(y);int maxdepth=level[y]-depth[y]+1;
			for (register int j=0;j<=maxdepth-1;j++)
			{
				cnt[pos[cur]+j+1]+=cnt[pos[y]+j];
				if (cnt[pos[cur]+j+1]>cnt[pos[cur]+ans[cur]] || (cnt[pos[cur]+j+1]==cnt[pos[cur]+ans[cur]] && j+1<ans[cur])) ans[cur]=j+1;
			}
		}
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	io.Get(n);int x,y;
	for (register int i=1;i<=n-1;i++) io.Get(x,y),addedge(x,y),addedge(y,x);
	depth[1]=1;dfs1(1,-1);dfs2(1);
	solve(1);
	for (register int i=1;i<=n;i++) io.Print(ans[i],'\n');
	io.flush();return 0;
}
