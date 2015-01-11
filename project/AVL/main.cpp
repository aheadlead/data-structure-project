#include <iostream>
#include <vector>

#include "avltree.h"

using namespace std;

int d[]={7, 5, 4, 3, 1};

void printtree(AVLNode * tree, int level=0)
{
    if (NULL == tree) return;
    for (int i=0; i<level; ++i)
        printf("  "), fflush(stdout);
    printf("{ value=%d, left=%p, right=%p, height=%lu }\n", tree->value, tree->left, tree->right, tree->height);
    fflush(stdout);
    printtree(tree->left, level+1);
    printtree(tree->right, level+1);
    return;
}

int main() {
    AVLTree tree;
    for (int i=0; i<5; ++i) {
        tree.insert(d[i]);
        printtree(tree.getRoot());
        printf("---------------------------\n");
    }
    return 0;
}
