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
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+9;
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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

bool visited[148];
int distA[148],distB[148],distC[148],n;
inline bool cmpA(int x,int y) {return distA[x]<distA[y];}
inline bool cmpB(int x,int y) {return distB[x]<distB[y];}
inline bool cmpC(int x,int y) {return distC[x]<distC[y];}

class UnknownTree
{
	inline bool equ(int x,int y,int z) {return x==y && x==z;}
	inline int Y()
	{
		int minn=INF,root=-1;
		for (register int i=1;i<=n;i++)
			if (distA[i]+distB[i]+distC[i]<minn) minn=distA[i]+distB[i]+distC[i];
		for (register int i=1;i<=n;i++)
			if (distA[i]+distB[i]+distC[i]==minn)
				{if (root==-1) root=i; else return 0;}
		int AB=distA[root]+distB[root],AC=distA[root]+distC[root],BC=distB[root]+distC[root];
		memset(visited,false,sizeof(visited));visited[root]=true;
		vector<int> ptA,ptB,ptC;ptA.clear();ptB.clear();ptC.clear();
		for (register int i=1;i<=n;i++)
		{
			if (i==root) continue;
			if (distA[i]+distB[i]==AB && distA[i]+distC[i]==AC)
			{
				if (visited[i]) return 0;
				if (distA[i]>=distA[root]) return 0;
				ptA.pb(i);visited[i]=true;
			}
			if (distA[i]+distB[i]==AB && distB[i]+distC[i]==BC)
			{
				if (visited[i]) return 0;
				if (distB[i]>=distB[root]) return 0;
				ptB.pb(i);visited[i]=true;
			}
			if (distA[i]+distC[i]==AC && distB[i]+distC[i]==BC)
			{
				if (visited[i]) return 0;
				if (distC[i]>=distC[root]) return 0;
				ptC.pb(i);visited[i]=true;
			}
		}
		sort(ptA.begin(),ptA.end(),cmpA);
		sort(ptB.begin(),ptB.end(),cmpB);
		sort(ptC.begin(),ptC.end(),cmpC);
		for (register int i=0;i<int(ptA.size())-1;i++)
			if (distA[ptA[i]]==distA[ptA[i+1]]) return 0;
		for (register int i=0;i<int(ptB.size())-1;i++)
			if (distB[ptB[i]]==distB[ptB[i+1]]) return 0;
		for (register int i=0;i<int(ptC.size())-1;i++)
			if (distC[ptC[i]]==distC[ptC[i+1]]) return 0;
		int pt[148];
		for (register int i=1;i<=n;i++) pt[i]=i;
		sort(pt+1,pt+n+1,cmpA);int ans=1,cnt;
		for (register int i=1;i<=n;i++)
			if (!visited[pt[i]])
			{
				cnt=0;
				for (register int j=1;j<=i-1;j++)
					if (distA[pt[i]]>distA[pt[j]] && equ(distA[pt[i]]-distA[pt[j]],distB[pt[i]]-distB[pt[j]],distC[pt[i]]-distC[pt[j]])) cnt++;
				if (equ(distA[pt[i]],distB[pt[i]]-AB,distC[pt[i]]-AC)) cnt++;
				if (equ(distB[pt[i]],distA[pt[i]]-AB,distC[pt[i]]-BC)) cnt++;
				if (equ(distC[pt[i]],distA[pt[i]]-AC,distB[pt[i]]-BC)) cnt++;
				if (!cnt) return 0;
				ans=1ll*ans*cnt%MOD;
			}
		return ans;
	}
	inline int calc(int AB,int AC)
	{
		if (!AB || !AC) return 0;
		vector<int> ptB,ptC;ptB.clear();ptC.clear();
		memset(visited,false,sizeof(visited));
		for (register int i=1;i<=n;i++)
		{
			if (distA[i]+distB[i]==AB)
			{
				if (visited[i]) return 0;
				if (distC[i]!=AC+distA[i]) return 0;
				ptB.pb(i);visited[i]=true;
			}
			if (distA[i]+distC[i]==AC)
			{
				if (visited[i]) return 0;
				if (distB[i]!=AB+distA[i]) return 0;
				ptC.pb(i);visited[i]=true;
			}
		}
		sort(ptB.begin(),ptB.end(),cmpB);
		sort(ptC.begin(),ptC.end(),cmpC);
		for (register int i=0;i<int(ptB.size())-1;i++) if (distB[ptB[i]]==distB[ptB[i+1]]) return 0;
		for (register int i=0;i<int(ptC.size())-1;i++) if (distC[ptC[i]]==distC[ptC[i+1]]) return 0;
		int pt[148];
		for (register int i=1;i<=n;i++) pt[i]=i;
		sort(pt+1,pt+n+1,cmpA);int ans=1,cnt;
		for (register int i=1;i<=n;i++)
			if (!visited[pt[i]])
			{
				cnt=0;
				for (register int j=1;j<=i-1;j++)
					if (distA[pt[i]]>distA[pt[j]] && equ(distA[pt[i]]-distA[pt[j]],distB[pt[i]]-distB[pt[j]],distC[pt[i]]-distC[pt[j]])) cnt++;
				if (equ(distA[pt[i]],distB[pt[i]]-AB,distC[pt[i]]-AC)) cnt++;
				if (equ(distB[pt[i]],distA[pt[i]]-AB,distC[pt[i]]-(AB+AC))) cnt++;
				if (equ(distC[pt[i]],distA[pt[i]]-AC,distB[pt[i]]-(AB+AC))) cnt++;
				if (!cnt) return 0;
				ans=1ll*ans*cnt%MOD;
			}
		return ans;
	}
	inline int Line(vector<int> B,vector<int> A,vector<int> C)
	{
		for (register int i=1;i<=n;i++) distA[i]=A[i-1];
		for (register int i=1;i<=n;i++) distB[i]=B[i-1];
		for (register int i=1;i<=n;i++) distC[i]=C[i-1];
		vector<int> AB,AC;AB.clear();AC.clear();
		int maxn=-INF,minn=INF;
		for (register int i=1;i<=n;i++) maxn=max(maxn,myabs(distA[i]-distB[i])),minn=min(minn,myabs(distA[i]-distB[i]));
		if (maxn==minn) AB.pb(maxn);
		minn=INF;
		for (register int i=1;i<=n;i++) minn=min(minn,distA[i]+distB[i]);
		AB.pb(minn);
		maxn=-INF;minn=INF;
		for (register int i=1;i<=n;i++) maxn=max(maxn,myabs(distA[i]-distC[i])),minn=min(minn,myabs(distA[i]-distC[i]));
		if (maxn==minn) AC.pb(maxn);
		minn=INF;
		for (register int i=1;i<=n;i++) minn=min(minn,distA[i]+distC[i]);
		AC.pb(minn);
		int res=0;
		for (auto d1 : AB)
			for (auto d2 : AC)
				Add(res,calc(d1,d2));
		return res;
	}
	public:
		inline int getCount(vector<int> A,vector<int> B,vector<int> C)
		{
			n=int(A.size());
			for (register int i=1;i<=n;i++) distA[i]=A[i-1];
			for (register int i=1;i<=n;i++) distB[i]=B[i-1];
			for (register int i=1;i<=n;i++) distC[i]=C[i-1];
			return add(add(add(Y()+Line(B,A,C))+Line(A,B,C))+Line(A,C,B));
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	vector<int> aa,bb,cc;int nn;
	UnknownTree A;
	while (cin>>nn)
	{
		aa.clear();bb.clear();cc.clear();int x;
		for (register int i=1;i<=nn;i++) cin>>x,aa.pb(x);
		for (register int i=1;i<=nn;i++) cin>>x,bb.pb(x);
		for (register int i=1;i<=nn;i++) cin>>x,cc.pb(x);
		cout<<A.getcount(aa,bb,cc)<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif