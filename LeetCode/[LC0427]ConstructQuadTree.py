class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        def dfs(l1, r1, l2, r2):
            if all(grid[i][j] == grid[l1][l2] for i in range(l1, r1) for j in range(l2, r2)):
                return Node(grid[l1][l2], True)
            else:
                return Node(
                    1,
                    False,
                    dfs(l1, (l1 + r1) >> 1, l2, (l2 + r2) >> 1),
                    dfs(l1, (l1 + r1) >> 1, (l2 + r2) >> 1, r2),
                    dfs((l1 + r1) >> 1, r1, l2, (l2 + r2) >> 1),
                    dfs((l1 + r1) >> 1, r1, (l2 + r2) >> 1, r2)
                )
        return dfs(0, len(grid), 0, len(grid[0]))