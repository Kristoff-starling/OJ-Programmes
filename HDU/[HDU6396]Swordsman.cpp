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
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char End)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(End);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=1e5;

int n,k;
int val[10];

struct node
{
	int val[6],add[6];
	inline void input ()
	{
		for (register int i=1;i<=k;i++) io.Get(val[i]);
		for (register int i=1;i<=k;i++) io.Get(add[i]);
	}
}a[MAXN+48];

multiset<Pair> s[10];
vector<Pair> v;int ans;

inline void Clear()
{
	for (register int i=1;i<=k;i++) s[i].clear();
	ans=0;
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca,i,j;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(k);Clear();
		for (i=1;i<=k;i++) io.Get(val[i]);
		for (i=1;i<=n;i++) a[i].input(),s[1].insert(mp(a[i].val[1],i));
		for(;;)
		{
			for (i=1;i<=k-1;i++)
				while (s[i].size() && s[i].begin()->x<=val[i])
				{
					Pair ins=(*s[i].begin());
					ins.x=a[ins.y].val[i+1];
					s[i+1].insert(ins);
					s[i].erase(s[i].begin());
				}
			int cc=0;
			while (s[k].size() && s[k].begin()->x<=val[k])
			{
				Pair ins=(*s[k].begin());
				cc++;for (j=1;j<=k;j++) val[j]+=a[ins.y].add[j];
				s[k].erase(s[k].begin());
			}
			if (!cc) break;
			ans+=cc;
		}
		io.Print(ans,'\n');
		for (i=1;i<=k;i++) io.Print(val[i],i==k?'\n':' ');
	}
	io.flush();return 0;
}
