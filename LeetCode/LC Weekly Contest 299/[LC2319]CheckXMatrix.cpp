class Solution {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = int(grid.size());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == j && grid[i][j] == 0) return false;
                if (i + j == n-1 && grid[i][j] == 0) return false;
                if (!(i == j || i + j == n-1) && grid[i][j] != 0) return false;
            }
        return true;
    }
};