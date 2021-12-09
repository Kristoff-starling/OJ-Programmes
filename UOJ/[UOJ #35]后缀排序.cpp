#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

char s[100048];

namespace SAIS
{
    #define N 200000 // 建议开2倍以上字符串长度
    int n, s[N], s1[N], sa[N], t[N], p[N], cnt[N], idx[N];
    int rk[N], lcp[N];
    #define pushl(x) sa[idx[s[x]]++]=x
    #define pushs(x) sa[idx[s[x]]--]=x
    void inducedsort(int *s, int *t, int *sa, int *cnt, int n, int m, int *v, int top)
    {
        std::fill(sa+1, sa+n+1, 0);
        memcpy(idx, cnt, sizeof(int)*(m+1));
        for(int i=top; i; --i) pushs(v[i]);
        for(int i=1; i<=m; ++i) idx[i]=cnt[i-1]+1;
        for(int i=1; i<=n; ++i)
        {
            int x=sa[i]-1;
            if(x&&t[x]==1) pushl(x);
        }
        memcpy(idx, cnt, sizeof(int)*(m+1));
        for(int i=n; i; --i)
        {
            int x=sa[i]-1;
            if(x&&t[sa[i]-1]==0) pushs(sa[i]-1);
        }
    }
    void SAIS(int *s, int *t, int *p, int *cnt, int n, int m) // 
    {
        int top=0, *s1=s+n+1;
        t[n]=0;
        for(int i=1; i<=n; ++i) ++cnt[s[i]];
        for(int i=1; i<=m; ++i) cnt[i]+=cnt[i-1];
        for(int i=n-1; i; --i) t[i]=(s[i]==s[i+1]?t[i+1]:s[i]>s[i+1]);
        for(int i=2; i<=n; ++i) rk[i]=((t[i-1]&&!t[i])?(p[++top]=i, top):0);
        inducedsort(s, t, sa, cnt, n, m, p, top);
        int nm=0;
        for(int i=1, x=0, y=0; i<=n; ++i) if(x=rk[sa[i]])
        {
            if(!m||p[x+1]-p[x]!=p[y+1]-p[y]) ++nm;
            else
            {
                for(int l=p[x], r=p[y]; l<=p[x+1]; ++l, ++r)
                    if(s[l]!=s[r]) { ++nm; break; }
            }
            y=x;
            s1[x]=nm;
        }
        if(nm<top) SAIS(s1, t+n+1, p+n+1, cnt+m+1, top, nm);
        else for(int i=1; i<=top; ++i) sa[s1[i]]=i;
        for(int i=1; i<=top; ++i) s1[i]=p[sa[i]];
        inducedsort(s, t, sa, cnt, n, m, s1, top);
    }
    void construct_sa(char *rs)
    {
        int n=strlen(rs+1);
        rep(i,1,n) s[i]=rs[i];
        s[++n]=1;SAIS(s,t,p,cnt,n,'z'+2);
        rep(i,1,n-1) sa[i]=sa[i+1];
        sa[n]=0;n--;
    }
    void construct_lcp(char *rs)
    {
        int n=strlen(rs+1);
        for(int i=1; i<=n; ++i) rk[sa[i]]=i;
        for(int i=1, k=0; i<=n; ++i) if(rk[i]<n)
        {
            int j=sa[rk[i]+1];
            k=max(0, k-1);
            while(rs[i+k]==rs[j+k]) ++k;
            lcp[rk[i]]=k;
        }
    }
}

int main ()
{
    scanf("%s",s+1);SAIS::construct_sa(s);int n=strlen(s+1);
    rep(i,1,n) printf("%d ",SAIS::sa[i]);puts("");
    SAIS::construct_lcp(s);
    rep(i,1,n-1) printf("%d ",SAIS::lcp[i]);puts("");
    return 0;
}