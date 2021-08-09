#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define Pair pair<int,int>
#define x first
#define y second
#define mp make_pair
using namespace std;

const int MAXN=1e6;

char s[MAXN+48];int n;

int cnt[MAXN+48],fir[MAXN+48],sec[MAXN+48],sa[MAXN+48],tmp[MAXN+48];
int rnk[MAXN+48],lcp[MAXN+48];

namespace SA
{
	inline bool compare_sa(int x,int y,int k)
	{
		if (fir[x]!=fir[y]) return fir[x]<fir[y];
		int tmp1=(x+k<=n?fir[x+k]:-1),tmp2=(y+k<=n?fir[y+k]:-1);
		return tmp1<tmp2;
	}
	inline void construct_sa(char s[])
	{
		int maxind='z';memset(cnt+1,0,maxind<<2);
		for (int i=1;i<=n;i++) cnt[s[i]]++;
		for (int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
		for (int i=n;i>=1;i--) sa[cnt[s[i]]--]=i;
		fir[sa[1]]=1;for (int i=2;i<=n;i++) fir[sa[i]]=fir[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
		for (int len=1;len<=n;len<<=1)
		{
			int tot=0;
			for (int i=n-len+1;i<=n;i++) sec[++tot]=i;
			for (int i=1;i<=n;i++) if (sa[i]>len) sec[++tot]=sa[i]-len;
			memset(cnt+1,0,maxind<<2);
			for (int i=1;i<=n;i++) cnt[fir[sec[i]]]++;
			for (int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (int i=n;i>=1;i--) sa[cnt[fir[sec[i]]]--]=sec[i];
			tmp[sa[1]]=tot=1;
			for (int i=2;i<=n;i++) tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i],len);
			memcpy(fir+1,tmp+1,n<<2);
			maxind=fir[sa[n]];if (maxind>=n) break;
		}
	}
	inline void construct_lcp()
	{
		int h=0;
		for (int i=1;i<=n;i++) rnk[sa[i]]=i;
		for (int i=1;i<=n;i++)
		{
			int j=sa[rnk[i]-1];
			if (h) h--;
			while (i+h<=n && j+h<=n && s[i+h]==s[j+h]) h++;
			lcp[rnk[i]-1]=h;
		}
	}
}

Pair sta[MAXN+48];int tot;
LL ans[MAXN+48];

int main ()
{
    scanf("%d%s",&n,s+1);
    SA::construct_sa(s);SA::construct_lcp();
    tot=0;LL cur=0;
    rep(i,1,n) ans[i]+=(n-i+1);
    rep(i,1,n)
    {
        ans[sa[i]]+=cur;
        if (i!=n)
        {
            int curval=lcp[i],curcnt=1;
            while (tot && sta[tot].x>=curval) cur-=1ll*sta[tot].x*sta[tot].y,curcnt+=sta[tot].y,tot--;
            cur+=1ll*curval*curcnt;sta[++tot]=mp(curval,curcnt);
        }
    }
    tot=0;cur=0;
    REP(i,n,1)
    {
        ans[sa[i]]+=cur;
        if (i!=1)
        {
            int curval=lcp[i-1],curcnt=1;
            while (tot && sta[tot].x>=curval) cur-=1ll*sta[tot].x*sta[tot].y,curcnt+=sta[tot].y,tot--;
            cur+=1ll*curval*curcnt;sta[++tot]=mp(curval,curcnt);
        }
    }
    rep(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}