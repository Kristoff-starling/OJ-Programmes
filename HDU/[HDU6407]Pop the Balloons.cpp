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

struct Bigint
{
	int b[48],len;
	inline void clear() {memset(b,0,sizeof(b));len=0;}
	inline Bigint operator * (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=len;i++)
			for (register int j=1;j<=other.len;j++)
				res.b[i+j-1]+=b[i]*other.b[j];
		res.len=len+other.len-1;
		for (register int i=1;i<=res.len;i++) res.b[i+1]+=res.b[i]/10,res.b[i]%=10;
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline void Print()
	{
		for (register int i=len;i>=1;i--) io.Writechar('0'+b[i]);
		io.Writechar('\n');
	}
};

template <class T> inline Bigint Set(T x)
{
	Bigint res;res.clear();
	while (x) res.b[++res.len]=x%10,x/=10;
	if (res.len==0) res.len=1;
	return res;
}

int n,m,K;
char a[48][48];
int Pos[48][48],ptot[48];

inline int getsta(int Mask,int pos) {return (Mask>>((pos-1)<<1))&3;}
inline void Set(int &Mask,int pos,int nv) {Mask&=(((1<<(12<<1))-1)^(3<<((pos-1)<<1)));Mask^=(nv<<((pos-1)<<1));}

int head[48],to[4000048],nxt[4000048],tot=1;
inline void add(int num,int Mask)
{
	to[++tot]=Mask;nxt[tot]=head[num];head[num]=tot;
}

int seq[20];
inline int getmask(int t)
{
	int res=0;
	for (register int i=1;i<=t;i++) Set(res,i,seq[i]);
	return res;
}

inline void dfs(int cur)
{
	if (cur>1) add(cur-1,getmask(cur-1));
	if (cur>12) return;
	for (register int i=0;i<=2;i++) seq[cur]=i,dfs(cur+1);
}

LL dp[2][20000000];
int masklist[2][1000048],mtot[2];
LL ans[48];

inline void Clear(int X)
{
	for (register int i=head[n];i;i=nxt[i]) dp[X][to[i]]=0;
	mtot[X]=0;
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i,j,Mask,M,toMask,ca;io.Get(ca);
	dfs(1);
	//0: not done and no left
	//1: not done and has left
	//2: done
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(K);
		memset(ans,0,sizeof(ans));
		for (i=1;i<=n;i++) io.getstring(a[i]+1);
		for (j=1;j<=m;j++)
		{
			ptot[j]=0;
			for (i=1;i<=n;i++)
				if (a[i][j]=='Q') Pos[j][++ptot[j]]=i;
		}
		dp[0][0]=1;mtot[0]=1;masklist[0][1]=0;int Cur=0,Nxt=1;
		for (i=1;i<=m;i++)
		{
			mtot[Nxt]=0;
			for (j=1;j<=mtot[Cur];j++)
			{
				Mask=masklist[Cur][j];
				for (register int kk=1;kk<=ptot[i];kk++)
				{
					register int k=Pos[i][kk];
					if (a[k][i]=='Q' && getsta(Mask,k)!=2)
					{
						toMask=Mask;Set(toMask,k,2);
						if (!dp[Nxt][toMask]) masklist[Nxt][++mtot[Nxt]]=toMask;
						dp[Nxt][toMask]+=dp[Cur][Mask];
					}
				}
				toMask=Mask;
				for (register int kk=1;kk<=ptot[i];kk++)
				{
					register int k=Pos[i][kk];
					if (a[k][i]=='Q' && !getsta(Mask,k)) Set(toMask,k,1);
				}
				if (!dp[Nxt][toMask]) masklist[Nxt][++mtot[Nxt]]=toMask;
				dp[Nxt][toMask]+=dp[Cur][Mask];
				dp[Cur][Mask]=0;
			}
			Cur^=1;Nxt^=1;
		}
		for (i=1;i<=mtot[Cur];i++)
		{
			Mask=masklist[Cur][i];register int cnt=0;
			for (register int k=1;k<=n;k++)
			{
				register int res=getsta(Mask,k);
				if (res==1) {cnt=-1;break;}
				if (res==2) cnt++;
			}
			if (cnt!=-1) ans[cnt]+=dp[Cur][Mask];
			dp[Cur][Mask]=0;
		}
		LL fans=1;
		for (i=1;i<=K;i++)
		{
			fans=fans*i;
			if (ans[i]==0) {io.Print(0);continue;}
			(Set(fans)*Set(ans[i])).Print();
		}
	}
	io.flush();return 0;
}
