#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,a[10000],b[10000];
int sta[10000],tot;

void doit(int l,int r,bool s[])
{
    if (l>r) {s[0]=true;s[1]=s[2]=false;return;}
    int cnt[2]={0,0};
    rep(i,l,r) if (b[i]==0) cnt[0]++; else cnt[1]++;
    bool f=false;
    if (cnt[0]<cnt[1])
    {
        rep(i,l,r) b[i]^=1;
        swap(cnt[0],cnt[1]);
        f=true;
    }
    if (cnt[0]>cnt[1])
    {
        tot=0;
        rep(i,l,r)
        {
            sta[++tot]=b[i];
            if (tot>=3 && sta[tot-2]==0 && sta[tot-1]==0) sta[tot-2]=0,tot-=2;
        }
        int cnt0=0,cnt1=0;
        rep(i,1,tot) if (sta[i]==0) cnt0++; else cnt1++;
        s[1]=true;
        if (cnt0<=cnt1) s[0]=true;
        if (cnt0<cnt1) s[2]=true;
        if (f) swap(s[1],s[2]);
        return;
    }
    if (cnt[0]==cnt[1])
    {
        s[0]=true;tot=0;
        rep(i,l,r)
        {
            sta[++tot]=b[i];
            if (tot>=3 && sta[tot-2]==0 && sta[tot-1]==0) sta[tot-2]=0,tot-=2;
        }
        int cnt0=0,cnt1=0;
        rep(i,1,tot) if (sta[i]==0) cnt0++; else cnt1++;
        if (cnt1>cnt0) s[2]=true;
        tot=0;
        rep(i,l,r)
        {
            sta[++tot]=b[i];
            if (tot>=3 && sta[tot-2]==1 && sta[tot-1]==1) sta[tot-2]=1,tot-=2;
        }
        cnt0=0;cnt1=0;
        rep(i,1,tot) if (sta[i]==0) cnt0++; else cnt1++;
        if (cnt0>cnt1) s[1]=true;
        if (f) swap(s[1],s[2]);
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
        bool L[3],R[3];
        rep(i,1,n)
        {
            rep(j,1,n) if (a[j]<a[i]) b[j]=0; else b[j]=1;
            rep(j,0,2) L[j]=R[j]=false;
            doit(1,i-1,L);doit(i+1,n,R);
            if ((L[0] && R[0]) || (L[1] && R[2]) || (L[2] && R[1])) printf("1"); else printf("0");
        }
        puts("");
    }
    return 0;
}