#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#define Pair pair<int, int>
#define mp make_pair
using namespace std;

const int MAXN = 2e5 + 10;

int n, m;
int l[MAXN], r[MAXN];
vector<int> R[MAXN];

priority_queue<Pair> q;

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", l + i, r + i);
        R[l[i]].push_back(r[i]);
        q.push(mp(-r[i], l[i]));
    }
    long long ans = 0;
    for (int i = 1; i <= m; i++)
    {
        while (!q.empty() && q.top().second < i)
            q.pop();
        int maxr = q.empty() ? m : -q.top().first - 1;
        ans += maxr - i + 1;
    }
    printf("%lld\n", ans);
    return 0;
}