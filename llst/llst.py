class LList:
    def __init__(self):
        self.head = None
        self.size = 0

    def print(self):
        node = self.head
        print(node.item, end=" ")
        while node.next is not None:
            node = node.next
            print(node.item, end=" ")
        print("\n")
        
    def build(self, lst):
        self.head = Node()
        self.head.item = lst[0]
        self.size += 1
        cur, nxt = self.head, None
        for elem in lst[1:]:
            nxt = Node()
            nxt.item = elem
            cur.next = nxt
            cur = nxt
            self.size += 1
    
    def get_at(self, idx):
        tmp = self.head
        for i in range(idx):
            tmp = tmp.next
        return tmp
    
class Node:
    def __init__(self):
        self.item = None
        self.next = None

def main():
    lst = [1, 2, 3, 4, 5, 6, 7]
    L = LList()
    L.build(lst)
    L.print()
    print("\n", L.size)
    
if __name__ == "__main__":
    main()
