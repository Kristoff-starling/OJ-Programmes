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
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0'; else while (x) s[++pt]='0'+x%10,x/=10;
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

int n,ans;
int a[48];
string method[48];

inline bool solve(int pos)
{
	if (pos==ans+1)
	{
		if (a[pos]!=n) return false;
		io.Print(ans);io.flush();
		for (register int i=1;i<=ans;i++) cout<<method[i]<<endl;
		return true;
	}
	for (register int i=1;i<=pos;i++)
		for (register int j=1;j<=pos;j++)
			for (register int k=1;k<=8;k<<=1)
			{
				if (a[i]+k*a[j]<=a[pos] || a[i]+k*a[j]>n) continue;
				a[pos+1]=a[i]+k*a[j];
				method[pos]="lea e"+string(1,'a'+pos)+"x, [e"+string(1,'a'+i-1)+"x + "+string(1,'0'+k)+"*e"+string(1,'a'+j-1)+"x]";
				if (solve(pos+1)) return true;
			}
	for (register int i=1;i<=pos;i++)
		for (register int k=1;k<=8;k<<=1)
		{
			if (k*a[i]<=a[pos] || k*a[i]>n) continue;
			a[pos+1]=k*a[i];
			method[pos]="lea e"+string(1,'a'+pos)+"x, ["+string(1,'0'+k)+"*e"+string(1,'a'+i-1)+"x]";
			if (solve(pos+1)) return true;
		}
	return false;
}

int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	memset(a,0,sizeof(a));a[1]=1;
	io.Get(n);
//	cerr<<n<<endl;
#ifdef DEBUG
	cerr<<i<<endl;
#endif
	for (;;++ans) if (solve(1)) break;
	return 0;
}
