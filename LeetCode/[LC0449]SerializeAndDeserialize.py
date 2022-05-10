class Codec:
    def serialize(self, root: TreeNode) -> str:
        ret = []
        def dfs(root: TreeNode):
            if root is None: return
            ret.append(root.val)
            dfs(root.left); dfs(root.right)
            
        dfs(root)
        return ','.join(map(str, ret))

    def deserialize(self, data: str) -> TreeNode:
        if not data: return None

        def construct(pre, mid):
            if not pre: return None
            rt = pre[0]
            i = mid.index(rt)
            root = TreeNode(rt)
            root.left = construct(pre[1:i+1], mid[:i])
            root.right = construct(pre[i+1:], mid[i+1:])
            return root

        pre = list(map(int, data.split(',')))
        mid = sorted(pre)
        return construct(pre, mid)