from llst import LList, Node
import _ctypes

def di(obj_id): return _ctypes.PyObj_FromPtr(obj_id)

def reorder(L):
    n = L.size // 2
    rgt = L.get_at(n - 1)
    fpart_last_ptr = id(rgt)
    rgt = rgt.next
    for i in range(n):
        mdl = rgt
        rgt = rgt.next
        mdl.next = lft if (i > 0) else None
        lft = mdl
    di(fpart_last_ptr).next = mdl
    return

def main():
    L = LList()
    L.build([1, 2, 3, 4, 5, 6, 7, 8])
    L.print()
    reorder(L)
    L.print()

    L = LList()
    L.build([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    L.print()
    reorder(L)
    L.print()

    L = LList()
    L.build(["Il", "ya", "ss", "so", "na", "se", "id", "mo"])
    L.print()
    reorder(L)
    L.print()

if __name__ == "__main__":
    main()