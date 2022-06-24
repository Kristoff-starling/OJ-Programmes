class Solution:
    def largestValues(self, root: Optional[TreeNode]) -> List[int]:
        if root is None: return []
        q = [(root, 0)]
        ans = [root.val]
        while q:
            cur, depth = q.pop(0)
            if cur is None: continue
            if len(ans) <= depth: ans.append(cur.val)
            ans[depth] = max(ans[depth], cur.val)
            q.append((cur.left, depth + 1))
            q.append((cur.right, depth + 1))
        return ans