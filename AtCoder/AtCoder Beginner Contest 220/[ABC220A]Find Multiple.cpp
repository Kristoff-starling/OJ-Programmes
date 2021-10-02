#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int main ()
{
    int a,b,c;
    cin>>a>>b>>c;
    rep(i,a,b) if (i%c==0) {cout<<i<<endl;return 0;}
    cout<<-1<<endl;return 0;
}