#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int k,X,len;
string s;

void doit(int X)
{
    if (X==0) return;
    int w=X%k;doit(X/k);
    string ss="0";ss[0]+=10-k+w;s+=ss;
}

int main ()
{
    ios::sync_with_stdio(false);
    int ca;cin>>ca;
    while (ca--)
    {
        cin>>k>>X;long long pw=k;
        len=1;while (X>pw) X-=pw,len++,pw*=k;
        X--;s="";doit(X);
        int delta=len-int(s.size());string ss="0";ss[0]+=10-k;
        while (delta--) s=ss+s;
        cout<<s<<endl;
    }
    return 0;
}