// #include "treenode.cpp"
#include <iostream>
using namespace std;

struct test_case {
    int val;
    int a;
    int d;
};

class test {
    int a;
    test_case* obj;
    public: 
        test(int aval=0, test_case *obj_val=nullptr) {
            a = aval;
            if (obj_val==nullptr){
                obj =  new test_case{10000, 25, 100};

            }
            else {
            obj = obj_val;
            }
        };
        test_case* do_something(test_case &aref) {
            aref.val = 15;
            return &aref;
        };
        int get_a() const {return a;}
        int get_obj_val() const {return obj->val;};
        test_case* get_obj() const {return obj;};

        friend test operator+(const test& t2, const test& t1){
            test temp;
            temp.a = t1.a + t2.a;
            test_case* temp_obj = t2.get_obj();
            temp.obj->val = t1.obj->val + t2.obj->val;
            temp.obj->a = t1.obj->a + t2.obj->a;
            (*temp.obj).d = (*t1.obj).d+(*t2.obj).d;
            
            return temp;
        }


};

int main(){

    test_case a;
    a.val=25;
    test something_new(0, &a), something_new2(1, &a);
    
    cout << something_new.get_obj_val() << "\n";
    cout << "functional";
    test another = something_new + something_new2;
    cout << "\n " << another.get_obj_val();

    return 0;
}