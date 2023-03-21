struct Node {
    Value: i32,
    NextPointer: Link
}

struct LinkedList {
    Head: Link
}

enum Link {
    Empty,
    NonEmpty(Box<Node>)
}

impl LinkedList {
    fn new() -> Self {
        Self{Head: Link::Empty}
    }

    fn pushFront(&mut self, Value: i32) {
        let NewNode = Box::new(Node{Value: Value,
            NextPointer: std::mem::replace(&mut self.Head, Link::Empty)});
        self.Head = Link::NonEmpty(NewNode);
    }

    fn popFront(&mut self) -> Option<i32> {
        match std::mem::replace(&mut self.Head, Link::Empty) {
            Link::Empty => None,
            Link::NonEmpty(Node) => {
                self.Head = Node.NextPointer;
                Some(Node.Value)
            }        
        }
    }
}

#[cfg(test)]
mod LinkedListTest {
    use super::LinkedList;

    #[test]
    fn test() {
        let mut MyList = LinkedList::new();
        assert_eq!(MyList.popFront(), None);
        MyList.pushFront(1);
        MyList.pushFront(2);
        MyList.pushFront(3);
        assert_eq!(MyList.popFront(), Some(3));
        assert_eq!(MyList.popFront(), Some(2));
        MyList.pushFront(4);
        MyList.pushFront(5);
        assert_eq!(MyList.popFront(), Some(5));
        assert_eq!(MyList.popFront(), Some(4));
        assert_eq!(MyList.popFront(), Some(1));
        assert_eq!(MyList.popFront(), None);
    }
}
