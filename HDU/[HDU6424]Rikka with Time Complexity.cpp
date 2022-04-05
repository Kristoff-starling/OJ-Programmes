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

struct Data
{
	int x,y;
	Data () {}
	inline Data(int xx,int yy) {x=xx;y=yy;}
	inline bool operator == (const Data &other) const {return min(x,y)==min(other.x,other.y) && max(x,y)==max(other.x,other.y);}
	inline bool operator < (const Data &other) const
	{
		if (min(x,y)!=min(other.x,other.y)) return min(x,y)>min(other.x,other.y);
		return max(x,y)>max(other.x,other.y);
	}
}A[2],B[2];

int a[5],b[5];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca,lena,lenb;io.Get(ca);
	while (ca--)
	{
		io.Get(lena);io.Get(lenb);
		for (register int i=1;i<=lena;i++) io.Get(a[i]);
		for (register int i=lena+1;i<=3;i++) a[i]=INF;
		for (register int i=1;i<=lenb;i++) io.Get(b[i]);
		for (register int i=lenb+1;i<=3;i++) b[i]=INF;
		A[0]=Data(a[1]+2,INF);A[1]=Data(a[2]+1,a[3]);
		B[0]=Data(b[1]+2,INF);B[1]=Data(b[2]+1,b[3]);
		if (A[0]<A[1]) swap(A[0],A[1]);
		if (B[0]<B[1]) swap(B[0],B[1]);
		if (!(A[0]==B[0]))
		{
			if (A[0]<B[0]) io.Print(-1,'\n'); else io.Print(1,'\n');
		}
		else if (!(A[1]==B[1]))
		{
			if (A[1]<B[1]) io.Print(-1,'\n'); else io.Print(1,'\n');
		}
		else {io.Print(0,'\n');}
	}
	io.flush();return 0;
}
