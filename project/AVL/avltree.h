#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <exception>

class AVLException : public std::exception { };

class ElementNotFound : public AVLException { };
class EmptyTree : public AVLException { };
class OutOfMemory : public AVLException { };

class AVLTree;
class AVLNode;

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void insert(int value);
        int remove(int value);
        AVLNode * find();
        AVLNode * upper_bound(int value);
        AVLNode * lower_bound(int value);
        AVLNode * getRoot() { return root; } // only for debug
    private:
        AVLNode * root;
};

class AVLNode {
    public:
        AVLNode();
        AVLNode(int value);
        ~AVLNode();
        static void insert(AVLNode ** ptree, int value);
        // 移除本子树内值为 value 的节点，返回树深度变化情况。
        // 遇到多个相同 value 的节点的情况时，只移除一个。
        int remove(int value);
        // 寻找特定值的节点，返回其地址
        AVLNode * find(int value);
        int value;
        AVLNode * left;
        AVLNode * right;
        size_t height;
    private:
        // 将本节点移除，并返回其父节点应该指向的地址
        AVLNode * __remove();
        void leftRotate();
        void rightRotate();
        // 维护本节点的 AVL 性质，要求其子树都具有 AVL 性质
        void maintain();
        static size_t getHeight(AVLNode * tree);
};

#endif // __AVLTREE_H__
