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

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int A,B,C,D,P,n;

struct Matrix
{
	int b[5][5];
	inline void clear() {memset(b,0,sizeof(b));}
	inline void init_I()
	{
		clear();
		for (register int i=1;i<=3;i++) b[i][i]=1;
	}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				res.b[i][j]=add(b[i][j]+ma.b[i][j]);
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				for (register int k=1;k<=3;k++)
					res.b[i][j]=add(res.b[i][j]+(1ll*b[i][k]*ma.b[k][j])%MOD);
		return res;
	}
}cur,trans;

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

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca;io.Get(ca);
	while (ca--)
	{
		io.Get(A);io.Get(B);io.Get(C);io.Get(D);io.Get(P);io.Get(n);
		trans.b[1][1]=0;trans.b[1][2]=C;trans.b[1][3]=0;
		trans.b[2][1]=1;trans.b[2][2]=D;trans.b[2][3]=0;
		trans.b[3][1]=0;trans.b[3][2]=1;trans.b[3][3]=1;
		if (n==1) {io.Print(A);continue;}
		if (n==2) {io.Print(B);continue;}
		if (n==3) {io.Print(A+B+P/3);continue;}
		cur.b[1][1]=A;cur.b[1][2]=B;cur.b[1][3]=P/3;
		int cc=P/2,nxt,pos=3,npos;
		for (;cc;cc=P/((P/cc)+1))
		{
			npos=P/cc;cur.b[1][3]=cc;
			if (npos>=n)
			{
				cur=cur*quick_pow(trans,n-pos+1);
				pos=n;break;
			}
			cur=cur*quick_pow(trans,npos-pos+1);
			pos=npos+1;
		}
		if (pos<n)
		{
			cur.b[1][3]=0;
			cur=cur*quick_pow(trans,n-pos+1);
		}
		io.Print(cur.b[1][2]);
	}
	io.flush();return 0;
}
