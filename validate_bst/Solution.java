class Test {
  public static void main(String[] args) {
    ;
  }
}

class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;

  TreeNode() {
  }

  TreeNode(int val) {
    this.val = val;
  }

  TreeNode(int val, TreeNode left, TreeNode right) {
    this.val = val;
    this.left = left;
    this.right = right;
  }
}

class Solution {
  public boolean isValidSubBST(TreeNode root, long min, long max) {
    if (root == null) {
      return true;
    }
    if (root.val <= min || root.val >= max) {
      return false;
    }
    return isValidSubBST(root.left, min, root.val) &&
        isValidSubBST(root.right, root.val, max);
  }

  public boolean isValidBST(TreeNode root) {
    return isValidSubBST(root, (long) Integer.MIN_VALUE - 1L,
        (long) Integer.MAX_VALUE + 1L);
  }
}
