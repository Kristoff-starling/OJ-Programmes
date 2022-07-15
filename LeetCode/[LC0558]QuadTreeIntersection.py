class Solution:
    def intersect(self, quadTree1: 'Node', quadTree2: 'Node') -> 'Node':
        def merge(root1: 'Node', root2: 'Node') -> 'Node':
            if (root1.isLeaf and root1.val == 1) or (root2.isLeaf and root2.val == 0): return root1
            if (root1.isLeaf and root1.val == 0) or (root2.isLeaf and root2.val == 1): return root2
            
            r1 = merge(root1.topLeft, root2.topLeft)
            r2 = merge(root1.topRight, root2.topRight)
            r3 = merge(root1.bottomLeft, root2.bottomLeft)
            r4 = merge(root1.bottomRight, root2.bottomRight)
            if r1.isLeaf and r2.isLeaf and r3.isLeaf and r4.isLeaf and r1.val == r2.val == r3.val == r4.val: return r1
            return Node(None, False, r1, r2, r3, r4)
        return merge(quadTree1, quadTree2)