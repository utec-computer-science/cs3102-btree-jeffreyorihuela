#include <memory>
#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace utec
{

template <class Trait>
struct Node
{
    int count = 0;
    //the keyword static declares members that are NOT bound to class instances

    //the constexpr specifier declares that it is possible to evaluate
    //the value of the function or variable at compile time.

    static constexpr int BTREE_ORDER = Trait::BTREE_ORDER;
    using type_ = typename Trait::type_;
    using node_ptr = typename std::shared_ptr<Node<Trait>>;

    std::array<type_, BTREE_ORDER + 1> data;
    std::array<node_ptr, BTREE_ORDER + 2> children;

    Node() {
        std::fill(children.begin(), children.end(), nullptr);
    }

    void insert_in_node(int pos, const type_ &value)
    {
        int j = count;
        while (j > pos)
        {
            data[j] = data[j - 1];
            children[j + 1] = children[j];
            j--;
        }
        data[j] = value;
        children[j + 1] = children[j];

        count++;
    }

    bool is_overflow() { return count > BTREE_ORDER; }
};

template <class Trait>
class BTree
{
    enum states
    {
        BT_OVERFLOW,
        BT_UNDERFLOW,
        NORMAL,
    };

    static constexpr int BTREE_ORDER = Trait::BTREE_ORDER;
    using type_ = typename Trait::type_;
    typedef std::shared_ptr<Node<Trait>> node_ptr;

    node_ptr root;

public:
    BTree() {
        root = std::make_shared<Node<Trait>>();
    }

    void insert(const type_ &value)
    {
        int state = insert(root, value);
        if (state == BT_OVERFLOW)
        {
            split_root(root, value);
        }
    }

    int insert(node_ptr ptr, const type_ &value)
    {
        int pos = 0;
        while (pos < ptr->count && ptr->data[pos] < value)
        {
            pos++;
        }
        if (ptr->children[pos] != nullptr)
        {
            int state = insert(ptr->children[pos], value);
            if (state == BT_OVERFLOW)
            {
                split(ptr, pos);
            }
        }
        else
        {
            ptr->insert_in_node(pos,value);
        }
        return ptr->is_overflow() == true ? BT_OVERFLOW : NORMAL;
    }

    void split(node_ptr ptr, int pos)
    {
        constexpr int half = ceil(BTREE_ORDER / 2.0);
        node_ptr node_in_overflow = ptr->children[pos];
        node_ptr child_one = std::make_shared<Node<Trait>>();
        node_ptr child_two = std::make_shared<Node<Trait>>();
        std::copy_n(node_in_overflow->children.begin(), half + 1, child_one->children.begin());
        std::copy_n(node_in_overflow->data.begin(), half, child_one->data.begin());
        child_one->count = half;
        ptr->insert_in_node(pos, node_in_overflow->data[half]);
        std::copy_n(node_in_overflow->children.begin() + half + 1, half, child_two->children.begin());
        std::copy_n(node_in_overflow->data.begin() + half + 1, half - 1, child_two->data.begin());
        child_two->count = half - 1;
        ptr->children[pos] = child_one;
        ptr->children[pos + 1] = child_two;
    }

    void split_root(node_ptr ptr, int pos)
    {
        constexpr int half = ceil(BTREE_ORDER / 2.0);
        node_ptr node_in_overflow = ptr;
        node_ptr child_one = std::make_shared<Node<Trait>>();
        node_ptr child_two = std::make_shared<Node<Trait>>();
        std::copy_n(node_in_overflow->children.begin(), half + 1, child_one->children.begin());
        std::copy_n(node_in_overflow->data.begin(), half, child_one->data.begin());
        child_one->count = half;
        ptr->count = 0;
        ptr->insert_in_node(0, node_in_overflow->data[half]);
        std::copy_n(node_in_overflow->children.begin() + half + 1, half, child_two->children.begin());
        std::copy_n(node_in_overflow->data.begin() + half + 1, half - 1, child_two->data.begin());
        child_two->count = half - 1;
        ptr->children[0] = child_one;
        ptr->children[1] = child_two;
    }

    void print()
    {
        print(root, 0);
        std::cout << "________________________\n";
    }

    void print(node_ptr ptr, int level)
    {
        if (ptr)
        {
            int i;
            for (i = ptr->count - 1; i >= 0; i--)
            {
                print(ptr->children[i + 1], level + 1);

                for (int k = 0; k < level; k++)
                {
                    std::cout << "   ";
                }
                std::cout << ptr->data[i] << '\n';
            }
            print(ptr->children[i + 1], level + 1);
        }
    }
};

} // namespace utec
