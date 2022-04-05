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
// #define LOCAL true

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

const int MAXN=50;

int n,lim;
int ans;int cnt,curedge,curans;

LL adj[MAXN+48];
int val[MAXN+48],Cnt[MAXN+48];int seq[MAXN+48];int Len,LLen,full,Alledge;
int sum[4][1500048],num[1500048];
int pos[MAXN+48];double T,emer;LL Full;
int cc=0;

inline bool cmp(int x,int y) {return val[x]>val[y];}

inline int Countsum(LL Mask) {return sum[1][Mask&full]+sum[2][Mask>>Len&full]+sum[3][Mask>>(Len<<1)&full];}
inline int Countnum(LL Mask) {return num[Mask&full]+num[Mask>>Len&full]+num[Mask>>LLen&full];}
inline int calc(int x) {return x*(x-1)>>1;}

/*
inline void dfs(int cur,LL must,LL used)
{
	// cc++;
	// if (cc>=49000000) {emer=true;return;}
	//if ((clock()-T)/CLOCKS_PER_SEC>double(1.9)) {emer=true;return;}
	if (curans+Countsum(must>>(cur-1)<<(cur-1))>=ans) return;
	if (cnt+CountNum(must>>(cur-1))>lim) return;
	if (calc(n-CountNum(used))==Alledge-curedge) {ans=curans;return;}
	if (cur==n+1) return;
	//choose this node
	curedge+=Cnt[seq[cur]]-CountNum(used&adj[seq[cur]]);
	cnt++;curans+=val[seq[cur]];
	dfs(cur+1,must,used|(1ll<<(cur-1)));
	if (emer) return;
	curedge-=Cnt[seq[cur]]-CountNum(used&adj[seq[cur]]);
	cnt--;curans-=val[seq[cur]];
	//ignore this node
	if (!(must>>(cur-1)&1)) dfs(cur+1,must|(Full^adj[seq[cur]]),used);
}
*/

inline void dfs(int cur,LL valid)
{
	if (cur==n+1)
	{
		if (curans>ans) ans=curans;
		return;
	}
	if (curans+Countsum(valid)<=ans) return;
	if (cnt+__builtin_popcountll(valid>>(cur-1)<<(cur-1))<lim) return;
	//choose this node
	if (valid&(1ll<<(cur-1)))
	{
		cnt++;curans+=val[seq[cur]];
		dfs(cur+1,valid&adj[seq[cur]]);
		cnt--;curans-=val[seq[cur]];
	}
	//ignore this node
	dfs(cur+1,valid&(Full^(1ll<<(cur-1))));
}

class MagicMolecule
{
	public:
		inline int maxMagicPower(vector<int> V,vector<string> Graph)
		{
			T=clock();emer=false;
			n=int(V.size());for (register int i=1;i<=n;i++) val[i]=V[i-1];	
			for (register int i=1;i<=n;i++) seq[i]=i;
			sort(seq+1,seq+n+1,cmp);
			for (register int i=1;i<=n;i++) pos[seq[i]]=i;
			Alledge=0;
			for (register int i=1;i<=n;i++)
			{
				adj[i]=0;Cnt[i]=0;
				for (register int j=1;j<=n;j++) if (Graph[i-1][j-1]=='Y') Cnt[i]++,adj[i]|=(1ll<<(pos[j]-1)),Alledge++;
			}
			Alledge>>=1;
			lim=ceil(double(n)/3*2);Len=n/3+1;full=(1<<Len)-1;LLen=(Len<<1);
			for (register int i=1;i<=3;i++)
				for (register int Mask=0;Mask<=(1<<Len)-1;Mask++)
				{
					sum[i][Mask]=0;
					for (register int j=1;j<=Len;j++)
						if ((i-1)*Len+j<=n && Mask&(1<<(j-1)))
							sum[i][Mask]+=val[seq[(i-1)*Len+j]];
				}
			for (register int Mask=0;Mask<=(1<<Len)-1;Mask++)
			{
				num[Mask]=0;
				for (register int i=1;i<=Len;i++) if (Mask&(1<<(i-1))) num[Mask]++;
			}
			/*for (register int Mask=0;Mask<=(1<<Len)-1;Mask++)
			{
				Num[Mask]=0;
				for (register int i=1;i<=Len;i++) if (Mask&(1<<(i-1))) Num[Mask]++;
			}*/
			Full=(1ll<<n)-1;
			ans=-1;cnt=0;curans=0;dfs(1,Full);
			return ans;
		}
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
	double t=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;vector<int> vv;
	string s;vector<string> ss;
	MagicMolecule A;
	while (cin>>nn)
	{
		vv.clear();ss.clear();
		for (int i=1;i<=nn;i++)
		{
			int x;cin>>x;
			vv.pb(x);
		}
		for (int i=1;i<=nn;i++)
		{
			cin>>s;
			ss.pb(s);
		}
		cout<<A.maxMagicPower(vv,ss)<<endl;
		cerr<<"---------"<<endl;
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	io.flush();return 0;
}
#endif