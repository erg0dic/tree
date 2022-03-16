#include "../include/treenode.h"
#include <iostream>
#include <assert.h>
using namespace std;

class node
{
    public:   
        string val;
        node* left;
        node* right;
        node(string v="n", node* l=nullptr, node* r=nullptr) : val(v), left(l), right(r) {};
        ~node(){};
};


void all_binaries(string binary, string store[], int len){

    if (binary.size() < len) {
        cout << "1";
        store.push_back(binary);
        // cout<<binary;
        // all_binaries(binary+"0", store, len );
        // all_binaries(binary+"1", store, len );
    }
    else {
        return;
    }
}


// void allinputs(vector<string>& store){
//     // infer the zero inputs from the truth inputs
//     cout << "inside";
//     string b = "";
//     return all_binaries(b, store, 4);
// }




int main(){

    node a("0", nullptr, nullptr);
    cout << a.val;
    cout << a.val.size();
    vector<int> store;
    store.push_back(1);

    // // allinputs(store);
    // for (auto i:store){
    //     cout << i;
    // }

    return 0;
}