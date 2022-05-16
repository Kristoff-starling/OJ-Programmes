class Solution:
    def inorderSuccessor(self, root: TreeNode, p: TreeNode) -> TreeNode:
        if p.right is None:
            last, cur = None, root
            while cur != p:
                if cur.val >= p.val: last = cur
                if cur.val >= p.val: cur = cur.left
                else: cur = cur.right
            return last
        p = p.right
        while p.left != None: p = p.left
        return p