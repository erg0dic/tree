#ifndef TREENODE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TREENODE_H
#include "treenode.h"
#include <vector>
#include <iostream>
class BinaryTree {

    public:
        int tree_height;
        treenode *root;
        bool is_avl;
        friend class treenode;
        BinaryTree(int);
        ~BinaryTree() {};//{deletetree(root);};
        int treesize(treenode *r);
        int treeheight(treenode *r, int height);
        treenode* search(treenode* x, int key);
        treenode* get_root() {if (root != nullptr) {return root;} else {return nullptr;}}
        treenode* min(treenode* x);
        treenode* max(treenode* x);
        treenode* successor(treenode* treenoderef );
        void in_order_traversal(treenode* noderef );
        treenode* delete_value(treenode *r, int val);
        treenode* insert(treenode *r, treenode *n); // probably needs opt later
        // recursively delete all nodes/subtrees out of t
        treenode * deletetree(treenode *r);
        void prettyprint();
        treenode * clone_subtree(const treenode *t);
        void transplant(treenode *u, treenode *v);
        void tree_delete(int z);
        treenode* find_min(); // <-> peak, is O(logn)

        // compare, reduce, build, verify, eval, delete
};

class Heap : public BinaryTree {
    public:
        Heap(int x=0) : BinaryTree(x) {};
        int extract_min(treenode *r); // O(logn)
        void build(std::vector<treenode>& nodes);
        ~Heap() {};

};

class AVL : public BinaryTree {
    public:
        AVL(int);
        // int extract_min(treenode *r); // O(logn)
        ~AVL() {};
        void rebalance(treenode *r, treenode *root);
        treenode* insert_new(int val);
        void delete_val(treenode *r, int val);
        treenode* extract_min();
        // int extract_min(treenode *r);
        static void update_height(treenode *r);
        static void fixtree(treenode *r, treenode *root);
        static int BF(treenode *r); // balance factor
        static void update_node_height(treenode *u);
        static void left_rotate(treenode *x, treenode *root);
        static void right_rotate(treenode *y, treenode *root);

};

BinaryTree::BinaryTree(int root_key=0){
    tree_height=1;
    root = treenode::create_node(root_key);
    is_avl = false;
}

AVL::AVL(int root_key=0){
    tree_height=0;
    root = treenode::create_node(root_key);
    is_avl = true;
}


// helper/util functions that might prove useful in the near future 

void BinaryTree::transplant(treenode *u, treenode *v){
    // not used
    if (u->parent==nullptr){
        u = v;
    }
    else if (u->parent->left_child == u){
        u->parent->left_child = v;
    }
    else {
        u->parent->right_child = v;
    }
    if (v!=nullptr){
        v->parent=u->parent;
        delete u;}
}
void update_parent_pointers(treenode *temp, treenode *r);
int maxf(int x, int y);
int height(treenode *u);

#endif