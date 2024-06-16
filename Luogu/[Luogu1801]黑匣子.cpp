#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;

int n, m;
int a[MAXN];

std::priority_queue<int> q1, q2;

int main ()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    int pos, cur = 0;
    while (m--)
    {
        std::cin >> pos;
        while (cur < pos)
        {
            ++cur;
            if (!q1.empty() && q1.top() > a[cur])
            {
                q2.push(-q1.top());
                q1.pop();
                q1.push(a[cur]);
            }
            else
                q2.push(-a[cur]);
        }
        q1.push(-q2.top());
        q2.pop();
        std::cout << q1.top() << '\n';
    }
    return 0;
}