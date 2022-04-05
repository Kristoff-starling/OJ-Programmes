#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define ull unsigned long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=3e5;
const int base=7;

int n,q,k;
int a[MAXN+48];
char s[10000048];int len;

namespace Hash
{
	const int hashmod=19260817;
	//vector<pair<ull,int> > v[hashmod+48];
	int head[hashmod+48],to[20000048],nxt[20000048];ull R[20000048];int tot=1;
	inline void add(int s,ull rr)
	{
		to[++tot]=1;
		R[tot]=rr;
		nxt[tot]=head[s];
		head[s]=tot;
	}
	inline void clear()
	{
		memset(head,0,sizeof(head));
		tot=1;
	}
	inline void update(ull hsh,int delta)
	{
		int pos=hsh%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (R[i]==hsh) {to[i]++;return;}
		add(pos,hsh);
	}
	inline int query(ull hsh)
	{
		int pos=hsh%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (R[i]==hsh) return to[i];
		return 0;
	}
}

int pre[MAXN+48],nxt[MAXN+48];
ull pw[148],L[148],R[148];int len1,len2;

int main ()
{
	int i,op,x,y,pt,cnt,clen;ull h;
	n=getint();q=getint();Hash::clear();
	for (i=1;i<=n;i++) a[i]=getint(),pre[i]=nxt[i]=0,Hash::update(a[i],1);
	pw[0]=1;for (i=1;i<=50;i++) pw[i]=pw[i-1]*base;
	int cc=0;
	while (q--)
	{
		op=getint();
		if (op==1)
		{
			x=getint();y=getint();
			nxt[x]=y;pre[y]=x;
			for (pt=x,cnt=0;pt && cnt<=59;pt=pre[pt],cnt++) L[cnt+1]=pw[cnt]*a[pt]+L[cnt];len1=cnt;
			for (pt=y,cnt=0;pt && cnt<=59;pt=nxt[pt],cnt++) R[cnt+1]=R[cnt]*base+a[pt];len2=cnt;
			for (clen=2;clen<=50;clen++)
			{
				int lim=min(clen-1,len1);
				for (i=max(1,clen-len2);i<=lim;i++)
				{
					ull hsh=L[i]*pw[clen-i]+R[clen-i];
					Hash::update(hsh,1);
				}
			}
		}
		if (op==2)
		{
			x=getint();y=nxt[x];
			nxt[x]=0;pre[y]=0;
			for (pt=x,cnt=0;pt && cnt<=59;pt=pre[pt],cnt++) L[cnt+1]=(ull)a[pt]*pw[cnt]+L[cnt];len1=cnt;
			for (pt=y,cnt=0;pt && cnt<=59;pt=nxt[pt],cnt++) R[cnt+1]=R[cnt]*base+a[pt];len2=cnt;
			for (clen=2;clen<=50;clen++)
			{
				int lim=min(clen-1,len1);
				for (i=max(1,clen-len2);i<=lim;i++)
				{
					ull hsh=L[i]*pw[clen-i]+R[clen-i];
					Hash::update(hsh,-1);
				}
			}
		}
		if (op==3)
		{
			scanf("%s",s+1);k=getint();len=strlen(s+1);
			h=0;for (i=1;i<=k;i++) h=h*base+s[i]-'0';
			LL ans=Hash::query(h);
			for (i=k+1;i<=len;i++)
			{
				h-=pw[k-1]*(s[i-k]-'0');h=h*base+s[i]-'0';
				ans=(ans*Hash::query(h))%MOD;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
