class Solution:
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        q, ans = [root], 0
        while q:
            cur = q.pop(0)
            ans = cur.val
            if cur.right != None: q.append(cur.right)
            if cur.left != None: q.append(cur.left)
        return ans