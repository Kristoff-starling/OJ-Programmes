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

char s[5][5];

inline void rotate(int x,int y,char type)
{
	char tmp[10];
	if (type=='C')
	{
		tmp[1]=s[x][y];tmp[2]=s[x][y+1];tmp[3]=s[x+1][y+1];tmp[4]=s[x+1][y];
		s[x][y+1]=tmp[1];s[x+1][y+1]=tmp[2];s[x+1][y]=tmp[3];s[x][y]=tmp[4];
	}
	else
	{
		tmp[1]=s[x][y+1];tmp[2]=s[x][y];tmp[3]=s[x+1][y];tmp[4]=s[x+1][y+1];
		s[x][y]=tmp[1];s[x+1][y]=tmp[2];s[x+1][y+1]=tmp[3];s[x][y+1]=tmp[4];
	}
}

inline void doit(int pos,char type)
{
	int x,y;
	if (pos<=2) x=1; else x=2;
	if (pos&1) y=1; else y=2;
	rotate(x,y,type);
}

int main ()
{
	int ca;io.Get(ca);int i,j,n,pos;char type;char op[5];
	while (ca--)
	{
		io.Get(n);
		for (i=1;i<=3;i++) io.getstring(s[i]+1);
		while (n--)
		{
			io.getstring(op+1);pos=op[1]-'0';type=op[2];
			doit(pos,type);
		}
		for (i=1;i<=3;i++) io.printstring(s[i]),io.Writechar('\n');
	}
	io.flush();return 0;
}
