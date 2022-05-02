#include "../include/bintree.h"
#include <iostream>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <string>
#include <array>

// bool AVL::is_avl = true;

void BinaryTree::in_order_traversal(treenode *noderef){
    if (noderef != nullptr) {
        // std::cout<< noderef->key;
        // if (noderef->key == 15) std::cout << noderef->left_child->key, assert(false);
        // assert(noderef->key==-7);
        in_order_traversal(noderef->left_child);
        std::cout << noderef->key << " "; 
        in_order_traversal(noderef->right_child);
    }; 
    return;
}

treenode* BinaryTree::search(treenode *x, int keyv){
    if (x==nullptr || x->key == keyv) {
        return x;
    }
    else if (keyv < x->key){
        return search(x->left_child, keyv);
    }
    else {
        return search(x->right_child, keyv);
    }

}

treenode* BinaryTree::min(treenode *x){
    if (x->left_child != nullptr) {
        x=min(x->left_child);
    }
    return x; 
}

treenode* BinaryTree::max(treenode *x){
    if (x->right_child != nullptr) {
        x=max(x->right_child);
    }
    return x; 
}

// treenode* BinaryTree::insert(treenode *r, treenode *n){
//     // base case if nothing is passed. Not actually needed. So this is conventionally the root node
//     // assert(is_avl==true);
//     if (r==nullptr) {
//         r=n;
//         return r;
//     }

//     if (n->key <= r->key) {
//             if (r->left_child==nullptr) {
//                 n->parent = r;
//             }
//             r = insert(r->left_child, n);
//             // n->parent = r;
            

//         }
//     else {
//                 if (r->right_child==nullptr) {
//                         n->parent = r;
//                     }
                
//                 r = insert(r->right_child, n);
//                 // n->parent = r;
                

//     }
//     return r;

treenode* BinaryTree::insert(treenode *r, treenode *n){
    // base case if nothing is passed. Not actually needed. So this is conventionally the root node
    // assert(is_avl==true);
    while (true){
           
        if (n->key <= r->key){
            if (r->left_child==nullptr){
                r->left_child = n;
                n->parent = r;
                break;
            }
            else {
                r=r->left_child;
            }
        }
        else {
            
            if (r->right_child==nullptr){
                r->right_child = n;
                n->parent = r;
                break;
            }
            else {
                r=r->right_child;
            }
        }
    }
    
    return n;


    // // base case
    // if (new_node != nullptr){
    // //     std::cout << new_node->key << "\n";
    // //     treenode *tmp = new_node;
    // //     AVL::update_node_height(new_node);
    // //     AVL::fixtree(new_node);

    // return new_node;
    // }

}

int BinaryTree::treesize(treenode *r) {
    // this is also a leaf node class for merged nodes
    if (r==nullptr ){
        return 0;
    }
    
    return 1+treesize(r->left_child)+treesize(r->right_child);
}

int maxf(int x, int y) {
    if (x>=y) {
        return x;
    }
    else {
        return y;
    }
};

int BinaryTree::treeheight(treenode *r, int height) {
    if (r==nullptr){
        return height;
    }
    else { 
        return maxf(treeheight(r->left_child, height+1), 
                    treeheight(r->right_child, height+1));}
    
}

treenode* BinaryTree::deletetree(treenode *r){
    /*
    internal method
    Note: Not a good OOP practice to use delete this. 
    Changed this to the current version that consumes a treenode 
    pointer arg.  
    */
    if (r==nullptr){
        return nullptr;
    }
    else {
        deletetree(r->left_child);
        deletetree(r->right_child);
        delete r;
    }
    return nullptr;

}

void AVL::left_rotate(treenode *x, treenode *root){
    if (x==nullptr){
        return;
    }
    // turn y's left subtree into x's right subtree
    treenode *y = x->right_child;
    x->right_child = y->left_child;
    if (y->left_child != nullptr){
        y->left_child->parent = x;
    }
    y->parent = x->parent;
    // root is now y, this clause is only possible for the root by definition
    if (x->parent == nullptr){
        root=y;
    }
    else if (x == x->parent->left_child){
        x->parent->left_child = y;
    }
    else {
        x->parent->right_child = y;
    }
    y->left_child = x;
    x->parent = y;
    update_node_height(y);
    update_node_height(x);
}

