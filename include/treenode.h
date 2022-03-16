// #include "bintree.h"
#include <iostream>
class treenode {
    // treenode& operator=(const treenode& ) = delete; // delete the base assignment operator
    // treenode( const treenode & ) = delete;
    public:
        treenode *left_child;
        treenode *right_child;
        treenode *parent;
        int node_height;
        int key;   // TODO: template this for applications later
        treenode(int key,  treenode *lc,  treenode *rc, treenode *pc, int nh); // construct
        ~treenode() {std::cout<<"deleting treenode in progress... \n";}; // destruct
        static treenode* create_node(int value=0); // set a default value maybe? 
        treenode* left();
        treenode* right();
        int get_key();
        friend treenode* clone(const treenode *t);


};

// construct
treenode::treenode(int keyv=0, treenode *lc=nullptr,
                  treenode *rc=nullptr, treenode *pc=nullptr, int nh=0) :  
                            key(keyv), left_child(lc), right_child(rc), parent(pc), node_height(nh) {};

treenode* treenode::create_node(int value){
    return new treenode(value);
};

treenode* clone(const treenode *t){
    if (t==nullptr){
        return nullptr;
    }
    else {
        return new treenode(t->key, clone(t->left_child), clone(t->right_child));
    }
}
