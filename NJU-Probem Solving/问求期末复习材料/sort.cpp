#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MAXN=1e5;

int n;
int a[MAXN+48];

vector<int> v1,v2;
int split(int A[],int l,int r)
{
    swap(A[l],A[(l+r)>>1]);
    v1.clear();v2.clear();int tmp=a[l];
    rep(i,l+1,r)
    {
        int op=(rand()&1);if (a[i]<tmp) op=0;if (a[i]>tmp) op=1;
        if (!op) v1.pb(a[i]); else v2.pb(a[i]);
    }
    int pt=l;for (auto item : v1) A[pt++]=item;
    int res=pt;A[pt++]=tmp;for (auto item : v2) A[pt++]=item;
    return res;
}

void sort(int A[],int l,int r)
{
    if (l>=r) return;
    int pos=split(A,l,r);sort(A,l,pos-1);sort(A,pos+1,r);
}

int main ()
{
    srand(time(NULL));
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    random_shuffle(a+1,a+n+1);
    sort(a,1,n);rep(i,1,n) printf("%d ",a[i]);puts("");
    return 0;
}