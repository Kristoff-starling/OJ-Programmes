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
const LL LINF=1e18+48;
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
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

int x,k,n,q;
int C[10];
int vMask[348],tot;
Pair spe[48];
map<int,int> Mp;

struct Matrix
{
	LL b[278][278];
	inline void clear()
	{
		for (register int i=1;i<=tot;i++)
			for (register int j=1;j<=tot;j++)
				b[i][j]=LINF;
	}
	inline void init_I()
	{
		clear();
		for (register int i=1;i<=tot;i++) b[i][i]=0;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=tot;i++)
			for (register int j=1;j<=tot;j++)
				for (register int k=1;k<=tot;k++)
					res.b[i][j]=min(res.b[i][j],b[i][k]+ma.b[k][j]);
		return res;
	}
	inline Matrix operator ^ (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int j=1;j<=tot;j++)
			for (register int k=1;k<=tot;k++)
				res.b[1][j]=min(res.b[1][j],b[1][k]+ma.b[k][j]);
		return res;
	}
}sta,Trans,trans;

inline Matrix quick_pow(Matrix x,int y)
{
	Matrix res;res.init_I();
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

inline Pair identify(int Mask)
{
	Pair res=mp(0,0);
	for (register int i=1;i<=k+1;i++)
		if (Mask&(1<<(i-1)))
			{if (res.x==0) res.x=i; else res.y=i;}
	return res;
}

inline int lastdigit(int Mask)
{
	register int i;
	for (i=1;!(Mask&(1<<(i-1)));i++) {}
	return i;
}	

int main ()
{
	io.Get(x);io.Get(k);io.Get(n);io.Get(q);int i,j,r,c;
	for (i=1;i<=k;i++) io.Get(C[i]);
	for (register int Mask=1;Mask<=(1<<k)-1;Mask++)
		if (__builtin_popcount(Mask)==x) vMask[++tot]=Mask;
	for (i=1;i<=q;i++) io.Get(spe[i].x),io.Get(spe[i].y),Mp[spe[i].x]=spe[i].y;
	sort(spe+1,spe+q+1);spe[++q]=mp(n+1,0);
	int cp=x,sMask;
	for (sMask=1;sMask<=tot && vMask[sMask]!=((1<<x)-1)<<(k-x);sMask++) {}
	sta.clear();sta.b[1][sMask]=0;
	Trans.clear();
	for (i=1;i<=tot;i++)
		for (j=1;j<=tot;j++)
		{
			int delta=(vMask[i]^(vMask[j]<<1));
			if (__builtin_popcount(delta)==0)
				Trans.b[i][j]=0;
			else if (__builtin_popcount(delta)==2 && lastdigit(vMask[i])==lastdigit(delta))
			{
				Pair pos=identify(delta);
				Trans.b[i][j]=C[pos.y-pos.x];
			}
		}
	for (i=1;i<=q;i++)
	{
		if (cp<spe[i].x-1)
		{
			sta=sta^quick_pow(Trans,spe[i].x-1-cp);
			cp=spe[i].x-1;
		}
		if (cp==n) break;
		int tar=min(spe[i+1].x-1,spe[i].x+k+1);
		for (j=cp+1;j<=tar;j++)
		{
			trans.clear();
			for (r=1;r<=tot;r++)
				for (c=1;c<=tot;c++)
				{
					int delta=(vMask[r]^(vMask[c]<<1));
					if (__builtin_popcount(delta)==0)
						trans.b[r][c]=0;
					else if (__builtin_popcount(delta)==2 && (lastdigit(vMask[r])==lastdigit(delta)))
					{
						Pair pos=identify(delta);
						trans.b[r][c]=C[pos.y-pos.x];
						int rpos=(j-k+1+pos.y-1-1);
						trans.b[r][c]+=Mp[rpos];
					}
				}
			sta=sta^trans;
		}
		cp=tar;
	}
	int eMask;LL ans=LINF;
	for (eMask=1;eMask<=tot && vMask[eMask]!=(((1<<x)-1)<<(k-x));eMask++) {}
	ans=min(ans,sta.b[1][eMask]);
	for (i=n+1;i<=n+k-x;i++)
	{
		trans.clear();
		for (r=1;r<=tot;r++)
			for (c=1;c<=tot;c++)
			{
				int delta=(vMask[r]^(vMask[c]<<1));
				if (__builtin_popcount(delta)==0)
					trans.b[r][c]=0;
				else if (__builtin_popcount(delta)==2 && (lastdigit(vMask[r])==lastdigit(delta)))
				{
					Pair pos=identify(delta);
					trans.b[r][c]=C[pos.y-pos.x];
					int rpos=(i-k+1+pos.y-1-1);
					trans.b[r][c]+=Mp[rpos];
				}
			}
		sta=sta^trans;
		for (eMask=1;eMask<=tot && vMask[eMask]!=(((1<<x)-1)<<(k-x-(i-n)));eMask++) {}
		ans=min(ans,sta.b[1][eMask]);
	}
	io.Print(ans);
	io.flush();return 0;
}