void AVL::right_rotate(treenode *y, treenode *root){
    if (y==nullptr){
        return;
    }
    // turn x's right subtree into y's left subtree
    treenode *x = y->left_child;
    y->left_child = x->right_child;
    // set y parent
    if (x->right_child != nullptr){
        x->right_child->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr){
        root=x; // root is now x
    }
    else if (y == y->parent->left_child){
        y->parent->left_child = x;
    }
    else {
        y->parent->right_child = x;
    }
    x->right_child = y;
    y->parent = x;
    update_node_height(x);
    update_node_height(y);
}

treenode* BinaryTree::clone_subtree(const treenode *t){
    if (root != t){
        treenode* temp =  clone(t);
        deletetree(root);
        root = temp;
    }
    return root;
}

void update_parent_pointers(treenode *temp, treenode *r){
    // base root does not have a parent pointer
    if (temp->parent==nullptr){
        return;
    }
    // changing the og node's parent pointers
    if (temp->key < temp->parent->key ) {
        temp->parent->left_child = r;
        
    }
    else {
        temp->parent->right_child = r;
    }
    // changing the new node's (og node's child) parent pointer 
    if (r != nullptr){
        r->parent = temp->parent;
    }
}

// tree reduction: following the generic delete the node with key==val method
treenode* BinaryTree::delete_value(treenode *r, int val){
    if (r==nullptr){
        // throw std::invalid_argument("key not found! this is an internal method so recheck logic...");
        return nullptr; 
    }
    // search left
    else if (val < r->key) {
        delete_value(r->left_child, val);
    }
    // search right
    else if (val > r->key) {
        delete_value(r->right_child, val);
    }
    // found the value 2 cases
    // case a: root has two children: choose the successor (min right sub tree node) as the new root 
    else if (r->left_child != nullptr && r->right_child != nullptr) {
            // successor is the new root
            r->key = min(r->right_child)->key;
            // now remove the successor
            delete_value(r->right_child, r->key);
        }
    else {
        // root has one child so appropriately set the root to that child and delete it
        treenode *temp = r;
        // if (r->key==-8){
        // std::cout << "\n inside the tree extract min " << r << " " << temp << " " << temp->left_child << " " << temp->right_child;
        //     // assert(false);
        //     std::cout << "\n" << " parent key is: " << r->parent->right_child->key << "\n";
        //     assert(r->parent->key == r->key);
        //     }
        if (r->left_child == nullptr && r->right_child != nullptr) {
            r = r->right_child;
            update_parent_pointers(temp, r);
            
        }
        else if (r->left_child != nullptr && r->right_child == nullptr) {
 
            r = r->left_child;
            update_parent_pointers(temp, r);
        }
        // update the parent pointers for the leaf node case!
        else {
            update_parent_pointers(temp, nullptr);
        }
        // treenode *temp_parent = temp->parent;
        delete temp;
        return nullptr;
    }

}


void BinaryTree::prettyprint() {
    int h = treeheight(root, 1);
    treenode* root_copy=root;
    // print tree in O(exp(n)) time by exhaustively enumerating all O(exp(n)) paths
    if (h>16){
        assert(h<16);
        std::cout << "Can't handle trees with heights bigger than 16";
        }

    int pathcounter=1;
    int max_pathcount = pow(2, h);
    int counter; 
    int h_counter;
    h_counter=0;
    std::string gap_string = "";
    for (int i=0;i<max_pathcount;i++){
        gap_string += " ";
    }
    // increase the h level
    while (h_counter <= h) {
        int partial_max_pathcount = pow(2,h_counter);

        // find all the paths at this h level of the tree
        while (pathcounter<partial_max_pathcount){
            auto pathbinary=std::bitset<16>(pathcounter);  // ps[16-h:] will be the relevent bits
            root_copy=root;
            counter = 1;
            // find a leaf node
            bool null_val = false;
            while (counter < h_counter) {
                // 0 is a left traversal
                if (pathbinary.to_string()[16-h_counter+counter]=='0'){
                    
                    if (root_copy->left_child !=nullptr) {
                        root_copy=root_copy->left_child;
                    }
                    else {
                        null_val=true;
                    }

                }
                else {
                    if (root_copy->right_child != nullptr) {
                        root_copy=root_copy->right_child;
                    }
                    else {
                        null_val=true;
                    }
                }
                ++counter;
            }
        std::string print_val = "n"; // default null print
        if (!null_val) {
            print_val = std::to_string(root_copy->key);
            if (is_avl){ // debug the avl e.g. for node_height
                print_val = std::to_string(root_copy->key);
                }
            }

        // fractal print... every single element in a line            
        int gap_length_to_print = gap_string.size()/(partial_max_pathcount);

        for (int j = 0; j<gap_length_to_print-print_val.size();j++){
            std::cout << " ";
        }

        std::cout << print_val;
        for (int j = 0; j<gap_length_to_print;j++){
            std::cout << " ";
        }
        ++pathcounter;

        }

    ++h_counter;
    std::cout<<"\n";
    }

}


