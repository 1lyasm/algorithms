from balance_bst import *

def main():
    solution = Solution()
    root = TreeNode(1, None,
              TreeNode(2, None,
                TreeNode(3, None,
                  TreeNode(4, None,
                    None))))
    
    def test():
      newRoot = solution.balanceBST(root)
      print(newRoot.val)
      print(newRoot.right.val)
      print(newRoot.left.val)
      print(newRoot.left.right.val)

    test()

main()
