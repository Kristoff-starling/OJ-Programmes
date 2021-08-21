#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int a,b,c,n;
int ord[4];

char s[4][1048];

struct node
{
    int val,id;
    bool operator < (const node &other) const {return val>other.val;}
}A[4];

int main ()
{
    rep(i,1,3) scanf("%d",&A[i].val),A[i].id=i;scanf("%d",&n);
    sort(A+1,A+4);
    if (A[1].val+A[2].val-A[3].val>n) {puts("NO");return 0;}
    rep(i,1,A[1].val) s[1][i]=s[2][i]='a';
    rep(i,A[1].val+1,n) s[1][i]='b',s[2][i]='c';
    rep(i,1,A[1].val-A[3].val) s[3][i]='d';
    rep(i,A[1].val-A[3].val+1,A[1].val) s[3][i]='a';
    rep(i,A[1].val+1,A[1].val+A[2].val-A[3].val) s[3][i]='b';
    rep(i,A[1].val+A[2].val-A[3].val+1,n) s[3][i]='d';
    int ord[4];
    rep(i,1,3)
    {
        if (A[i].id==1) ord[4-i]=3;
        if (A[i].id==2) ord[4-i]=1;
        if (A[i].id==3) ord[4-i]=2;
    }
    rep(i,1,3)
    {
        int pos;
        rep(j,1,3) if (ord[j]==i) pos=j;
        rep(j,1,n) printf("%c",s[pos][j]);
        puts("");
    }
    return 0;
}