int height(treenode *u){
    if (u==nullptr) {
        return -1;
    }
    else {
        return u->node_height;
    }
}

void AVL::update_node_height(treenode *u){
    
    u->node_height = 1+maxf((height(u->left_child)), height(u->right_child));

}

/* 4 cases for a misbalance (violation of the AVL property):
Assume Z is the higher left/right successor of X (root)
and the inductive hypothesis.
    1. Z is a `right_child` of X and BF(Z) <= 0 (right right )
    2. Z is a `right_child` of X and BF(Z) >= 0 (right left)
    3. Z is a `left_child` of X and BF(Z) >= 0 (left left)
    4. Z is a `left_child` of X and BF(Z) <= 0  (left right)

Correct: 
    1. by a `left_rotate` of X
    2. by `left_rotate` of Z's left child followed by a `right_rotate` of X
    3. by a `right_rotate` of X 
    4.  by `right_rotate` of Z's right child followed by  `left_rotate` of X
*/
void AVL::fixtree(treenode *u, treenode *root){
    // remember to update node heights before calling this
    while (u!=nullptr) {
    update_node_height(u);
    if (height(u->left_child)>= 2 + height(u->right_child)){
        // if(u->left_child != nullptr) { // for safety
            if (height(u->left_child->left_child) < height(u->left_child->right_child)){
                left_rotate(u->left_child, root); // i.e. make u.l.l's height bigger  case 4
            }
        // }
        right_rotate(u, root); // case 3
       
    } 
    // symmetric to above
    else if (height(u->right_child)>= 2+height(u->left_child)){
        // if(u->right_child != nullptr){          
            if (height(u->right_child->right_child) < height(u->right_child->left_child)){
                    right_rotate(u->right_child, root); // i.e. make u.r.r's height bigger case 2
            }
        // }
        left_rotate(u, root); // case 1
       
        }
    u=u->parent;
    }
    return;
}


// AVL property: invariant if balancing factor (BF) in {-1,0,1}
int AVL::BF(treenode *r){
    int diff = 0; // 0 can also be default for leaf nodesS
    if (r->left_child != nullptr && r->right_child != nullptr){
        diff =  height(r->left_child)-height(r->right_child);
    }
    return diff;
}

void AVL::rebalance(treenode *r, treenode *root){
    if (is_avl) {
    fixtree(r, root);
    }
}

treenode* AVL::insert_new(int val){
    root=get_root();
    auto new_node = treenode::create_node(val);
    insert(root, new_node);
    // rebalance(new_node, root);
    return new_node;
}

void AVL::delete_val(treenode *root, int val){
    treenode* node = search(get_root(), val);
    treenode* deleted_node_parent;
    if (node !=nullptr) {treenode* deleted_node_parent = node->parent;}
    else {
        deleted_node_parent=nullptr;
    }
    // std::cout<<"parent is: "<<deleted_node_parent->key<<"\n";
    delete_value(get_root(), val);
    // if (deleted_node_parent != nullptr){
    // rebalance(deleted_node_parent, get_root());
    // }
}

treenode* BinaryTree::find_min() {
    treenode *min_node= min(get_root());
    return min_node;
}

treenode* AVL::extract_min(){
    treenode* min_node = find_min();
    treenode* copy_min_node = treenode::create_node(min_node->key);
    copy_min_node->symbol = min_node->symbol;
    delete_val(get_root(), min_node->key);
    std::cout<<"here"<<copy_min_node->key;
    return copy_min_node;
}

void huffman_traversal(treenode *ht, std::string code){
    if (ht != nullptr){
        huffman_traversal(ht->ht_left, code+'0');
        std::cout<<code<< " for symbol" << " "<< ht<<"\n";
        huffman_traversal(ht->ht_right, code+'1');
        // add to some vector or hashmap reference.... if the libraries worked!!!
    }
    return;
}

