class Solution {
    int d[100048];
    int q[2][100048], cnt[2];
    bool exist[100048];
    vector<int> v[100048];
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < n; i++) d[i] = 0, v[i].clear(), exist[i] = true;
        for (int i = 0; i < int(edges.size()); i++)
            d[edges[i][0]]++, d[edges[i][1]]++, v[edges[i][0]].push_back(edges[i][1]), v[edges[i][1]].push_back(edges[i][0]);
        int cur = 0, nxt = 1; cnt[0] = cnt[1] = 0; int cc = n;
        for (int i = 0; i < n; i++) if (d[i] == 1) q[cur][++cnt[cur]] = i;
        while (cc > 2)
        {
            cnt[nxt] = 0;
            for (int i = 1; i <= cnt[cur]; i++)
            {
                int node = q[cur][i]; exist[node] = false; cc--;
                for (auto nei : v[node]) if (exist[nei])
                {
                    d[nei]--;
                    if (d[nei] == 1) q[nxt][++cnt[nxt]] = nei;
                }
            }
            cur ^= 1; nxt ^= 1;
        }
        vector<int> ans; ans.clear();
        for (int i = 0; i < n; i++) if (exist[i]) ans.push_back(i);
        return ans;
    }
};