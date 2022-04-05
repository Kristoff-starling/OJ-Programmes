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

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline int xint()
    {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s)
    {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c > 32; c = xchar()) * s++ = c;
        *s = 0;
    }
    inline void wchar(int x)
    {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(LL x)
    {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void wstring(const char *s)
    {
        while (*s) wchar(*s++);
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int MAXN=5e5;

int n,L;

struct node
{
	int type,dist;
	inline bool operator < (const node &x) const {return dist<x.dist;}
}a[MAXN*6];
int aa[MAXN+48],bb[MAXN+48];

struct node2
{
	LL sum;int cnt;
}A[MAXN*6],B[MAXN*6];
int base=MAXN*2;
LL sum=0,ans=LINF;
LL cp,cn;

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		n=io.xint();L=io.xint();
		for (i=1;i<=n;i++) aa[i]=io.xint();
		for (i=1;i<=n;i++) bb[i]=io.xint();
		int k1=1,k2=1,tot=0;
		while (k1<=n && k2<=n)
		{
			if (aa[k1]<=bb[k2]) a[++tot].dist=aa[k1++],a[tot].type=0;
			else a[++tot].dist=bb[k2++],a[tot].type=1;
		}
		while (k1<=n) a[++tot].dist=aa[k1++],a[tot].type=0;
		while (k2<=n) a[++tot].dist=bb[k2++],a[tot].type=1;
		for (i=n*2+1;i<=n*4;i++) a[i]=a[i-n*2],a[i].dist+=L;
		int cc=0;sum=0;base=MAXN*2;ans=LINF;cp=0;cn=0;
		for (i=base-n-48;i<=base+n+48;i++) A[i].sum=A[i].cnt=0,B[i].sum=B[i].cnt=0; 
		for (i=1;i<=n*2;i++)
		{
			if (!a[i].type) cc++; else cc--;
			int dist=a[i].dist-a[1].dist;
			if (!a[i].type)
			{
				if (cc>0) sum-=dist,cn++; else sum+=dist,cp++;
				A[base+cc].sum+=dist;A[base+cc].cnt++;
			}
			else
			{
				if (cc>=0) sum+=dist,cp++; else sum-=dist,cn++;
				B[base+cc].sum+=dist;B[base+cc].cnt++;
			}
		}
		LL pres=0;
		ans=min(ans,sum);
		for (i=1;i<=n*2-1;i++)
		{
			pres+=a[i+1].dist-a[i].dist;
			if (!a[i].type)
			{
				A[base+1].cnt--;A[base+1].sum-=a[i].dist-a[1].dist;cn--;
				sum-=1ll*cp*(a[i+1].dist-a[i].dist);sum+=1ll*cn*(a[i+1].dist-a[i].dist);
				LL csum=B[base].sum-1ll*pres*B[base].cnt;
				sum-=csum*2;cp-=B[base].cnt;cn+=B[base].cnt;
				base++;
				csum=A[base].sum-1ll*pres*A[base].cnt;
				sum+=csum*2;cn-=A[base].cnt;cp+=A[base].cnt;
				A[base].cnt++;A[base].sum+=a[i+n*2].dist-a[1].dist;cp++;
				sum+=(a[i+n*2].dist-a[1].dist)-pres;
			}
			else
			{
				B[base-1].cnt--;B[base-1].sum-=a[i].dist-a[1].dist;cn--;
				sum-=1ll*cp*(a[i+1].dist-a[i].dist);sum+=1ll*cn*(a[i+1].dist-a[i].dist);
				LL csum=A[base].sum-1ll*pres*A[base].cnt;
				sum-=csum*2;cp-=A[base].cnt;cn+=A[base].cnt;
				base--;
				csum=B[base].sum-1ll*pres*B[base].cnt;
				sum+=csum*2;cn-=B[base].cnt;cp+=B[base].cnt;
				B[base].cnt++;B[base].sum+=a[i+n*2].dist-a[1].dist;cp++;
				sum+=(a[i+n*2].dist-a[1].dist)-pres;
			}
			ans=min(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