void make_huffman_tree(std::array<char, 6>& syms, std::array<int, 6>& freqs, int s){
    AVL priority_queue;
    treenode *root = priority_queue.get_root();
    root->key = freqs[0];
    root->symbol = syms[0];
    int array_size = s; // could have replaced with vector.size() if vector was working!!!
    // 1. start off with all the symbols as leaves 
    for (int i=1;i<array_size-1;i++){
        auto nn = priority_queue.insert_new(freqs[i]);
        nn->symbol=syms[i];
    }
    priority_queue.in_order_traversal(priority_queue.get_root());
    // 2. build the huffman tree
    int i =0;
    std::cout<<"\n"<<"size is "<< priority_queue.treesize(priority_queue.get_root());
    int size=0;
    while (true) {
        std::cout<<"iteration "<<i << "\n"; 
        auto min1 = priority_queue.find_min();
        auto k1 = min1->key; 
        auto v1 = min1->symbol;
        priority_queue.delete_val(priority_queue.get_root(), k1);
        // priority_queue.in_order_traversal(priority_queue.get_root()); 
        auto min2 = priority_queue.find_min();
        auto k2 = min2->key; 
        auto v2 = min2->symbol;
        priority_queue.delete_val(priority_queue.get_root(), k2);

        std::cout<<"min1, min2 "<<k1 << " "<< k2 << "\n";
        priority_queue.in_order_traversal(priority_queue.get_root()); 

        int merged_internal_node_val = k1+k2;
        treenode* merged_node = priority_queue.insert_new(merged_internal_node_val);
        merged_node->ht_left = treenode::create_node(k1);
        merged_node->ht_left->symbol=v1;
        merged_node->ht_right= treenode::create_node(k2);
        merged_node->ht_left->symbol=v2;
        size = priority_queue.treesize(priority_queue.get_root());
        std::cout<<"\n size is "<<size;
        // if(i==3)assert(false);
        if (size==1){break;}
        
        i+=1;

    }
    std::cout<<"done!";
    // 3. traverse the huffman tree and build the encoding
    huffman_traversal(priority_queue.get_root(), "");

    // 4. store it in a file and then use it for encoding-decoding files...
}


int main(){
    /*
    for debugging... 
    nothing to see here 
    */
    AVL a;
    AVL bsss;
    std::cout<<a.max(a.get_root())->key << "\n";
    int arr[] = {-6, 4, 5, 12, -7, 19, -9, -2, 1, 5, 9, 12};
    for (int i=0; i<std::size(arr);i++) {
        auto nn =a.insert_new(arr[i]);
        std::cout << nn->key << "\n";
        // a.rebalance(a.find_min(), a.get_root());
    }
    a.in_order_traversal(a.get_root());
    std::cout << "\n";
    // a.is_avl = false; // just to get the heights
    a.prettyprint();
    // assert(false);
    assert(a.get_root()!=nullptr);
    // a.in_order_traversal(a.get_root());
    // a.delete_value(a.get_root(), 0);
    a.in_order_traversal(a.get_root());
    // assert (a.get_root()->key==5);

    // std::cout << "\n min val found: " << a.find_min()->key;
    std::cout<<"\n tree height: "<<a.treeheight(a.get_root(), 0);
    std::cout<<"\n found key: "<<a.search(a.get_root(), 5)->key;
    // what has lived must at some point die
    for (int i=0; i<std::size(arr);i++) {
        // if (arr[i]==0) std::cout << "\n entering -7 now.... \n parent is: " << a.search(a.get_root(), 0)->key, assert(false);
        // std::cout<<"\n new root: "<<a.get_root()->key <<" ";
        // if (arr[i]==-7) assert(false);
        std::cout<<"\n new root, entering: "<<a.get_root()->key <<" " << arr[i]<< " ";
        // a.in_order_traversal(a.get_root());
        a.delete_val(a.find_min(), arr[i]);
        std::cout<<"\nentering successful\n";
        a.prettyprint();
        // a.in_order_traversal(a.get_root());
        std::cout << " "<< arr[i] <<" ";
    }
    // a.in_order_traversal(a.get_root());
    a.delete_value(a.get_root(), a.get_root()->key);
    // a.in_order_traversal(a.get_root());
    std::cout << "\n success!\n";
    // assert(a.treesize(a.get_root())==0);
    // std::cout<<"aaa \n" << std::endl << "aaa";
    // a.prettyprint(a.get_root(), 0);

    // std::cout<<"testing the huffman tree "<<"\n";
    std::array<int, 6> freqs = {15, 2, 5, 8, 12, 14};
    std::array<char, 6> syms = {'A', 'B', 'C', 'D', 'E', 'F'};
    make_huffman_tree(syms, freqs, 6);


    return 0;
}






