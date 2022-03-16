#include <iostream>
#include <bitset>
#include <assert.h>
#include <cmath>
#include <vector>
using namespace std;




int main(){
    bitset<16> a(15);
    cout << pow(2,5);
    cout << (int)a.to_ulong();
    cout << "\n" << a;
    assert(a[0]!=0);
    vector<string> b;
    string in;
    cout <<"write in";
    in = "0000";
    b.push_back(in);
    // cout << b[0];

    return 0;
}