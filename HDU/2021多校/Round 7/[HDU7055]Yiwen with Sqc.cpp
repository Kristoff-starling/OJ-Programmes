#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;
const int MOD=998244353;

char s[MAXN+48];
int I[48],II[48];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Sub(int &x,int y) {x=sub(x-y);}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s",s+1);int n=strlen(s+1);
        rep(i,1,26) I[i]=II[i]=0;
        int ans=0,sss=0;
        rep(i,1,n)
        {
            int ch=s[i]-'a'+1;
            Sub(sss,II[ch]);
            Add(II[ch],add(I[ch]+I[ch]+i));Add(I[ch],i);
            Add(sss,II[ch]);Add(ans,sss);
        }
        printf("%d\n",ans);
    }
    return 0;
}