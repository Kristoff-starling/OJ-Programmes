class Solution:
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:
        self.ans = 0
        def dfs(self, cur, s):
            s = s * 2 + cur.val
            if cur.left is None and cur.right is None:
                self.ans += s
                return
            if cur.left != None: dfs(self, cur.left, s)
            if cur.right != None: dfs(self, cur.right, s)
        dfs(self, root, 0)
        return self.ans