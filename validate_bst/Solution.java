import java.util.Stack;

class Test {
  public static void main(String[] args) { ; }
}

class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;

  TreeNode() {}

  TreeNode(int val) { this.val = val; }

  TreeNode(int val, TreeNode left, TreeNode right) {
    this.val = val;
    this.left = left;
    this.right = right;
  }
}

class Solution {
  public boolean isValidBST(TreeNode root) {
    var stack = new Stack<TreeNode>();
    var cur = root;
    TreeNode prev = null;
    while (cur != null || !stack.isEmpty()) {
      while (cur != null) {
        stack.push(cur);
        cur = cur.left;
      }
      cur = stack.pop();
      if (prev != null && cur.val <= prev.val) {
        return false;
      }
      prev = cur;
      cur = cur.right;
    }
    return true;
  }
}
