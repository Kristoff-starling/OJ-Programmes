class Solution:
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        def findnode(fa: TreeNode, cur: TreeNode, lr: int, val: int):
            if cur is None: return (None, None, None)
            if cur.val == val: return (fa, cur, lr)
            if cur.val < val: return findnode(cur, cur.right, 1, val)
            else: return findnode(cur, cur.left, 0, val)
        def merge(L: TreeNode, R: TreeNode):
            if L is None: return R
            if R is None: return L
            if random.randint(0, 100) % 2 == 1:
                L.right = merge(L.right, R)
                return L
            else:
                R.left = merge(L, R.left)
                return R

        fa, node, lr = findnode(None, root, 0, key)
        if node is None: return root
        if fa is None: return merge(node.left, node.right)
        elif lr == 0: fa.left = merge(node.left, node.right)
        else: fa.right = merge(node.left, node.right)
        return root