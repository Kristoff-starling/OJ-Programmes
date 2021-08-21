#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MAXN=1e5;

int n,a[MAXN+48];

int isprime[MAXN+48];
int prime[MAXN+48],tot;

void sieve()
{
    memset(isprime,1,sizeof(isprime));
    tot=0;
    rep(i,1,MAXN) isprime[i]=i; 
    rep(i,2,MAXN)
    {
        if (isprime[i]==i) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=prime[j];
            if (i%prime[j]==0) break;
        }
    }
}

int big[MAXN+48],id[MAXN+48];
vector<int> table[MAXN+48];

void init(int x)
{
    int curfac=1,t=0,tmp=x;
    vector<int> fac;fac.clear();
    while (x!=1)
    {
        if (isprime[x]!=curfac)
        {
            if (t&1) fac.pb(curfac);
            curfac=isprime[x];
            t=1;
        }
        else
            t++;
        x/=isprime[x];
    }
    big[tmp]=fac.back();
    id[tmp]=1;for (auto item : fac) id[tmp]*=item;
    if (!int(table[id[tmp]].size())) table[id[tmp]]=fac;
}

int cnt[MAXN+48],seq[MAXN+48],stot;

unordered_map<int,int> num[MAXN+48];

int t[MAXN+48],tcnt[MAXN+48],ttot;

int Get(int x,int y)
{
    int res=1,sz1=int(table[x].size()),sz2=int(table[y].size());
    for (int k1=0,k2=0;k1<sz1 || k2<sz2;)
    {
        if (k1<sz1 && k2<sz2 && table[x][k1]==table[y][k2]) k1++,k2++;  
        if (k1<sz1 && (k2>=sz2 || (k2<sz2 && table[x][k1]<table[y][k2])))
        {
            res*=table[x][k1];
            k1++;
        }
        if (k2<sz2 && (k1>=sz1 || (k1<sz1 && table[y][k2]<table[x][k1])))
        {
            res*=table[y][k2];
            k2++;
        }
    }
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    sieve();
    rep(i,2,MAXN) init(i);
    long long ans;
    while (ca--)
    {
        memset(cnt,0,sizeof(cnt));
        rep(i,1,MAXN) num[i].clear();
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),cnt[id[a[i]]]++;
        stot=0;ans=0;
        rep(i,1,n) if (big[a[i]]<30) seq[++stot]=a[i];
        else
            num[big[a[i]]][id[a[i]]]++;
        REP(i,MAXN,31) if (int(num[i].size()))
        {
            ttot=0;
            for (unordered_map<int,int>::iterator iter=num[i].begin();iter!=num[i].end();iter++)
            {
                t[++ttot]=iter->first;
                tcnt[ttot]=iter->second;
                cnt[id[t[ttot]]]-=tcnt[ttot];
            }
            rep(j,1,ttot) ans+=1ll*tcnt[j]*(tcnt[j]-1)/2*cnt[1];
            rep(j,1,ttot) rep(k,j+1,ttot)
            {
                int tar=Get(t[j],t[k]);
                ans+=1ll*tcnt[j]*tcnt[k]*cnt[tar];
            }
        }
    }
}