class Solution:
    def isUnivalTree(self, root: TreeNode) -> bool:
        val = []
        def dfs(cur: TreeNode):
            if cur is None: return
            val.append(cur.val)
            dfs(cur.left)
            dfs(cur.right)
        dfs(root)
        return len(set(val)) == 1