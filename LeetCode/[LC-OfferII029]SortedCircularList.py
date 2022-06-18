class Solution:
    def insert(self, head: 'Node', insertVal: int) -> 'Node':
        if head == None:
            head = Node(insertVal)
            head.next = head
            return head
        rt = head
        while head.val <= head.next.val and head.next != rt: head = head.next
        if not head.next.val < insertVal < head.val:
            head.next = Node(insertVal, head.next)
            return rt
        while head.next.val < insertVal: head = head.next
        head.next = Node(insertVal, head.next)
        return rt