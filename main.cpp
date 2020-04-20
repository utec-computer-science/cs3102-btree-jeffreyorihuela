#include <iostream>
#include "btree.cpp"

using namespace utec;


struct Trait5 {
    static constexpr int BTREE_ORDER = 5;
    using type_ = int;
};

struct Trait2 {
    static constexpr int BTREE_ORDER = 2;
    using type_ = char;
};

int main() {

    BTree<Trait5> btree;
    for (int i = 1; i < 28; i++)
    {
        btree.insert(i);
        btree.print();
    }
    

    std::cout << "other trait \n\n\n ";

    BTree<Trait2> btree_;

    for (int i = 97; i <= 122;i++)
    {
        std::cout << "insert letter " << (char)i << '\n';
        btree_.insert((char)i);

    btree_.print();
    }


    return 0;
}

