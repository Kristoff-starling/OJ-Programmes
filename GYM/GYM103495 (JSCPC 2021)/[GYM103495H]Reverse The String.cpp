#include <bits/stdc++.h>
#define ull unsigned long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MAXN=2e5;

int len,n;
char ss[MAXN+48],s[MAXN+48],minn[MAXN+48];

namespace SA
{
	int cnt[MAXN+48],fir[MAXN+48],sec[MAXN+48],sa[MAXN+48],tmp[MAXN+48];
	int rnk[MAXN+48],lcp[MAXN+48],ST[MAXN+48][21],Log[MAXN+48];
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
}

char s1[MAXN+48],s2[MAXN+48];

struct Hash
{
    const int p=19260817;
    ull hsh[MAXN+48],pw[MAXN+48];
    void init_hash(char *s)
    {
        hsh[0]=0;
        rep(i,1,n) hsh[i]=hsh[i-1]*p+s[i];
        pw[0]=1;
        rep(i,1,n) pw[i]=pw[i-1]*p;
    }
    ull query_hash(int l,int r)
    {
        return hsh[r]-hsh[l-1]*pw[r-l+1];
    }
}h1,h2;

ull query_hash1(int l,int r) {return h1.query_hash(l,r);}
ull query_hash2(int l,int r) {return h2.query_hash(n+1-r,n+1-l);}

bool compare_string(int r1,int r2)
{
    assert(r1 != r2);
    if (r1>r2) return false;
    if (query_hash2(1,r1) != query_hash2(r2-r1+1,r2)) return false;
    if (query_hash1(r1+1,r2) == query_hash2(1,r2-r1)) return false;
    int L1=r1+1,R1=r2,L2=1,R2=r2-r1;
    while (L1 != R1)
    {
        int mid=(R1-L1+1) / 2;
        if (query_hash1(L1,L1+mid-1) == query_hash2(R2-mid+1,R2))
            L1+=mid,R2-=mid;
        else
            R1=L1+mid-1,L2=R2-mid+1; 
    }
    assert(L2 == R2);
    return s1[L2]<s1[L1];
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s",ss+1);len=strlen(ss+1);
        minn[len]=ss[len];REP(i,len-1,1) minn[i]=min(minn[i+1],ss[i]);
        int L=1;while (L<=len && ss[L]==minn[L]) L++;
        if (L>len) {printf("%s\n",ss+1);continue;}
        int r;
        for (r=len,n=1;r>=L;r--,n++) s[n]=ss[r];
        s[n]='\0';n--;
        SA::construct_sa(s);
        strcpy(s1+1,s+1);strcpy(s2+1,s+1);reverse(s1+1,s1+n+1);
        h1.init_hash(s1);h2.init_hash(s2);
        int best=n+1-SA::sa[1];
        rep(i,2,n)
            if (compare_string(best,n+1-SA::sa[i])) best=n+1-SA::sa[i]; 
        reverse(ss+L,ss+L+best);
        printf("%s\n",ss+1);
    }
    return 0;
}