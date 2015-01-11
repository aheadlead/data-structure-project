#include <algorithm>
#include <cassert>
#include <stack>

using std::max;
using std::swap;
using std::stack;

#include "avltree.h"

AVLTree::AVLTree() {
    root = NULL;
}

AVLTree::~AVLTree() {
    if (NULL != root) {
        delete root;
        root = NULL;
    }
}

void AVLTree::insert(int value) {
    if (NULL == this->root) {
        this->root = new AVLNode(value);
        if (NULL == this->root) {
            throw OutOfMemory();
        }
    }
    else {
        AVLNode::insert(&this->root, value);
    }
}

AVLNode::AVLNode() {
    this->value = 0;
    this->height = 1;
    this->left = NULL;
    this->right = NULL;
    return; 
}

AVLNode::AVLNode(int value) {
    this->value = value;
    this->height = 1;
    this->left = NULL;
    this->right = NULL;
    return;
}

AVLNode::~AVLNode() {
    if (NULL != this->left) {
        delete this->left;
        this->left = NULL;
    }
    if (NULL != this->right) {
        delete this->right;
        this->right = NULL;
    }
}

void AVLNode::leftRotate() {
    // 变量名的来源是 http://zh.wikipedia.org/wiki/AVL树
    AVLNode * root = this;
    AVLNode * pivot = this->right;

    swap(root->value, pivot->value);
    root->right = pivot->right;
    pivot->right = pivot->left;
    pivot->left = root->left;
    root->left = pivot;

    pivot->height = 1 + max(
            AVLNode::getHeight(pivot->left),
            AVLNode::getHeight(pivot->right));
    root->height = 1 + max(
            AVLNode::getHeight(root->left),
            AVLNode::getHeight(root->right));
}
void AVLNode::rightRotate() {
    // 变量名的来源是 http://zh.wikipedia.org/wiki/AVL树
    AVLNode * root = this;
    AVLNode * pivot = this->left;

    swap(root->value, pivot->value);
    root->left = pivot->left;
    pivot->left = pivot->right;
    pivot->right = root->right;
    root->right = pivot;

    pivot->height = 1 + max(
            AVLNode::getHeight(pivot->left),
            AVLNode::getHeight(pivot->right));
    root->height = 1 + max(
            AVLNode::getHeight(root->left),
            AVLNode::getHeight(root->right));
}

void AVLNode::insert(AVLNode ** ptree, int value) { // static 
    AVLNode * tree;
    // 因为可能会对一个空指针进行插入操作，所以函数是 static 的
    if (NULL == *ptree) { 
        // 插入
        *ptree = new AVLNode(value);
        if (NULL == *ptree) {
            throw OutOfMemory();
        }
        return;
    }
    else {
        tree = *ptree;
        // 寻找
        if (value < tree->value) {
            AVLNode::insert(&tree->left, value);
        }
        else {
            AVLNode::insert(&tree->right, value);
        }
    }

    tree->height = 1 + max(
            AVLNode::getHeight(tree->left), 
            AVLNode::getHeight(tree->right));

    tree->maintain();
    
    return;
}

