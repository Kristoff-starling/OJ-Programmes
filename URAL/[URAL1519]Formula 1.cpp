// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n,m;
char Map[48][48];

const int hashmod=199999;

struct Hash
{
	int head[hashmod+48],to[1600048],nxt[1600048],tot;LL val[1600048];
	inline void clear() {memset(head,0,sizeof(head));tot=0;}
	inline void insert(int Mask,LL nv)
	{
		int pos=Mask%hashmod;
		for (register int i=head[pos];i;i=nxt[i]) if (to[i]==Mask) {val[i]+=nv;return;}
		to[++tot]=Mask;nxt[tot]=head[pos];head[pos]=tot;val[tot]=nv;
	}
	inline LL query(int Mask)
	{
		int pos=Mask%hashmod;
		for (register int i=head[pos];i;i=nxt[i]) if (to[i]==Mask) return val[i];
		return 0;
	}
}hsh[2];

inline int getplug(int Mask,int pos) {return Mask>>((pos-1)<<1)&3;}
inline int setplug(int &Mask,int pos,int newplug) {int tmp=(1<<((m+1)<<1))-1;tmp^=(3<<((pos-1)<<1));Mask&=tmp;Mask|=(newplug<<((pos-1)<<1));}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,m);
	rep(i,1,n) scanf("%s",Map[i]+1);
	hsh[0].clear();hsh[0].insert(0,1);int cur=0,nxt=1;
	int ex=n,ey=m;
	while (Map[ex][ey]=='*' && ex) {ey--;if (ey==0) ex--,ey=m;}
	rep(i,1,n)
	{
		rep(j,1,m)
		{
			hsh[nxt].clear();
			rep(k,0,hashmod-1)
				for (register int l=hsh[cur].head[k];l;l=hsh[cur].nxt[l])
				{
					int Mask=hsh[cur].to[l],toMask;LL val=hsh[cur].val[l];
					int plug1=getplug(Mask,j),plug2=getplug(Mask,j+1);
					if (Map[i][j]=='*' && (plug1 || plug2)) continue;
					if (Map[i][j]=='*') {hsh[nxt].insert(Mask,val);continue;}
					if (!plug1 && !plug2)
					{
						if (i!=n && j!=m) toMask=Mask,setplug(toMask,j,1),setplug(toMask,j+1,2),hsh[nxt].insert(toMask,val);
					}
					if (!plug1 && plug2)
					{
						if (i!=n) toMask=Mask,setplug(toMask,j+1,0),setplug(toMask,j,plug2),hsh[nxt].insert(toMask,val);
						if (j!=m) toMask=Mask,hsh[nxt].insert(toMask,val);
					}
					if (plug1 && !plug2)
					{
						if (i!=n) toMask=Mask,hsh[nxt].insert(toMask,val);
						if (j!=m) toMask=Mask,setplug(toMask,j,0),setplug(toMask,j+1,plug1),hsh[nxt].insert(toMask,val);
					}
					if (plug1==1 && plug2==1)
					{
						int presum=0;int p=j+2;
						while (p<=m+1)
						{
							int cplug=getplug(Mask,p);
							if (cplug==2 && !presum) break;
							if (cplug==1) presum++;
							if (cplug==2) presum--;
							p++;
						}
						toMask=Mask;setplug(toMask,j,0);setplug(toMask,j+1,0);setplug(toMask,p,1);
						hsh[nxt].insert(toMask,val);
					}
					if (plug1==1 && plug2==2)
					{
						if (i==ex && j==ey)
						{
							toMask=Mask;setplug(toMask,j,0);setplug(toMask,j+1,0);
							hsh[nxt].insert(toMask,val);
						}
					}
					if (plug1==2 && plug2==1)
					{
						toMask=Mask;setplug(toMask,j,0);setplug(toMask,j+1,0);
						hsh[nxt].insert(toMask,val);
					}
					if (plug1==2 && plug2==2)
					{
						int sufsum=0,p=j-1;
						while (p>=1)
						{
							int cplug=getplug(Mask,p);
							if (cplug==1 && !sufsum) break;
							if (cplug==1) sufsum--;
							if (cplug==2) sufsum++;
							p--;
						}
						toMask=Mask;setplug(toMask,j,0);setplug(toMask,j+1,0);setplug(toMask,p,2);
						hsh[nxt].insert(toMask,val);
					}
				}
			cur^=1;nxt^=1;
		}
		hsh[nxt].clear();
		rep(k,0,hashmod-1)
			for (register int l=hsh[cur].head[k];l;l=hsh[cur].nxt[l])
			{	
				int Mask=hsh[cur].to[l];LL val=hsh[cur].val[l];
				if (getplug(Mask,m+1)==0) Mask<<=2,hsh[nxt].insert(Mask,val);
			}
		cur^=1;nxt^=1;
	}
	printf("%lld\n",hsh[cur].query(0));
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
