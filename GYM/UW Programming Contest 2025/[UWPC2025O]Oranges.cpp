#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 3e5 + 10;

template<typename T> inline T get_min(T x, T y) { return x > y ? y : x; }
template<typename T> inline T get_max(T x, T y) { return x > y ? x : y; }
template<typename T> inline void check_max(T &x, T y) { x = (x > y ? x : y); }
template<typename T> inline void check_min(T &x, T y) { x = (x > y ? y : x); }

int n, val[MAXN];
vector<int> v[MAXN];

int fa[MAXN], sz[MAXN];
int map_id[MAXN];
map<ll, int> m[MAXN];
ll sum[MAXN];

void dfs(int cur, int father)
{
    fa[cur] = father;
    for (auto y : v[cur])
        if (y != father)
        {
            dfs(y, cur);
            sz[cur] += sz[y]; 
            sum[cur] += sum[y];
        }
    sz[cur]++;
    sum[cur] += val[cur];
}

ll ans = 1e18;
map<ll, int> upper_m;

void map_add(map<ll, int> *m, ll val)
{
    (*m)[val]++;
}

void map_remove(map<ll, int> *m, ll val)
{
    if ((*m)[val] == 1)
        (*m).erase(val);
    else
        (*m)[val]--;
}

void update_ans(ll sum1, ll sum2, ll sum3)
{
    check_min(ans, get_max(get_max(sum1, sum2), sum3) - get_min(get_min(sum1, sum2), sum3));
}

void find_and_update(map<ll, int> *m, ll target, ll sum1, int mode)
{
    auto iter = (*m).lower_bound(target);
    if (iter != (*m).end())
    {
        ll sum2 = (mode == 0) ? iter->first - sum1 : iter->first;
        ll sum3 = sum[1] - sum1 - sum2;
        update_ans(sum1, sum2, sum3);
    }
    if (iter != (*m).begin())
    {
        iter--;
        ll sum2 = (mode == 0) ? iter->first - sum1 : iter->first;
        ll sum3 = sum[1] - sum1 - sum2;
        update_ans(sum1, sum2, sum3);
    }
}

void dfs_upper(int cur, int father)
{
    ll target = (sum[1] - sum[cur] + 1) / 2 + sum[cur];
    find_and_update(&upper_m, target, sum[cur], 0);
    if (cur != 1)
        map_add(&upper_m, sum[cur]);
    for (auto y : v[cur])
        if (y != father)
            dfs_upper(y, cur);
    if (cur != 1)
        map_remove(&upper_m, sum[cur]);
}

void dfs2(int cur, int father)
{
    for (auto y : v[cur])
        if (y != father)
            dfs2(y, cur);
    if (v[cur].size() == 1)
        // no children
        map_id[cur] = cur;
    else
    {
        map_id[cur] = map_id[v[cur][1]]; // tht biggest subtree
        for (int i = 2; i < int(v[cur].size()); i++)
        {
            int to_id = map_id[v[cur][i]];
            for (auto iter = m[to_id].begin(); iter != m[to_id].end(); iter++)
            {
                ll target = (sum[1] - iter->first + 1) / 2;
                find_and_update(&m[map_id[cur]], target, iter->first, 1);
            }
            for (auto iter = m[to_id].begin(); iter != m[to_id].end(); iter++)
                map_add(&m[map_id[cur]], iter->first);
        }
    }
    map_add(&m[map_id[cur]], sum[cur]);
}

int main ()
{
    // freopen("o.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", val + i);
    int x, y;
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    v[1].push_back(0); sz[0] = n + 1;
    for (int i = 1; i <= n; i++)
        sort(v[i].begin(), v[i].end(), [](const int &x, const int &y){ return sz[x] > sz[y]; });
    // case 1: tree_2 contains tree_1
    dfs_upper(1, 0);
    // case 2: disjoint(tree_1, tree_2)
    dfs2(1, 0);
    printf("%lld\n", ans);
    return 0;
}