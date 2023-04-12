#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "construct_binary_tree.h"

static int find(int *arr, int len, int target) {
    int i;
    for (i = 0; i < len && arr[i] != target; ++i);
    return i;
}

static struct TreeNode *buildSubtree(int *pre, int preLen, int *in,
    int inLen, int preInd) {
    struct TreeNode *root;
    int inRootPos = -1;
    if (inLen < 1) {
        return 0;
    }
    for (; ; ++preInd) {
        if (preInd >= preLen) {
            return 0;
        }
        inRootPos = find(in, inLen, pre[preInd]);
        if (inRootPos != inLen) {
            break;
        }
    }
    root = calloc(1, sizeof(struct TreeNode));
    root->val = pre[preInd];
    root->left = buildSubtree(pre, preLen, in, inRootPos, preInd + 1);
    root->right = buildSubtree(pre, preLen,
        &in[inRootPos + 1], inLen - inRootPos - 1, preInd + 1);
    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder,
    int inorderSize) {
    return buildSubtree(preorder, preorderSize,
        inorder, inorderSize, 0);
}