int AVLNode::remove(int value) {
    // 删除算法参考了 http://blog.csdn.net/minimicall/article/details/6496109
    // 中文维基百科简直坑爹，也有不靠谱的时候。
    if (value == this->value) {
        if (NULL == this->left && NULL == this->right) {
            /*  叶子结点（左右子树空）          
             *
             *           father                father
             *          /      \              /      \
             *      [this]    {A!}   =====> NULL    {A!}
             *     /      \
             *   NULL    NULL           
             *
             *  图示
             *   father 表示一个节点。
             *   [this] 表示**当前**的节点。（方括号用于强调。）
             *   {A!} 表示一颗根节点为 A 的子树（可能是空树，即 NULL ）。
             *  高度变化
             *   这种情况下，子树 {[this]} 的高度必减一。
             */
            delete this;
            return -1;
        }
        if (NULL == this->left && NULL != this->right) {
            /*  左子树空，右子树非空
             *
             *           father               father
             *          /      \             /      \
             *      [this]    {C}   =====>  {B}    {C}
             *     /      \
             *   NULL    {B}
             *
             *  图示
             *   {B} 表示一颗根节点为 B 的非空子树。
             *  说明
             *   这里的非空子树 B ，只可能为一个节点。假设 B 不止一个节点，则非
             *   空子树 B 的高度必大于 1 （参见二叉树深度的下界）。因为 [this]
             *   的左子树的高度为 0 。所以这与 AVL 树的条件矛盾，因为 [this] 节
             *   点的平衡因子必小于 -1 。
             *  高度变化
             *   这种情况下，子树 {[this]} 的高度必减一。
             *   
             */
            this->value = this->right->value;
            this->right = NULL;
            return -1;
        }
        if (NULL != this->left) {
            /*  左子树非空
             *
             *                     father               father
             *                    /      \             /      \
             *                [this]    {A}   =====>  {B}    {A}
             *               /      \
             *          {shabi}    {B!}    
             *     
             *  图示
             *   {shabi} 表示一颗根节点为 shabi 的非空子树。（这里特别说明一下
             *   ， 233 。）
             *  说明
             *   这里是要删除 [this] 节点。欲删除 [this] 的话，需要找一个最大的
             *   比 [this] 节点的小的节点来替换（这里说的是节点的 value ）。于
             *   是在 {shabi} 中寻找。根据二叉查找树的性质，当子树 {shabi} 的节
             *   点个数不止一个时，子树 {shabi} 中最大的节点一定在子树 {shabi}
             *   的右子树当中。递归的使用这个性质，就知道要找的这个节点最终可
             *   以归约为这二种情况：
             *
             *                     father                      father  
             *                    /      \                    /      \
             *                [this]    {A}               [this]    {A}
             *               /      \                    /      \
             *            shabi    {B!}               shabi     {B}
             *           /     \                     /     \
             *         NULL   NULL                 ...     ...         
             *                                               \
             *                                                V
             *                                               / \
             *                                            {C!} NULL    
             *
             *   对于左边的情况容易处理，而且也可以按照右边的处理方式处理。下面
             *   描述对于右边情况的处理。
             *
             *   令节点 V 则是子树 {shabi} 中最大的节点。{C!} 是一个子树，易证
             *   节点数量只能为 0 或 1 ，否则不满足 AVL 树的性质。
             *
             *   首先把 [this] 节点的 value 替换为 V 节点的 value ，然后删除 V
             *   节点。删除 V 节点时可调用 V 节点的 remove() 方法。删除 V 节点
             *   时，只有以下两种情况：
             *        
             *      1)  ...          2)  ...
             *            \                \
             *             V                V           P.S.这里只关注树的下部
             *            / \              / \              （路人：好羞耻。）
             *         NULL NULL          W  NULL
             *                           / \
             *                        NULL NULL
             *
             *   情况 1 即为叶子节点，可以直接去掉。
             *
             *   然而，情况 2 就是本情况（左子树非空），对于在 remove 节点 V 时
             *   遇到情况 2，经过一个 remove() 方法后，会变为这样：
             *           
             *           ...
             *             \
             *              W
             *             / \
             *          NULL NULL
             *
             *   这样就成功的删除了节点 V 。
             *
             *   由于节点 [this] 的 value 被原节点 V 的 value 所替换，实际上也就
             *   相当于节点 [this] 被删除，而节点 V 并没有被删除。
             *
             *   这样就完成了一次删除的操作。
             *  高度变化
             *   
             *
             */
            AVLNode * shabi = this->left;
            // 找到 shabi 中具有最大的的值的节点，存于 shabi 中
            for (; NULL != shabi->right; shabi=shabi->right); 
            this->value = shabi->value;
            // 删除 shabi
            shabi->remove(shabi->value);
        }
    }
    else {
        if (this->value > value) {
        }
        else {
        }
    }
}

AVLNode * AVLNode::__remove()  {
    AVLNode * ret;
    if (NULL != this->left && NULL != this->right) {
        // 当具有双孩子的时候
        
        // 寻找当前节点的左子树的最大值，
        stack<AVLNode * > s;
        s.push(this->left);
        for (; ; ) {
            if (NULL != s.top()->right) {
                s.push(s.top()->right);
            }
            else {
                break;
            }
        }

        ret = NULL; // TODO
    }
    else {
        // 当具有不具有双孩子的时候
        if (NULL != this->left) {
            // 只有左孩子
            ret = this->left;
        }
        else if (NULL != this->right) {
            // 只有右孩子
            ret = this->right;
        }
        else {
            // 没有孩子
            ret = NULL;
        }
    }
    delete this;
    return ret;
}

void AVLNode::maintain() {
    // 计算左右子树的高度
    int heightDifference = 
        AVLNode::getHeight(this->left) - AVLNode::getHeight(this->right);

    switch (heightDifference) {
        case 2:
            // L 情况
            heightDifference = AVLNode::getHeight(this->left->left) -
                AVLNode::getHeight(this->left->right);
            switch (heightDifference) {
                case 1:
                    // LL 情况
                    this->rightRotate();
                    break;
                case -1:
                    // LR 情况
                    this->left->leftRotate();
                    this->rightRotate();
                    break;
                default:
                    assert("impossible" == 0);
            }
            break;
        case -2:
            // R 情况
            heightDifference = AVLNode::getHeight(this->right->left) -
                AVLNode::getHeight(this->right->right);
            switch (heightDifference) {
                case 1:
                    // RL 情况
                    this->right->rightRotate();
                    this->leftRotate();
                    break;
                case -1:
                    // RR 情况
                    this->leftRotate();
                    break;
                default:
                    assert("impossible" == 0);
            }
    }
}

inline size_t AVLNode::getHeight(AVLNode * tree) {
    if (NULL == tree) {
        return 0;
    }
    else {
        return tree->height;
    }
}
