#include "..\include\treenode.h"
#include <iostream>
#include <assert.h>

// return the left child
treenode* treenode::left(){
    return left_child;
};

treenode* treenode::right(){
    return right_child;
};

int treenode::get_key(){
    return key;
};

int main() {
    // test...
    treenode a(5), b(6), c(7);
    a.left_child = &b;
    a.right_child = &b;

    std::cout << a.get_key();
    // a.deletetreenode(&a);
    // std::cout<< a.right_child;
    // assert (a.right_child == nullptr);
    // assert (a.left_child == nullptr);
    // std::cout<< "\n" << a.get_key();
    return 0;
}