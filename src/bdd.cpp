#include <vector>
#include <iostream>
#include <map>
#include <assert.h>
#include <cmath>
#include <bitset>
using namespace std;

class node
{
    public:  
        string val;
        node* left;
        node* right;
        node(string v="n", node* l=nullptr, node* r=nullptr) : val(v), left(l), right(r) {};
        ~node(){cout << "deleting "+val+" node ...";};
};

void print(vector<string>& x);
void build_binary_tree_helper(node *t, string path, int h);
void test_reduced_bdd_helper(node *t, string path, vector<string>& out);


void get_all_binary_inputs(string binary, vector<string>& store, int len){
    if (binary.size() <= len) {
        get_all_binary_inputs(binary+"0", store, len);
        get_all_binary_inputs(binary+"1", store, len);
    }
    if (binary.size()==len){
        store.push_back(binary);
    }
    return;

}

vector<string> get_all_truth_inputs(vector<string>& truth_store){
    // infer zero inputs for the binary decision tree using truth values
    map<string, string> in_out_map;
    int inp_size = truth_store[0].size();
    for (auto i: truth_store){
        in_out_map[i.substr(0, inp_size-1)] = "1"; // i[inp_size-1]= will make sure this is a 1 by default
    }

    vector<string> store;

    get_all_binary_inputs("", store, truth_store[0].size()-1);

    for (int i=0;i < store.size();i++){
        if (in_out_map.count(store[i]) != 1){
            store[i] += "0"; // boolean function evaluates to a false

        }
        else{
            store[i] += "1"; // truth boolean
        }
    }
    return store;

}

void build(node *t, vector<string>& inputs){
    // tautological case: 2^(len(input)) truths
    if (inputs.size() == pow(2, inputs[0].size())) {
        t->val = "1";
        return;
    }

    for (auto in : inputs){
        build_binary_tree_helper(t, in, 0);
    }
}

void build_binary_tree_helper(node *t, string path, int h){
    if (path.size()==1){
        t->val = path; // leaf node
        return;
    }

    else if (path[0]=='0'){
        if (t->left==nullptr){
            t->left = new node("x"+to_string(h+1));
        }
        build_binary_tree_helper(t->left, path.substr(1,path.size()), h+1);
    }
    else {
        if (t->right==nullptr){
            t->right = new node("x"+to_string(h+1));
        }
        build_binary_tree_helper(t->right, path.substr(1,path.size()), h+1);
    }

}

void delete_subtree(node *t){
    if (t!=nullptr){
        delete_subtree(t->left);
        delete_subtree(t->right);
        delete t; // Note: actually freeing the pointer from pointing to some pointed-to memory
    }
    return;
}

bool isomorphic(node *l, node *r){
    // standard method. Left-right path asymmetry means we don't consider an extra permutation
    if (l==nullptr && r ==nullptr ){
        return true;
    }
    else if (l != nullptr && r == nullptr){
        return false;
    }
    else if (l == nullptr && r != nullptr){
        return false;
    }

    else {
        return l->val == r->val && isomorphic(l->left, r->left) && isomorphic(l->right, r->right);
    }
}
void reduce(node *t){
    // two steps: 1. merge isomorphic subgraphs 2. delete nodes with identical child values
    
    // null pointer case
    if (t==nullptr){
        return;
    }
    // null child pointer case that messes with below
    if (t->left == nullptr && t->right == nullptr){
         return;
    }

    // merge the two sub trees and eliminate the identical children
    if (isomorphic(t->left, t->right)){
        node *tmp = t->right;
        node *tmp2 = t->left;
        t->val = t->right->val;
        t->left = tmp->left;
        t->right = tmp->right;
        delete_subtree(tmp);
        delete_subtree(tmp2);
    }

    reduce(t->left);
    reduce(t->right);
    
    return;


}

void test_reduced_bdd(node *t, vector<string>& inputs){
    for (auto in : inputs){
        vector<string> out;
        out.push_back(" ");
        test_reduced_bdd_helper(t, in, out);
        // cout << out[0] << " vs " << in[in.size()-1] << "\n";
        assert(in[in.size()-1]==out[0][0]);
    }
}

void test_reduced_bdd_helper(node *t, string path, vector<string>& out){

    if (t->left == nullptr && t->right == nullptr){
        out[0] = t->val;
        return;
    }

    if (path[0]=='0'){
            if (t->left != nullptr) {
            test_reduced_bdd_helper(t->left, path.substr(1,path.size()), out);
            }
        }
    
    else {
            if (t->right != nullptr){
            test_reduced_bdd_helper(t->right, path.substr(1,path.size()), out);
            }

    }

}


int maxf(int x, int y) {
    if (x>=y) {
        return x;
    }
    else {
        return y;
    }
}
 
int treeheight(node *r, int height) {
    if (r==nullptr){
        return height;
    }
    else {
        return maxf(treeheight(r->left, height+1),
                    treeheight(r->right, height+1));
        }
}

void in_order_traversal(node *t){
    if (t!=nullptr){
        in_order_traversal(t->left);
        cout << t->val <<" ";
        in_order_traversal(t->right);
    }
    return;
}


void print(vector<string>& x){
    cout << "{ ";
    for (auto i:x){
        cout <<  i << " ";
    }
    cout <<  "} \n";
}

void prettyprint(node *root) {
    int h = treeheight(root, 0);
    cout << "tree height is " << h;
    node* root_copy=root;
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
        gap_string += "  ";
    }
    // increase the h level
    while (h_counter <= h) {
        int partial_max_pathcount = pow(2,h_counter);
 
        // find all the paths at this h level of the tree
        while (pathcounter<partial_max_pathcount){
            auto pathbinary=bitset<16>(pathcounter);  // ps[16-h:] will be the relevent bits
            root_copy=root;
            counter = 1;
            // find a leaf node
            bool null_val = false;
            while (counter < h_counter) {
                // 0 is a left traversal
                if (pathbinary.to_string()[16-h_counter+counter]=='0'){
                   
                    if (root_copy->left !=nullptr) {
                        root_copy=root_copy->left;
                    }
                    else {
                        null_val=true;
                    }
 
                }
                else {
                    if (root_copy->right != nullptr) {
                        root_copy=root_copy->right;
                    }
                    else {
                        null_val=true;
                    }
                }
                ++counter;
            }
        std::string print_val = "n"; // default null print
        if (!null_val) {
            print_val = root_copy->val;
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

int main(){
    node * a = new node("x0");
    // cout << a->left;
    // delete a;
    vector<string> truth_store;
    truth_store.push_back("0001");
    truth_store.push_back("0111");
    truth_store.push_back("1111");
    truth_store.push_back("1101");

    vector<string> store;
    get_all_binary_inputs("", store, 3);
    print(store);
    auto inps = get_all_truth_inputs(truth_store);
    print(inps);
    string d = "01001";
    cout << d.substr(1,d.size());
    build(a, inps);
    cout << "\n";
    // in_order_traversal(a);
    prettyprint(a);
    reduce(a);
    // in_order_traversal(a);
    // cout << a->val;
    // cout << "\n";
    prettyprint(a);
    cout << "\n";
    // vector<string> out;
    // out.push_back(" ");
    // test_reduced_bdd_helper(a, inps[0].substr(0, inps[0].size()), out);
    // cout<< out[0];

    test_reduced_bdd(a, inps);

    // in_order_traversal(a);
    return 0;
}