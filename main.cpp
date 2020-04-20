#include <iostream>
#include "btree.cpp"

using namespace utec;


struct Trait5 {
    static constexpr int BTREE_ORDER = 5;
    using type_ = int;
};


int main() {

    BTree<Trait5> btree;
    for (int i = 1; i < 28; i++)
    {
        btree.insert(i);
    }
    
    btree.print();

    return 0;
}

