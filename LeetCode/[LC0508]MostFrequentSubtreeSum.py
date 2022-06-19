class Solution:
    def findFrequentTreeSum(self, root: TreeNode) -> List[int]:
        cc = defaultdict(int)
        def dfs(cur):
            if cur is None: return 0
            s = cur.val + dfs(cur.left) + dfs(cur.right)
            cc[s] += 1
            return s
        dfs(root)
        return [s for s, cnt in cc.items() if cnt == max(cc.values())]