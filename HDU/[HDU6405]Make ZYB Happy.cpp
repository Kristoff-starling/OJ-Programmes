#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void getstring(string &s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) s+=string(1,ch);
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

const int MAXN=4e5;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

int n,q;
string s[MAXN+48];
int h[MAXN+48];

int sum[MAXN+48],ans[MAXN+48],maxlen;

namespace SAM
{
	const int MAXN=1e6;
	int maxn[MAXN+48],nxt[MAXN+48][27],par[MAXN+48],h[MAXN+48],visited[MAXN+48],root,last,tot;
	inline void init() {root=last=tot=1;}
	inline void extend(char ch)
	{
		int w=ch-'a'+1,p=last,np=++tot;maxn[np]=maxn[p]+1;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=root;last=np;return;}
		int q=nxt[p][w];
		if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
		int nq=++tot;maxn[nq]=maxn[p]+1;
		memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[q]=par[np]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
		last=np;
	}
	inline void insert(string s)
	{
		last=root;int len=int(s.size());
		for (register int i=0;i<=len-1;i++) extend(s[i]);
	}
	inline void go(string s,int ind,int val)
	{
		int pos=root,len=int(s.size());
		for (register int i=0;i<len;i++)
		{
			pos=nxt[pos][s[i]-'a'+1];int tmp=pos;
			while (tmp && visited[tmp]!=ind)
			{
				visited[tmp]=ind;
				if (!h[tmp]) h[tmp]=val; else h[tmp]=(1ll*h[tmp]*val)%MOD;
				tmp=par[tmp];
			}
		}
	}
}

int main ()
{
	int i,qlen;io.Get(n);SAM::init();
	for (i=1;i<=n;i++)
	{
		io.getstring(s[i]);
		SAM::insert(s[i]);
		maxlen=max(maxlen,int(s[i].size()));
	}
	for (i=1;i<=n;i++) io.Get(h[i]);
	for (i=1;i<=n;i++) SAM::go(s[i],i,h[i]);
	for (i=2;i<=SAM::tot;i++)
	{
		int L=SAM::maxn[SAM::par[i]]+1,R=SAM::maxn[i];
		sum[L]=add(sum[L]+SAM::h[i]);sum[R+1]=sub(sum[R+1]-SAM::h[i]);
	}
	int ss=0,cur=1,vv=0;
	for (i=1;i<=maxlen;i++)
	{
		cur=(1ll*cur*26)%MOD;
		ss=add(ss+cur);
		sum[i]=add(sum[i]+sum[i-1]);
		vv=add(vv+sum[i]);
		ans[i]=1ll*vv*quick_pow(ss,MOD-2)%MOD;
	}
	io.Get(q);
	while (q--)
	{
		io.Get(qlen);
		qlen=min(qlen,maxlen);
		io.Print(ans[qlen],'\n');
	}
	io.flush();return 0;
}
