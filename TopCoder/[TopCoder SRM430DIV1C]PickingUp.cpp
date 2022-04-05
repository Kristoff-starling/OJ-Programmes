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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}

struct method
{
	int Mask,minMask;LL val;
};
vector<method> a[48],b[48];

inline bool cmp_small(method x,method y) {return x.val<y.val;}
inline bool cmp_big(method x,method y) {if (x.val!=y.val) return x.val>y.val; return x.Mask>y.Mask;}

class PickingUp
{
	int n,n1,n2;
	LL sa1[48],sa2[48],sb1[48],sb2[48];	
	struct Ans
	{
		LL val;
		int Mask1,Mask2;
		inline bool operator < (const Ans &other) const
		{
			if (val!=other.val) return val<other.val;
			if (Mask1!=other.Mask1) return Mask1<other.Mask1;
			return Mask2<other.Mask2;
		}
	}ans,Cur;
	inline void Clear()
	{
		for (register int i=0;i<=40;i++) a[i].clear(),b[i].clear();
	}
	public:
		inline vector<int> fairPickingUp(vector<LL> score1,vector<LL> score2)
		{
			n=int(score1.size());n1=n/2;n2=n-n1;
			Clear();
			for (register int i=1;i<=n1;i++) sa1[i]=score1[i-1],sb1[i]=score2[i-1];
			for (register int i=1;i<=n2;i++) sa2[i]=score1[n1-1+i],sb2[i]=score2[n1-1+i];
			// na=(1<<n1);nb=(1<<n2);method cur;
			method cur;
			for (register int Mask=0,i=1;Mask<=(1<<n1)-1;Mask++,i++)
			{
				// a[i].Mask=Mask;a[i].val=0;
				cur.Mask=Mask;cur.val=0;
				for (register int j=1;j<=n1;j++)
					if (!(Mask&(1<<(j-1)))) cur.val+=sa1[n1-j+1]; else cur.val-=sb1[n1-j+1];
				// if (Mask==2) cerr<<cur.val<<"^^"<<endl;
				a[__builtin_popcount(Mask)].pb(cur);
			}
			for (register int Mask=0,i=1;Mask<=(1<<n2)-1;Mask++,i++)
			{
				// b[i].Mask=Mask;b[i].val=0;
				cur.Mask=Mask;cur.val=0;
				for (register int j=1;j<=n2;j++)
					if (!(Mask&(1<<(j-1)))) cur.val+=sa2[n2-j+1]; else cur.val-=sb2[n2-j+1];
				// if (Mask==1) cerr<<cur.val<<"^^^"<<endl;
				b[__builtin_popcount(Mask)].pb(cur);
			}
			for (register int i=0;i<=n1;i++) sort(a[i].begin(),a[i].end(),cmp_small);
			for (register int i=0;i<=n2;i++)
			{
				sort(b[i].begin(),b[i].end(),cmp_big);
				int sz=int(b[i].size());
				if (!sz) continue;
				b[i][sz-1].minMask=b[i][sz-1].Mask;
				for (register int j=sz-2;j>=0;j--) b[i][j].minMask=((b[i][j].val==b[i][j+1].val)?b[i][j+1].minMask:b[i][j].Mask);
			}
			// sort(a+1,a+na+1,cmp_small);sort(b+1,b+nb+1,cmp_big);
			// b[nb].minMask=b[nb].Mask;
			// for (register int i=nb-1;i>=1;i--) b[i].minMask=((b[i].val==b[i+1].val)?b[i+1].minMask:b[i].Mask);
			int pt=1;ans.val=LINF;
			for (register int num=0;num<=n1;num++)
			{
				int to=n/2-num,sz=int(b[to].size());pt=0;
				for (register int i=0;i<int(a[num].size());i++)
				{

					while (pt<sz-1 && a[num][i].val+b[to][pt+1].val>=0) pt++;
					// if (a[num][i].Mask==1) cerr<<b[to][pt].Mask<<"&&"<<' '<<a[num][i].val<<' '<<b[to][pt].val<<"&&"<<endl;
					Cur.val=myabs(a[num][i].val+b[to][pt].val);Cur.Mask1=a[num][i].Mask;Cur.Mask2=b[to][pt].Mask;
					// if (Cur<ans) ans=Cur;
					if (Cur<ans)
					{
						ans.val=Cur.val;
						ans.Mask1=Cur.Mask1;
						ans.Mask2=Cur.Mask2;
					}
					if (pt<sz-1)
					{
						Cur.val=myabs(a[num][i].val+b[to][pt+1].val);Cur.Mask1=a[num][i].Mask;Cur.Mask2=b[to][pt+1].minMask;
											// if (a[num][i].Mask==2) cerr<<b[to][pt].Mask<<"&&"<<' '<<a[num][i].val<<' '<<b[to][pt].val<<"&&"<<endl;

						if (Cur<ans)
						{
							ans.val=Cur.val;
							ans.Mask1=Cur.Mask1;
							ans.Mask2=Cur.Mask2;
						}
					}
				}
			}
			vector<int> res;res.clear();
			// cerr<<ans.val<<"!"<<endl;
			// cerr<<ans.Mask1<<' '<<ans.Mask
			for (register int i=n1;i>=1;i--)
				if (!(ans.Mask1&(1<<(i-1)))) res.pb(1); else res.pb(2);
			for (register int i=n2;i>=1;i--)
				if (!(ans.Mask2&(1<<(i-1)))) res.pb(1); else res.pb(2);
			return res;
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	vector<LL> aa,bb;int nn,x;
	PickingUp A;
	while (cin>>nn)
	{
		aa.clear();bb.clear();
		for (register int i=1;i<=nn;i++) cin>>x,aa.pb(x);
		for (register int i=1;i<=nn;i++) cin>>x,bb.pb(x);
		// cout<<A.fairPickingUp(aa,bb)<<endl;
		vector<int> res=A.fairPickingUp(aa,bb);
		for (register int i=0;i<int(res.size());i++) cout<<res[i]<<' ';
		cout<<endl;
	}
	// io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif
