class Solution:
  def computeHeight(self, root):
    if not root:
      return -1
    root.height = max(self.computeHeight(root.left), 
      self.computeHeight(root.right)) + 1
    return root.height
  
  def getHeight(self, root):
    if not root:
      return -1
    return root.height

  def getSkew(self, root):
    if not root:
      return 0
    return self.getHeight(root.right) - \
      self.getHeight(root.left)

  def rotL(self, root):
    oldLeft = root.right.left
    newRoot = root.right
    root.right.left = root
    root = newRoot
    root.left.right = oldLeft
    return root

  def rotR(self, root):
    oldRight = root.left.right
    newRoot = root.left
    root.left.right = root
    root = newRoot
    root.right.left = oldRight
    return root
  
  def balance(self, root):
    if not root:
      return None
    self.computeHeight(root)
    root.left = self.balance(root.left)
    root.right = self.balance(root.right)
    if self.getSkew(root.right) <= -1:
      root.right = self.rotR(root.right)
      root.right = self.balance(root.right)
    if self.getSkew(root.left) >= 1:
      root.left = self.rotL(root.left)
      root.left = self.balance(root.left)
    if self.getSkew(root) >= 2:
      root = self.rotL(root)
      root = self.balance(root)
    if self.getSkew(root) <= -2:
      root = self.rotR(root)
      root = self.balance(root)
    return root

  def balanceBST(self, root: TreeNode) -> TreeNode:
    return self.balance(root)
  